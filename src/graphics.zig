const std = @import("std");
const memory = @import("memory.zig");
const Memory = memory.Memory;
const TileDataFlag = memory.TileDataFlag;
const Palette = memory.Palette;

pub const Screen = [144][160]u8;

const Vec2 = @Vector(2, i16);

fn renderTile(self: *Memory, tileIdx: u8, offset: Vec2, tileData: TileDataFlag, palette: Palette) u2 {
    const tile = self.VRAM.Data[if (tileData == .x80) tileIdx else ((tileIdx ^ 0x80) + 0x80)];
    const tileRow = tile[@intCast(offset[1])];
    const tileCol: u4 = @intCast(offset[0]);
    const rawColor = ((tileRow >> (7 - tileCol)) & 1) | (((tileRow >> (15 - tileCol)) & 1) << 1);
    return palette.get(rawColor);
}

fn renderTileMap(self: *Memory, pos: Vec2, tileMap: u1, tileData: TileDataFlag) u2 {
    const tilePos = pos >> @as(Vec2, @splat(3));
    const tileOffset = pos & @as(Vec2, @splat(0b111));
    const tileIdx = self.VRAM.Map[tileMap][@intCast(tilePos[1])][@intCast(tilePos[0])];
    return renderTile(self, tileIdx, tileOffset, tileData, self.IOPorts.BGP);
}

fn renderSprite(self: *Memory, spriteTile: u8, offset: Vec2, palette: [4]u2) u2 {
    return renderTile(self, spriteTile, offset, 1, palette);
}

fn spriteCmp(self: *Memory, a: u8, b: u8) bool {
    const spriteA = self.OAM[a];
    const spriteB = self.OAM[b];
    return if (spriteA.X == spriteB.X) a > b else spriteA.X > spriteB.X;
}

// zig fmt: off
pub fn drawLine(self: *Memory, screen: *Screen) void {
    const scroll = Vec2{ self.IOPorts.SCX, self.IOPorts.SCY };
    const wndPos = Vec2{ self.IOPorts.WX, self.IOPorts.WY };
    const tallSprites = self.IOPorts.LCDC.SpriteSize == .S8x16;
    var lineSprites: [40]u8 = undefined;
    for (&lineSprites, 0..) |*s, i| {
        s.* = @intCast(40 - 1 - i);
    }
    std.sort.heap(u8, &lineSprites, self, spriteCmp);
    const y = self.IOPorts.LY;
    for (&screen[y], 0..) |*pixel, x| {
        var color: u2 = 0;
        const screenPos = Vec2{ @intCast(x), @intCast(y) };
        if (self.IOPorts.LCDC.BGEnable) {
            color = renderTileMap(self,
                screenPos +% scroll,
                self.IOPorts.LCDC.BGTileMap,
                self.IOPorts.LCDC.BGWindowTileData
            );
        }
        if (self.IOPorts.LCDC.WindowEnable
            and wndPos[0] <= 166
            and wndPos[1] <= 143
            and screenPos[0] >= wndPos[0]
            and screenPos[1] >= wndPos[1]
        ) {
            color = renderTileMap(self,
                screenPos -% wndPos,
                self.IOPorts.LCDC.WindowTileMap,
                self.IOPorts.LCDC.BGWindowTileData
            );
        }
        for (lineSprites) |idx| {
            const sprite = self.OAM[idx];
            const spritePos = Vec2{ sprite.X, sprite.Y };
            var spriteRelPos = screenPos - spritePos - Vec2{ 8, 16 };
            const palette = switch (sprite.Flags.Palette) {
                .OBJ0PAL => self.IOPorts.OBP0,
                .OBJ1PAL => self.IOPorts.OBP1,
            };
            if ((sprite.Flags.Priority == 0 or color == 0)
                and spriteRelPos[0] >= 0
                and spriteRelPos[0] < 8
                and spriteRelPos[1] >= 0
            ) {
                if (sprite.Flags.XFlip) {
                    spriteRelPos[0] ^= 0b111;
                }
                if (sprite.Flags.YFlip) {
                    spriteRelPos[1] ^= if (tallSprites) 0b1111 else 0b111;
                }
                const spriteColor = if (spriteRelPos[1] < 8)
                    renderTile(self,
                        if (tallSprites) sprite.Tile & 0xFE else sprite.Tile,
                        spriteRelPos,
                        .x80,
                        palette
                    )
                else if (tallSprites and spriteRelPos[1] < 16)
                    renderTile(self,
                        sprite.Tile | 1,
                        spriteRelPos - Vec2{ 0, 8 },
                        .x80,
                        palette
                    )
                else 0;
                if (spriteColor != 0) {
                    color = spriteColor;
                }
            }
        }
        pixel.* = color;
    }
}