/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <glad/gl.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif




static GLADloadfunc glad_global_on_demand_gl_loader_func = NULL;

void gladSetGLOnDemandLoader(GLADloadfunc loader) {
    glad_global_on_demand_gl_loader_func = loader;
}

static GLADapiproc glad_gl_on_demand_loader(const char *name) {
    GLADapiproc result = NULL;
    if (result == NULL && glad_global_on_demand_gl_loader_func != NULL) {
        result = glad_global_on_demand_gl_loader_func(name);
    }
    /* this provokes a segmentation fault if there was no loader or no loader returned something useful */
    return result;
}


static void GLAD_API_PTR glad_on_demand_impl_glAccum(GLenum op, GLfloat value) {
    glad_glAccum = (PFNGLACCUMPROC) glad_gl_on_demand_loader("glAccum");
    glad_glAccum(op, value);
}
PFNGLACCUMPROC glad_glAccum = glad_on_demand_impl_glAccum;
static void GLAD_API_PTR glad_on_demand_impl_glActiveTexture(GLenum texture) {
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) glad_gl_on_demand_loader("glActiveTexture");
    glad_glActiveTexture(texture);
}
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = glad_on_demand_impl_glActiveTexture;
static void GLAD_API_PTR glad_on_demand_impl_glAlphaFunc(GLenum func, GLfloat ref) {
    glad_glAlphaFunc = (PFNGLALPHAFUNCPROC) glad_gl_on_demand_loader("glAlphaFunc");
    glad_glAlphaFunc(func, ref);
}
PFNGLALPHAFUNCPROC glad_glAlphaFunc = glad_on_demand_impl_glAlphaFunc;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glAreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences) {
    glad_glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC) glad_gl_on_demand_loader("glAreTexturesResident");
    return glad_glAreTexturesResident(n, textures, residences);
}
PFNGLARETEXTURESRESIDENTPROC glad_glAreTexturesResident = glad_on_demand_impl_glAreTexturesResident;
static void GLAD_API_PTR glad_on_demand_impl_glArrayElement(GLint i) {
    glad_glArrayElement = (PFNGLARRAYELEMENTPROC) glad_gl_on_demand_loader("glArrayElement");
    glad_glArrayElement(i);
}
PFNGLARRAYELEMENTPROC glad_glArrayElement = glad_on_demand_impl_glArrayElement;
static void GLAD_API_PTR glad_on_demand_impl_glAttachShader(GLuint program, GLuint shader) {
    glad_glAttachShader = (PFNGLATTACHSHADERPROC) glad_gl_on_demand_loader("glAttachShader");
    glad_glAttachShader(program, shader);
}
PFNGLATTACHSHADERPROC glad_glAttachShader = glad_on_demand_impl_glAttachShader;
static void GLAD_API_PTR glad_on_demand_impl_glBegin(GLenum mode) {
    glad_glBegin = (PFNGLBEGINPROC) glad_gl_on_demand_loader("glBegin");
    glad_glBegin(mode);
}
PFNGLBEGINPROC glad_glBegin = glad_on_demand_impl_glBegin;
static void GLAD_API_PTR glad_on_demand_impl_glBeginConditionalRender(GLuint id, GLenum mode) {
    glad_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) glad_gl_on_demand_loader("glBeginConditionalRender");
    glad_glBeginConditionalRender(id, mode);
}
PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender = glad_on_demand_impl_glBeginConditionalRender;
static void GLAD_API_PTR glad_on_demand_impl_glBeginQuery(GLenum target, GLuint id) {
    glad_glBeginQuery = (PFNGLBEGINQUERYPROC) glad_gl_on_demand_loader("glBeginQuery");
    glad_glBeginQuery(target, id);
}
PFNGLBEGINQUERYPROC glad_glBeginQuery = glad_on_demand_impl_glBeginQuery;
static void GLAD_API_PTR glad_on_demand_impl_glBeginTransformFeedback(GLenum primitiveMode) {
    glad_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) glad_gl_on_demand_loader("glBeginTransformFeedback");
    glad_glBeginTransformFeedback(primitiveMode);
}
PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback = glad_on_demand_impl_glBeginTransformFeedback;
static void GLAD_API_PTR glad_on_demand_impl_glBindAttribLocation(GLuint program, GLuint index, const GLchar * name) {
    glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) glad_gl_on_demand_loader("glBindAttribLocation");
    glad_glBindAttribLocation(program, index, name);
}
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = glad_on_demand_impl_glBindAttribLocation;
static void GLAD_API_PTR glad_on_demand_impl_glBindBuffer(GLenum target, GLuint buffer) {
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC) glad_gl_on_demand_loader("glBindBuffer");
    glad_glBindBuffer(target, buffer);
}
PFNGLBINDBUFFERPROC glad_glBindBuffer = glad_on_demand_impl_glBindBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) glad_gl_on_demand_loader("glBindBufferBase");
    glad_glBindBufferBase(target, index, buffer);
}
PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase = glad_on_demand_impl_glBindBufferBase;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) glad_gl_on_demand_loader("glBindBufferRange");
    glad_glBindBufferRange(target, index, buffer, offset, size);
}
PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange = glad_on_demand_impl_glBindBufferRange;
static void GLAD_API_PTR glad_on_demand_impl_glBindFragDataLocation(GLuint program, GLuint color, const GLchar * name) {
    glad_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) glad_gl_on_demand_loader("glBindFragDataLocation");
    glad_glBindFragDataLocation(program, color, name);
}
PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation = glad_on_demand_impl_glBindFragDataLocation;
static void GLAD_API_PTR glad_on_demand_impl_glBindFramebuffer(GLenum target, GLuint framebuffer) {
    glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) glad_gl_on_demand_loader("glBindFramebuffer");
    glad_glBindFramebuffer(target, framebuffer);
}
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer = glad_on_demand_impl_glBindFramebuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) glad_gl_on_demand_loader("glBindRenderbuffer");
    glad_glBindRenderbuffer(target, renderbuffer);
}
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer = glad_on_demand_impl_glBindRenderbuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindTexture(GLenum target, GLuint texture) {
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC) glad_gl_on_demand_loader("glBindTexture");
    glad_glBindTexture(target, texture);
}
PFNGLBINDTEXTUREPROC glad_glBindTexture = glad_on_demand_impl_glBindTexture;
static void GLAD_API_PTR glad_on_demand_impl_glBindVertexArray(GLuint array) {
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glad_gl_on_demand_loader("glBindVertexArray");
    glad_glBindVertexArray(array);
}
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = glad_on_demand_impl_glBindVertexArray;
static void GLAD_API_PTR glad_on_demand_impl_glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap) {
    glad_glBitmap = (PFNGLBITMAPPROC) glad_gl_on_demand_loader("glBitmap");
    glad_glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}
PFNGLBITMAPPROC glad_glBitmap = glad_on_demand_impl_glBitmap;
static void GLAD_API_PTR glad_on_demand_impl_glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glBlendColor = (PFNGLBLENDCOLORPROC) glad_gl_on_demand_loader("glBlendColor");
    glad_glBlendColor(red, green, blue, alpha);
}
PFNGLBLENDCOLORPROC glad_glBlendColor = glad_on_demand_impl_glBlendColor;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquation(GLenum mode) {
    glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC) glad_gl_on_demand_loader("glBlendEquation");
    glad_glBlendEquation(mode);
}
PFNGLBLENDEQUATIONPROC glad_glBlendEquation = glad_on_demand_impl_glBlendEquation;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) glad_gl_on_demand_loader("glBlendEquationSeparate");
    glad_glBlendEquationSeparate(modeRGB, modeAlpha);
}
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate = glad_on_demand_impl_glBlendEquationSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFunc(GLenum sfactor, GLenum dfactor) {
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC) glad_gl_on_demand_loader("glBlendFunc");
    glad_glBlendFunc(sfactor, dfactor);
}
PFNGLBLENDFUNCPROC glad_glBlendFunc = glad_on_demand_impl_glBlendFunc;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) glad_gl_on_demand_loader("glBlendFuncSeparate");
    glad_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = glad_on_demand_impl_glBlendFuncSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) glad_gl_on_demand_loader("glBlitFramebuffer");
    glad_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer = glad_on_demand_impl_glBlitFramebuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage) {
    glad_glBufferData = (PFNGLBUFFERDATAPROC) glad_gl_on_demand_loader("glBufferData");
    glad_glBufferData(target, size, data, usage);
}
PFNGLBUFFERDATAPROC glad_glBufferData = glad_on_demand_impl_glBufferData;
static void GLAD_API_PTR glad_on_demand_impl_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data) {
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC) glad_gl_on_demand_loader("glBufferSubData");
    glad_glBufferSubData(target, offset, size, data);
}
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = glad_on_demand_impl_glBufferSubData;
static void GLAD_API_PTR glad_on_demand_impl_glCallList(GLuint list) {
    glad_glCallList = (PFNGLCALLLISTPROC) glad_gl_on_demand_loader("glCallList");
    glad_glCallList(list);
}
PFNGLCALLLISTPROC glad_glCallList = glad_on_demand_impl_glCallList;
static void GLAD_API_PTR glad_on_demand_impl_glCallLists(GLsizei n, GLenum type, const void * lists) {
    glad_glCallLists = (PFNGLCALLLISTSPROC) glad_gl_on_demand_loader("glCallLists");
    glad_glCallLists(n, type, lists);
}
PFNGLCALLLISTSPROC glad_glCallLists = glad_on_demand_impl_glCallLists;
static GLenum GLAD_API_PTR glad_on_demand_impl_glCheckFramebufferStatus(GLenum target) {
    glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) glad_gl_on_demand_loader("glCheckFramebufferStatus");
    return glad_glCheckFramebufferStatus(target);
}
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus = glad_on_demand_impl_glCheckFramebufferStatus;
static void GLAD_API_PTR glad_on_demand_impl_glClampColor(GLenum target, GLenum clamp) {
    glad_glClampColor = (PFNGLCLAMPCOLORPROC) glad_gl_on_demand_loader("glClampColor");
    glad_glClampColor(target, clamp);
}
PFNGLCLAMPCOLORPROC glad_glClampColor = glad_on_demand_impl_glClampColor;
static void GLAD_API_PTR glad_on_demand_impl_glClear(GLbitfield mask) {
    glad_glClear = (PFNGLCLEARPROC) glad_gl_on_demand_loader("glClear");
    glad_glClear(mask);
}
PFNGLCLEARPROC glad_glClear = glad_on_demand_impl_glClear;
static void GLAD_API_PTR glad_on_demand_impl_glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glClearAccum = (PFNGLCLEARACCUMPROC) glad_gl_on_demand_loader("glClearAccum");
    glad_glClearAccum(red, green, blue, alpha);
}
PFNGLCLEARACCUMPROC glad_glClearAccum = glad_on_demand_impl_glClearAccum;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) glad_gl_on_demand_loader("glClearBufferfi");
    glad_glClearBufferfi(buffer, drawbuffer, depth, stencil);
}
PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi = glad_on_demand_impl_glClearBufferfi;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) {
    glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) glad_gl_on_demand_loader("glClearBufferfv");
    glad_glClearBufferfv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv = glad_on_demand_impl_glClearBufferfv;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value) {
    glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) glad_gl_on_demand_loader("glClearBufferiv");
    glad_glClearBufferiv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv = glad_on_demand_impl_glClearBufferiv;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value) {
    glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) glad_gl_on_demand_loader("glClearBufferuiv");
    glad_glClearBufferuiv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv = glad_on_demand_impl_glClearBufferuiv;
static void GLAD_API_PTR glad_on_demand_impl_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glClearColor = (PFNGLCLEARCOLORPROC) glad_gl_on_demand_loader("glClearColor");
    glad_glClearColor(red, green, blue, alpha);
}
PFNGLCLEARCOLORPROC glad_glClearColor = glad_on_demand_impl_glClearColor;
static void GLAD_API_PTR glad_on_demand_impl_glClearDepth(GLdouble depth) {
    glad_glClearDepth = (PFNGLCLEARDEPTHPROC) glad_gl_on_demand_loader("glClearDepth");
    glad_glClearDepth(depth);
}
PFNGLCLEARDEPTHPROC glad_glClearDepth = glad_on_demand_impl_glClearDepth;
static void GLAD_API_PTR glad_on_demand_impl_glClearIndex(GLfloat c) {
    glad_glClearIndex = (PFNGLCLEARINDEXPROC) glad_gl_on_demand_loader("glClearIndex");
    glad_glClearIndex(c);
}
PFNGLCLEARINDEXPROC glad_glClearIndex = glad_on_demand_impl_glClearIndex;
static void GLAD_API_PTR glad_on_demand_impl_glClearStencil(GLint s) {
    glad_glClearStencil = (PFNGLCLEARSTENCILPROC) glad_gl_on_demand_loader("glClearStencil");
    glad_glClearStencil(s);
}
PFNGLCLEARSTENCILPROC glad_glClearStencil = glad_on_demand_impl_glClearStencil;
static void GLAD_API_PTR glad_on_demand_impl_glClientActiveTexture(GLenum texture) {
    glad_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) glad_gl_on_demand_loader("glClientActiveTexture");
    glad_glClientActiveTexture(texture);
}
PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture = glad_on_demand_impl_glClientActiveTexture;
static void GLAD_API_PTR glad_on_demand_impl_glClipPlane(GLenum plane, const GLdouble * equation) {
    glad_glClipPlane = (PFNGLCLIPPLANEPROC) glad_gl_on_demand_loader("glClipPlane");
    glad_glClipPlane(plane, equation);
}
PFNGLCLIPPLANEPROC glad_glClipPlane = glad_on_demand_impl_glClipPlane;
static void GLAD_API_PTR glad_on_demand_impl_glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
    glad_glColor3b = (PFNGLCOLOR3BPROC) glad_gl_on_demand_loader("glColor3b");
    glad_glColor3b(red, green, blue);
}
PFNGLCOLOR3BPROC glad_glColor3b = glad_on_demand_impl_glColor3b;
static void GLAD_API_PTR glad_on_demand_impl_glColor3bv(const GLbyte * v) {
    glad_glColor3bv = (PFNGLCOLOR3BVPROC) glad_gl_on_demand_loader("glColor3bv");
    glad_glColor3bv(v);
}
PFNGLCOLOR3BVPROC glad_glColor3bv = glad_on_demand_impl_glColor3bv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
    glad_glColor3d = (PFNGLCOLOR3DPROC) glad_gl_on_demand_loader("glColor3d");
    glad_glColor3d(red, green, blue);
}
PFNGLCOLOR3DPROC glad_glColor3d = glad_on_demand_impl_glColor3d;
static void GLAD_API_PTR glad_on_demand_impl_glColor3dv(const GLdouble * v) {
    glad_glColor3dv = (PFNGLCOLOR3DVPROC) glad_gl_on_demand_loader("glColor3dv");
    glad_glColor3dv(v);
}
PFNGLCOLOR3DVPROC glad_glColor3dv = glad_on_demand_impl_glColor3dv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    glad_glColor3f = (PFNGLCOLOR3FPROC) glad_gl_on_demand_loader("glColor3f");
    glad_glColor3f(red, green, blue);
}
PFNGLCOLOR3FPROC glad_glColor3f = glad_on_demand_impl_glColor3f;
static void GLAD_API_PTR glad_on_demand_impl_glColor3fv(const GLfloat * v) {
    glad_glColor3fv = (PFNGLCOLOR3FVPROC) glad_gl_on_demand_loader("glColor3fv");
    glad_glColor3fv(v);
}
PFNGLCOLOR3FVPROC glad_glColor3fv = glad_on_demand_impl_glColor3fv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3i(GLint red, GLint green, GLint blue) {
    glad_glColor3i = (PFNGLCOLOR3IPROC) glad_gl_on_demand_loader("glColor3i");
    glad_glColor3i(red, green, blue);
}
PFNGLCOLOR3IPROC glad_glColor3i = glad_on_demand_impl_glColor3i;
static void GLAD_API_PTR glad_on_demand_impl_glColor3iv(const GLint * v) {
    glad_glColor3iv = (PFNGLCOLOR3IVPROC) glad_gl_on_demand_loader("glColor3iv");
    glad_glColor3iv(v);
}
PFNGLCOLOR3IVPROC glad_glColor3iv = glad_on_demand_impl_glColor3iv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3s(GLshort red, GLshort green, GLshort blue) {
    glad_glColor3s = (PFNGLCOLOR3SPROC) glad_gl_on_demand_loader("glColor3s");
    glad_glColor3s(red, green, blue);
}
PFNGLCOLOR3SPROC glad_glColor3s = glad_on_demand_impl_glColor3s;
static void GLAD_API_PTR glad_on_demand_impl_glColor3sv(const GLshort * v) {
    glad_glColor3sv = (PFNGLCOLOR3SVPROC) glad_gl_on_demand_loader("glColor3sv");
    glad_glColor3sv(v);
}
PFNGLCOLOR3SVPROC glad_glColor3sv = glad_on_demand_impl_glColor3sv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    glad_glColor3ub = (PFNGLCOLOR3UBPROC) glad_gl_on_demand_loader("glColor3ub");
    glad_glColor3ub(red, green, blue);
}
PFNGLCOLOR3UBPROC glad_glColor3ub = glad_on_demand_impl_glColor3ub;
static void GLAD_API_PTR glad_on_demand_impl_glColor3ubv(const GLubyte * v) {
    glad_glColor3ubv = (PFNGLCOLOR3UBVPROC) glad_gl_on_demand_loader("glColor3ubv");
    glad_glColor3ubv(v);
}
PFNGLCOLOR3UBVPROC glad_glColor3ubv = glad_on_demand_impl_glColor3ubv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3ui(GLuint red, GLuint green, GLuint blue) {
    glad_glColor3ui = (PFNGLCOLOR3UIPROC) glad_gl_on_demand_loader("glColor3ui");
    glad_glColor3ui(red, green, blue);
}
PFNGLCOLOR3UIPROC glad_glColor3ui = glad_on_demand_impl_glColor3ui;
static void GLAD_API_PTR glad_on_demand_impl_glColor3uiv(const GLuint * v) {
    glad_glColor3uiv = (PFNGLCOLOR3UIVPROC) glad_gl_on_demand_loader("glColor3uiv");
    glad_glColor3uiv(v);
}
PFNGLCOLOR3UIVPROC glad_glColor3uiv = glad_on_demand_impl_glColor3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glColor3us(GLushort red, GLushort green, GLushort blue) {
    glad_glColor3us = (PFNGLCOLOR3USPROC) glad_gl_on_demand_loader("glColor3us");
    glad_glColor3us(red, green, blue);
}
PFNGLCOLOR3USPROC glad_glColor3us = glad_on_demand_impl_glColor3us;
static void GLAD_API_PTR glad_on_demand_impl_glColor3usv(const GLushort * v) {
    glad_glColor3usv = (PFNGLCOLOR3USVPROC) glad_gl_on_demand_loader("glColor3usv");
    glad_glColor3usv(v);
}
PFNGLCOLOR3USVPROC glad_glColor3usv = glad_on_demand_impl_glColor3usv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
    glad_glColor4b = (PFNGLCOLOR4BPROC) glad_gl_on_demand_loader("glColor4b");
    glad_glColor4b(red, green, blue, alpha);
}
PFNGLCOLOR4BPROC glad_glColor4b = glad_on_demand_impl_glColor4b;
static void GLAD_API_PTR glad_on_demand_impl_glColor4bv(const GLbyte * v) {
    glad_glColor4bv = (PFNGLCOLOR4BVPROC) glad_gl_on_demand_loader("glColor4bv");
    glad_glColor4bv(v);
}
PFNGLCOLOR4BVPROC glad_glColor4bv = glad_on_demand_impl_glColor4bv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) {
    glad_glColor4d = (PFNGLCOLOR4DPROC) glad_gl_on_demand_loader("glColor4d");
    glad_glColor4d(red, green, blue, alpha);
}
PFNGLCOLOR4DPROC glad_glColor4d = glad_on_demand_impl_glColor4d;
static void GLAD_API_PTR glad_on_demand_impl_glColor4dv(const GLdouble * v) {
    glad_glColor4dv = (PFNGLCOLOR4DVPROC) glad_gl_on_demand_loader("glColor4dv");
    glad_glColor4dv(v);
}
PFNGLCOLOR4DVPROC glad_glColor4dv = glad_on_demand_impl_glColor4dv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glColor4f = (PFNGLCOLOR4FPROC) glad_gl_on_demand_loader("glColor4f");
    glad_glColor4f(red, green, blue, alpha);
}
PFNGLCOLOR4FPROC glad_glColor4f = glad_on_demand_impl_glColor4f;
static void GLAD_API_PTR glad_on_demand_impl_glColor4fv(const GLfloat * v) {
    glad_glColor4fv = (PFNGLCOLOR4FVPROC) glad_gl_on_demand_loader("glColor4fv");
    glad_glColor4fv(v);
}
PFNGLCOLOR4FVPROC glad_glColor4fv = glad_on_demand_impl_glColor4fv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
    glad_glColor4i = (PFNGLCOLOR4IPROC) glad_gl_on_demand_loader("glColor4i");
    glad_glColor4i(red, green, blue, alpha);
}
PFNGLCOLOR4IPROC glad_glColor4i = glad_on_demand_impl_glColor4i;
static void GLAD_API_PTR glad_on_demand_impl_glColor4iv(const GLint * v) {
    glad_glColor4iv = (PFNGLCOLOR4IVPROC) glad_gl_on_demand_loader("glColor4iv");
    glad_glColor4iv(v);
}
PFNGLCOLOR4IVPROC glad_glColor4iv = glad_on_demand_impl_glColor4iv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) {
    glad_glColor4s = (PFNGLCOLOR4SPROC) glad_gl_on_demand_loader("glColor4s");
    glad_glColor4s(red, green, blue, alpha);
}
PFNGLCOLOR4SPROC glad_glColor4s = glad_on_demand_impl_glColor4s;
static void GLAD_API_PTR glad_on_demand_impl_glColor4sv(const GLshort * v) {
    glad_glColor4sv = (PFNGLCOLOR4SVPROC) glad_gl_on_demand_loader("glColor4sv");
    glad_glColor4sv(v);
}
PFNGLCOLOR4SVPROC glad_glColor4sv = glad_on_demand_impl_glColor4sv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    glad_glColor4ub = (PFNGLCOLOR4UBPROC) glad_gl_on_demand_loader("glColor4ub");
    glad_glColor4ub(red, green, blue, alpha);
}
PFNGLCOLOR4UBPROC glad_glColor4ub = glad_on_demand_impl_glColor4ub;
static void GLAD_API_PTR glad_on_demand_impl_glColor4ubv(const GLubyte * v) {
    glad_glColor4ubv = (PFNGLCOLOR4UBVPROC) glad_gl_on_demand_loader("glColor4ubv");
    glad_glColor4ubv(v);
}
PFNGLCOLOR4UBVPROC glad_glColor4ubv = glad_on_demand_impl_glColor4ubv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
    glad_glColor4ui = (PFNGLCOLOR4UIPROC) glad_gl_on_demand_loader("glColor4ui");
    glad_glColor4ui(red, green, blue, alpha);
}
PFNGLCOLOR4UIPROC glad_glColor4ui = glad_on_demand_impl_glColor4ui;
static void GLAD_API_PTR glad_on_demand_impl_glColor4uiv(const GLuint * v) {
    glad_glColor4uiv = (PFNGLCOLOR4UIVPROC) glad_gl_on_demand_loader("glColor4uiv");
    glad_glColor4uiv(v);
}
PFNGLCOLOR4UIVPROC glad_glColor4uiv = glad_on_demand_impl_glColor4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) {
    glad_glColor4us = (PFNGLCOLOR4USPROC) glad_gl_on_demand_loader("glColor4us");
    glad_glColor4us(red, green, blue, alpha);
}
PFNGLCOLOR4USPROC glad_glColor4us = glad_on_demand_impl_glColor4us;
static void GLAD_API_PTR glad_on_demand_impl_glColor4usv(const GLushort * v) {
    glad_glColor4usv = (PFNGLCOLOR4USVPROC) glad_gl_on_demand_loader("glColor4usv");
    glad_glColor4usv(v);
}
PFNGLCOLOR4USVPROC glad_glColor4usv = glad_on_demand_impl_glColor4usv;
static void GLAD_API_PTR glad_on_demand_impl_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glad_glColorMask = (PFNGLCOLORMASKPROC) glad_gl_on_demand_loader("glColorMask");
    glad_glColorMask(red, green, blue, alpha);
}
PFNGLCOLORMASKPROC glad_glColorMask = glad_on_demand_impl_glColorMask;
static void GLAD_API_PTR glad_on_demand_impl_glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    glad_glColorMaski = (PFNGLCOLORMASKIPROC) glad_gl_on_demand_loader("glColorMaski");
    glad_glColorMaski(index, r, g, b, a);
}
PFNGLCOLORMASKIPROC glad_glColorMaski = glad_on_demand_impl_glColorMaski;
static void GLAD_API_PTR glad_on_demand_impl_glColorMaterial(GLenum face, GLenum mode) {
    glad_glColorMaterial = (PFNGLCOLORMATERIALPROC) glad_gl_on_demand_loader("glColorMaterial");
    glad_glColorMaterial(face, mode);
}
PFNGLCOLORMATERIALPROC glad_glColorMaterial = glad_on_demand_impl_glColorMaterial;
static void GLAD_API_PTR glad_on_demand_impl_glColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glColorPointer = (PFNGLCOLORPOINTERPROC) glad_gl_on_demand_loader("glColorPointer");
    glad_glColorPointer(size, type, stride, pointer);
}
PFNGLCOLORPOINTERPROC glad_glColorPointer = glad_on_demand_impl_glColorPointer;
static void GLAD_API_PTR glad_on_demand_impl_glCompileShader(GLuint shader) {
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC) glad_gl_on_demand_loader("glCompileShader");
    glad_glCompileShader(shader);
}
PFNGLCOMPILESHADERPROC glad_glCompileShader = glad_on_demand_impl_glCompileShader;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) glad_gl_on_demand_loader("glCompressedTexImage1D");
    glad_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D = glad_on_demand_impl_glCompressedTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) glad_gl_on_demand_loader("glCompressedTexImage2D");
    glad_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = glad_on_demand_impl_glCompressedTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) glad_gl_on_demand_loader("glCompressedTexImage3D");
    glad_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D = glad_on_demand_impl_glCompressedTexImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage1D");
    glad_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D = glad_on_demand_impl_glCompressedTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage2D");
    glad_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D = glad_on_demand_impl_glCompressedTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage3D");
    glad_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D = glad_on_demand_impl_glCompressedTexSubImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) {
    glad_glCopyPixels = (PFNGLCOPYPIXELSPROC) glad_gl_on_demand_loader("glCopyPixels");
    glad_glCopyPixels(x, y, width, height, type);
}
PFNGLCOPYPIXELSPROC glad_glCopyPixels = glad_on_demand_impl_glCopyPixels;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glad_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) glad_gl_on_demand_loader("glCopyTexImage1D");
    glad_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}
PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D = glad_on_demand_impl_glCopyTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) glad_gl_on_demand_loader("glCopyTexImage2D");
    glad_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = glad_on_demand_impl_glCopyTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glad_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glCopyTexSubImage1D");
    glad_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}
PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D = glad_on_demand_impl_glCopyTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glCopyTexSubImage2D");
    glad_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = glad_on_demand_impl_glCopyTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glCopyTexSubImage3D");
    glad_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D = glad_on_demand_impl_glCopyTexSubImage3D;
static GLuint GLAD_API_PTR glad_on_demand_impl_glCreateProgram(void) {
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC) glad_gl_on_demand_loader("glCreateProgram");
    return glad_glCreateProgram();
}
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = glad_on_demand_impl_glCreateProgram;
static GLuint GLAD_API_PTR glad_on_demand_impl_glCreateShader(GLenum type) {
    glad_glCreateShader = (PFNGLCREATESHADERPROC) glad_gl_on_demand_loader("glCreateShader");
    return glad_glCreateShader(type);
}
PFNGLCREATESHADERPROC glad_glCreateShader = glad_on_demand_impl_glCreateShader;
static void GLAD_API_PTR glad_on_demand_impl_glCullFace(GLenum mode) {
    glad_glCullFace = (PFNGLCULLFACEPROC) glad_gl_on_demand_loader("glCullFace");
    glad_glCullFace(mode);
}
PFNGLCULLFACEPROC glad_glCullFace = glad_on_demand_impl_glCullFace;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteBuffers(GLsizei n, const GLuint * buffers) {
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) glad_gl_on_demand_loader("glDeleteBuffers");
    glad_glDeleteBuffers(n, buffers);
}
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = glad_on_demand_impl_glDeleteBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers) {
    glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) glad_gl_on_demand_loader("glDeleteFramebuffers");
    glad_glDeleteFramebuffers(n, framebuffers);
}
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers = glad_on_demand_impl_glDeleteFramebuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteLists(GLuint list, GLsizei range) {
    glad_glDeleteLists = (PFNGLDELETELISTSPROC) glad_gl_on_demand_loader("glDeleteLists");
    glad_glDeleteLists(list, range);
}
PFNGLDELETELISTSPROC glad_glDeleteLists = glad_on_demand_impl_glDeleteLists;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteProgram(GLuint program) {
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glad_gl_on_demand_loader("glDeleteProgram");
    glad_glDeleteProgram(program);
}
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = glad_on_demand_impl_glDeleteProgram;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteQueries(GLsizei n, const GLuint * ids) {
    glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC) glad_gl_on_demand_loader("glDeleteQueries");
    glad_glDeleteQueries(n, ids);
}
PFNGLDELETEQUERIESPROC glad_glDeleteQueries = glad_on_demand_impl_glDeleteQueries;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) {
    glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) glad_gl_on_demand_loader("glDeleteRenderbuffers");
    glad_glDeleteRenderbuffers(n, renderbuffers);
}
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers = glad_on_demand_impl_glDeleteRenderbuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteShader(GLuint shader) {
    glad_glDeleteShader = (PFNGLDELETESHADERPROC) glad_gl_on_demand_loader("glDeleteShader");
    glad_glDeleteShader(shader);
}
PFNGLDELETESHADERPROC glad_glDeleteShader = glad_on_demand_impl_glDeleteShader;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteTextures(GLsizei n, const GLuint * textures) {
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC) glad_gl_on_demand_loader("glDeleteTextures");
    glad_glDeleteTextures(n, textures);
}
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = glad_on_demand_impl_glDeleteTextures;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteVertexArrays(GLsizei n, const GLuint * arrays) {
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) glad_gl_on_demand_loader("glDeleteVertexArrays");
    glad_glDeleteVertexArrays(n, arrays);
}
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = glad_on_demand_impl_glDeleteVertexArrays;
static void GLAD_API_PTR glad_on_demand_impl_glDepthFunc(GLenum func) {
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC) glad_gl_on_demand_loader("glDepthFunc");
    glad_glDepthFunc(func);
}
PFNGLDEPTHFUNCPROC glad_glDepthFunc = glad_on_demand_impl_glDepthFunc;
static void GLAD_API_PTR glad_on_demand_impl_glDepthMask(GLboolean flag) {
    glad_glDepthMask = (PFNGLDEPTHMASKPROC) glad_gl_on_demand_loader("glDepthMask");
    glad_glDepthMask(flag);
}
PFNGLDEPTHMASKPROC glad_glDepthMask = glad_on_demand_impl_glDepthMask;
static void GLAD_API_PTR glad_on_demand_impl_glDepthRange(GLdouble n, GLdouble f) {
    glad_glDepthRange = (PFNGLDEPTHRANGEPROC) glad_gl_on_demand_loader("glDepthRange");
    glad_glDepthRange(n, f);
}
PFNGLDEPTHRANGEPROC glad_glDepthRange = glad_on_demand_impl_glDepthRange;
static void GLAD_API_PTR glad_on_demand_impl_glDetachShader(GLuint program, GLuint shader) {
    glad_glDetachShader = (PFNGLDETACHSHADERPROC) glad_gl_on_demand_loader("glDetachShader");
    glad_glDetachShader(program, shader);
}
PFNGLDETACHSHADERPROC glad_glDetachShader = glad_on_demand_impl_glDetachShader;
static void GLAD_API_PTR glad_on_demand_impl_glDisable(GLenum cap) {
    glad_glDisable = (PFNGLDISABLEPROC) glad_gl_on_demand_loader("glDisable");
    glad_glDisable(cap);
}
PFNGLDISABLEPROC glad_glDisable = glad_on_demand_impl_glDisable;
static void GLAD_API_PTR glad_on_demand_impl_glDisableClientState(GLenum array) {
    glad_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC) glad_gl_on_demand_loader("glDisableClientState");
    glad_glDisableClientState(array);
}
PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState = glad_on_demand_impl_glDisableClientState;
static void GLAD_API_PTR glad_on_demand_impl_glDisableVertexAttribArray(GLuint index) {
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) glad_gl_on_demand_loader("glDisableVertexAttribArray");
    glad_glDisableVertexAttribArray(index);
}
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = glad_on_demand_impl_glDisableVertexAttribArray;
static void GLAD_API_PTR glad_on_demand_impl_glDisablei(GLenum target, GLuint index) {
    glad_glDisablei = (PFNGLDISABLEIPROC) glad_gl_on_demand_loader("glDisablei");
    glad_glDisablei(target, index);
}
PFNGLDISABLEIPROC glad_glDisablei = glad_on_demand_impl_glDisablei;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC) glad_gl_on_demand_loader("glDrawArrays");
    glad_glDrawArrays(mode, first, count);
}
PFNGLDRAWARRAYSPROC glad_glDrawArrays = glad_on_demand_impl_glDrawArrays;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffer(GLenum buf) {
    glad_glDrawBuffer = (PFNGLDRAWBUFFERPROC) glad_gl_on_demand_loader("glDrawBuffer");
    glad_glDrawBuffer(buf);
}
PFNGLDRAWBUFFERPROC glad_glDrawBuffer = glad_on_demand_impl_glDrawBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffers(GLsizei n, const GLenum * bufs) {
    glad_glDrawBuffers = (PFNGLDRAWBUFFERSPROC) glad_gl_on_demand_loader("glDrawBuffers");
    glad_glDrawBuffers(n, bufs);
}
PFNGLDRAWBUFFERSPROC glad_glDrawBuffers = glad_on_demand_impl_glDrawBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices) {
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC) glad_gl_on_demand_loader("glDrawElements");
    glad_glDrawElements(mode, count, type, indices);
}
PFNGLDRAWELEMENTSPROC glad_glDrawElements = glad_on_demand_impl_glDrawElements;
static void GLAD_API_PTR glad_on_demand_impl_glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glDrawPixels = (PFNGLDRAWPIXELSPROC) glad_gl_on_demand_loader("glDrawPixels");
    glad_glDrawPixels(width, height, format, type, pixels);
}
PFNGLDRAWPIXELSPROC glad_glDrawPixels = glad_on_demand_impl_glDrawPixels;
static void GLAD_API_PTR glad_on_demand_impl_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices) {
    glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) glad_gl_on_demand_loader("glDrawRangeElements");
    glad_glDrawRangeElements(mode, start, end, count, type, indices);
}
PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements = glad_on_demand_impl_glDrawRangeElements;
static void GLAD_API_PTR glad_on_demand_impl_glEdgeFlag(GLboolean flag) {
    glad_glEdgeFlag = (PFNGLEDGEFLAGPROC) glad_gl_on_demand_loader("glEdgeFlag");
    glad_glEdgeFlag(flag);
}
PFNGLEDGEFLAGPROC glad_glEdgeFlag = glad_on_demand_impl_glEdgeFlag;
static void GLAD_API_PTR glad_on_demand_impl_glEdgeFlagPointer(GLsizei stride, const void * pointer) {
    glad_glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC) glad_gl_on_demand_loader("glEdgeFlagPointer");
    glad_glEdgeFlagPointer(stride, pointer);
}
PFNGLEDGEFLAGPOINTERPROC glad_glEdgeFlagPointer = glad_on_demand_impl_glEdgeFlagPointer;
static void GLAD_API_PTR glad_on_demand_impl_glEdgeFlagv(const GLboolean * flag) {
    glad_glEdgeFlagv = (PFNGLEDGEFLAGVPROC) glad_gl_on_demand_loader("glEdgeFlagv");
    glad_glEdgeFlagv(flag);
}
PFNGLEDGEFLAGVPROC glad_glEdgeFlagv = glad_on_demand_impl_glEdgeFlagv;
static void GLAD_API_PTR glad_on_demand_impl_glEnable(GLenum cap) {
    glad_glEnable = (PFNGLENABLEPROC) glad_gl_on_demand_loader("glEnable");
    glad_glEnable(cap);
}
PFNGLENABLEPROC glad_glEnable = glad_on_demand_impl_glEnable;
static void GLAD_API_PTR glad_on_demand_impl_glEnableClientState(GLenum array) {
    glad_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC) glad_gl_on_demand_loader("glEnableClientState");
    glad_glEnableClientState(array);
}
PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState = glad_on_demand_impl_glEnableClientState;
static void GLAD_API_PTR glad_on_demand_impl_glEnableVertexAttribArray(GLuint index) {
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glad_gl_on_demand_loader("glEnableVertexAttribArray");
    glad_glEnableVertexAttribArray(index);
}
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = glad_on_demand_impl_glEnableVertexAttribArray;
static void GLAD_API_PTR glad_on_demand_impl_glEnablei(GLenum target, GLuint index) {
    glad_glEnablei = (PFNGLENABLEIPROC) glad_gl_on_demand_loader("glEnablei");
    glad_glEnablei(target, index);
}
PFNGLENABLEIPROC glad_glEnablei = glad_on_demand_impl_glEnablei;
static void GLAD_API_PTR glad_on_demand_impl_glEnd(void) {
    glad_glEnd = (PFNGLENDPROC) glad_gl_on_demand_loader("glEnd");
    glad_glEnd();
}
PFNGLENDPROC glad_glEnd = glad_on_demand_impl_glEnd;
static void GLAD_API_PTR glad_on_demand_impl_glEndConditionalRender(void) {
    glad_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) glad_gl_on_demand_loader("glEndConditionalRender");
    glad_glEndConditionalRender();
}
PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender = glad_on_demand_impl_glEndConditionalRender;
static void GLAD_API_PTR glad_on_demand_impl_glEndList(void) {
    glad_glEndList = (PFNGLENDLISTPROC) glad_gl_on_demand_loader("glEndList");
    glad_glEndList();
}
PFNGLENDLISTPROC glad_glEndList = glad_on_demand_impl_glEndList;
static void GLAD_API_PTR glad_on_demand_impl_glEndQuery(GLenum target) {
    glad_glEndQuery = (PFNGLENDQUERYPROC) glad_gl_on_demand_loader("glEndQuery");
    glad_glEndQuery(target);
}
PFNGLENDQUERYPROC glad_glEndQuery = glad_on_demand_impl_glEndQuery;
static void GLAD_API_PTR glad_on_demand_impl_glEndTransformFeedback(void) {
    glad_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) glad_gl_on_demand_loader("glEndTransformFeedback");
    glad_glEndTransformFeedback();
}
PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback = glad_on_demand_impl_glEndTransformFeedback;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord1d(GLdouble u) {
    glad_glEvalCoord1d = (PFNGLEVALCOORD1DPROC) glad_gl_on_demand_loader("glEvalCoord1d");
    glad_glEvalCoord1d(u);
}
PFNGLEVALCOORD1DPROC glad_glEvalCoord1d = glad_on_demand_impl_glEvalCoord1d;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord1dv(const GLdouble * u) {
    glad_glEvalCoord1dv = (PFNGLEVALCOORD1DVPROC) glad_gl_on_demand_loader("glEvalCoord1dv");
    glad_glEvalCoord1dv(u);
}
PFNGLEVALCOORD1DVPROC glad_glEvalCoord1dv = glad_on_demand_impl_glEvalCoord1dv;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord1f(GLfloat u) {
    glad_glEvalCoord1f = (PFNGLEVALCOORD1FPROC) glad_gl_on_demand_loader("glEvalCoord1f");
    glad_glEvalCoord1f(u);
}
PFNGLEVALCOORD1FPROC glad_glEvalCoord1f = glad_on_demand_impl_glEvalCoord1f;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord1fv(const GLfloat * u) {
    glad_glEvalCoord1fv = (PFNGLEVALCOORD1FVPROC) glad_gl_on_demand_loader("glEvalCoord1fv");
    glad_glEvalCoord1fv(u);
}
PFNGLEVALCOORD1FVPROC glad_glEvalCoord1fv = glad_on_demand_impl_glEvalCoord1fv;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord2d(GLdouble u, GLdouble v) {
    glad_glEvalCoord2d = (PFNGLEVALCOORD2DPROC) glad_gl_on_demand_loader("glEvalCoord2d");
    glad_glEvalCoord2d(u, v);
}
PFNGLEVALCOORD2DPROC glad_glEvalCoord2d = glad_on_demand_impl_glEvalCoord2d;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord2dv(const GLdouble * u) {
    glad_glEvalCoord2dv = (PFNGLEVALCOORD2DVPROC) glad_gl_on_demand_loader("glEvalCoord2dv");
    glad_glEvalCoord2dv(u);
}
PFNGLEVALCOORD2DVPROC glad_glEvalCoord2dv = glad_on_demand_impl_glEvalCoord2dv;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord2f(GLfloat u, GLfloat v) {
    glad_glEvalCoord2f = (PFNGLEVALCOORD2FPROC) glad_gl_on_demand_loader("glEvalCoord2f");
    glad_glEvalCoord2f(u, v);
}
PFNGLEVALCOORD2FPROC glad_glEvalCoord2f = glad_on_demand_impl_glEvalCoord2f;
static void GLAD_API_PTR glad_on_demand_impl_glEvalCoord2fv(const GLfloat * u) {
    glad_glEvalCoord2fv = (PFNGLEVALCOORD2FVPROC) glad_gl_on_demand_loader("glEvalCoord2fv");
    glad_glEvalCoord2fv(u);
}
PFNGLEVALCOORD2FVPROC glad_glEvalCoord2fv = glad_on_demand_impl_glEvalCoord2fv;
static void GLAD_API_PTR glad_on_demand_impl_glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
    glad_glEvalMesh1 = (PFNGLEVALMESH1PROC) glad_gl_on_demand_loader("glEvalMesh1");
    glad_glEvalMesh1(mode, i1, i2);
}
PFNGLEVALMESH1PROC glad_glEvalMesh1 = glad_on_demand_impl_glEvalMesh1;
static void GLAD_API_PTR glad_on_demand_impl_glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
    glad_glEvalMesh2 = (PFNGLEVALMESH2PROC) glad_gl_on_demand_loader("glEvalMesh2");
    glad_glEvalMesh2(mode, i1, i2, j1, j2);
}
PFNGLEVALMESH2PROC glad_glEvalMesh2 = glad_on_demand_impl_glEvalMesh2;
static void GLAD_API_PTR glad_on_demand_impl_glEvalPoint1(GLint i) {
    glad_glEvalPoint1 = (PFNGLEVALPOINT1PROC) glad_gl_on_demand_loader("glEvalPoint1");
    glad_glEvalPoint1(i);
}
PFNGLEVALPOINT1PROC glad_glEvalPoint1 = glad_on_demand_impl_glEvalPoint1;
static void GLAD_API_PTR glad_on_demand_impl_glEvalPoint2(GLint i, GLint j) {
    glad_glEvalPoint2 = (PFNGLEVALPOINT2PROC) glad_gl_on_demand_loader("glEvalPoint2");
    glad_glEvalPoint2(i, j);
}
PFNGLEVALPOINT2PROC glad_glEvalPoint2 = glad_on_demand_impl_glEvalPoint2;
static void GLAD_API_PTR glad_on_demand_impl_glFeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer) {
    glad_glFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC) glad_gl_on_demand_loader("glFeedbackBuffer");
    glad_glFeedbackBuffer(size, type, buffer);
}
PFNGLFEEDBACKBUFFERPROC glad_glFeedbackBuffer = glad_on_demand_impl_glFeedbackBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glFinish(void) {
    glad_glFinish = (PFNGLFINISHPROC) glad_gl_on_demand_loader("glFinish");
    glad_glFinish();
}
PFNGLFINISHPROC glad_glFinish = glad_on_demand_impl_glFinish;
static void GLAD_API_PTR glad_on_demand_impl_glFlush(void) {
    glad_glFlush = (PFNGLFLUSHPROC) glad_gl_on_demand_loader("glFlush");
    glad_glFlush();
}
PFNGLFLUSHPROC glad_glFlush = glad_on_demand_impl_glFlush;
static void GLAD_API_PTR glad_on_demand_impl_glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {
    glad_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) glad_gl_on_demand_loader("glFlushMappedBufferRange");
    glad_glFlushMappedBufferRange(target, offset, length);
}
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange = glad_on_demand_impl_glFlushMappedBufferRange;
static void GLAD_API_PTR glad_on_demand_impl_glFogCoordPointer(GLenum type, GLsizei stride, const void * pointer) {
    glad_glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC) glad_gl_on_demand_loader("glFogCoordPointer");
    glad_glFogCoordPointer(type, stride, pointer);
}
PFNGLFOGCOORDPOINTERPROC glad_glFogCoordPointer = glad_on_demand_impl_glFogCoordPointer;
static void GLAD_API_PTR glad_on_demand_impl_glFogCoordd(GLdouble coord) {
    glad_glFogCoordd = (PFNGLFOGCOORDDPROC) glad_gl_on_demand_loader("glFogCoordd");
    glad_glFogCoordd(coord);
}
PFNGLFOGCOORDDPROC glad_glFogCoordd = glad_on_demand_impl_glFogCoordd;
static void GLAD_API_PTR glad_on_demand_impl_glFogCoorddv(const GLdouble * coord) {
    glad_glFogCoorddv = (PFNGLFOGCOORDDVPROC) glad_gl_on_demand_loader("glFogCoorddv");
    glad_glFogCoorddv(coord);
}
PFNGLFOGCOORDDVPROC glad_glFogCoorddv = glad_on_demand_impl_glFogCoorddv;
static void GLAD_API_PTR glad_on_demand_impl_glFogCoordf(GLfloat coord) {
    glad_glFogCoordf = (PFNGLFOGCOORDFPROC) glad_gl_on_demand_loader("glFogCoordf");
    glad_glFogCoordf(coord);
}
PFNGLFOGCOORDFPROC glad_glFogCoordf = glad_on_demand_impl_glFogCoordf;
static void GLAD_API_PTR glad_on_demand_impl_glFogCoordfv(const GLfloat * coord) {
    glad_glFogCoordfv = (PFNGLFOGCOORDFVPROC) glad_gl_on_demand_loader("glFogCoordfv");
    glad_glFogCoordfv(coord);
}
PFNGLFOGCOORDFVPROC glad_glFogCoordfv = glad_on_demand_impl_glFogCoordfv;
static void GLAD_API_PTR glad_on_demand_impl_glFogf(GLenum pname, GLfloat param) {
    glad_glFogf = (PFNGLFOGFPROC) glad_gl_on_demand_loader("glFogf");
    glad_glFogf(pname, param);
}
PFNGLFOGFPROC glad_glFogf = glad_on_demand_impl_glFogf;
static void GLAD_API_PTR glad_on_demand_impl_glFogfv(GLenum pname, const GLfloat * params) {
    glad_glFogfv = (PFNGLFOGFVPROC) glad_gl_on_demand_loader("glFogfv");
    glad_glFogfv(pname, params);
}
PFNGLFOGFVPROC glad_glFogfv = glad_on_demand_impl_glFogfv;
static void GLAD_API_PTR glad_on_demand_impl_glFogi(GLenum pname, GLint param) {
    glad_glFogi = (PFNGLFOGIPROC) glad_gl_on_demand_loader("glFogi");
    glad_glFogi(pname, param);
}
PFNGLFOGIPROC glad_glFogi = glad_on_demand_impl_glFogi;
static void GLAD_API_PTR glad_on_demand_impl_glFogiv(GLenum pname, const GLint * params) {
    glad_glFogiv = (PFNGLFOGIVPROC) glad_gl_on_demand_loader("glFogiv");
    glad_glFogiv(pname, params);
}
PFNGLFOGIVPROC glad_glFogiv = glad_on_demand_impl_glFogiv;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) glad_gl_on_demand_loader("glFramebufferRenderbuffer");
    glad_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer = glad_on_demand_impl_glFramebufferRenderbuffer;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) glad_gl_on_demand_loader("glFramebufferTexture1D");
    glad_glFramebufferTexture1D(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D = glad_on_demand_impl_glFramebufferTexture1D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) glad_gl_on_demand_loader("glFramebufferTexture2D");
    glad_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D = glad_on_demand_impl_glFramebufferTexture2D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
    glad_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) glad_gl_on_demand_loader("glFramebufferTexture3D");
    glad_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}
PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D = glad_on_demand_impl_glFramebufferTexture3D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) glad_gl_on_demand_loader("glFramebufferTextureLayer");
    glad_glFramebufferTextureLayer(target, attachment, texture, level, layer);
}
PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer = glad_on_demand_impl_glFramebufferTextureLayer;
static void GLAD_API_PTR glad_on_demand_impl_glFrontFace(GLenum mode) {
    glad_glFrontFace = (PFNGLFRONTFACEPROC) glad_gl_on_demand_loader("glFrontFace");
    glad_glFrontFace(mode);
}
PFNGLFRONTFACEPROC glad_glFrontFace = glad_on_demand_impl_glFrontFace;
static void GLAD_API_PTR glad_on_demand_impl_glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    glad_glFrustum = (PFNGLFRUSTUMPROC) glad_gl_on_demand_loader("glFrustum");
    glad_glFrustum(left, right, bottom, top, zNear, zFar);
}
PFNGLFRUSTUMPROC glad_glFrustum = glad_on_demand_impl_glFrustum;
static void GLAD_API_PTR glad_on_demand_impl_glGenBuffers(GLsizei n, GLuint * buffers) {
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC) glad_gl_on_demand_loader("glGenBuffers");
    glad_glGenBuffers(n, buffers);
}
PFNGLGENBUFFERSPROC glad_glGenBuffers = glad_on_demand_impl_glGenBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glGenFramebuffers(GLsizei n, GLuint * framebuffers) {
    glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) glad_gl_on_demand_loader("glGenFramebuffers");
    glad_glGenFramebuffers(n, framebuffers);
}
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = glad_on_demand_impl_glGenFramebuffers;
static GLuint GLAD_API_PTR glad_on_demand_impl_glGenLists(GLsizei range) {
    glad_glGenLists = (PFNGLGENLISTSPROC) glad_gl_on_demand_loader("glGenLists");
    return glad_glGenLists(range);
}
PFNGLGENLISTSPROC glad_glGenLists = glad_on_demand_impl_glGenLists;
static void GLAD_API_PTR glad_on_demand_impl_glGenQueries(GLsizei n, GLuint * ids) {
    glad_glGenQueries = (PFNGLGENQUERIESPROC) glad_gl_on_demand_loader("glGenQueries");
    glad_glGenQueries(n, ids);
}
PFNGLGENQUERIESPROC glad_glGenQueries = glad_on_demand_impl_glGenQueries;
static void GLAD_API_PTR glad_on_demand_impl_glGenRenderbuffers(GLsizei n, GLuint * renderbuffers) {
    glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) glad_gl_on_demand_loader("glGenRenderbuffers");
    glad_glGenRenderbuffers(n, renderbuffers);
}
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers = glad_on_demand_impl_glGenRenderbuffers;
static void GLAD_API_PTR glad_on_demand_impl_glGenTextures(GLsizei n, GLuint * textures) {
    glad_glGenTextures = (PFNGLGENTEXTURESPROC) glad_gl_on_demand_loader("glGenTextures");
    glad_glGenTextures(n, textures);
}
PFNGLGENTEXTURESPROC glad_glGenTextures = glad_on_demand_impl_glGenTextures;
static void GLAD_API_PTR glad_on_demand_impl_glGenVertexArrays(GLsizei n, GLuint * arrays) {
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glad_gl_on_demand_loader("glGenVertexArrays");
    glad_glGenVertexArrays(n, arrays);
}
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = glad_on_demand_impl_glGenVertexArrays;
static void GLAD_API_PTR glad_on_demand_impl_glGenerateMipmap(GLenum target) {
    glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) glad_gl_on_demand_loader("glGenerateMipmap");
    glad_glGenerateMipmap(target);
}
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = glad_on_demand_impl_glGenerateMipmap;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) glad_gl_on_demand_loader("glGetActiveAttrib");
    glad_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = glad_on_demand_impl_glGetActiveAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) glad_gl_on_demand_loader("glGetActiveUniform");
    glad_glGetActiveUniform(program, index, bufSize, length, size, type, name);
}
PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform = glad_on_demand_impl_glGetActiveUniform;
static void GLAD_API_PTR glad_on_demand_impl_glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) {
    glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) glad_gl_on_demand_loader("glGetAttachedShaders");
    glad_glGetAttachedShaders(program, maxCount, count, shaders);
}
PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders = glad_on_demand_impl_glGetAttachedShaders;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetAttribLocation(GLuint program, const GLchar * name) {
    glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) glad_gl_on_demand_loader("glGetAttribLocation");
    return glad_glGetAttribLocation(program, name);
}
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = glad_on_demand_impl_glGetAttribLocation;
static void GLAD_API_PTR glad_on_demand_impl_glGetBooleani_v(GLenum target, GLuint index, GLboolean * data) {
    glad_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) glad_gl_on_demand_loader("glGetBooleani_v");
    glad_glGetBooleani_v(target, index, data);
}
PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v = glad_on_demand_impl_glGetBooleani_v;
static void GLAD_API_PTR glad_on_demand_impl_glGetBooleanv(GLenum pname, GLboolean * data) {
    glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC) glad_gl_on_demand_loader("glGetBooleanv");
    glad_glGetBooleanv(pname, data);
}
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = glad_on_demand_impl_glGetBooleanv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) glad_gl_on_demand_loader("glGetBufferParameteriv");
    glad_glGetBufferParameteriv(target, pname, params);
}
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = glad_on_demand_impl_glGetBufferParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferPointerv(GLenum target, GLenum pname, void ** params) {
    glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) glad_gl_on_demand_loader("glGetBufferPointerv");
    glad_glGetBufferPointerv(target, pname, params);
}
PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv = glad_on_demand_impl_glGetBufferPointerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data) {
    glad_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) glad_gl_on_demand_loader("glGetBufferSubData");
    glad_glGetBufferSubData(target, offset, size, data);
}
PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData = glad_on_demand_impl_glGetBufferSubData;
static void GLAD_API_PTR glad_on_demand_impl_glGetClipPlane(GLenum plane, GLdouble * equation) {
    glad_glGetClipPlane = (PFNGLGETCLIPPLANEPROC) glad_gl_on_demand_loader("glGetClipPlane");
    glad_glGetClipPlane(plane, equation);
}
PFNGLGETCLIPPLANEPROC glad_glGetClipPlane = glad_on_demand_impl_glGetClipPlane;
static void GLAD_API_PTR glad_on_demand_impl_glGetCompressedTexImage(GLenum target, GLint level, void * img) {
    glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) glad_gl_on_demand_loader("glGetCompressedTexImage");
    glad_glGetCompressedTexImage(target, level, img);
}
PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage = glad_on_demand_impl_glGetCompressedTexImage;
static void GLAD_API_PTR glad_on_demand_impl_glGetDoublev(GLenum pname, GLdouble * data) {
    glad_glGetDoublev = (PFNGLGETDOUBLEVPROC) glad_gl_on_demand_loader("glGetDoublev");
    glad_glGetDoublev(pname, data);
}
PFNGLGETDOUBLEVPROC glad_glGetDoublev = glad_on_demand_impl_glGetDoublev;
static GLenum GLAD_API_PTR glad_on_demand_impl_glGetError(void) {
    glad_glGetError = (PFNGLGETERRORPROC) glad_gl_on_demand_loader("glGetError");
    return glad_glGetError();
}
PFNGLGETERRORPROC glad_glGetError = glad_on_demand_impl_glGetError;
static void GLAD_API_PTR glad_on_demand_impl_glGetFloatv(GLenum pname, GLfloat * data) {
    glad_glGetFloatv = (PFNGLGETFLOATVPROC) glad_gl_on_demand_loader("glGetFloatv");
    glad_glGetFloatv(pname, data);
}
PFNGLGETFLOATVPROC glad_glGetFloatv = glad_on_demand_impl_glGetFloatv;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetFragDataLocation(GLuint program, const GLchar * name) {
    glad_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) glad_gl_on_demand_loader("glGetFragDataLocation");
    return glad_glGetFragDataLocation(program, name);
}
PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation = glad_on_demand_impl_glGetFragDataLocation;
static void GLAD_API_PTR glad_on_demand_impl_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
    glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) glad_gl_on_demand_loader("glGetFramebufferAttachmentParameteriv");
    glad_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv = glad_on_demand_impl_glGetFramebufferAttachmentParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetIntegeri_v(GLenum target, GLuint index, GLint * data) {
    glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) glad_gl_on_demand_loader("glGetIntegeri_v");
    glad_glGetIntegeri_v(target, index, data);
}
PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v = glad_on_demand_impl_glGetIntegeri_v;
static void GLAD_API_PTR glad_on_demand_impl_glGetIntegerv(GLenum pname, GLint * data) {
    glad_glGetIntegerv = (PFNGLGETINTEGERVPROC) glad_gl_on_demand_loader("glGetIntegerv");
    glad_glGetIntegerv(pname, data);
}
PFNGLGETINTEGERVPROC glad_glGetIntegerv = glad_on_demand_impl_glGetIntegerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetLightfv(GLenum light, GLenum pname, GLfloat * params) {
    glad_glGetLightfv = (PFNGLGETLIGHTFVPROC) glad_gl_on_demand_loader("glGetLightfv");
    glad_glGetLightfv(light, pname, params);
}
PFNGLGETLIGHTFVPROC glad_glGetLightfv = glad_on_demand_impl_glGetLightfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetLightiv(GLenum light, GLenum pname, GLint * params) {
    glad_glGetLightiv = (PFNGLGETLIGHTIVPROC) glad_gl_on_demand_loader("glGetLightiv");
    glad_glGetLightiv(light, pname, params);
}
PFNGLGETLIGHTIVPROC glad_glGetLightiv = glad_on_demand_impl_glGetLightiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMapdv(GLenum target, GLenum query, GLdouble * v) {
    glad_glGetMapdv = (PFNGLGETMAPDVPROC) glad_gl_on_demand_loader("glGetMapdv");
    glad_glGetMapdv(target, query, v);
}
PFNGLGETMAPDVPROC glad_glGetMapdv = glad_on_demand_impl_glGetMapdv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMapfv(GLenum target, GLenum query, GLfloat * v) {
    glad_glGetMapfv = (PFNGLGETMAPFVPROC) glad_gl_on_demand_loader("glGetMapfv");
    glad_glGetMapfv(target, query, v);
}
PFNGLGETMAPFVPROC glad_glGetMapfv = glad_on_demand_impl_glGetMapfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMapiv(GLenum target, GLenum query, GLint * v) {
    glad_glGetMapiv = (PFNGLGETMAPIVPROC) glad_gl_on_demand_loader("glGetMapiv");
    glad_glGetMapiv(target, query, v);
}
PFNGLGETMAPIVPROC glad_glGetMapiv = glad_on_demand_impl_glGetMapiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMaterialfv(GLenum face, GLenum pname, GLfloat * params) {
    glad_glGetMaterialfv = (PFNGLGETMATERIALFVPROC) glad_gl_on_demand_loader("glGetMaterialfv");
    glad_glGetMaterialfv(face, pname, params);
}
PFNGLGETMATERIALFVPROC glad_glGetMaterialfv = glad_on_demand_impl_glGetMaterialfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMaterialiv(GLenum face, GLenum pname, GLint * params) {
    glad_glGetMaterialiv = (PFNGLGETMATERIALIVPROC) glad_gl_on_demand_loader("glGetMaterialiv");
    glad_glGetMaterialiv(face, pname, params);
}
PFNGLGETMATERIALIVPROC glad_glGetMaterialiv = glad_on_demand_impl_glGetMaterialiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetPixelMapfv(GLenum map, GLfloat * values) {
    glad_glGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC) glad_gl_on_demand_loader("glGetPixelMapfv");
    glad_glGetPixelMapfv(map, values);
}
PFNGLGETPIXELMAPFVPROC glad_glGetPixelMapfv = glad_on_demand_impl_glGetPixelMapfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetPixelMapuiv(GLenum map, GLuint * values) {
    glad_glGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC) glad_gl_on_demand_loader("glGetPixelMapuiv");
    glad_glGetPixelMapuiv(map, values);
}
PFNGLGETPIXELMAPUIVPROC glad_glGetPixelMapuiv = glad_on_demand_impl_glGetPixelMapuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetPixelMapusv(GLenum map, GLushort * values) {
    glad_glGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC) glad_gl_on_demand_loader("glGetPixelMapusv");
    glad_glGetPixelMapusv(map, values);
}
PFNGLGETPIXELMAPUSVPROC glad_glGetPixelMapusv = glad_on_demand_impl_glGetPixelMapusv;
static void GLAD_API_PTR glad_on_demand_impl_glGetPointerv(GLenum pname, void ** params) {
    glad_glGetPointerv = (PFNGLGETPOINTERVPROC) glad_gl_on_demand_loader("glGetPointerv");
    glad_glGetPointerv(pname, params);
}
PFNGLGETPOINTERVPROC glad_glGetPointerv = glad_on_demand_impl_glGetPointerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetPolygonStipple(GLubyte * mask) {
    glad_glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC) glad_gl_on_demand_loader("glGetPolygonStipple");
    glad_glGetPolygonStipple(mask);
}
PFNGLGETPOLYGONSTIPPLEPROC glad_glGetPolygonStipple = glad_on_demand_impl_glGetPolygonStipple;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glad_gl_on_demand_loader("glGetProgramInfoLog");
    glad_glGetProgramInfoLog(program, bufSize, length, infoLog);
}
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = glad_on_demand_impl_glGetProgramInfoLog;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramiv(GLuint program, GLenum pname, GLint * params) {
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC) glad_gl_on_demand_loader("glGetProgramiv");
    glad_glGetProgramiv(program, pname, params);
}
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = glad_on_demand_impl_glGetProgramiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params) {
    glad_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) glad_gl_on_demand_loader("glGetQueryObjectiv");
    glad_glGetQueryObjectiv(id, pname, params);
}
PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv = glad_on_demand_impl_glGetQueryObjectiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params) {
    glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) glad_gl_on_demand_loader("glGetQueryObjectuiv");
    glad_glGetQueryObjectuiv(id, pname, params);
}
PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv = glad_on_demand_impl_glGetQueryObjectuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryiv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetQueryiv = (PFNGLGETQUERYIVPROC) glad_gl_on_demand_loader("glGetQueryiv");
    glad_glGetQueryiv(target, pname, params);
}
PFNGLGETQUERYIVPROC glad_glGetQueryiv = glad_on_demand_impl_glGetQueryiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) glad_gl_on_demand_loader("glGetRenderbufferParameteriv");
    glad_glGetRenderbufferParameteriv(target, pname, params);
}
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv = glad_on_demand_impl_glGetRenderbufferParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glad_gl_on_demand_loader("glGetShaderInfoLog");
    glad_glGetShaderInfoLog(shader, bufSize, length, infoLog);
}
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = glad_on_demand_impl_glGetShaderInfoLog;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) {
    glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) glad_gl_on_demand_loader("glGetShaderSource");
    glad_glGetShaderSource(shader, bufSize, length, source);
}
PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource = glad_on_demand_impl_glGetShaderSource;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderiv(GLuint shader, GLenum pname, GLint * params) {
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC) glad_gl_on_demand_loader("glGetShaderiv");
    glad_glGetShaderiv(shader, pname, params);
}
PFNGLGETSHADERIVPROC glad_glGetShaderiv = glad_on_demand_impl_glGetShaderiv;
static const GLubyte * GLAD_API_PTR glad_on_demand_impl_glGetString(GLenum name) {
    glad_glGetString = (PFNGLGETSTRINGPROC) glad_gl_on_demand_loader("glGetString");
    return glad_glGetString(name);
}
PFNGLGETSTRINGPROC glad_glGetString = glad_on_demand_impl_glGetString;
static const GLubyte * GLAD_API_PTR glad_on_demand_impl_glGetStringi(GLenum name, GLuint index) {
    glad_glGetStringi = (PFNGLGETSTRINGIPROC) glad_gl_on_demand_loader("glGetStringi");
    return glad_glGetStringi(name, index);
}
PFNGLGETSTRINGIPROC glad_glGetStringi = glad_on_demand_impl_glGetStringi;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexEnvfv(GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetTexEnvfv = (PFNGLGETTEXENVFVPROC) glad_gl_on_demand_loader("glGetTexEnvfv");
    glad_glGetTexEnvfv(target, pname, params);
}
PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv = glad_on_demand_impl_glGetTexEnvfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexEnviv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexEnviv = (PFNGLGETTEXENVIVPROC) glad_gl_on_demand_loader("glGetTexEnviv");
    glad_glGetTexEnviv(target, pname, params);
}
PFNGLGETTEXENVIVPROC glad_glGetTexEnviv = glad_on_demand_impl_glGetTexEnviv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexGendv(GLenum coord, GLenum pname, GLdouble * params) {
    glad_glGetTexGendv = (PFNGLGETTEXGENDVPROC) glad_gl_on_demand_loader("glGetTexGendv");
    glad_glGetTexGendv(coord, pname, params);
}
PFNGLGETTEXGENDVPROC glad_glGetTexGendv = glad_on_demand_impl_glGetTexGendv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexGenfv(GLenum coord, GLenum pname, GLfloat * params) {
    glad_glGetTexGenfv = (PFNGLGETTEXGENFVPROC) glad_gl_on_demand_loader("glGetTexGenfv");
    glad_glGetTexGenfv(coord, pname, params);
}
PFNGLGETTEXGENFVPROC glad_glGetTexGenfv = glad_on_demand_impl_glGetTexGenfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexGeniv(GLenum coord, GLenum pname, GLint * params) {
    glad_glGetTexGeniv = (PFNGLGETTEXGENIVPROC) glad_gl_on_demand_loader("glGetTexGeniv");
    glad_glGetTexGeniv(coord, pname, params);
}
PFNGLGETTEXGENIVPROC glad_glGetTexGeniv = glad_on_demand_impl_glGetTexGeniv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    glad_glGetTexImage = (PFNGLGETTEXIMAGEPROC) glad_gl_on_demand_loader("glGetTexImage");
    glad_glGetTexImage(target, level, format, type, pixels);
}
PFNGLGETTEXIMAGEPROC glad_glGetTexImage = glad_on_demand_impl_glGetTexImage;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) {
    glad_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) glad_gl_on_demand_loader("glGetTexLevelParameterfv");
    glad_glGetTexLevelParameterfv(target, level, pname, params);
}
PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv = glad_on_demand_impl_glGetTexLevelParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) {
    glad_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) glad_gl_on_demand_loader("glGetTexLevelParameteriv");
    glad_glGetTexLevelParameteriv(target, level, pname, params);
}
PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv = glad_on_demand_impl_glGetTexLevelParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) glad_gl_on_demand_loader("glGetTexParameterIiv");
    glad_glGetTexParameterIiv(target, pname, params);
}
PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv = glad_on_demand_impl_glGetTexParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params) {
    glad_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) glad_gl_on_demand_loader("glGetTexParameterIuiv");
    glad_glGetTexParameterIuiv(target, pname, params);
}
PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv = glad_on_demand_impl_glGetTexParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) glad_gl_on_demand_loader("glGetTexParameterfv");
    glad_glGetTexParameterfv(target, pname, params);
}
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv = glad_on_demand_impl_glGetTexParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) glad_gl_on_demand_loader("glGetTexParameteriv");
    glad_glGetTexParameteriv(target, pname, params);
}
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv = glad_on_demand_impl_glGetTexParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) {
    glad_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) glad_gl_on_demand_loader("glGetTransformFeedbackVarying");
    glad_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying = glad_on_demand_impl_glGetTransformFeedbackVarying;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetUniformLocation(GLuint program, const GLchar * name) {
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glad_gl_on_demand_loader("glGetUniformLocation");
    return glad_glGetUniformLocation(program, name);
}
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = glad_on_demand_impl_glGetUniformLocation;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformfv(GLuint program, GLint location, GLfloat * params) {
    glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC) glad_gl_on_demand_loader("glGetUniformfv");
    glad_glGetUniformfv(program, location, params);
}
PFNGLGETUNIFORMFVPROC glad_glGetUniformfv = glad_on_demand_impl_glGetUniformfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformiv(GLuint program, GLint location, GLint * params) {
    glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC) glad_gl_on_demand_loader("glGetUniformiv");
    glad_glGetUniformiv(program, location, params);
}
PFNGLGETUNIFORMIVPROC glad_glGetUniformiv = glad_on_demand_impl_glGetUniformiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformuiv(GLuint program, GLint location, GLuint * params) {
    glad_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) glad_gl_on_demand_loader("glGetUniformuiv");
    glad_glGetUniformuiv(program, location, params);
}
PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv = glad_on_demand_impl_glGetUniformuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) glad_gl_on_demand_loader("glGetVertexAttribIiv");
    glad_glGetVertexAttribIiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv = glad_on_demand_impl_glGetVertexAttribIiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params) {
    glad_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) glad_gl_on_demand_loader("glGetVertexAttribIuiv");
    glad_glGetVertexAttribIuiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv = glad_on_demand_impl_glGetVertexAttribIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer) {
    glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) glad_gl_on_demand_loader("glGetVertexAttribPointerv");
    glad_glGetVertexAttribPointerv(index, pname, pointer);
}
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv = glad_on_demand_impl_glGetVertexAttribPointerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params) {
    glad_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) glad_gl_on_demand_loader("glGetVertexAttribdv");
    glad_glGetVertexAttribdv(index, pname, params);
}
PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv = glad_on_demand_impl_glGetVertexAttribdv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) {
    glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) glad_gl_on_demand_loader("glGetVertexAttribfv");
    glad_glGetVertexAttribfv(index, pname, params);
}
PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv = glad_on_demand_impl_glGetVertexAttribfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) glad_gl_on_demand_loader("glGetVertexAttribiv");
    glad_glGetVertexAttribiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv = glad_on_demand_impl_glGetVertexAttribiv;
static void GLAD_API_PTR glad_on_demand_impl_glHint(GLenum target, GLenum mode) {
    glad_glHint = (PFNGLHINTPROC) glad_gl_on_demand_loader("glHint");
    glad_glHint(target, mode);
}
PFNGLHINTPROC glad_glHint = glad_on_demand_impl_glHint;
static void GLAD_API_PTR glad_on_demand_impl_glIndexMask(GLuint mask) {
    glad_glIndexMask = (PFNGLINDEXMASKPROC) glad_gl_on_demand_loader("glIndexMask");
    glad_glIndexMask(mask);
}
PFNGLINDEXMASKPROC glad_glIndexMask = glad_on_demand_impl_glIndexMask;
static void GLAD_API_PTR glad_on_demand_impl_glIndexPointer(GLenum type, GLsizei stride, const void * pointer) {
    glad_glIndexPointer = (PFNGLINDEXPOINTERPROC) glad_gl_on_demand_loader("glIndexPointer");
    glad_glIndexPointer(type, stride, pointer);
}
PFNGLINDEXPOINTERPROC glad_glIndexPointer = glad_on_demand_impl_glIndexPointer;
static void GLAD_API_PTR glad_on_demand_impl_glIndexd(GLdouble c) {
    glad_glIndexd = (PFNGLINDEXDPROC) glad_gl_on_demand_loader("glIndexd");
    glad_glIndexd(c);
}
PFNGLINDEXDPROC glad_glIndexd = glad_on_demand_impl_glIndexd;
static void GLAD_API_PTR glad_on_demand_impl_glIndexdv(const GLdouble * c) {
    glad_glIndexdv = (PFNGLINDEXDVPROC) glad_gl_on_demand_loader("glIndexdv");
    glad_glIndexdv(c);
}
PFNGLINDEXDVPROC glad_glIndexdv = glad_on_demand_impl_glIndexdv;
static void GLAD_API_PTR glad_on_demand_impl_glIndexf(GLfloat c) {
    glad_glIndexf = (PFNGLINDEXFPROC) glad_gl_on_demand_loader("glIndexf");
    glad_glIndexf(c);
}
PFNGLINDEXFPROC glad_glIndexf = glad_on_demand_impl_glIndexf;
static void GLAD_API_PTR glad_on_demand_impl_glIndexfv(const GLfloat * c) {
    glad_glIndexfv = (PFNGLINDEXFVPROC) glad_gl_on_demand_loader("glIndexfv");
    glad_glIndexfv(c);
}
PFNGLINDEXFVPROC glad_glIndexfv = glad_on_demand_impl_glIndexfv;
static void GLAD_API_PTR glad_on_demand_impl_glIndexi(GLint c) {
    glad_glIndexi = (PFNGLINDEXIPROC) glad_gl_on_demand_loader("glIndexi");
    glad_glIndexi(c);
}
PFNGLINDEXIPROC glad_glIndexi = glad_on_demand_impl_glIndexi;
static void GLAD_API_PTR glad_on_demand_impl_glIndexiv(const GLint * c) {
    glad_glIndexiv = (PFNGLINDEXIVPROC) glad_gl_on_demand_loader("glIndexiv");
    glad_glIndexiv(c);
}
PFNGLINDEXIVPROC glad_glIndexiv = glad_on_demand_impl_glIndexiv;
static void GLAD_API_PTR glad_on_demand_impl_glIndexs(GLshort c) {
    glad_glIndexs = (PFNGLINDEXSPROC) glad_gl_on_demand_loader("glIndexs");
    glad_glIndexs(c);
}
PFNGLINDEXSPROC glad_glIndexs = glad_on_demand_impl_glIndexs;
static void GLAD_API_PTR glad_on_demand_impl_glIndexsv(const GLshort * c) {
    glad_glIndexsv = (PFNGLINDEXSVPROC) glad_gl_on_demand_loader("glIndexsv");
    glad_glIndexsv(c);
}
PFNGLINDEXSVPROC glad_glIndexsv = glad_on_demand_impl_glIndexsv;
static void GLAD_API_PTR glad_on_demand_impl_glIndexub(GLubyte c) {
    glad_glIndexub = (PFNGLINDEXUBPROC) glad_gl_on_demand_loader("glIndexub");
    glad_glIndexub(c);
}
PFNGLINDEXUBPROC glad_glIndexub = glad_on_demand_impl_glIndexub;
static void GLAD_API_PTR glad_on_demand_impl_glIndexubv(const GLubyte * c) {
    glad_glIndexubv = (PFNGLINDEXUBVPROC) glad_gl_on_demand_loader("glIndexubv");
    glad_glIndexubv(c);
}
PFNGLINDEXUBVPROC glad_glIndexubv = glad_on_demand_impl_glIndexubv;
static void GLAD_API_PTR glad_on_demand_impl_glInitNames(void) {
    glad_glInitNames = (PFNGLINITNAMESPROC) glad_gl_on_demand_loader("glInitNames");
    glad_glInitNames();
}
PFNGLINITNAMESPROC glad_glInitNames = glad_on_demand_impl_glInitNames;
static void GLAD_API_PTR glad_on_demand_impl_glInterleavedArrays(GLenum format, GLsizei stride, const void * pointer) {
    glad_glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC) glad_gl_on_demand_loader("glInterleavedArrays");
    glad_glInterleavedArrays(format, stride, pointer);
}
PFNGLINTERLEAVEDARRAYSPROC glad_glInterleavedArrays = glad_on_demand_impl_glInterleavedArrays;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsBuffer(GLuint buffer) {
    glad_glIsBuffer = (PFNGLISBUFFERPROC) glad_gl_on_demand_loader("glIsBuffer");
    return glad_glIsBuffer(buffer);
}
PFNGLISBUFFERPROC glad_glIsBuffer = glad_on_demand_impl_glIsBuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsEnabled(GLenum cap) {
    glad_glIsEnabled = (PFNGLISENABLEDPROC) glad_gl_on_demand_loader("glIsEnabled");
    return glad_glIsEnabled(cap);
}
PFNGLISENABLEDPROC glad_glIsEnabled = glad_on_demand_impl_glIsEnabled;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsEnabledi(GLenum target, GLuint index) {
    glad_glIsEnabledi = (PFNGLISENABLEDIPROC) glad_gl_on_demand_loader("glIsEnabledi");
    return glad_glIsEnabledi(target, index);
}
PFNGLISENABLEDIPROC glad_glIsEnabledi = glad_on_demand_impl_glIsEnabledi;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsFramebuffer(GLuint framebuffer) {
    glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) glad_gl_on_demand_loader("glIsFramebuffer");
    return glad_glIsFramebuffer(framebuffer);
}
PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer = glad_on_demand_impl_glIsFramebuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsList(GLuint list) {
    glad_glIsList = (PFNGLISLISTPROC) glad_gl_on_demand_loader("glIsList");
    return glad_glIsList(list);
}
PFNGLISLISTPROC glad_glIsList = glad_on_demand_impl_glIsList;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsProgram(GLuint program) {
    glad_glIsProgram = (PFNGLISPROGRAMPROC) glad_gl_on_demand_loader("glIsProgram");
    return glad_glIsProgram(program);
}
PFNGLISPROGRAMPROC glad_glIsProgram = glad_on_demand_impl_glIsProgram;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsQuery(GLuint id) {
    glad_glIsQuery = (PFNGLISQUERYPROC) glad_gl_on_demand_loader("glIsQuery");
    return glad_glIsQuery(id);
}
PFNGLISQUERYPROC glad_glIsQuery = glad_on_demand_impl_glIsQuery;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsRenderbuffer(GLuint renderbuffer) {
    glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) glad_gl_on_demand_loader("glIsRenderbuffer");
    return glad_glIsRenderbuffer(renderbuffer);
}
PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer = glad_on_demand_impl_glIsRenderbuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsShader(GLuint shader) {
    glad_glIsShader = (PFNGLISSHADERPROC) glad_gl_on_demand_loader("glIsShader");
    return glad_glIsShader(shader);
}
PFNGLISSHADERPROC glad_glIsShader = glad_on_demand_impl_glIsShader;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsTexture(GLuint texture) {
    glad_glIsTexture = (PFNGLISTEXTUREPROC) glad_gl_on_demand_loader("glIsTexture");
    return glad_glIsTexture(texture);
}
PFNGLISTEXTUREPROC glad_glIsTexture = glad_on_demand_impl_glIsTexture;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsVertexArray(GLuint array) {
    glad_glIsVertexArray = (PFNGLISVERTEXARRAYPROC) glad_gl_on_demand_loader("glIsVertexArray");
    return glad_glIsVertexArray(array);
}
PFNGLISVERTEXARRAYPROC glad_glIsVertexArray = glad_on_demand_impl_glIsVertexArray;
static void GLAD_API_PTR glad_on_demand_impl_glLightModelf(GLenum pname, GLfloat param) {
    glad_glLightModelf = (PFNGLLIGHTMODELFPROC) glad_gl_on_demand_loader("glLightModelf");
    glad_glLightModelf(pname, param);
}
PFNGLLIGHTMODELFPROC glad_glLightModelf = glad_on_demand_impl_glLightModelf;
static void GLAD_API_PTR glad_on_demand_impl_glLightModelfv(GLenum pname, const GLfloat * params) {
    glad_glLightModelfv = (PFNGLLIGHTMODELFVPROC) glad_gl_on_demand_loader("glLightModelfv");
    glad_glLightModelfv(pname, params);
}
PFNGLLIGHTMODELFVPROC glad_glLightModelfv = glad_on_demand_impl_glLightModelfv;
static void GLAD_API_PTR glad_on_demand_impl_glLightModeli(GLenum pname, GLint param) {
    glad_glLightModeli = (PFNGLLIGHTMODELIPROC) glad_gl_on_demand_loader("glLightModeli");
    glad_glLightModeli(pname, param);
}
PFNGLLIGHTMODELIPROC glad_glLightModeli = glad_on_demand_impl_glLightModeli;
static void GLAD_API_PTR glad_on_demand_impl_glLightModeliv(GLenum pname, const GLint * params) {
    glad_glLightModeliv = (PFNGLLIGHTMODELIVPROC) glad_gl_on_demand_loader("glLightModeliv");
    glad_glLightModeliv(pname, params);
}
PFNGLLIGHTMODELIVPROC glad_glLightModeliv = glad_on_demand_impl_glLightModeliv;
static void GLAD_API_PTR glad_on_demand_impl_glLightf(GLenum light, GLenum pname, GLfloat param) {
    glad_glLightf = (PFNGLLIGHTFPROC) glad_gl_on_demand_loader("glLightf");
    glad_glLightf(light, pname, param);
}
PFNGLLIGHTFPROC glad_glLightf = glad_on_demand_impl_glLightf;
static void GLAD_API_PTR glad_on_demand_impl_glLightfv(GLenum light, GLenum pname, const GLfloat * params) {
    glad_glLightfv = (PFNGLLIGHTFVPROC) glad_gl_on_demand_loader("glLightfv");
    glad_glLightfv(light, pname, params);
}
PFNGLLIGHTFVPROC glad_glLightfv = glad_on_demand_impl_glLightfv;
static void GLAD_API_PTR glad_on_demand_impl_glLighti(GLenum light, GLenum pname, GLint param) {
    glad_glLighti = (PFNGLLIGHTIPROC) glad_gl_on_demand_loader("glLighti");
    glad_glLighti(light, pname, param);
}
PFNGLLIGHTIPROC glad_glLighti = glad_on_demand_impl_glLighti;
static void GLAD_API_PTR glad_on_demand_impl_glLightiv(GLenum light, GLenum pname, const GLint * params) {
    glad_glLightiv = (PFNGLLIGHTIVPROC) glad_gl_on_demand_loader("glLightiv");
    glad_glLightiv(light, pname, params);
}
PFNGLLIGHTIVPROC glad_glLightiv = glad_on_demand_impl_glLightiv;
static void GLAD_API_PTR glad_on_demand_impl_glLineStipple(GLint factor, GLushort pattern) {
    glad_glLineStipple = (PFNGLLINESTIPPLEPROC) glad_gl_on_demand_loader("glLineStipple");
    glad_glLineStipple(factor, pattern);
}
PFNGLLINESTIPPLEPROC glad_glLineStipple = glad_on_demand_impl_glLineStipple;
static void GLAD_API_PTR glad_on_demand_impl_glLineWidth(GLfloat width) {
    glad_glLineWidth = (PFNGLLINEWIDTHPROC) glad_gl_on_demand_loader("glLineWidth");
    glad_glLineWidth(width);
}
PFNGLLINEWIDTHPROC glad_glLineWidth = glad_on_demand_impl_glLineWidth;
static void GLAD_API_PTR glad_on_demand_impl_glLinkProgram(GLuint program) {
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC) glad_gl_on_demand_loader("glLinkProgram");
    glad_glLinkProgram(program);
}
PFNGLLINKPROGRAMPROC glad_glLinkProgram = glad_on_demand_impl_glLinkProgram;
static void GLAD_API_PTR glad_on_demand_impl_glListBase(GLuint base) {
    glad_glListBase = (PFNGLLISTBASEPROC) glad_gl_on_demand_loader("glListBase");
    glad_glListBase(base);
}
PFNGLLISTBASEPROC glad_glListBase = glad_on_demand_impl_glListBase;
static void GLAD_API_PTR glad_on_demand_impl_glLoadIdentity(void) {
    glad_glLoadIdentity = (PFNGLLOADIDENTITYPROC) glad_gl_on_demand_loader("glLoadIdentity");
    glad_glLoadIdentity();
}
PFNGLLOADIDENTITYPROC glad_glLoadIdentity = glad_on_demand_impl_glLoadIdentity;
static void GLAD_API_PTR glad_on_demand_impl_glLoadMatrixd(const GLdouble * m) {
    glad_glLoadMatrixd = (PFNGLLOADMATRIXDPROC) glad_gl_on_demand_loader("glLoadMatrixd");
    glad_glLoadMatrixd(m);
}
PFNGLLOADMATRIXDPROC glad_glLoadMatrixd = glad_on_demand_impl_glLoadMatrixd;
static void GLAD_API_PTR glad_on_demand_impl_glLoadMatrixf(const GLfloat * m) {
    glad_glLoadMatrixf = (PFNGLLOADMATRIXFPROC) glad_gl_on_demand_loader("glLoadMatrixf");
    glad_glLoadMatrixf(m);
}
PFNGLLOADMATRIXFPROC glad_glLoadMatrixf = glad_on_demand_impl_glLoadMatrixf;
static void GLAD_API_PTR glad_on_demand_impl_glLoadName(GLuint name) {
    glad_glLoadName = (PFNGLLOADNAMEPROC) glad_gl_on_demand_loader("glLoadName");
    glad_glLoadName(name);
}
PFNGLLOADNAMEPROC glad_glLoadName = glad_on_demand_impl_glLoadName;
static void GLAD_API_PTR glad_on_demand_impl_glLoadTransposeMatrixd(const GLdouble * m) {
    glad_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC) glad_gl_on_demand_loader("glLoadTransposeMatrixd");
    glad_glLoadTransposeMatrixd(m);
}
PFNGLLOADTRANSPOSEMATRIXDPROC glad_glLoadTransposeMatrixd = glad_on_demand_impl_glLoadTransposeMatrixd;
static void GLAD_API_PTR glad_on_demand_impl_glLoadTransposeMatrixf(const GLfloat * m) {
    glad_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC) glad_gl_on_demand_loader("glLoadTransposeMatrixf");
    glad_glLoadTransposeMatrixf(m);
}
PFNGLLOADTRANSPOSEMATRIXFPROC glad_glLoadTransposeMatrixf = glad_on_demand_impl_glLoadTransposeMatrixf;
static void GLAD_API_PTR glad_on_demand_impl_glLogicOp(GLenum opcode) {
    glad_glLogicOp = (PFNGLLOGICOPPROC) glad_gl_on_demand_loader("glLogicOp");
    glad_glLogicOp(opcode);
}
PFNGLLOGICOPPROC glad_glLogicOp = glad_on_demand_impl_glLogicOp;
static void GLAD_API_PTR glad_on_demand_impl_glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points) {
    glad_glMap1d = (PFNGLMAP1DPROC) glad_gl_on_demand_loader("glMap1d");
    glad_glMap1d(target, u1, u2, stride, order, points);
}
PFNGLMAP1DPROC glad_glMap1d = glad_on_demand_impl_glMap1d;
static void GLAD_API_PTR glad_on_demand_impl_glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points) {
    glad_glMap1f = (PFNGLMAP1FPROC) glad_gl_on_demand_loader("glMap1f");
    glad_glMap1f(target, u1, u2, stride, order, points);
}
PFNGLMAP1FPROC glad_glMap1f = glad_on_demand_impl_glMap1f;
static void GLAD_API_PTR glad_on_demand_impl_glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points) {
    glad_glMap2d = (PFNGLMAP2DPROC) glad_gl_on_demand_loader("glMap2d");
    glad_glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}
PFNGLMAP2DPROC glad_glMap2d = glad_on_demand_impl_glMap2d;
static void GLAD_API_PTR glad_on_demand_impl_glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points) {
    glad_glMap2f = (PFNGLMAP2FPROC) glad_gl_on_demand_loader("glMap2f");
    glad_glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}
PFNGLMAP2FPROC glad_glMap2f = glad_on_demand_impl_glMap2f;
static void * GLAD_API_PTR glad_on_demand_impl_glMapBuffer(GLenum target, GLenum access) {
    glad_glMapBuffer = (PFNGLMAPBUFFERPROC) glad_gl_on_demand_loader("glMapBuffer");
    return glad_glMapBuffer(target, access);
}
PFNGLMAPBUFFERPROC glad_glMapBuffer = glad_on_demand_impl_glMapBuffer;
static void * GLAD_API_PTR glad_on_demand_impl_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
    glad_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) glad_gl_on_demand_loader("glMapBufferRange");
    return glad_glMapBufferRange(target, offset, length, access);
}
PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange = glad_on_demand_impl_glMapBufferRange;
static void GLAD_API_PTR glad_on_demand_impl_glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
    glad_glMapGrid1d = (PFNGLMAPGRID1DPROC) glad_gl_on_demand_loader("glMapGrid1d");
    glad_glMapGrid1d(un, u1, u2);
}
PFNGLMAPGRID1DPROC glad_glMapGrid1d = glad_on_demand_impl_glMapGrid1d;
static void GLAD_API_PTR glad_on_demand_impl_glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
    glad_glMapGrid1f = (PFNGLMAPGRID1FPROC) glad_gl_on_demand_loader("glMapGrid1f");
    glad_glMapGrid1f(un, u1, u2);
}
PFNGLMAPGRID1FPROC glad_glMapGrid1f = glad_on_demand_impl_glMapGrid1f;
static void GLAD_API_PTR glad_on_demand_impl_glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) {
    glad_glMapGrid2d = (PFNGLMAPGRID2DPROC) glad_gl_on_demand_loader("glMapGrid2d");
    glad_glMapGrid2d(un, u1, u2, vn, v1, v2);
}
PFNGLMAPGRID2DPROC glad_glMapGrid2d = glad_on_demand_impl_glMapGrid2d;
static void GLAD_API_PTR glad_on_demand_impl_glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
    glad_glMapGrid2f = (PFNGLMAPGRID2FPROC) glad_gl_on_demand_loader("glMapGrid2f");
    glad_glMapGrid2f(un, u1, u2, vn, v1, v2);
}
PFNGLMAPGRID2FPROC glad_glMapGrid2f = glad_on_demand_impl_glMapGrid2f;
static void GLAD_API_PTR glad_on_demand_impl_glMaterialf(GLenum face, GLenum pname, GLfloat param) {
    glad_glMaterialf = (PFNGLMATERIALFPROC) glad_gl_on_demand_loader("glMaterialf");
    glad_glMaterialf(face, pname, param);
}
PFNGLMATERIALFPROC glad_glMaterialf = glad_on_demand_impl_glMaterialf;
static void GLAD_API_PTR glad_on_demand_impl_glMaterialfv(GLenum face, GLenum pname, const GLfloat * params) {
    glad_glMaterialfv = (PFNGLMATERIALFVPROC) glad_gl_on_demand_loader("glMaterialfv");
    glad_glMaterialfv(face, pname, params);
}
PFNGLMATERIALFVPROC glad_glMaterialfv = glad_on_demand_impl_glMaterialfv;
static void GLAD_API_PTR glad_on_demand_impl_glMateriali(GLenum face, GLenum pname, GLint param) {
    glad_glMateriali = (PFNGLMATERIALIPROC) glad_gl_on_demand_loader("glMateriali");
    glad_glMateriali(face, pname, param);
}
PFNGLMATERIALIPROC glad_glMateriali = glad_on_demand_impl_glMateriali;
static void GLAD_API_PTR glad_on_demand_impl_glMaterialiv(GLenum face, GLenum pname, const GLint * params) {
    glad_glMaterialiv = (PFNGLMATERIALIVPROC) glad_gl_on_demand_loader("glMaterialiv");
    glad_glMaterialiv(face, pname, params);
}
PFNGLMATERIALIVPROC glad_glMaterialiv = glad_on_demand_impl_glMaterialiv;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixMode(GLenum mode) {
    glad_glMatrixMode = (PFNGLMATRIXMODEPROC) glad_gl_on_demand_loader("glMatrixMode");
    glad_glMatrixMode(mode);
}
PFNGLMATRIXMODEPROC glad_glMatrixMode = glad_on_demand_impl_glMatrixMode;
static void GLAD_API_PTR glad_on_demand_impl_glMultMatrixd(const GLdouble * m) {
    glad_glMultMatrixd = (PFNGLMULTMATRIXDPROC) glad_gl_on_demand_loader("glMultMatrixd");
    glad_glMultMatrixd(m);
}
PFNGLMULTMATRIXDPROC glad_glMultMatrixd = glad_on_demand_impl_glMultMatrixd;
static void GLAD_API_PTR glad_on_demand_impl_glMultMatrixf(const GLfloat * m) {
    glad_glMultMatrixf = (PFNGLMULTMATRIXFPROC) glad_gl_on_demand_loader("glMultMatrixf");
    glad_glMultMatrixf(m);
}
PFNGLMULTMATRIXFPROC glad_glMultMatrixf = glad_on_demand_impl_glMultMatrixf;
static void GLAD_API_PTR glad_on_demand_impl_glMultTransposeMatrixd(const GLdouble * m) {
    glad_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC) glad_gl_on_demand_loader("glMultTransposeMatrixd");
    glad_glMultTransposeMatrixd(m);
}
PFNGLMULTTRANSPOSEMATRIXDPROC glad_glMultTransposeMatrixd = glad_on_demand_impl_glMultTransposeMatrixd;
static void GLAD_API_PTR glad_on_demand_impl_glMultTransposeMatrixf(const GLfloat * m) {
    glad_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC) glad_gl_on_demand_loader("glMultTransposeMatrixf");
    glad_glMultTransposeMatrixf(m);
}
PFNGLMULTTRANSPOSEMATRIXFPROC glad_glMultTransposeMatrixf = glad_on_demand_impl_glMultTransposeMatrixf;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount) {
    glad_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) glad_gl_on_demand_loader("glMultiDrawArrays");
    glad_glMultiDrawArrays(mode, first, count, drawcount);
}
PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays = glad_on_demand_impl_glMultiDrawArrays;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount) {
    glad_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) glad_gl_on_demand_loader("glMultiDrawElements");
    glad_glMultiDrawElements(mode, count, type, indices, drawcount);
}
PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements = glad_on_demand_impl_glMultiDrawElements;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1d(GLenum target, GLdouble s) {
    glad_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC) glad_gl_on_demand_loader("glMultiTexCoord1d");
    glad_glMultiTexCoord1d(target, s);
}
PFNGLMULTITEXCOORD1DPROC glad_glMultiTexCoord1d = glad_on_demand_impl_glMultiTexCoord1d;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1dv(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC) glad_gl_on_demand_loader("glMultiTexCoord1dv");
    glad_glMultiTexCoord1dv(target, v);
}
PFNGLMULTITEXCOORD1DVPROC glad_glMultiTexCoord1dv = glad_on_demand_impl_glMultiTexCoord1dv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1f(GLenum target, GLfloat s) {
    glad_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC) glad_gl_on_demand_loader("glMultiTexCoord1f");
    glad_glMultiTexCoord1f(target, s);
}
PFNGLMULTITEXCOORD1FPROC glad_glMultiTexCoord1f = glad_on_demand_impl_glMultiTexCoord1f;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1fv(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC) glad_gl_on_demand_loader("glMultiTexCoord1fv");
    glad_glMultiTexCoord1fv(target, v);
}
PFNGLMULTITEXCOORD1FVPROC glad_glMultiTexCoord1fv = glad_on_demand_impl_glMultiTexCoord1fv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1i(GLenum target, GLint s) {
    glad_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC) glad_gl_on_demand_loader("glMultiTexCoord1i");
    glad_glMultiTexCoord1i(target, s);
}
PFNGLMULTITEXCOORD1IPROC glad_glMultiTexCoord1i = glad_on_demand_impl_glMultiTexCoord1i;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1iv(GLenum target, const GLint * v) {
    glad_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC) glad_gl_on_demand_loader("glMultiTexCoord1iv");
    glad_glMultiTexCoord1iv(target, v);
}
PFNGLMULTITEXCOORD1IVPROC glad_glMultiTexCoord1iv = glad_on_demand_impl_glMultiTexCoord1iv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1s(GLenum target, GLshort s) {
    glad_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC) glad_gl_on_demand_loader("glMultiTexCoord1s");
    glad_glMultiTexCoord1s(target, s);
}
PFNGLMULTITEXCOORD1SPROC glad_glMultiTexCoord1s = glad_on_demand_impl_glMultiTexCoord1s;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1sv(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC) glad_gl_on_demand_loader("glMultiTexCoord1sv");
    glad_glMultiTexCoord1sv(target, v);
}
PFNGLMULTITEXCOORD1SVPROC glad_glMultiTexCoord1sv = glad_on_demand_impl_glMultiTexCoord1sv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t) {
    glad_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC) glad_gl_on_demand_loader("glMultiTexCoord2d");
    glad_glMultiTexCoord2d(target, s, t);
}
PFNGLMULTITEXCOORD2DPROC glad_glMultiTexCoord2d = glad_on_demand_impl_glMultiTexCoord2d;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2dv(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC) glad_gl_on_demand_loader("glMultiTexCoord2dv");
    glad_glMultiTexCoord2dv(target, v);
}
PFNGLMULTITEXCOORD2DVPROC glad_glMultiTexCoord2dv = glad_on_demand_impl_glMultiTexCoord2dv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t) {
    glad_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC) glad_gl_on_demand_loader("glMultiTexCoord2f");
    glad_glMultiTexCoord2f(target, s, t);
}
PFNGLMULTITEXCOORD2FPROC glad_glMultiTexCoord2f = glad_on_demand_impl_glMultiTexCoord2f;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2fv(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC) glad_gl_on_demand_loader("glMultiTexCoord2fv");
    glad_glMultiTexCoord2fv(target, v);
}
PFNGLMULTITEXCOORD2FVPROC glad_glMultiTexCoord2fv = glad_on_demand_impl_glMultiTexCoord2fv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2i(GLenum target, GLint s, GLint t) {
    glad_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC) glad_gl_on_demand_loader("glMultiTexCoord2i");
    glad_glMultiTexCoord2i(target, s, t);
}
PFNGLMULTITEXCOORD2IPROC glad_glMultiTexCoord2i = glad_on_demand_impl_glMultiTexCoord2i;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2iv(GLenum target, const GLint * v) {
    glad_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC) glad_gl_on_demand_loader("glMultiTexCoord2iv");
    glad_glMultiTexCoord2iv(target, v);
}
PFNGLMULTITEXCOORD2IVPROC glad_glMultiTexCoord2iv = glad_on_demand_impl_glMultiTexCoord2iv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2s(GLenum target, GLshort s, GLshort t) {
    glad_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC) glad_gl_on_demand_loader("glMultiTexCoord2s");
    glad_glMultiTexCoord2s(target, s, t);
}
PFNGLMULTITEXCOORD2SPROC glad_glMultiTexCoord2s = glad_on_demand_impl_glMultiTexCoord2s;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2sv(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC) glad_gl_on_demand_loader("glMultiTexCoord2sv");
    glad_glMultiTexCoord2sv(target, v);
}
PFNGLMULTITEXCOORD2SVPROC glad_glMultiTexCoord2sv = glad_on_demand_impl_glMultiTexCoord2sv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r) {
    glad_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC) glad_gl_on_demand_loader("glMultiTexCoord3d");
    glad_glMultiTexCoord3d(target, s, t, r);
}
PFNGLMULTITEXCOORD3DPROC glad_glMultiTexCoord3d = glad_on_demand_impl_glMultiTexCoord3d;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3dv(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC) glad_gl_on_demand_loader("glMultiTexCoord3dv");
    glad_glMultiTexCoord3dv(target, v);
}
PFNGLMULTITEXCOORD3DVPROC glad_glMultiTexCoord3dv = glad_on_demand_impl_glMultiTexCoord3dv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r) {
    glad_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC) glad_gl_on_demand_loader("glMultiTexCoord3f");
    glad_glMultiTexCoord3f(target, s, t, r);
}
PFNGLMULTITEXCOORD3FPROC glad_glMultiTexCoord3f = glad_on_demand_impl_glMultiTexCoord3f;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3fv(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC) glad_gl_on_demand_loader("glMultiTexCoord3fv");
    glad_glMultiTexCoord3fv(target, v);
}
PFNGLMULTITEXCOORD3FVPROC glad_glMultiTexCoord3fv = glad_on_demand_impl_glMultiTexCoord3fv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r) {
    glad_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC) glad_gl_on_demand_loader("glMultiTexCoord3i");
    glad_glMultiTexCoord3i(target, s, t, r);
}
PFNGLMULTITEXCOORD3IPROC glad_glMultiTexCoord3i = glad_on_demand_impl_glMultiTexCoord3i;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3iv(GLenum target, const GLint * v) {
    glad_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC) glad_gl_on_demand_loader("glMultiTexCoord3iv");
    glad_glMultiTexCoord3iv(target, v);
}
PFNGLMULTITEXCOORD3IVPROC glad_glMultiTexCoord3iv = glad_on_demand_impl_glMultiTexCoord3iv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r) {
    glad_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC) glad_gl_on_demand_loader("glMultiTexCoord3s");
    glad_glMultiTexCoord3s(target, s, t, r);
}
PFNGLMULTITEXCOORD3SPROC glad_glMultiTexCoord3s = glad_on_demand_impl_glMultiTexCoord3s;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3sv(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC) glad_gl_on_demand_loader("glMultiTexCoord3sv");
    glad_glMultiTexCoord3sv(target, v);
}
PFNGLMULTITEXCOORD3SVPROC glad_glMultiTexCoord3sv = glad_on_demand_impl_glMultiTexCoord3sv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    glad_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC) glad_gl_on_demand_loader("glMultiTexCoord4d");
    glad_glMultiTexCoord4d(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4DPROC glad_glMultiTexCoord4d = glad_on_demand_impl_glMultiTexCoord4d;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4dv(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC) glad_gl_on_demand_loader("glMultiTexCoord4dv");
    glad_glMultiTexCoord4dv(target, v);
}
PFNGLMULTITEXCOORD4DVPROC glad_glMultiTexCoord4dv = glad_on_demand_impl_glMultiTexCoord4dv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    glad_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC) glad_gl_on_demand_loader("glMultiTexCoord4f");
    glad_glMultiTexCoord4f(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f = glad_on_demand_impl_glMultiTexCoord4f;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4fv(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC) glad_gl_on_demand_loader("glMultiTexCoord4fv");
    glad_glMultiTexCoord4fv(target, v);
}
PFNGLMULTITEXCOORD4FVPROC glad_glMultiTexCoord4fv = glad_on_demand_impl_glMultiTexCoord4fv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q) {
    glad_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC) glad_gl_on_demand_loader("glMultiTexCoord4i");
    glad_glMultiTexCoord4i(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4IPROC glad_glMultiTexCoord4i = glad_on_demand_impl_glMultiTexCoord4i;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4iv(GLenum target, const GLint * v) {
    glad_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC) glad_gl_on_demand_loader("glMultiTexCoord4iv");
    glad_glMultiTexCoord4iv(target, v);
}
PFNGLMULTITEXCOORD4IVPROC glad_glMultiTexCoord4iv = glad_on_demand_impl_glMultiTexCoord4iv;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) {
    glad_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC) glad_gl_on_demand_loader("glMultiTexCoord4s");
    glad_glMultiTexCoord4s(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4SPROC glad_glMultiTexCoord4s = glad_on_demand_impl_glMultiTexCoord4s;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4sv(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC) glad_gl_on_demand_loader("glMultiTexCoord4sv");
    glad_glMultiTexCoord4sv(target, v);
}
PFNGLMULTITEXCOORD4SVPROC glad_glMultiTexCoord4sv = glad_on_demand_impl_glMultiTexCoord4sv;
static void GLAD_API_PTR glad_on_demand_impl_glNewList(GLuint list, GLenum mode) {
    glad_glNewList = (PFNGLNEWLISTPROC) glad_gl_on_demand_loader("glNewList");
    glad_glNewList(list, mode);
}
PFNGLNEWLISTPROC glad_glNewList = glad_on_demand_impl_glNewList;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
    glad_glNormal3b = (PFNGLNORMAL3BPROC) glad_gl_on_demand_loader("glNormal3b");
    glad_glNormal3b(nx, ny, nz);
}
PFNGLNORMAL3BPROC glad_glNormal3b = glad_on_demand_impl_glNormal3b;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3bv(const GLbyte * v) {
    glad_glNormal3bv = (PFNGLNORMAL3BVPROC) glad_gl_on_demand_loader("glNormal3bv");
    glad_glNormal3bv(v);
}
PFNGLNORMAL3BVPROC glad_glNormal3bv = glad_on_demand_impl_glNormal3bv;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
    glad_glNormal3d = (PFNGLNORMAL3DPROC) glad_gl_on_demand_loader("glNormal3d");
    glad_glNormal3d(nx, ny, nz);
}
PFNGLNORMAL3DPROC glad_glNormal3d = glad_on_demand_impl_glNormal3d;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3dv(const GLdouble * v) {
    glad_glNormal3dv = (PFNGLNORMAL3DVPROC) glad_gl_on_demand_loader("glNormal3dv");
    glad_glNormal3dv(v);
}
PFNGLNORMAL3DVPROC glad_glNormal3dv = glad_on_demand_impl_glNormal3dv;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
    glad_glNormal3f = (PFNGLNORMAL3FPROC) glad_gl_on_demand_loader("glNormal3f");
    glad_glNormal3f(nx, ny, nz);
}
PFNGLNORMAL3FPROC glad_glNormal3f = glad_on_demand_impl_glNormal3f;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3fv(const GLfloat * v) {
    glad_glNormal3fv = (PFNGLNORMAL3FVPROC) glad_gl_on_demand_loader("glNormal3fv");
    glad_glNormal3fv(v);
}
PFNGLNORMAL3FVPROC glad_glNormal3fv = glad_on_demand_impl_glNormal3fv;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3i(GLint nx, GLint ny, GLint nz) {
    glad_glNormal3i = (PFNGLNORMAL3IPROC) glad_gl_on_demand_loader("glNormal3i");
    glad_glNormal3i(nx, ny, nz);
}
PFNGLNORMAL3IPROC glad_glNormal3i = glad_on_demand_impl_glNormal3i;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3iv(const GLint * v) {
    glad_glNormal3iv = (PFNGLNORMAL3IVPROC) glad_gl_on_demand_loader("glNormal3iv");
    glad_glNormal3iv(v);
}
PFNGLNORMAL3IVPROC glad_glNormal3iv = glad_on_demand_impl_glNormal3iv;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
    glad_glNormal3s = (PFNGLNORMAL3SPROC) glad_gl_on_demand_loader("glNormal3s");
    glad_glNormal3s(nx, ny, nz);
}
PFNGLNORMAL3SPROC glad_glNormal3s = glad_on_demand_impl_glNormal3s;
static void GLAD_API_PTR glad_on_demand_impl_glNormal3sv(const GLshort * v) {
    glad_glNormal3sv = (PFNGLNORMAL3SVPROC) glad_gl_on_demand_loader("glNormal3sv");
    glad_glNormal3sv(v);
}
PFNGLNORMAL3SVPROC glad_glNormal3sv = glad_on_demand_impl_glNormal3sv;
static void GLAD_API_PTR glad_on_demand_impl_glNormalPointer(GLenum type, GLsizei stride, const void * pointer) {
    glad_glNormalPointer = (PFNGLNORMALPOINTERPROC) glad_gl_on_demand_loader("glNormalPointer");
    glad_glNormalPointer(type, stride, pointer);
}
PFNGLNORMALPOINTERPROC glad_glNormalPointer = glad_on_demand_impl_glNormalPointer;
static void GLAD_API_PTR glad_on_demand_impl_glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    glad_glOrtho = (PFNGLORTHOPROC) glad_gl_on_demand_loader("glOrtho");
    glad_glOrtho(left, right, bottom, top, zNear, zFar);
}
PFNGLORTHOPROC glad_glOrtho = glad_on_demand_impl_glOrtho;
static void GLAD_API_PTR glad_on_demand_impl_glPassThrough(GLfloat token) {
    glad_glPassThrough = (PFNGLPASSTHROUGHPROC) glad_gl_on_demand_loader("glPassThrough");
    glad_glPassThrough(token);
}
PFNGLPASSTHROUGHPROC glad_glPassThrough = glad_on_demand_impl_glPassThrough;
static void GLAD_API_PTR glad_on_demand_impl_glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values) {
    glad_glPixelMapfv = (PFNGLPIXELMAPFVPROC) glad_gl_on_demand_loader("glPixelMapfv");
    glad_glPixelMapfv(map, mapsize, values);
}
PFNGLPIXELMAPFVPROC glad_glPixelMapfv = glad_on_demand_impl_glPixelMapfv;
static void GLAD_API_PTR glad_on_demand_impl_glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values) {
    glad_glPixelMapuiv = (PFNGLPIXELMAPUIVPROC) glad_gl_on_demand_loader("glPixelMapuiv");
    glad_glPixelMapuiv(map, mapsize, values);
}
PFNGLPIXELMAPUIVPROC glad_glPixelMapuiv = glad_on_demand_impl_glPixelMapuiv;
static void GLAD_API_PTR glad_on_demand_impl_glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values) {
    glad_glPixelMapusv = (PFNGLPIXELMAPUSVPROC) glad_gl_on_demand_loader("glPixelMapusv");
    glad_glPixelMapusv(map, mapsize, values);
}
PFNGLPIXELMAPUSVPROC glad_glPixelMapusv = glad_on_demand_impl_glPixelMapusv;
static void GLAD_API_PTR glad_on_demand_impl_glPixelStoref(GLenum pname, GLfloat param) {
    glad_glPixelStoref = (PFNGLPIXELSTOREFPROC) glad_gl_on_demand_loader("glPixelStoref");
    glad_glPixelStoref(pname, param);
}
PFNGLPIXELSTOREFPROC glad_glPixelStoref = glad_on_demand_impl_glPixelStoref;
static void GLAD_API_PTR glad_on_demand_impl_glPixelStorei(GLenum pname, GLint param) {
    glad_glPixelStorei = (PFNGLPIXELSTOREIPROC) glad_gl_on_demand_loader("glPixelStorei");
    glad_glPixelStorei(pname, param);
}
PFNGLPIXELSTOREIPROC glad_glPixelStorei = glad_on_demand_impl_glPixelStorei;
static void GLAD_API_PTR glad_on_demand_impl_glPixelTransferf(GLenum pname, GLfloat param) {
    glad_glPixelTransferf = (PFNGLPIXELTRANSFERFPROC) glad_gl_on_demand_loader("glPixelTransferf");
    glad_glPixelTransferf(pname, param);
}
PFNGLPIXELTRANSFERFPROC glad_glPixelTransferf = glad_on_demand_impl_glPixelTransferf;
static void GLAD_API_PTR glad_on_demand_impl_glPixelTransferi(GLenum pname, GLint param) {
    glad_glPixelTransferi = (PFNGLPIXELTRANSFERIPROC) glad_gl_on_demand_loader("glPixelTransferi");
    glad_glPixelTransferi(pname, param);
}
PFNGLPIXELTRANSFERIPROC glad_glPixelTransferi = glad_on_demand_impl_glPixelTransferi;
static void GLAD_API_PTR glad_on_demand_impl_glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
    glad_glPixelZoom = (PFNGLPIXELZOOMPROC) glad_gl_on_demand_loader("glPixelZoom");
    glad_glPixelZoom(xfactor, yfactor);
}
PFNGLPIXELZOOMPROC glad_glPixelZoom = glad_on_demand_impl_glPixelZoom;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterf(GLenum pname, GLfloat param) {
    glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC) glad_gl_on_demand_loader("glPointParameterf");
    glad_glPointParameterf(pname, param);
}
PFNGLPOINTPARAMETERFPROC glad_glPointParameterf = glad_on_demand_impl_glPointParameterf;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfv(GLenum pname, const GLfloat * params) {
    glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) glad_gl_on_demand_loader("glPointParameterfv");
    glad_glPointParameterfv(pname, params);
}
PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv = glad_on_demand_impl_glPointParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameteri(GLenum pname, GLint param) {
    glad_glPointParameteri = (PFNGLPOINTPARAMETERIPROC) glad_gl_on_demand_loader("glPointParameteri");
    glad_glPointParameteri(pname, param);
}
PFNGLPOINTPARAMETERIPROC glad_glPointParameteri = glad_on_demand_impl_glPointParameteri;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameteriv(GLenum pname, const GLint * params) {
    glad_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) glad_gl_on_demand_loader("glPointParameteriv");
    glad_glPointParameteriv(pname, params);
}
PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv = glad_on_demand_impl_glPointParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glPointSize(GLfloat size) {
    glad_glPointSize = (PFNGLPOINTSIZEPROC) glad_gl_on_demand_loader("glPointSize");
    glad_glPointSize(size);
}
PFNGLPOINTSIZEPROC glad_glPointSize = glad_on_demand_impl_glPointSize;
static void GLAD_API_PTR glad_on_demand_impl_glPolygonMode(GLenum face, GLenum mode) {
    glad_glPolygonMode = (PFNGLPOLYGONMODEPROC) glad_gl_on_demand_loader("glPolygonMode");
    glad_glPolygonMode(face, mode);
}
PFNGLPOLYGONMODEPROC glad_glPolygonMode = glad_on_demand_impl_glPolygonMode;
static void GLAD_API_PTR glad_on_demand_impl_glPolygonOffset(GLfloat factor, GLfloat units) {
    glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) glad_gl_on_demand_loader("glPolygonOffset");
    glad_glPolygonOffset(factor, units);
}
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset = glad_on_demand_impl_glPolygonOffset;
static void GLAD_API_PTR glad_on_demand_impl_glPolygonStipple(const GLubyte * mask) {
    glad_glPolygonStipple = (PFNGLPOLYGONSTIPPLEPROC) glad_gl_on_demand_loader("glPolygonStipple");
    glad_glPolygonStipple(mask);
}
PFNGLPOLYGONSTIPPLEPROC glad_glPolygonStipple = glad_on_demand_impl_glPolygonStipple;
static void GLAD_API_PTR glad_on_demand_impl_glPopAttrib(void) {
    glad_glPopAttrib = (PFNGLPOPATTRIBPROC) glad_gl_on_demand_loader("glPopAttrib");
    glad_glPopAttrib();
}
PFNGLPOPATTRIBPROC glad_glPopAttrib = glad_on_demand_impl_glPopAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glPopClientAttrib(void) {
    glad_glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC) glad_gl_on_demand_loader("glPopClientAttrib");
    glad_glPopClientAttrib();
}
PFNGLPOPCLIENTATTRIBPROC glad_glPopClientAttrib = glad_on_demand_impl_glPopClientAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glPopMatrix(void) {
    glad_glPopMatrix = (PFNGLPOPMATRIXPROC) glad_gl_on_demand_loader("glPopMatrix");
    glad_glPopMatrix();
}
PFNGLPOPMATRIXPROC glad_glPopMatrix = glad_on_demand_impl_glPopMatrix;
static void GLAD_API_PTR glad_on_demand_impl_glPopName(void) {
    glad_glPopName = (PFNGLPOPNAMEPROC) glad_gl_on_demand_loader("glPopName");
    glad_glPopName();
}
PFNGLPOPNAMEPROC glad_glPopName = glad_on_demand_impl_glPopName;
static void GLAD_API_PTR glad_on_demand_impl_glPrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities) {
    glad_glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC) glad_gl_on_demand_loader("glPrioritizeTextures");
    glad_glPrioritizeTextures(n, textures, priorities);
}
PFNGLPRIORITIZETEXTURESPROC glad_glPrioritizeTextures = glad_on_demand_impl_glPrioritizeTextures;
static void GLAD_API_PTR glad_on_demand_impl_glPushAttrib(GLbitfield mask) {
    glad_glPushAttrib = (PFNGLPUSHATTRIBPROC) glad_gl_on_demand_loader("glPushAttrib");
    glad_glPushAttrib(mask);
}
PFNGLPUSHATTRIBPROC glad_glPushAttrib = glad_on_demand_impl_glPushAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glPushClientAttrib(GLbitfield mask) {
    glad_glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC) glad_gl_on_demand_loader("glPushClientAttrib");
    glad_glPushClientAttrib(mask);
}
PFNGLPUSHCLIENTATTRIBPROC glad_glPushClientAttrib = glad_on_demand_impl_glPushClientAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glPushMatrix(void) {
    glad_glPushMatrix = (PFNGLPUSHMATRIXPROC) glad_gl_on_demand_loader("glPushMatrix");
    glad_glPushMatrix();
}
PFNGLPUSHMATRIXPROC glad_glPushMatrix = glad_on_demand_impl_glPushMatrix;
static void GLAD_API_PTR glad_on_demand_impl_glPushName(GLuint name) {
    glad_glPushName = (PFNGLPUSHNAMEPROC) glad_gl_on_demand_loader("glPushName");
    glad_glPushName(name);
}
PFNGLPUSHNAMEPROC glad_glPushName = glad_on_demand_impl_glPushName;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2d(GLdouble x, GLdouble y) {
    glad_glRasterPos2d = (PFNGLRASTERPOS2DPROC) glad_gl_on_demand_loader("glRasterPos2d");
    glad_glRasterPos2d(x, y);
}
PFNGLRASTERPOS2DPROC glad_glRasterPos2d = glad_on_demand_impl_glRasterPos2d;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2dv(const GLdouble * v) {
    glad_glRasterPos2dv = (PFNGLRASTERPOS2DVPROC) glad_gl_on_demand_loader("glRasterPos2dv");
    glad_glRasterPos2dv(v);
}
PFNGLRASTERPOS2DVPROC glad_glRasterPos2dv = glad_on_demand_impl_glRasterPos2dv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2f(GLfloat x, GLfloat y) {
    glad_glRasterPos2f = (PFNGLRASTERPOS2FPROC) glad_gl_on_demand_loader("glRasterPos2f");
    glad_glRasterPos2f(x, y);
}
PFNGLRASTERPOS2FPROC glad_glRasterPos2f = glad_on_demand_impl_glRasterPos2f;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2fv(const GLfloat * v) {
    glad_glRasterPos2fv = (PFNGLRASTERPOS2FVPROC) glad_gl_on_demand_loader("glRasterPos2fv");
    glad_glRasterPos2fv(v);
}
PFNGLRASTERPOS2FVPROC glad_glRasterPos2fv = glad_on_demand_impl_glRasterPos2fv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2i(GLint x, GLint y) {
    glad_glRasterPos2i = (PFNGLRASTERPOS2IPROC) glad_gl_on_demand_loader("glRasterPos2i");
    glad_glRasterPos2i(x, y);
}
PFNGLRASTERPOS2IPROC glad_glRasterPos2i = glad_on_demand_impl_glRasterPos2i;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2iv(const GLint * v) {
    glad_glRasterPos2iv = (PFNGLRASTERPOS2IVPROC) glad_gl_on_demand_loader("glRasterPos2iv");
    glad_glRasterPos2iv(v);
}
PFNGLRASTERPOS2IVPROC glad_glRasterPos2iv = glad_on_demand_impl_glRasterPos2iv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2s(GLshort x, GLshort y) {
    glad_glRasterPos2s = (PFNGLRASTERPOS2SPROC) glad_gl_on_demand_loader("glRasterPos2s");
    glad_glRasterPos2s(x, y);
}
PFNGLRASTERPOS2SPROC glad_glRasterPos2s = glad_on_demand_impl_glRasterPos2s;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos2sv(const GLshort * v) {
    glad_glRasterPos2sv = (PFNGLRASTERPOS2SVPROC) glad_gl_on_demand_loader("glRasterPos2sv");
    glad_glRasterPos2sv(v);
}
PFNGLRASTERPOS2SVPROC glad_glRasterPos2sv = glad_on_demand_impl_glRasterPos2sv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
    glad_glRasterPos3d = (PFNGLRASTERPOS3DPROC) glad_gl_on_demand_loader("glRasterPos3d");
    glad_glRasterPos3d(x, y, z);
}
PFNGLRASTERPOS3DPROC glad_glRasterPos3d = glad_on_demand_impl_glRasterPos3d;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3dv(const GLdouble * v) {
    glad_glRasterPos3dv = (PFNGLRASTERPOS3DVPROC) glad_gl_on_demand_loader("glRasterPos3dv");
    glad_glRasterPos3dv(v);
}
PFNGLRASTERPOS3DVPROC glad_glRasterPos3dv = glad_on_demand_impl_glRasterPos3dv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
    glad_glRasterPos3f = (PFNGLRASTERPOS3FPROC) glad_gl_on_demand_loader("glRasterPos3f");
    glad_glRasterPos3f(x, y, z);
}
PFNGLRASTERPOS3FPROC glad_glRasterPos3f = glad_on_demand_impl_glRasterPos3f;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3fv(const GLfloat * v) {
    glad_glRasterPos3fv = (PFNGLRASTERPOS3FVPROC) glad_gl_on_demand_loader("glRasterPos3fv");
    glad_glRasterPos3fv(v);
}
PFNGLRASTERPOS3FVPROC glad_glRasterPos3fv = glad_on_demand_impl_glRasterPos3fv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3i(GLint x, GLint y, GLint z) {
    glad_glRasterPos3i = (PFNGLRASTERPOS3IPROC) glad_gl_on_demand_loader("glRasterPos3i");
    glad_glRasterPos3i(x, y, z);
}
PFNGLRASTERPOS3IPROC glad_glRasterPos3i = glad_on_demand_impl_glRasterPos3i;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3iv(const GLint * v) {
    glad_glRasterPos3iv = (PFNGLRASTERPOS3IVPROC) glad_gl_on_demand_loader("glRasterPos3iv");
    glad_glRasterPos3iv(v);
}
PFNGLRASTERPOS3IVPROC glad_glRasterPos3iv = glad_on_demand_impl_glRasterPos3iv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3s(GLshort x, GLshort y, GLshort z) {
    glad_glRasterPos3s = (PFNGLRASTERPOS3SPROC) glad_gl_on_demand_loader("glRasterPos3s");
    glad_glRasterPos3s(x, y, z);
}
PFNGLRASTERPOS3SPROC glad_glRasterPos3s = glad_on_demand_impl_glRasterPos3s;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos3sv(const GLshort * v) {
    glad_glRasterPos3sv = (PFNGLRASTERPOS3SVPROC) glad_gl_on_demand_loader("glRasterPos3sv");
    glad_glRasterPos3sv(v);
}
PFNGLRASTERPOS3SVPROC glad_glRasterPos3sv = glad_on_demand_impl_glRasterPos3sv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glRasterPos4d = (PFNGLRASTERPOS4DPROC) glad_gl_on_demand_loader("glRasterPos4d");
    glad_glRasterPos4d(x, y, z, w);
}
PFNGLRASTERPOS4DPROC glad_glRasterPos4d = glad_on_demand_impl_glRasterPos4d;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4dv(const GLdouble * v) {
    glad_glRasterPos4dv = (PFNGLRASTERPOS4DVPROC) glad_gl_on_demand_loader("glRasterPos4dv");
    glad_glRasterPos4dv(v);
}
PFNGLRASTERPOS4DVPROC glad_glRasterPos4dv = glad_on_demand_impl_glRasterPos4dv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glRasterPos4f = (PFNGLRASTERPOS4FPROC) glad_gl_on_demand_loader("glRasterPos4f");
    glad_glRasterPos4f(x, y, z, w);
}
PFNGLRASTERPOS4FPROC glad_glRasterPos4f = glad_on_demand_impl_glRasterPos4f;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4fv(const GLfloat * v) {
    glad_glRasterPos4fv = (PFNGLRASTERPOS4FVPROC) glad_gl_on_demand_loader("glRasterPos4fv");
    glad_glRasterPos4fv(v);
}
PFNGLRASTERPOS4FVPROC glad_glRasterPos4fv = glad_on_demand_impl_glRasterPos4fv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
    glad_glRasterPos4i = (PFNGLRASTERPOS4IPROC) glad_gl_on_demand_loader("glRasterPos4i");
    glad_glRasterPos4i(x, y, z, w);
}
PFNGLRASTERPOS4IPROC glad_glRasterPos4i = glad_on_demand_impl_glRasterPos4i;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4iv(const GLint * v) {
    glad_glRasterPos4iv = (PFNGLRASTERPOS4IVPROC) glad_gl_on_demand_loader("glRasterPos4iv");
    glad_glRasterPos4iv(v);
}
PFNGLRASTERPOS4IVPROC glad_glRasterPos4iv = glad_on_demand_impl_glRasterPos4iv;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glRasterPos4s = (PFNGLRASTERPOS4SPROC) glad_gl_on_demand_loader("glRasterPos4s");
    glad_glRasterPos4s(x, y, z, w);
}
PFNGLRASTERPOS4SPROC glad_glRasterPos4s = glad_on_demand_impl_glRasterPos4s;
static void GLAD_API_PTR glad_on_demand_impl_glRasterPos4sv(const GLshort * v) {
    glad_glRasterPos4sv = (PFNGLRASTERPOS4SVPROC) glad_gl_on_demand_loader("glRasterPos4sv");
    glad_glRasterPos4sv(v);
}
PFNGLRASTERPOS4SVPROC glad_glRasterPos4sv = glad_on_demand_impl_glRasterPos4sv;
static void GLAD_API_PTR glad_on_demand_impl_glReadBuffer(GLenum src) {
    glad_glReadBuffer = (PFNGLREADBUFFERPROC) glad_gl_on_demand_loader("glReadBuffer");
    glad_glReadBuffer(src);
}
PFNGLREADBUFFERPROC glad_glReadBuffer = glad_on_demand_impl_glReadBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    glad_glReadPixels = (PFNGLREADPIXELSPROC) glad_gl_on_demand_loader("glReadPixels");
    glad_glReadPixels(x, y, width, height, format, type, pixels);
}
PFNGLREADPIXELSPROC glad_glReadPixels = glad_on_demand_impl_glReadPixels;
static void GLAD_API_PTR glad_on_demand_impl_glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    glad_glRectd = (PFNGLRECTDPROC) glad_gl_on_demand_loader("glRectd");
    glad_glRectd(x1, y1, x2, y2);
}
PFNGLRECTDPROC glad_glRectd = glad_on_demand_impl_glRectd;
static void GLAD_API_PTR glad_on_demand_impl_glRectdv(const GLdouble * v1, const GLdouble * v2) {
    glad_glRectdv = (PFNGLRECTDVPROC) glad_gl_on_demand_loader("glRectdv");
    glad_glRectdv(v1, v2);
}
PFNGLRECTDVPROC glad_glRectdv = glad_on_demand_impl_glRectdv;
static void GLAD_API_PTR glad_on_demand_impl_glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    glad_glRectf = (PFNGLRECTFPROC) glad_gl_on_demand_loader("glRectf");
    glad_glRectf(x1, y1, x2, y2);
}
PFNGLRECTFPROC glad_glRectf = glad_on_demand_impl_glRectf;
static void GLAD_API_PTR glad_on_demand_impl_glRectfv(const GLfloat * v1, const GLfloat * v2) {
    glad_glRectfv = (PFNGLRECTFVPROC) glad_gl_on_demand_loader("glRectfv");
    glad_glRectfv(v1, v2);
}
PFNGLRECTFVPROC glad_glRectfv = glad_on_demand_impl_glRectfv;
static void GLAD_API_PTR glad_on_demand_impl_glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
    glad_glRecti = (PFNGLRECTIPROC) glad_gl_on_demand_loader("glRecti");
    glad_glRecti(x1, y1, x2, y2);
}
PFNGLRECTIPROC glad_glRecti = glad_on_demand_impl_glRecti;
static void GLAD_API_PTR glad_on_demand_impl_glRectiv(const GLint * v1, const GLint * v2) {
    glad_glRectiv = (PFNGLRECTIVPROC) glad_gl_on_demand_loader("glRectiv");
    glad_glRectiv(v1, v2);
}
PFNGLRECTIVPROC glad_glRectiv = glad_on_demand_impl_glRectiv;
static void GLAD_API_PTR glad_on_demand_impl_glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
    glad_glRects = (PFNGLRECTSPROC) glad_gl_on_demand_loader("glRects");
    glad_glRects(x1, y1, x2, y2);
}
PFNGLRECTSPROC glad_glRects = glad_on_demand_impl_glRects;
static void GLAD_API_PTR glad_on_demand_impl_glRectsv(const GLshort * v1, const GLshort * v2) {
    glad_glRectsv = (PFNGLRECTSVPROC) glad_gl_on_demand_loader("glRectsv");
    glad_glRectsv(v1, v2);
}
PFNGLRECTSVPROC glad_glRectsv = glad_on_demand_impl_glRectsv;
static GLint GLAD_API_PTR glad_on_demand_impl_glRenderMode(GLenum mode) {
    glad_glRenderMode = (PFNGLRENDERMODEPROC) glad_gl_on_demand_loader("glRenderMode");
    return glad_glRenderMode(mode);
}
PFNGLRENDERMODEPROC glad_glRenderMode = glad_on_demand_impl_glRenderMode;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) glad_gl_on_demand_loader("glRenderbufferStorage");
    glad_glRenderbufferStorage(target, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage = glad_on_demand_impl_glRenderbufferStorage;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) glad_gl_on_demand_loader("glRenderbufferStorageMultisample");
    glad_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample = glad_on_demand_impl_glRenderbufferStorageMultisample;
static void GLAD_API_PTR glad_on_demand_impl_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
    glad_glRotated = (PFNGLROTATEDPROC) glad_gl_on_demand_loader("glRotated");
    glad_glRotated(angle, x, y, z);
}
PFNGLROTATEDPROC glad_glRotated = glad_on_demand_impl_glRotated;
static void GLAD_API_PTR glad_on_demand_impl_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    glad_glRotatef = (PFNGLROTATEFPROC) glad_gl_on_demand_loader("glRotatef");
    glad_glRotatef(angle, x, y, z);
}
PFNGLROTATEFPROC glad_glRotatef = glad_on_demand_impl_glRotatef;
static void GLAD_API_PTR glad_on_demand_impl_glSampleCoverage(GLfloat value, GLboolean invert) {
    glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) glad_gl_on_demand_loader("glSampleCoverage");
    glad_glSampleCoverage(value, invert);
}
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage = glad_on_demand_impl_glSampleCoverage;
static void GLAD_API_PTR glad_on_demand_impl_glScaled(GLdouble x, GLdouble y, GLdouble z) {
    glad_glScaled = (PFNGLSCALEDPROC) glad_gl_on_demand_loader("glScaled");
    glad_glScaled(x, y, z);
}
PFNGLSCALEDPROC glad_glScaled = glad_on_demand_impl_glScaled;
static void GLAD_API_PTR glad_on_demand_impl_glScalef(GLfloat x, GLfloat y, GLfloat z) {
    glad_glScalef = (PFNGLSCALEFPROC) glad_gl_on_demand_loader("glScalef");
    glad_glScalef(x, y, z);
}
PFNGLSCALEFPROC glad_glScalef = glad_on_demand_impl_glScalef;
static void GLAD_API_PTR glad_on_demand_impl_glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glScissor = (PFNGLSCISSORPROC) glad_gl_on_demand_loader("glScissor");
    glad_glScissor(x, y, width, height);
}
PFNGLSCISSORPROC glad_glScissor = glad_on_demand_impl_glScissor;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue) {
    glad_glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC) glad_gl_on_demand_loader("glSecondaryColor3b");
    glad_glSecondaryColor3b(red, green, blue);
}
PFNGLSECONDARYCOLOR3BPROC glad_glSecondaryColor3b = glad_on_demand_impl_glSecondaryColor3b;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3bv(const GLbyte * v) {
    glad_glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC) glad_gl_on_demand_loader("glSecondaryColor3bv");
    glad_glSecondaryColor3bv(v);
}
PFNGLSECONDARYCOLOR3BVPROC glad_glSecondaryColor3bv = glad_on_demand_impl_glSecondaryColor3bv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue) {
    glad_glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC) glad_gl_on_demand_loader("glSecondaryColor3d");
    glad_glSecondaryColor3d(red, green, blue);
}
PFNGLSECONDARYCOLOR3DPROC glad_glSecondaryColor3d = glad_on_demand_impl_glSecondaryColor3d;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3dv(const GLdouble * v) {
    glad_glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC) glad_gl_on_demand_loader("glSecondaryColor3dv");
    glad_glSecondaryColor3dv(v);
}
PFNGLSECONDARYCOLOR3DVPROC glad_glSecondaryColor3dv = glad_on_demand_impl_glSecondaryColor3dv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    glad_glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC) glad_gl_on_demand_loader("glSecondaryColor3f");
    glad_glSecondaryColor3f(red, green, blue);
}
PFNGLSECONDARYCOLOR3FPROC glad_glSecondaryColor3f = glad_on_demand_impl_glSecondaryColor3f;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3fv(const GLfloat * v) {
    glad_glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC) glad_gl_on_demand_loader("glSecondaryColor3fv");
    glad_glSecondaryColor3fv(v);
}
PFNGLSECONDARYCOLOR3FVPROC glad_glSecondaryColor3fv = glad_on_demand_impl_glSecondaryColor3fv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3i(GLint red, GLint green, GLint blue) {
    glad_glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC) glad_gl_on_demand_loader("glSecondaryColor3i");
    glad_glSecondaryColor3i(red, green, blue);
}
PFNGLSECONDARYCOLOR3IPROC glad_glSecondaryColor3i = glad_on_demand_impl_glSecondaryColor3i;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3iv(const GLint * v) {
    glad_glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC) glad_gl_on_demand_loader("glSecondaryColor3iv");
    glad_glSecondaryColor3iv(v);
}
PFNGLSECONDARYCOLOR3IVPROC glad_glSecondaryColor3iv = glad_on_demand_impl_glSecondaryColor3iv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3s(GLshort red, GLshort green, GLshort blue) {
    glad_glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC) glad_gl_on_demand_loader("glSecondaryColor3s");
    glad_glSecondaryColor3s(red, green, blue);
}
PFNGLSECONDARYCOLOR3SPROC glad_glSecondaryColor3s = glad_on_demand_impl_glSecondaryColor3s;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3sv(const GLshort * v) {
    glad_glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC) glad_gl_on_demand_loader("glSecondaryColor3sv");
    glad_glSecondaryColor3sv(v);
}
PFNGLSECONDARYCOLOR3SVPROC glad_glSecondaryColor3sv = glad_on_demand_impl_glSecondaryColor3sv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    glad_glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC) glad_gl_on_demand_loader("glSecondaryColor3ub");
    glad_glSecondaryColor3ub(red, green, blue);
}
PFNGLSECONDARYCOLOR3UBPROC glad_glSecondaryColor3ub = glad_on_demand_impl_glSecondaryColor3ub;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3ubv(const GLubyte * v) {
    glad_glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC) glad_gl_on_demand_loader("glSecondaryColor3ubv");
    glad_glSecondaryColor3ubv(v);
}
PFNGLSECONDARYCOLOR3UBVPROC glad_glSecondaryColor3ubv = glad_on_demand_impl_glSecondaryColor3ubv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue) {
    glad_glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC) glad_gl_on_demand_loader("glSecondaryColor3ui");
    glad_glSecondaryColor3ui(red, green, blue);
}
PFNGLSECONDARYCOLOR3UIPROC glad_glSecondaryColor3ui = glad_on_demand_impl_glSecondaryColor3ui;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3uiv(const GLuint * v) {
    glad_glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC) glad_gl_on_demand_loader("glSecondaryColor3uiv");
    glad_glSecondaryColor3uiv(v);
}
PFNGLSECONDARYCOLOR3UIVPROC glad_glSecondaryColor3uiv = glad_on_demand_impl_glSecondaryColor3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3us(GLushort red, GLushort green, GLushort blue) {
    glad_glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC) glad_gl_on_demand_loader("glSecondaryColor3us");
    glad_glSecondaryColor3us(red, green, blue);
}
PFNGLSECONDARYCOLOR3USPROC glad_glSecondaryColor3us = glad_on_demand_impl_glSecondaryColor3us;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColor3usv(const GLushort * v) {
    glad_glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC) glad_gl_on_demand_loader("glSecondaryColor3usv");
    glad_glSecondaryColor3usv(v);
}
PFNGLSECONDARYCOLOR3USVPROC glad_glSecondaryColor3usv = glad_on_demand_impl_glSecondaryColor3usv;
static void GLAD_API_PTR glad_on_demand_impl_glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC) glad_gl_on_demand_loader("glSecondaryColorPointer");
    glad_glSecondaryColorPointer(size, type, stride, pointer);
}
PFNGLSECONDARYCOLORPOINTERPROC glad_glSecondaryColorPointer = glad_on_demand_impl_glSecondaryColorPointer;
static void GLAD_API_PTR glad_on_demand_impl_glSelectBuffer(GLsizei size, GLuint * buffer) {
    glad_glSelectBuffer = (PFNGLSELECTBUFFERPROC) glad_gl_on_demand_loader("glSelectBuffer");
    glad_glSelectBuffer(size, buffer);
}
PFNGLSELECTBUFFERPROC glad_glSelectBuffer = glad_on_demand_impl_glSelectBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glShadeModel(GLenum mode) {
    glad_glShadeModel = (PFNGLSHADEMODELPROC) glad_gl_on_demand_loader("glShadeModel");
    glad_glShadeModel(mode);
}
PFNGLSHADEMODELPROC glad_glShadeModel = glad_on_demand_impl_glShadeModel;
static void GLAD_API_PTR glad_on_demand_impl_glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length) {
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC) glad_gl_on_demand_loader("glShaderSource");
    glad_glShaderSource(shader, count, string, length);
}
PFNGLSHADERSOURCEPROC glad_glShaderSource = glad_on_demand_impl_glShaderSource;
static void GLAD_API_PTR glad_on_demand_impl_glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    glad_glStencilFunc = (PFNGLSTENCILFUNCPROC) glad_gl_on_demand_loader("glStencilFunc");
    glad_glStencilFunc(func, ref, mask);
}
PFNGLSTENCILFUNCPROC glad_glStencilFunc = glad_on_demand_impl_glStencilFunc;
static void GLAD_API_PTR glad_on_demand_impl_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) glad_gl_on_demand_loader("glStencilFuncSeparate");
    glad_glStencilFuncSeparate(face, func, ref, mask);
}
PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate = glad_on_demand_impl_glStencilFuncSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glStencilMask(GLuint mask) {
    glad_glStencilMask = (PFNGLSTENCILMASKPROC) glad_gl_on_demand_loader("glStencilMask");
    glad_glStencilMask(mask);
}
PFNGLSTENCILMASKPROC glad_glStencilMask = glad_on_demand_impl_glStencilMask;
static void GLAD_API_PTR glad_on_demand_impl_glStencilMaskSeparate(GLenum face, GLuint mask) {
    glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) glad_gl_on_demand_loader("glStencilMaskSeparate");
    glad_glStencilMaskSeparate(face, mask);
}
PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate = glad_on_demand_impl_glStencilMaskSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    glad_glStencilOp = (PFNGLSTENCILOPPROC) glad_gl_on_demand_loader("glStencilOp");
    glad_glStencilOp(fail, zfail, zpass);
}
PFNGLSTENCILOPPROC glad_glStencilOp = glad_on_demand_impl_glStencilOp;
static void GLAD_API_PTR glad_on_demand_impl_glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) glad_gl_on_demand_loader("glStencilOpSeparate");
    glad_glStencilOpSeparate(face, sfail, dpfail, dppass);
}
PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate = glad_on_demand_impl_glStencilOpSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1d(GLdouble s) {
    glad_glTexCoord1d = (PFNGLTEXCOORD1DPROC) glad_gl_on_demand_loader("glTexCoord1d");
    glad_glTexCoord1d(s);
}
PFNGLTEXCOORD1DPROC glad_glTexCoord1d = glad_on_demand_impl_glTexCoord1d;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1dv(const GLdouble * v) {
    glad_glTexCoord1dv = (PFNGLTEXCOORD1DVPROC) glad_gl_on_demand_loader("glTexCoord1dv");
    glad_glTexCoord1dv(v);
}
PFNGLTEXCOORD1DVPROC glad_glTexCoord1dv = glad_on_demand_impl_glTexCoord1dv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1f(GLfloat s) {
    glad_glTexCoord1f = (PFNGLTEXCOORD1FPROC) glad_gl_on_demand_loader("glTexCoord1f");
    glad_glTexCoord1f(s);
}
PFNGLTEXCOORD1FPROC glad_glTexCoord1f = glad_on_demand_impl_glTexCoord1f;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1fv(const GLfloat * v) {
    glad_glTexCoord1fv = (PFNGLTEXCOORD1FVPROC) glad_gl_on_demand_loader("glTexCoord1fv");
    glad_glTexCoord1fv(v);
}
PFNGLTEXCOORD1FVPROC glad_glTexCoord1fv = glad_on_demand_impl_glTexCoord1fv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1i(GLint s) {
    glad_glTexCoord1i = (PFNGLTEXCOORD1IPROC) glad_gl_on_demand_loader("glTexCoord1i");
    glad_glTexCoord1i(s);
}
PFNGLTEXCOORD1IPROC glad_glTexCoord1i = glad_on_demand_impl_glTexCoord1i;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1iv(const GLint * v) {
    glad_glTexCoord1iv = (PFNGLTEXCOORD1IVPROC) glad_gl_on_demand_loader("glTexCoord1iv");
    glad_glTexCoord1iv(v);
}
PFNGLTEXCOORD1IVPROC glad_glTexCoord1iv = glad_on_demand_impl_glTexCoord1iv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1s(GLshort s) {
    glad_glTexCoord1s = (PFNGLTEXCOORD1SPROC) glad_gl_on_demand_loader("glTexCoord1s");
    glad_glTexCoord1s(s);
}
PFNGLTEXCOORD1SPROC glad_glTexCoord1s = glad_on_demand_impl_glTexCoord1s;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord1sv(const GLshort * v) {
    glad_glTexCoord1sv = (PFNGLTEXCOORD1SVPROC) glad_gl_on_demand_loader("glTexCoord1sv");
    glad_glTexCoord1sv(v);
}
PFNGLTEXCOORD1SVPROC glad_glTexCoord1sv = glad_on_demand_impl_glTexCoord1sv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2d(GLdouble s, GLdouble t) {
    glad_glTexCoord2d = (PFNGLTEXCOORD2DPROC) glad_gl_on_demand_loader("glTexCoord2d");
    glad_glTexCoord2d(s, t);
}
PFNGLTEXCOORD2DPROC glad_glTexCoord2d = glad_on_demand_impl_glTexCoord2d;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2dv(const GLdouble * v) {
    glad_glTexCoord2dv = (PFNGLTEXCOORD2DVPROC) glad_gl_on_demand_loader("glTexCoord2dv");
    glad_glTexCoord2dv(v);
}
PFNGLTEXCOORD2DVPROC glad_glTexCoord2dv = glad_on_demand_impl_glTexCoord2dv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2f(GLfloat s, GLfloat t) {
    glad_glTexCoord2f = (PFNGLTEXCOORD2FPROC) glad_gl_on_demand_loader("glTexCoord2f");
    glad_glTexCoord2f(s, t);
}
PFNGLTEXCOORD2FPROC glad_glTexCoord2f = glad_on_demand_impl_glTexCoord2f;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2fv(const GLfloat * v) {
    glad_glTexCoord2fv = (PFNGLTEXCOORD2FVPROC) glad_gl_on_demand_loader("glTexCoord2fv");
    glad_glTexCoord2fv(v);
}
PFNGLTEXCOORD2FVPROC glad_glTexCoord2fv = glad_on_demand_impl_glTexCoord2fv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2i(GLint s, GLint t) {
    glad_glTexCoord2i = (PFNGLTEXCOORD2IPROC) glad_gl_on_demand_loader("glTexCoord2i");
    glad_glTexCoord2i(s, t);
}
PFNGLTEXCOORD2IPROC glad_glTexCoord2i = glad_on_demand_impl_glTexCoord2i;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2iv(const GLint * v) {
    glad_glTexCoord2iv = (PFNGLTEXCOORD2IVPROC) glad_gl_on_demand_loader("glTexCoord2iv");
    glad_glTexCoord2iv(v);
}
PFNGLTEXCOORD2IVPROC glad_glTexCoord2iv = glad_on_demand_impl_glTexCoord2iv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2s(GLshort s, GLshort t) {
    glad_glTexCoord2s = (PFNGLTEXCOORD2SPROC) glad_gl_on_demand_loader("glTexCoord2s");
    glad_glTexCoord2s(s, t);
}
PFNGLTEXCOORD2SPROC glad_glTexCoord2s = glad_on_demand_impl_glTexCoord2s;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord2sv(const GLshort * v) {
    glad_glTexCoord2sv = (PFNGLTEXCOORD2SVPROC) glad_gl_on_demand_loader("glTexCoord2sv");
    glad_glTexCoord2sv(v);
}
PFNGLTEXCOORD2SVPROC glad_glTexCoord2sv = glad_on_demand_impl_glTexCoord2sv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
    glad_glTexCoord3d = (PFNGLTEXCOORD3DPROC) glad_gl_on_demand_loader("glTexCoord3d");
    glad_glTexCoord3d(s, t, r);
}
PFNGLTEXCOORD3DPROC glad_glTexCoord3d = glad_on_demand_impl_glTexCoord3d;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3dv(const GLdouble * v) {
    glad_glTexCoord3dv = (PFNGLTEXCOORD3DVPROC) glad_gl_on_demand_loader("glTexCoord3dv");
    glad_glTexCoord3dv(v);
}
PFNGLTEXCOORD3DVPROC glad_glTexCoord3dv = glad_on_demand_impl_glTexCoord3dv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
    glad_glTexCoord3f = (PFNGLTEXCOORD3FPROC) glad_gl_on_demand_loader("glTexCoord3f");
    glad_glTexCoord3f(s, t, r);
}
PFNGLTEXCOORD3FPROC glad_glTexCoord3f = glad_on_demand_impl_glTexCoord3f;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3fv(const GLfloat * v) {
    glad_glTexCoord3fv = (PFNGLTEXCOORD3FVPROC) glad_gl_on_demand_loader("glTexCoord3fv");
    glad_glTexCoord3fv(v);
}
PFNGLTEXCOORD3FVPROC glad_glTexCoord3fv = glad_on_demand_impl_glTexCoord3fv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3i(GLint s, GLint t, GLint r) {
    glad_glTexCoord3i = (PFNGLTEXCOORD3IPROC) glad_gl_on_demand_loader("glTexCoord3i");
    glad_glTexCoord3i(s, t, r);
}
PFNGLTEXCOORD3IPROC glad_glTexCoord3i = glad_on_demand_impl_glTexCoord3i;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3iv(const GLint * v) {
    glad_glTexCoord3iv = (PFNGLTEXCOORD3IVPROC) glad_gl_on_demand_loader("glTexCoord3iv");
    glad_glTexCoord3iv(v);
}
PFNGLTEXCOORD3IVPROC glad_glTexCoord3iv = glad_on_demand_impl_glTexCoord3iv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3s(GLshort s, GLshort t, GLshort r) {
    glad_glTexCoord3s = (PFNGLTEXCOORD3SPROC) glad_gl_on_demand_loader("glTexCoord3s");
    glad_glTexCoord3s(s, t, r);
}
PFNGLTEXCOORD3SPROC glad_glTexCoord3s = glad_on_demand_impl_glTexCoord3s;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord3sv(const GLshort * v) {
    glad_glTexCoord3sv = (PFNGLTEXCOORD3SVPROC) glad_gl_on_demand_loader("glTexCoord3sv");
    glad_glTexCoord3sv(v);
}
PFNGLTEXCOORD3SVPROC glad_glTexCoord3sv = glad_on_demand_impl_glTexCoord3sv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    glad_glTexCoord4d = (PFNGLTEXCOORD4DPROC) glad_gl_on_demand_loader("glTexCoord4d");
    glad_glTexCoord4d(s, t, r, q);
}
PFNGLTEXCOORD4DPROC glad_glTexCoord4d = glad_on_demand_impl_glTexCoord4d;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4dv(const GLdouble * v) {
    glad_glTexCoord4dv = (PFNGLTEXCOORD4DVPROC) glad_gl_on_demand_loader("glTexCoord4dv");
    glad_glTexCoord4dv(v);
}
PFNGLTEXCOORD4DVPROC glad_glTexCoord4dv = glad_on_demand_impl_glTexCoord4dv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    glad_glTexCoord4f = (PFNGLTEXCOORD4FPROC) glad_gl_on_demand_loader("glTexCoord4f");
    glad_glTexCoord4f(s, t, r, q);
}
PFNGLTEXCOORD4FPROC glad_glTexCoord4f = glad_on_demand_impl_glTexCoord4f;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4fv(const GLfloat * v) {
    glad_glTexCoord4fv = (PFNGLTEXCOORD4FVPROC) glad_gl_on_demand_loader("glTexCoord4fv");
    glad_glTexCoord4fv(v);
}
PFNGLTEXCOORD4FVPROC glad_glTexCoord4fv = glad_on_demand_impl_glTexCoord4fv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
    glad_glTexCoord4i = (PFNGLTEXCOORD4IPROC) glad_gl_on_demand_loader("glTexCoord4i");
    glad_glTexCoord4i(s, t, r, q);
}
PFNGLTEXCOORD4IPROC glad_glTexCoord4i = glad_on_demand_impl_glTexCoord4i;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4iv(const GLint * v) {
    glad_glTexCoord4iv = (PFNGLTEXCOORD4IVPROC) glad_gl_on_demand_loader("glTexCoord4iv");
    glad_glTexCoord4iv(v);
}
PFNGLTEXCOORD4IVPROC glad_glTexCoord4iv = glad_on_demand_impl_glTexCoord4iv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
    glad_glTexCoord4s = (PFNGLTEXCOORD4SPROC) glad_gl_on_demand_loader("glTexCoord4s");
    glad_glTexCoord4s(s, t, r, q);
}
PFNGLTEXCOORD4SPROC glad_glTexCoord4s = glad_on_demand_impl_glTexCoord4s;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoord4sv(const GLshort * v) {
    glad_glTexCoord4sv = (PFNGLTEXCOORD4SVPROC) glad_gl_on_demand_loader("glTexCoord4sv");
    glad_glTexCoord4sv(v);
}
PFNGLTEXCOORD4SVPROC glad_glTexCoord4sv = glad_on_demand_impl_glTexCoord4sv;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC) glad_gl_on_demand_loader("glTexCoordPointer");
    glad_glTexCoordPointer(size, type, stride, pointer);
}
PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer = glad_on_demand_impl_glTexCoordPointer;
static void GLAD_API_PTR glad_on_demand_impl_glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
    glad_glTexEnvf = (PFNGLTEXENVFPROC) glad_gl_on_demand_loader("glTexEnvf");
    glad_glTexEnvf(target, pname, param);
}
PFNGLTEXENVFPROC glad_glTexEnvf = glad_on_demand_impl_glTexEnvf;
static void GLAD_API_PTR glad_on_demand_impl_glTexEnvfv(GLenum target, GLenum pname, const GLfloat * params) {
    glad_glTexEnvfv = (PFNGLTEXENVFVPROC) glad_gl_on_demand_loader("glTexEnvfv");
    glad_glTexEnvfv(target, pname, params);
}
PFNGLTEXENVFVPROC glad_glTexEnvfv = glad_on_demand_impl_glTexEnvfv;
static void GLAD_API_PTR glad_on_demand_impl_glTexEnvi(GLenum target, GLenum pname, GLint param) {
    glad_glTexEnvi = (PFNGLTEXENVIPROC) glad_gl_on_demand_loader("glTexEnvi");
    glad_glTexEnvi(target, pname, param);
}
PFNGLTEXENVIPROC glad_glTexEnvi = glad_on_demand_impl_glTexEnvi;
static void GLAD_API_PTR glad_on_demand_impl_glTexEnviv(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexEnviv = (PFNGLTEXENVIVPROC) glad_gl_on_demand_loader("glTexEnviv");
    glad_glTexEnviv(target, pname, params);
}
PFNGLTEXENVIVPROC glad_glTexEnviv = glad_on_demand_impl_glTexEnviv;
static void GLAD_API_PTR glad_on_demand_impl_glTexGend(GLenum coord, GLenum pname, GLdouble param) {
    glad_glTexGend = (PFNGLTEXGENDPROC) glad_gl_on_demand_loader("glTexGend");
    glad_glTexGend(coord, pname, param);
}
PFNGLTEXGENDPROC glad_glTexGend = glad_on_demand_impl_glTexGend;
static void GLAD_API_PTR glad_on_demand_impl_glTexGendv(GLenum coord, GLenum pname, const GLdouble * params) {
    glad_glTexGendv = (PFNGLTEXGENDVPROC) glad_gl_on_demand_loader("glTexGendv");
    glad_glTexGendv(coord, pname, params);
}
PFNGLTEXGENDVPROC glad_glTexGendv = glad_on_demand_impl_glTexGendv;
static void GLAD_API_PTR glad_on_demand_impl_glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
    glad_glTexGenf = (PFNGLTEXGENFPROC) glad_gl_on_demand_loader("glTexGenf");
    glad_glTexGenf(coord, pname, param);
}
PFNGLTEXGENFPROC glad_glTexGenf = glad_on_demand_impl_glTexGenf;
static void GLAD_API_PTR glad_on_demand_impl_glTexGenfv(GLenum coord, GLenum pname, const GLfloat * params) {
    glad_glTexGenfv = (PFNGLTEXGENFVPROC) glad_gl_on_demand_loader("glTexGenfv");
    glad_glTexGenfv(coord, pname, params);
}
PFNGLTEXGENFVPROC glad_glTexGenfv = glad_on_demand_impl_glTexGenfv;
static void GLAD_API_PTR glad_on_demand_impl_glTexGeni(GLenum coord, GLenum pname, GLint param) {
    glad_glTexGeni = (PFNGLTEXGENIPROC) glad_gl_on_demand_loader("glTexGeni");
    glad_glTexGeni(coord, pname, param);
}
PFNGLTEXGENIPROC glad_glTexGeni = glad_on_demand_impl_glTexGeni;
static void GLAD_API_PTR glad_on_demand_impl_glTexGeniv(GLenum coord, GLenum pname, const GLint * params) {
    glad_glTexGeniv = (PFNGLTEXGENIVPROC) glad_gl_on_demand_loader("glTexGeniv");
    glad_glTexGeniv(coord, pname, params);
}
PFNGLTEXGENIVPROC glad_glTexGeniv = glad_on_demand_impl_glTexGeniv;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage1D = (PFNGLTEXIMAGE1DPROC) glad_gl_on_demand_loader("glTexImage1D");
    glad_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}
PFNGLTEXIMAGE1DPROC glad_glTexImage1D = glad_on_demand_impl_glTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC) glad_gl_on_demand_loader("glTexImage2D");
    glad_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = glad_on_demand_impl_glTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC) glad_gl_on_demand_loader("glTexImage3D");
    glad_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}
PFNGLTEXIMAGE3DPROC glad_glTexImage3D = glad_on_demand_impl_glTexImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIiv(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) glad_gl_on_demand_loader("glTexParameterIiv");
    glad_glTexParameterIiv(target, pname, params);
}
PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv = glad_on_demand_impl_glTexParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIuiv(GLenum target, GLenum pname, const GLuint * params) {
    glad_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) glad_gl_on_demand_loader("glTexParameterIuiv");
    glad_glTexParameterIuiv(target, pname, params);
}
PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv = glad_on_demand_impl_glTexParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC) glad_gl_on_demand_loader("glTexParameterf");
    glad_glTexParameterf(target, pname, param);
}
PFNGLTEXPARAMETERFPROC glad_glTexParameterf = glad_on_demand_impl_glTexParameterf;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) glad_gl_on_demand_loader("glTexParameterfv");
    glad_glTexParameterfv(target, pname, params);
}
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = glad_on_demand_impl_glTexParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC) glad_gl_on_demand_loader("glTexParameteri");
    glad_glTexParameteri(target, pname, param);
}
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = glad_on_demand_impl_glTexParameteri;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) glad_gl_on_demand_loader("glTexParameteriv");
    glad_glTexParameteriv(target, pname, params);
}
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = glad_on_demand_impl_glTexParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glTexSubImage1D");
    glad_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}
PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D = glad_on_demand_impl_glTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glTexSubImage2D");
    glad_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = glad_on_demand_impl_glTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glTexSubImage3D");
    glad_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D = glad_on_demand_impl_glTexSubImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode) {
    glad_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) glad_gl_on_demand_loader("glTransformFeedbackVaryings");
    glad_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings = glad_on_demand_impl_glTransformFeedbackVaryings;
static void GLAD_API_PTR glad_on_demand_impl_glTranslated(GLdouble x, GLdouble y, GLdouble z) {
    glad_glTranslated = (PFNGLTRANSLATEDPROC) glad_gl_on_demand_loader("glTranslated");
    glad_glTranslated(x, y, z);
}
PFNGLTRANSLATEDPROC glad_glTranslated = glad_on_demand_impl_glTranslated;
static void GLAD_API_PTR glad_on_demand_impl_glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    glad_glTranslatef = (PFNGLTRANSLATEFPROC) glad_gl_on_demand_loader("glTranslatef");
    glad_glTranslatef(x, y, z);
}
PFNGLTRANSLATEFPROC glad_glTranslatef = glad_on_demand_impl_glTranslatef;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1f(GLint location, GLfloat v0) {
    glad_glUniform1f = (PFNGLUNIFORM1FPROC) glad_gl_on_demand_loader("glUniform1f");
    glad_glUniform1f(location, v0);
}
PFNGLUNIFORM1FPROC glad_glUniform1f = glad_on_demand_impl_glUniform1f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform1fv = (PFNGLUNIFORM1FVPROC) glad_gl_on_demand_loader("glUniform1fv");
    glad_glUniform1fv(location, count, value);
}
PFNGLUNIFORM1FVPROC glad_glUniform1fv = glad_on_demand_impl_glUniform1fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1i(GLint location, GLint v0) {
    glad_glUniform1i = (PFNGLUNIFORM1IPROC) glad_gl_on_demand_loader("glUniform1i");
    glad_glUniform1i(location, v0);
}
PFNGLUNIFORM1IPROC glad_glUniform1i = glad_on_demand_impl_glUniform1i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform1iv = (PFNGLUNIFORM1IVPROC) glad_gl_on_demand_loader("glUniform1iv");
    glad_glUniform1iv(location, count, value);
}
PFNGLUNIFORM1IVPROC glad_glUniform1iv = glad_on_demand_impl_glUniform1iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1ui(GLint location, GLuint v0) {
    glad_glUniform1ui = (PFNGLUNIFORM1UIPROC) glad_gl_on_demand_loader("glUniform1ui");
    glad_glUniform1ui(location, v0);
}
PFNGLUNIFORM1UIPROC glad_glUniform1ui = glad_on_demand_impl_glUniform1ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform1uiv = (PFNGLUNIFORM1UIVPROC) glad_gl_on_demand_loader("glUniform1uiv");
    glad_glUniform1uiv(location, count, value);
}
PFNGLUNIFORM1UIVPROC glad_glUniform1uiv = glad_on_demand_impl_glUniform1uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    glad_glUniform2f = (PFNGLUNIFORM2FPROC) glad_gl_on_demand_loader("glUniform2f");
    glad_glUniform2f(location, v0, v1);
}
PFNGLUNIFORM2FPROC glad_glUniform2f = glad_on_demand_impl_glUniform2f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform2fv = (PFNGLUNIFORM2FVPROC) glad_gl_on_demand_loader("glUniform2fv");
    glad_glUniform2fv(location, count, value);
}
PFNGLUNIFORM2FVPROC glad_glUniform2fv = glad_on_demand_impl_glUniform2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2i(GLint location, GLint v0, GLint v1) {
    glad_glUniform2i = (PFNGLUNIFORM2IPROC) glad_gl_on_demand_loader("glUniform2i");
    glad_glUniform2i(location, v0, v1);
}
PFNGLUNIFORM2IPROC glad_glUniform2i = glad_on_demand_impl_glUniform2i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform2iv = (PFNGLUNIFORM2IVPROC) glad_gl_on_demand_loader("glUniform2iv");
    glad_glUniform2iv(location, count, value);
}
PFNGLUNIFORM2IVPROC glad_glUniform2iv = glad_on_demand_impl_glUniform2iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2ui(GLint location, GLuint v0, GLuint v1) {
    glad_glUniform2ui = (PFNGLUNIFORM2UIPROC) glad_gl_on_demand_loader("glUniform2ui");
    glad_glUniform2ui(location, v0, v1);
}
PFNGLUNIFORM2UIPROC glad_glUniform2ui = glad_on_demand_impl_glUniform2ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform2uiv = (PFNGLUNIFORM2UIVPROC) glad_gl_on_demand_loader("glUniform2uiv");
    glad_glUniform2uiv(location, count, value);
}
PFNGLUNIFORM2UIVPROC glad_glUniform2uiv = glad_on_demand_impl_glUniform2uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glad_glUniform3f = (PFNGLUNIFORM3FPROC) glad_gl_on_demand_loader("glUniform3f");
    glad_glUniform3f(location, v0, v1, v2);
}
PFNGLUNIFORM3FPROC glad_glUniform3f = glad_on_demand_impl_glUniform3f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC) glad_gl_on_demand_loader("glUniform3fv");
    glad_glUniform3fv(location, count, value);
}
PFNGLUNIFORM3FVPROC glad_glUniform3fv = glad_on_demand_impl_glUniform3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    glad_glUniform3i = (PFNGLUNIFORM3IPROC) glad_gl_on_demand_loader("glUniform3i");
    glad_glUniform3i(location, v0, v1, v2);
}
PFNGLUNIFORM3IPROC glad_glUniform3i = glad_on_demand_impl_glUniform3i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform3iv = (PFNGLUNIFORM3IVPROC) glad_gl_on_demand_loader("glUniform3iv");
    glad_glUniform3iv(location, count, value);
}
PFNGLUNIFORM3IVPROC glad_glUniform3iv = glad_on_demand_impl_glUniform3iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    glad_glUniform3ui = (PFNGLUNIFORM3UIPROC) glad_gl_on_demand_loader("glUniform3ui");
    glad_glUniform3ui(location, v0, v1, v2);
}
PFNGLUNIFORM3UIPROC glad_glUniform3ui = glad_on_demand_impl_glUniform3ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform3uiv = (PFNGLUNIFORM3UIVPROC) glad_gl_on_demand_loader("glUniform3uiv");
    glad_glUniform3uiv(location, count, value);
}
PFNGLUNIFORM3UIVPROC glad_glUniform3uiv = glad_on_demand_impl_glUniform3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glad_glUniform4f = (PFNGLUNIFORM4FPROC) glad_gl_on_demand_loader("glUniform4f");
    glad_glUniform4f(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4FPROC glad_glUniform4f = glad_on_demand_impl_glUniform4f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform4fv = (PFNGLUNIFORM4FVPROC) glad_gl_on_demand_loader("glUniform4fv");
    glad_glUniform4fv(location, count, value);
}
PFNGLUNIFORM4FVPROC glad_glUniform4fv = glad_on_demand_impl_glUniform4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glad_glUniform4i = (PFNGLUNIFORM4IPROC) glad_gl_on_demand_loader("glUniform4i");
    glad_glUniform4i(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4IPROC glad_glUniform4i = glad_on_demand_impl_glUniform4i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform4iv = (PFNGLUNIFORM4IVPROC) glad_gl_on_demand_loader("glUniform4iv");
    glad_glUniform4iv(location, count, value);
}
PFNGLUNIFORM4IVPROC glad_glUniform4iv = glad_on_demand_impl_glUniform4iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    glad_glUniform4ui = (PFNGLUNIFORM4UIPROC) glad_gl_on_demand_loader("glUniform4ui");
    glad_glUniform4ui(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4UIPROC glad_glUniform4ui = glad_on_demand_impl_glUniform4ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform4uiv = (PFNGLUNIFORM4UIVPROC) glad_gl_on_demand_loader("glUniform4uiv");
    glad_glUniform4uiv(location, count, value);
}
PFNGLUNIFORM4UIVPROC glad_glUniform4uiv = glad_on_demand_impl_glUniform4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) glad_gl_on_demand_loader("glUniformMatrix2fv");
    glad_glUniformMatrix2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv = glad_on_demand_impl_glUniformMatrix2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) glad_gl_on_demand_loader("glUniformMatrix2x3fv");
    glad_glUniformMatrix2x3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv = glad_on_demand_impl_glUniformMatrix2x3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) glad_gl_on_demand_loader("glUniformMatrix2x4fv");
    glad_glUniformMatrix2x4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv = glad_on_demand_impl_glUniformMatrix2x4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) glad_gl_on_demand_loader("glUniformMatrix3fv");
    glad_glUniformMatrix3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv = glad_on_demand_impl_glUniformMatrix3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) glad_gl_on_demand_loader("glUniformMatrix3x2fv");
    glad_glUniformMatrix3x2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv = glad_on_demand_impl_glUniformMatrix3x2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) glad_gl_on_demand_loader("glUniformMatrix3x4fv");
    glad_glUniformMatrix3x4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv = glad_on_demand_impl_glUniformMatrix3x4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glad_gl_on_demand_loader("glUniformMatrix4fv");
    glad_glUniformMatrix4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = glad_on_demand_impl_glUniformMatrix4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) glad_gl_on_demand_loader("glUniformMatrix4x2fv");
    glad_glUniformMatrix4x2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv = glad_on_demand_impl_glUniformMatrix4x2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) glad_gl_on_demand_loader("glUniformMatrix4x3fv");
    glad_glUniformMatrix4x3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv = glad_on_demand_impl_glUniformMatrix4x3fv;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glUnmapBuffer(GLenum target) {
    glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) glad_gl_on_demand_loader("glUnmapBuffer");
    return glad_glUnmapBuffer(target);
}
PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer = glad_on_demand_impl_glUnmapBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glUseProgram(GLuint program) {
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC) glad_gl_on_demand_loader("glUseProgram");
    glad_glUseProgram(program);
}
PFNGLUSEPROGRAMPROC glad_glUseProgram = glad_on_demand_impl_glUseProgram;
static void GLAD_API_PTR glad_on_demand_impl_glValidateProgram(GLuint program) {
    glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) glad_gl_on_demand_loader("glValidateProgram");
    glad_glValidateProgram(program);
}
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = glad_on_demand_impl_glValidateProgram;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2d(GLdouble x, GLdouble y) {
    glad_glVertex2d = (PFNGLVERTEX2DPROC) glad_gl_on_demand_loader("glVertex2d");
    glad_glVertex2d(x, y);
}
PFNGLVERTEX2DPROC glad_glVertex2d = glad_on_demand_impl_glVertex2d;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2dv(const GLdouble * v) {
    glad_glVertex2dv = (PFNGLVERTEX2DVPROC) glad_gl_on_demand_loader("glVertex2dv");
    glad_glVertex2dv(v);
}
PFNGLVERTEX2DVPROC glad_glVertex2dv = glad_on_demand_impl_glVertex2dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2f(GLfloat x, GLfloat y) {
    glad_glVertex2f = (PFNGLVERTEX2FPROC) glad_gl_on_demand_loader("glVertex2f");
    glad_glVertex2f(x, y);
}
PFNGLVERTEX2FPROC glad_glVertex2f = glad_on_demand_impl_glVertex2f;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2fv(const GLfloat * v) {
    glad_glVertex2fv = (PFNGLVERTEX2FVPROC) glad_gl_on_demand_loader("glVertex2fv");
    glad_glVertex2fv(v);
}
PFNGLVERTEX2FVPROC glad_glVertex2fv = glad_on_demand_impl_glVertex2fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2i(GLint x, GLint y) {
    glad_glVertex2i = (PFNGLVERTEX2IPROC) glad_gl_on_demand_loader("glVertex2i");
    glad_glVertex2i(x, y);
}
PFNGLVERTEX2IPROC glad_glVertex2i = glad_on_demand_impl_glVertex2i;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2iv(const GLint * v) {
    glad_glVertex2iv = (PFNGLVERTEX2IVPROC) glad_gl_on_demand_loader("glVertex2iv");
    glad_glVertex2iv(v);
}
PFNGLVERTEX2IVPROC glad_glVertex2iv = glad_on_demand_impl_glVertex2iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2s(GLshort x, GLshort y) {
    glad_glVertex2s = (PFNGLVERTEX2SPROC) glad_gl_on_demand_loader("glVertex2s");
    glad_glVertex2s(x, y);
}
PFNGLVERTEX2SPROC glad_glVertex2s = glad_on_demand_impl_glVertex2s;
static void GLAD_API_PTR glad_on_demand_impl_glVertex2sv(const GLshort * v) {
    glad_glVertex2sv = (PFNGLVERTEX2SVPROC) glad_gl_on_demand_loader("glVertex2sv");
    glad_glVertex2sv(v);
}
PFNGLVERTEX2SVPROC glad_glVertex2sv = glad_on_demand_impl_glVertex2sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
    glad_glVertex3d = (PFNGLVERTEX3DPROC) glad_gl_on_demand_loader("glVertex3d");
    glad_glVertex3d(x, y, z);
}
PFNGLVERTEX3DPROC glad_glVertex3d = glad_on_demand_impl_glVertex3d;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3dv(const GLdouble * v) {
    glad_glVertex3dv = (PFNGLVERTEX3DVPROC) glad_gl_on_demand_loader("glVertex3dv");
    glad_glVertex3dv(v);
}
PFNGLVERTEX3DVPROC glad_glVertex3dv = glad_on_demand_impl_glVertex3dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    glad_glVertex3f = (PFNGLVERTEX3FPROC) glad_gl_on_demand_loader("glVertex3f");
    glad_glVertex3f(x, y, z);
}
PFNGLVERTEX3FPROC glad_glVertex3f = glad_on_demand_impl_glVertex3f;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3fv(const GLfloat * v) {
    glad_glVertex3fv = (PFNGLVERTEX3FVPROC) glad_gl_on_demand_loader("glVertex3fv");
    glad_glVertex3fv(v);
}
PFNGLVERTEX3FVPROC glad_glVertex3fv = glad_on_demand_impl_glVertex3fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3i(GLint x, GLint y, GLint z) {
    glad_glVertex3i = (PFNGLVERTEX3IPROC) glad_gl_on_demand_loader("glVertex3i");
    glad_glVertex3i(x, y, z);
}
PFNGLVERTEX3IPROC glad_glVertex3i = glad_on_demand_impl_glVertex3i;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3iv(const GLint * v) {
    glad_glVertex3iv = (PFNGLVERTEX3IVPROC) glad_gl_on_demand_loader("glVertex3iv");
    glad_glVertex3iv(v);
}
PFNGLVERTEX3IVPROC glad_glVertex3iv = glad_on_demand_impl_glVertex3iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3s(GLshort x, GLshort y, GLshort z) {
    glad_glVertex3s = (PFNGLVERTEX3SPROC) glad_gl_on_demand_loader("glVertex3s");
    glad_glVertex3s(x, y, z);
}
PFNGLVERTEX3SPROC glad_glVertex3s = glad_on_demand_impl_glVertex3s;
static void GLAD_API_PTR glad_on_demand_impl_glVertex3sv(const GLshort * v) {
    glad_glVertex3sv = (PFNGLVERTEX3SVPROC) glad_gl_on_demand_loader("glVertex3sv");
    glad_glVertex3sv(v);
}
PFNGLVERTEX3SVPROC glad_glVertex3sv = glad_on_demand_impl_glVertex3sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glVertex4d = (PFNGLVERTEX4DPROC) glad_gl_on_demand_loader("glVertex4d");
    glad_glVertex4d(x, y, z, w);
}
PFNGLVERTEX4DPROC glad_glVertex4d = glad_on_demand_impl_glVertex4d;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4dv(const GLdouble * v) {
    glad_glVertex4dv = (PFNGLVERTEX4DVPROC) glad_gl_on_demand_loader("glVertex4dv");
    glad_glVertex4dv(v);
}
PFNGLVERTEX4DVPROC glad_glVertex4dv = glad_on_demand_impl_glVertex4dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glVertex4f = (PFNGLVERTEX4FPROC) glad_gl_on_demand_loader("glVertex4f");
    glad_glVertex4f(x, y, z, w);
}
PFNGLVERTEX4FPROC glad_glVertex4f = glad_on_demand_impl_glVertex4f;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4fv(const GLfloat * v) {
    glad_glVertex4fv = (PFNGLVERTEX4FVPROC) glad_gl_on_demand_loader("glVertex4fv");
    glad_glVertex4fv(v);
}
PFNGLVERTEX4FVPROC glad_glVertex4fv = glad_on_demand_impl_glVertex4fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4i(GLint x, GLint y, GLint z, GLint w) {
    glad_glVertex4i = (PFNGLVERTEX4IPROC) glad_gl_on_demand_loader("glVertex4i");
    glad_glVertex4i(x, y, z, w);
}
PFNGLVERTEX4IPROC glad_glVertex4i = glad_on_demand_impl_glVertex4i;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4iv(const GLint * v) {
    glad_glVertex4iv = (PFNGLVERTEX4IVPROC) glad_gl_on_demand_loader("glVertex4iv");
    glad_glVertex4iv(v);
}
PFNGLVERTEX4IVPROC glad_glVertex4iv = glad_on_demand_impl_glVertex4iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glVertex4s = (PFNGLVERTEX4SPROC) glad_gl_on_demand_loader("glVertex4s");
    glad_glVertex4s(x, y, z, w);
}
PFNGLVERTEX4SPROC glad_glVertex4s = glad_on_demand_impl_glVertex4s;
static void GLAD_API_PTR glad_on_demand_impl_glVertex4sv(const GLshort * v) {
    glad_glVertex4sv = (PFNGLVERTEX4SVPROC) glad_gl_on_demand_loader("glVertex4sv");
    glad_glVertex4sv(v);
}
PFNGLVERTEX4SVPROC glad_glVertex4sv = glad_on_demand_impl_glVertex4sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1d(GLuint index, GLdouble x) {
    glad_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) glad_gl_on_demand_loader("glVertexAttrib1d");
    glad_glVertexAttrib1d(index, x);
}
PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d = glad_on_demand_impl_glVertexAttrib1d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) glad_gl_on_demand_loader("glVertexAttrib1dv");
    glad_glVertexAttrib1dv(index, v);
}
PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv = glad_on_demand_impl_glVertexAttrib1dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1f(GLuint index, GLfloat x) {
    glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) glad_gl_on_demand_loader("glVertexAttrib1f");
    glad_glVertexAttrib1f(index, x);
}
PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f = glad_on_demand_impl_glVertexAttrib1f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) glad_gl_on_demand_loader("glVertexAttrib1fv");
    glad_glVertexAttrib1fv(index, v);
}
PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv = glad_on_demand_impl_glVertexAttrib1fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1s(GLuint index, GLshort x) {
    glad_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) glad_gl_on_demand_loader("glVertexAttrib1s");
    glad_glVertexAttrib1s(index, x);
}
PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s = glad_on_demand_impl_glVertexAttrib1s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) glad_gl_on_demand_loader("glVertexAttrib1sv");
    glad_glVertexAttrib1sv(index, v);
}
PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv = glad_on_demand_impl_glVertexAttrib1sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
    glad_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) glad_gl_on_demand_loader("glVertexAttrib2d");
    glad_glVertexAttrib2d(index, x, y);
}
PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d = glad_on_demand_impl_glVertexAttrib2d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) glad_gl_on_demand_loader("glVertexAttrib2dv");
    glad_glVertexAttrib2dv(index, v);
}
PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv = glad_on_demand_impl_glVertexAttrib2dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) glad_gl_on_demand_loader("glVertexAttrib2f");
    glad_glVertexAttrib2f(index, x, y);
}
PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f = glad_on_demand_impl_glVertexAttrib2f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) glad_gl_on_demand_loader("glVertexAttrib2fv");
    glad_glVertexAttrib2fv(index, v);
}
PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv = glad_on_demand_impl_glVertexAttrib2fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2s(GLuint index, GLshort x, GLshort y) {
    glad_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) glad_gl_on_demand_loader("glVertexAttrib2s");
    glad_glVertexAttrib2s(index, x, y);
}
PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s = glad_on_demand_impl_glVertexAttrib2s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) glad_gl_on_demand_loader("glVertexAttrib2sv");
    glad_glVertexAttrib2sv(index, v);
}
PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv = glad_on_demand_impl_glVertexAttrib2sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    glad_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) glad_gl_on_demand_loader("glVertexAttrib3d");
    glad_glVertexAttrib3d(index, x, y, z);
}
PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d = glad_on_demand_impl_glVertexAttrib3d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) glad_gl_on_demand_loader("glVertexAttrib3dv");
    glad_glVertexAttrib3dv(index, v);
}
PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv = glad_on_demand_impl_glVertexAttrib3dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) glad_gl_on_demand_loader("glVertexAttrib3f");
    glad_glVertexAttrib3f(index, x, y, z);
}
PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f = glad_on_demand_impl_glVertexAttrib3f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) glad_gl_on_demand_loader("glVertexAttrib3fv");
    glad_glVertexAttrib3fv(index, v);
}
PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv = glad_on_demand_impl_glVertexAttrib3fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
    glad_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) glad_gl_on_demand_loader("glVertexAttrib3s");
    glad_glVertexAttrib3s(index, x, y, z);
}
PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s = glad_on_demand_impl_glVertexAttrib3s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) glad_gl_on_demand_loader("glVertexAttrib3sv");
    glad_glVertexAttrib3sv(index, v);
}
PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv = glad_on_demand_impl_glVertexAttrib3sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nbv(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nbv");
    glad_glVertexAttrib4Nbv(index, v);
}
PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv = glad_on_demand_impl_glVertexAttrib4Nbv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Niv(GLuint index, const GLint * v) {
    glad_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) glad_gl_on_demand_loader("glVertexAttrib4Niv");
    glad_glVertexAttrib4Niv(index, v);
}
PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv = glad_on_demand_impl_glVertexAttrib4Niv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nsv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nsv");
    glad_glVertexAttrib4Nsv(index, v);
}
PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv = glad_on_demand_impl_glVertexAttrib4Nsv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    glad_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) glad_gl_on_demand_loader("glVertexAttrib4Nub");
    glad_glVertexAttrib4Nub(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub = glad_on_demand_impl_glVertexAttrib4Nub;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nubv");
    glad_glVertexAttrib4Nubv(index, v);
}
PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv = glad_on_demand_impl_glVertexAttrib4Nubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nuiv(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nuiv");
    glad_glVertexAttrib4Nuiv(index, v);
}
PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv = glad_on_demand_impl_glVertexAttrib4Nuiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nusv(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nusv");
    glad_glVertexAttrib4Nusv(index, v);
}
PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv = glad_on_demand_impl_glVertexAttrib4Nusv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4bv(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) glad_gl_on_demand_loader("glVertexAttrib4bv");
    glad_glVertexAttrib4bv(index, v);
}
PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv = glad_on_demand_impl_glVertexAttrib4bv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) glad_gl_on_demand_loader("glVertexAttrib4d");
    glad_glVertexAttrib4d(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d = glad_on_demand_impl_glVertexAttrib4d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) glad_gl_on_demand_loader("glVertexAttrib4dv");
    glad_glVertexAttrib4dv(index, v);
}
PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv = glad_on_demand_impl_glVertexAttrib4dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) glad_gl_on_demand_loader("glVertexAttrib4f");
    glad_glVertexAttrib4f(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f = glad_on_demand_impl_glVertexAttrib4f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) glad_gl_on_demand_loader("glVertexAttrib4fv");
    glad_glVertexAttrib4fv(index, v);
}
PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv = glad_on_demand_impl_glVertexAttrib4fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4iv(GLuint index, const GLint * v) {
    glad_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) glad_gl_on_demand_loader("glVertexAttrib4iv");
    glad_glVertexAttrib4iv(index, v);
}
PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv = glad_on_demand_impl_glVertexAttrib4iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) glad_gl_on_demand_loader("glVertexAttrib4s");
    glad_glVertexAttrib4s(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s = glad_on_demand_impl_glVertexAttrib4s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) glad_gl_on_demand_loader("glVertexAttrib4sv");
    glad_glVertexAttrib4sv(index, v);
}
PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv = glad_on_demand_impl_glVertexAttrib4sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) glad_gl_on_demand_loader("glVertexAttrib4ubv");
    glad_glVertexAttrib4ubv(index, v);
}
PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv = glad_on_demand_impl_glVertexAttrib4ubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) glad_gl_on_demand_loader("glVertexAttrib4uiv");
    glad_glVertexAttrib4uiv(index, v);
}
PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv = glad_on_demand_impl_glVertexAttrib4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4usv(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) glad_gl_on_demand_loader("glVertexAttrib4usv");
    glad_glVertexAttrib4usv(index, v);
}
PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv = glad_on_demand_impl_glVertexAttrib4usv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1i(GLuint index, GLint x) {
    glad_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) glad_gl_on_demand_loader("glVertexAttribI1i");
    glad_glVertexAttribI1i(index, x);
}
PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i = glad_on_demand_impl_glVertexAttribI1i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) glad_gl_on_demand_loader("glVertexAttribI1iv");
    glad_glVertexAttribI1iv(index, v);
}
PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv = glad_on_demand_impl_glVertexAttribI1iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1ui(GLuint index, GLuint x) {
    glad_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) glad_gl_on_demand_loader("glVertexAttribI1ui");
    glad_glVertexAttribI1ui(index, x);
}
PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui = glad_on_demand_impl_glVertexAttribI1ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) glad_gl_on_demand_loader("glVertexAttribI1uiv");
    glad_glVertexAttribI1uiv(index, v);
}
PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv = glad_on_demand_impl_glVertexAttribI1uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2i(GLuint index, GLint x, GLint y) {
    glad_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) glad_gl_on_demand_loader("glVertexAttribI2i");
    glad_glVertexAttribI2i(index, x, y);
}
PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i = glad_on_demand_impl_glVertexAttribI2i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) glad_gl_on_demand_loader("glVertexAttribI2iv");
    glad_glVertexAttribI2iv(index, v);
}
PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv = glad_on_demand_impl_glVertexAttribI2iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) {
    glad_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) glad_gl_on_demand_loader("glVertexAttribI2ui");
    glad_glVertexAttribI2ui(index, x, y);
}
PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui = glad_on_demand_impl_glVertexAttribI2ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) glad_gl_on_demand_loader("glVertexAttribI2uiv");
    glad_glVertexAttribI2uiv(index, v);
}
PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv = glad_on_demand_impl_glVertexAttribI2uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {
    glad_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) glad_gl_on_demand_loader("glVertexAttribI3i");
    glad_glVertexAttribI3i(index, x, y, z);
}
PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i = glad_on_demand_impl_glVertexAttribI3i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) glad_gl_on_demand_loader("glVertexAttribI3iv");
    glad_glVertexAttribI3iv(index, v);
}
PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv = glad_on_demand_impl_glVertexAttribI3iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {
    glad_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) glad_gl_on_demand_loader("glVertexAttribI3ui");
    glad_glVertexAttribI3ui(index, x, y, z);
}
PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui = glad_on_demand_impl_glVertexAttribI3ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) glad_gl_on_demand_loader("glVertexAttribI3uiv");
    glad_glVertexAttribI3uiv(index, v);
}
PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv = glad_on_demand_impl_glVertexAttribI3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4bv(GLuint index, const GLbyte * v) {
    glad_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) glad_gl_on_demand_loader("glVertexAttribI4bv");
    glad_glVertexAttribI4bv(index, v);
}
PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv = glad_on_demand_impl_glVertexAttribI4bv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    glad_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) glad_gl_on_demand_loader("glVertexAttribI4i");
    glad_glVertexAttribI4i(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i = glad_on_demand_impl_glVertexAttribI4i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) glad_gl_on_demand_loader("glVertexAttribI4iv");
    glad_glVertexAttribI4iv(index, v);
}
PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv = glad_on_demand_impl_glVertexAttribI4iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4sv(GLuint index, const GLshort * v) {
    glad_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) glad_gl_on_demand_loader("glVertexAttribI4sv");
    glad_glVertexAttribI4sv(index, v);
}
PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv = glad_on_demand_impl_glVertexAttribI4sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) glad_gl_on_demand_loader("glVertexAttribI4ubv");
    glad_glVertexAttribI4ubv(index, v);
}
PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv = glad_on_demand_impl_glVertexAttribI4ubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    glad_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) glad_gl_on_demand_loader("glVertexAttribI4ui");
    glad_glVertexAttribI4ui(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui = glad_on_demand_impl_glVertexAttribI4ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) glad_gl_on_demand_loader("glVertexAttribI4uiv");
    glad_glVertexAttribI4uiv(index, v);
}
PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv = glad_on_demand_impl_glVertexAttribI4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4usv(GLuint index, const GLushort * v) {
    glad_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) glad_gl_on_demand_loader("glVertexAttribI4usv");
    glad_glVertexAttribI4usv(index, v);
}
PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv = glad_on_demand_impl_glVertexAttribI4usv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) glad_gl_on_demand_loader("glVertexAttribIPointer");
    glad_glVertexAttribIPointer(index, size, type, stride, pointer);
}
PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer = glad_on_demand_impl_glVertexAttribIPointer;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glad_gl_on_demand_loader("glVertexAttribPointer");
    glad_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = glad_on_demand_impl_glVertexAttribPointer;
static void GLAD_API_PTR glad_on_demand_impl_glVertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glVertexPointer = (PFNGLVERTEXPOINTERPROC) glad_gl_on_demand_loader("glVertexPointer");
    glad_glVertexPointer(size, type, stride, pointer);
}
PFNGLVERTEXPOINTERPROC glad_glVertexPointer = glad_on_demand_impl_glVertexPointer;
static void GLAD_API_PTR glad_on_demand_impl_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glViewport = (PFNGLVIEWPORTPROC) glad_gl_on_demand_loader("glViewport");
    glad_glViewport(x, y, width, height);
}
PFNGLVIEWPORTPROC glad_glViewport = glad_on_demand_impl_glViewport;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2d(GLdouble x, GLdouble y) {
    glad_glWindowPos2d = (PFNGLWINDOWPOS2DPROC) glad_gl_on_demand_loader("glWindowPos2d");
    glad_glWindowPos2d(x, y);
}
PFNGLWINDOWPOS2DPROC glad_glWindowPos2d = glad_on_demand_impl_glWindowPos2d;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2dv(const GLdouble * v) {
    glad_glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC) glad_gl_on_demand_loader("glWindowPos2dv");
    glad_glWindowPos2dv(v);
}
PFNGLWINDOWPOS2DVPROC glad_glWindowPos2dv = glad_on_demand_impl_glWindowPos2dv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2f(GLfloat x, GLfloat y) {
    glad_glWindowPos2f = (PFNGLWINDOWPOS2FPROC) glad_gl_on_demand_loader("glWindowPos2f");
    glad_glWindowPos2f(x, y);
}
PFNGLWINDOWPOS2FPROC glad_glWindowPos2f = glad_on_demand_impl_glWindowPos2f;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2fv(const GLfloat * v) {
    glad_glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC) glad_gl_on_demand_loader("glWindowPos2fv");
    glad_glWindowPos2fv(v);
}
PFNGLWINDOWPOS2FVPROC glad_glWindowPos2fv = glad_on_demand_impl_glWindowPos2fv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2i(GLint x, GLint y) {
    glad_glWindowPos2i = (PFNGLWINDOWPOS2IPROC) glad_gl_on_demand_loader("glWindowPos2i");
    glad_glWindowPos2i(x, y);
}
PFNGLWINDOWPOS2IPROC glad_glWindowPos2i = glad_on_demand_impl_glWindowPos2i;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2iv(const GLint * v) {
    glad_glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC) glad_gl_on_demand_loader("glWindowPos2iv");
    glad_glWindowPos2iv(v);
}
PFNGLWINDOWPOS2IVPROC glad_glWindowPos2iv = glad_on_demand_impl_glWindowPos2iv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2s(GLshort x, GLshort y) {
    glad_glWindowPos2s = (PFNGLWINDOWPOS2SPROC) glad_gl_on_demand_loader("glWindowPos2s");
    glad_glWindowPos2s(x, y);
}
PFNGLWINDOWPOS2SPROC glad_glWindowPos2s = glad_on_demand_impl_glWindowPos2s;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos2sv(const GLshort * v) {
    glad_glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC) glad_gl_on_demand_loader("glWindowPos2sv");
    glad_glWindowPos2sv(v);
}
PFNGLWINDOWPOS2SVPROC glad_glWindowPos2sv = glad_on_demand_impl_glWindowPos2sv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3d(GLdouble x, GLdouble y, GLdouble z) {
    glad_glWindowPos3d = (PFNGLWINDOWPOS3DPROC) glad_gl_on_demand_loader("glWindowPos3d");
    glad_glWindowPos3d(x, y, z);
}
PFNGLWINDOWPOS3DPROC glad_glWindowPos3d = glad_on_demand_impl_glWindowPos3d;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3dv(const GLdouble * v) {
    glad_glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC) glad_gl_on_demand_loader("glWindowPos3dv");
    glad_glWindowPos3dv(v);
}
PFNGLWINDOWPOS3DVPROC glad_glWindowPos3dv = glad_on_demand_impl_glWindowPos3dv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3f(GLfloat x, GLfloat y, GLfloat z) {
    glad_glWindowPos3f = (PFNGLWINDOWPOS3FPROC) glad_gl_on_demand_loader("glWindowPos3f");
    glad_glWindowPos3f(x, y, z);
}
PFNGLWINDOWPOS3FPROC glad_glWindowPos3f = glad_on_demand_impl_glWindowPos3f;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3fv(const GLfloat * v) {
    glad_glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC) glad_gl_on_demand_loader("glWindowPos3fv");
    glad_glWindowPos3fv(v);
}
PFNGLWINDOWPOS3FVPROC glad_glWindowPos3fv = glad_on_demand_impl_glWindowPos3fv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3i(GLint x, GLint y, GLint z) {
    glad_glWindowPos3i = (PFNGLWINDOWPOS3IPROC) glad_gl_on_demand_loader("glWindowPos3i");
    glad_glWindowPos3i(x, y, z);
}
PFNGLWINDOWPOS3IPROC glad_glWindowPos3i = glad_on_demand_impl_glWindowPos3i;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3iv(const GLint * v) {
    glad_glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC) glad_gl_on_demand_loader("glWindowPos3iv");
    glad_glWindowPos3iv(v);
}
PFNGLWINDOWPOS3IVPROC glad_glWindowPos3iv = glad_on_demand_impl_glWindowPos3iv;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3s(GLshort x, GLshort y, GLshort z) {
    glad_glWindowPos3s = (PFNGLWINDOWPOS3SPROC) glad_gl_on_demand_loader("glWindowPos3s");
    glad_glWindowPos3s(x, y, z);
}
PFNGLWINDOWPOS3SPROC glad_glWindowPos3s = glad_on_demand_impl_glWindowPos3s;
static void GLAD_API_PTR glad_on_demand_impl_glWindowPos3sv(const GLshort * v) {
    glad_glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC) glad_gl_on_demand_loader("glWindowPos3sv");
    glad_glWindowPos3sv(v);
}
PFNGLWINDOWPOS3SVPROC glad_glWindowPos3sv = glad_on_demand_impl_glWindowPos3sv;


 


#ifdef __cplusplus
}
#endif
