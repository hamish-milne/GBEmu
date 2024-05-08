const std = @import("std");
const memory = @import("memory.zig");
const Memory = memory.Memory;
const TileDataFlag = memory.TileDataFlag;
const Palette = memory.Palette;

pub const Width = 160;
pub const Height = 144;

pub const Screen = [Height][Width]u8;

const Vec2 = @Vector(2, u8);

fn renderTile(self: *Memory, tileIdx: u8, offset: Vec2, tileData: TileDataFlag, palette: u8) u2 {
    const tileIdx_: u16 = tileIdx;
    const tile = self.VRAM.Data[if (tileData == .x80) tileIdx_ else ((tileIdx_ ^ 0x80) + 0x80)];
    const tileRow = tile[@intCast(offset[1])];
    const tileCol: u4 = @intCast(offset[0]);
    const rawColor = ((tileRow >> (7 - tileCol)) & 1) | (((tileRow >> (15 - tileCol)) & 1) << 1);
    return @truncate(palette >> @intCast(rawColor * 2));
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
    for (&screen[screen.len - y - 1], 0..) |*pixel, x| {
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
            var spriteX = @as(i16, screenPos[0]) - spritePos[0] - 8;
            var spriteY = @as(i16, screenPos[1]) - spritePos[1] - 16;
            const palette = switch (sprite.Flags.Palette) {
                .OBJ0PAL => self.IOPorts.OBP0,
                .OBJ1PAL => self.IOPorts.OBP1,
            };
            if ((sprite.Flags.Priority == 0 or color == 0)
                and spriteX >= 0
                and spriteX < 8
                and spriteY >= 0
            ) {
                if (sprite.Flags.XFlip) {
                    spriteX ^= 0b111;
                }
                if (sprite.Flags.YFlip) {
                    spriteY ^= if (tallSprites) 0b1111 else 0b111;
                }
                const spriteColor = if (spriteY < 8)
                    renderTile(self,
                        if (tallSprites) sprite.Tile & 0xFE else sprite.Tile,
                        Vec2 { @intCast(spriteX), @intCast(spriteY) },
                        .x80,
                        palette
                    )
                else if (tallSprites and spriteY < 16)
                    renderTile(self,
                        sprite.Tile | 1,
                        Vec2 { @intCast(spriteX), @intCast(spriteY - 8) },
                        .x80,
                        palette
                    )
                else 0;
                if (spriteColor != 0) {
                    color = spriteColor;
                }
            }
        }
        pixel.* = @as(u8, color);
    }
}