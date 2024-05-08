pub usingnamespace @cImport({
    @cDefine("GLAD_GL_IMPLEMENTATION", {});
    @cDefine("GLAD_API_CALL", "");
    @cInclude("glfw/deps/glad/gl.h");
    @cInclude("GLFW/glfw3.h");
    @cInclude("soundio/soundio.h");
});
