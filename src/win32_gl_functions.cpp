#include <core/gl_functions.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <functional>
#include <string>
#include <sstream>

PFNGLGETSTRINGIPROC glGetStringi = 0;

namespace opengl_core
{
  void gl_functions::configure(const render_context &context)
  {
    symbol_loader sym_loader("OpenGL32.dll");
    assert(sym_loader.get_good() && "Failed to load OpenGL32.dll");

    // NOTE: glext.h from https://www.opengl.org/registry/api/GL/glext.h
    // intitially groups functions by versions. Then it groups by extensions.
    // Some extensions are duplicated. Duplicates have the appropriate suffix.
    // e.g. ARB, NV, ..., etc.
    typedef std::function<void(symbol_loader *)> load_func;
    std::pair<std::vector<int>, load_func> versions[] =
    {
      std::make_pair<std::vector<int>, load_func>({3, 0}, std::bind(
        &opengl_core::gl_functions::load_3_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({2, 1}, std::bind(
        &opengl_core::gl_functions::load_2_1, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({2, 0}, std::bind(
        &opengl_core::gl_functions::load_2_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 5}, std::bind(
        &opengl_core::gl_functions::load_1_5, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 4}, std::bind(
        &opengl_core::gl_functions::load_1_4, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 3}, std::bind(
        &opengl_core::gl_functions::load_1_3, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 2}, std::bind(
        &opengl_core::gl_functions::load_1_2, &sym_loader))
    };
    for (auto version : versions) {
      if (version.first[0] <= context.query_major_version() &&
        version.first[1] <= context.query_minor_version()) {
        version.second(&sym_loader);
      }
    }

    std::vector<std::string> extensions_vector;

    if (context.query_major_version() >= 3) {
      glGetStringi = (PFNGLGETSTRINGIPROC)sym_loader.load("glGetStringi");
      assert(glGetStringi && "Could not acquire glGetStringi");

      std::cout << "Extensions availiable for (using glGetStringi()): "
        << context.query_major_version() << "."
        << context.query_minor_version() << " versioned context " << std::endl;
      GLint n = 0;
      glGetIntegerv(GL_NUM_EXTENSIONS, &n);
      for (GLint i = 0; i < n; ++i) {
        const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
        extensions_vector.push_back(extension);
      }
    } else {
      std::cout << "Extensions availiable for (using glGetString(): "
        << context.query_major_version() << "."
        << context.query_minor_version() << " versioned context " << std::endl;

      const GLubyte *extensions = glGetString(GL_EXTENSIONS);
      std::string std_extensions((const char*)extensions);
      std::replace(std_extensions.begin(), std_extensions.end(), ' ', '\n');
      std::stringstream ss(std_extensions);

      while (ss.good()) {
        std::string extension;
        std::getline(ss, extension);
        extensions_vector.push_back(extension);
      }
    }
  }
}

// OpenGL 1.2
PFNGLMINMAXPROC glMinmax = 0;
PFNGLGETMINMAXPROC glGetMinmax = 0;
PFNGLHISTOGRAMPROC glHistogram = 0;
PFNGLBLENDCOLORPROC glBlendColor = 0;
PFNGLCOLORTABLEPROC glColorTable = 0;
PFNGLTEXIMAGE3DPROC glTexImage3D = 0;
PFNGLRESETMINMAXPROC glResetMinmax = 0;
PFNGLGETHISTOGRAMPROC glGetHistogram = 0;
PFNGLBLENDEQUATIONPROC glBlendEquation = 0;
PFNGLGETCOLORTABLEPROC glGetColorTable = 0;
PFNGLCOLORSUBTABLEPROC glColorSubTable = 0;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = 0;
PFNGLCOPYCOLORTABLEPROC glCopyColorTable = 0;
PFNGLRESETHISTOGRAMPROC glResetHistogram = 0;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = 0;
PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable = 0;
PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = 0;
PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter = 0;
PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D = 0;
PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D = 0;
PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter = 0;
PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv = 0;
PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv = 0;
PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv = 0;
PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv = 0;
PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf = 0;
PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri = 0;
PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv = 0;
PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv = 0;
PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D = 0;
PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D = 0;
PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv = 0;
PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv = 0;
PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv = 0;
PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv = 0;
PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv = 0;
PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv = 0;

// OpenGL 1.3
PFNGLACTIVETEXTUREPROC glActiveTexture = 0;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = 0;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = 0;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = 0;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = 0;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = 0;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = 0;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = 0;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = 0;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = 0;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = 0;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = 0;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = 0;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = 0;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = 0;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = 0;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = 0;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = 0;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = 0;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = 0;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = 0;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = 0;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = 0;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = 0;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = 0;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = 0;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = 0;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = 0;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = 0;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = 0;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = 0;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = 0;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = 0;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = 0;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = 0;
PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = 0;
PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = 0;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = 0;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = 0;

// OpenGL 1.4
PFNGLFOGCOORDFPROC glFogCoordf = 0;
PFNGLFOGCOORDDPROC glFogCoordd = 0;
PFNGLFOGCOORDFVPROC glFogCoordfv = 0;
PFNGLFOGCOORDDVPROC glFogCoorddv = 0;
PFNGLWINDOWPOS2DPROC glWindowPos2d = 0;
PFNGLWINDOWPOS2FPROC glWindowPos2f = 0;
PFNGLWINDOWPOS2IPROC glWindowPos2i = 0;
PFNGLWINDOWPOS2SPROC glWindowPos2s = 0;
PFNGLWINDOWPOS3DPROC glWindowPos3d = 0;
PFNGLWINDOWPOS3FPROC glWindowPos3f = 0;
PFNGLWINDOWPOS3IPROC glWindowPos3i = 0;
PFNGLWINDOWPOS3SPROC glWindowPos3s = 0;
PFNGLWINDOWPOS2DVPROC glWindowPos2dv = 0;
PFNGLWINDOWPOS2FVPROC glWindowPos2fv = 0;
PFNGLWINDOWPOS2IVPROC glWindowPos2iv = 0;
PFNGLWINDOWPOS2SVPROC glWindowPos2sv = 0;
PFNGLWINDOWPOS3DVPROC glWindowPos3dv = 0;
PFNGLWINDOWPOS3FVPROC glWindowPos3fv = 0;
PFNGLWINDOWPOS3IVPROC glWindowPos3iv = 0;
PFNGLWINDOWPOS3SVPROC glWindowPos3sv = 0;
PFNGLFOGCOORDPOINTERPROC glFogCoordPointer = 0;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = 0;
PFNGLPOINTPARAMETERFPROC glPointParameterf = 0;
PFNGLPOINTPARAMETERIPROC glPointParameteri = 0;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = 0;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = 0;
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = 0;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = 0;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = 0;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = 0;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = 0;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = 0;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = 0;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = 0;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = 0;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = 0;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = 0;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = 0;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = 0;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = 0;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = 0;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = 0;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = 0;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = 0;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = 0;

// OpenGL 1.5
PFNGLISQUERYPROC glIsQuery = 0;
PFNGLENDQUERYPROC glEndQuery = 0;
PFNGLISBUFFERPROC glIsBuffer = 0;
PFNGLMAPBUFFERPROC glMapBuffer = 0;
PFNGLGENQUERIESPROC glGenQueries = 0;
PFNGLBEGINQUERYPROC glBeginQuery = 0;
PFNGLGETQUERYIVPROC glGetQueryiv = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = 0;
PFNGLDELETEQUERIESPROC glDeleteQueries = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
PFNGLBUFFERSUBDATAPROC glBufferSubData = 0;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = 0;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = 0;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = 0;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = 0;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = 0;

// OpenGL 2.0
PFNGLISSHADERPROC glIsShader = 0;
PFNGLISPROGRAMPROC glIsProgram = 0;
PFNGLUNIFORM1FPROC glUniform1f = 0;
PFNGLUNIFORM2FPROC glUniform2f = 0;
PFNGLUNIFORM3FPROC glUniform3f = 0;
PFNGLUNIFORM4FPROC glUniform4f = 0;
PFNGLUNIFORM1IPROC glUniform1i = 0;
PFNGLUNIFORM2IPROC glUniform2i = 0;
PFNGLUNIFORM3IPROC glUniform3i = 0;
PFNGLUNIFORM4IPROC glUniform4i = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLUNIFORM1FVPROC glUniform1fv = 0;
PFNGLUNIFORM2FVPROC glUniform2fv = 0;
PFNGLUNIFORM3FVPROC glUniform3fv = 0;
PFNGLUNIFORM4FVPROC glUniform4fv = 0;
PFNGLUNIFORM1IVPROC glUniform1iv = 0;
PFNGLUNIFORM2IVPROC glUniform2iv = 0;
PFNGLUNIFORM3IVPROC glUniform3iv = 0;
PFNGLUNIFORM4IVPROC glUniform4iv = 0;
PFNGLDRAWBUFFERSPROC glDrawBuffers = 0;
PFNGLGETSHADERIVPROC glGetShaderiv = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLDETACHSHADERPROC glDetachShader = 0;
PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
PFNGLGETUNIFORMFVPROC glGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC glGetUniformiv = 0;
PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = 0;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = 0;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = 0;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = 0;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = 0;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = 0;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = 0;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = 0;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = 0;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = 0;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = 0;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = 0;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = 0;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = 0;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = 0;

// OpenGL 2.1
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = 0;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = 0;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = 0;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = 0;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = 0;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = 0;

// OpenGL 3.0
// OpenGL 3.0 also reuses entry points from these extensions:
//  ARB_framebuffer_object
//  ARB_map_buffer_range
//  ARB_vertex_array_object
PFNGLENABLEIPROC glEnablei = 0;
PFNGLDISABLEIPROC glDisablei = 0;
PFNGLCOLORMASKIPROC glColorMaski = 0;
PFNGLISENABLEDIPROC glIsEnabledi = 0;
PFNGLCLAMPCOLORPROC glClampColor = 0;
PFNGLUNIFORM1UIPROC glUniform1ui = 0;
PFNGLUNIFORM2UIPROC glUniform2ui = 0;
PFNGLUNIFORM3UIPROC glUniform3ui = 0;
PFNGLUNIFORM4UIPROC glUniform4ui = 0;
PFNGLUNIFORM1UIVPROC glUniform1uiv = 0;
PFNGLUNIFORM2UIVPROC glUniform2uiv = 0;
PFNGLUNIFORM3UIVPROC glUniform3uiv = 0;
PFNGLUNIFORM4UIVPROC glUniform4uiv = 0;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = 0;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = 0;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = 0;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = 0;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = 0;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = 0;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = 0;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = 0;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = 0;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = 0;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = 0;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = 0;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = 0;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = 0;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = 0;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = 0;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = 0;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = 0;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = 0;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = 0;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = 0;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = 0;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = 0;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = 0;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = 0;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = 0;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = 0;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = 0;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = 0;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = 0;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = 0;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = 0;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = 0;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = 0;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = 0;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = 0;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = 0;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = 0;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = 0;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = 0;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = 0;

#define LOAD_GL_FUNCTION(type, name, sym_loader) \
  name = (type)sym_loader->load(#name); \
  assert(name != nullptr); \
  std::cout << "Successfully Loaded " << (#name) << " @" << std::hex \
    << (&name) << std::dec << std::endl;

namespace opengl_core
{
  void gl_functions::load_1_2(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 1.2 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLMINMAXPROC, glMinmax, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETMINMAXPROC, glGetMinmax, sym_loader);
    LOAD_GL_FUNCTION(PFNGLHISTOGRAMPROC, glHistogram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBLENDCOLORPROC, glBlendColor, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOLORTABLEPROC, glColorTable, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXIMAGE3DPROC, glTexImage3D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLRESETMINMAXPROC, glResetMinmax, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETHISTOGRAMPROC, glGetHistogram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBLENDEQUATIONPROC, glBlendEquation, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCOLORTABLEPROC, glGetColorTable, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOLORSUBTABLEPROC, glColorSubTable, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYCOLORTABLEPROC, glCopyColorTable, sym_loader);
    LOAD_GL_FUNCTION(PFNGLRESETHISTOGRAMPROC, glResetHistogram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYCOLORSUBTABLEPROC, glCopyColorSubTable,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSEPARABLEFILTER2DPROC, glSeparableFilter2D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETSEPARABLEFILTERPROC, glGetSeparableFilter,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONFILTER1DPROC, glConvolutionFilter1D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONFILTER2DPROC, glConvolutionFilter2D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCONVOLUTIONFILTERPROC, glGetConvolutionFilter,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETMINMAXPARAMETERFVPROC, glGetMinmaxParameterfv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETMINMAXPARAMETERIVPROC, glGetMinmaxParameteriv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOLORTABLEPARAMETERFVPROC, glColorTableParameterfv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOLORTABLEPARAMETERIVPROC, glColorTableParameteriv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONPARAMETERFPROC, glConvolutionParameterf,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONPARAMETERIPROC, glConvolutionParameteri,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONPARAMETERFVPROC, glConvolutionParameterfv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCONVOLUTIONPARAMETERIVPROC, glConvolutionParameteriv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYCONVOLUTIONFILTER1DPROC,
      glCopyConvolutionFilter1D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYCONVOLUTIONFILTER2DPROC,
      glCopyConvolutionFilter2D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETHISTOGRAMPARAMETERFVPROC,
      glGetHistogramParameterfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETHISTOGRAMPARAMETERIVPROC,
      glGetHistogramParameteriv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCOLORTABLEPARAMETERFVPROC,
      glGetColorTableParameterfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCOLORTABLEPARAMETERIVPROC,
      glGetColorTableParameteriv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCONVOLUTIONPARAMETERFVPROC,
      glGetConvolutionParameterfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCONVOLUTIONPARAMETERIVPROC,
      glGetConvolutionParameteriv, sym_loader);
  }

  void gl_functions::load_1_3(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 1.3 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLACTIVETEXTUREPROC, glActiveTexture, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLLOADTRANSPOSEMATRIXFPROC, glLoadTransposeMatrixf,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLLOADTRANSPOSEMATRIXDPROC, glLoadTransposeMatrixd,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTTRANSPOSEMATRIXFPROC, glMultTransposeMatrixf,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTTRANSPOSEMATRIXDPROC, glMultTransposeMatrixd,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,
      glCompressedTexSubImage3D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,
      glCompressedTexSubImage2D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC,
      glCompressedTexSubImage1D, sym_loader);
  }

  void gl_functions::load_1_4(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 1.4 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLFOGCOORDFPROC, glFogCoordf, sym_loader);
    LOAD_GL_FUNCTION(PFNGLFOGCOORDDPROC, glFogCoordd, sym_loader);
    LOAD_GL_FUNCTION(PFNGLFOGCOORDFVPROC, glFogCoordfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLFOGCOORDDVPROC, glFogCoorddv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2DPROC, glWindowPos2d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2FPROC, glWindowPos2f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2IPROC, glWindowPos2i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2SPROC, glWindowPos2s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3DPROC, glWindowPos3d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3FPROC, glWindowPos3f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3IPROC, glWindowPos3i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3SPROC, glWindowPos3s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2DVPROC, glWindowPos2dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2FVPROC, glWindowPos2fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2IVPROC, glWindowPos2iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS2SVPROC, glWindowPos2sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3DVPROC, glWindowPos3dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3FVPROC, glWindowPos3fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3IVPROC, glWindowPos3iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLWINDOWPOS3SVPROC, glWindowPos3sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLFOGCOORDPOINTERPROC, glFogCoordPointer, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays, sym_loader);
    LOAD_GL_FUNCTION(PFNGLPOINTPARAMETERFPROC, glPointParameterf, sym_loader);
    LOAD_GL_FUNCTION(PFNGLPOINTPARAMETERIPROC, glPointParameteri, sym_loader);
    LOAD_GL_FUNCTION(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3BPROC, glSecondaryColor3b, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3DPROC, glSecondaryColor3d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3FPROC, glSecondaryColor3f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3IPROC, glSecondaryColor3i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3SPROC, glSecondaryColor3s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3BVPROC, glSecondaryColor3bv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3DVPROC, glSecondaryColor3dv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3FVPROC, glSecondaryColor3fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3IVPROC, glSecondaryColor3iv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3SVPROC, glSecondaryColor3sv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3UBPROC, glSecondaryColor3ub,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3UIPROC, glSecondaryColor3ui,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3USPROC, glSecondaryColor3us,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3UBVPROC, glSecondaryColor3ubv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3UIVPROC, glSecondaryColor3uiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLOR3USVPROC, glSecondaryColor3usv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSECONDARYCOLORPOINTERPROC, glSecondaryColorPointer,
      sym_loader);
  }

  void gl_functions::load_1_5(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 1.5 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLISQUERYPROC, glIsQuery, sym_loader);
    LOAD_GL_FUNCTION(PFNGLENDQUERYPROC, glEndQuery, sym_loader);
    LOAD_GL_FUNCTION(PFNGLISBUFFERPROC, glIsBuffer, sym_loader);
    LOAD_GL_FUNCTION(PFNGLMAPBUFFERPROC, glMapBuffer, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGENQUERIESPROC, glGenQueries, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBEGINQUERYPROC, glBeginQuery, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETQUERYIVPROC, glGetQueryiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBINDBUFFERPROC, glBindBuffer, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBUFFERDATAPROC, glBufferData, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNMAPBUFFERPROC, glUnmapBuffer, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDELETEQUERIESPROC, glDeleteQueries, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBUFFERSUBDATAPROC, glBufferSubData, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv,
      sym_loader);
  }

  void gl_functions::load_2_0(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 2.0 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLISSHADERPROC, glIsShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLISPROGRAMPROC, glIsProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1FPROC, glUniform1f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2FPROC, glUniform2f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3FPROC, glUniform3f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4FPROC, glUniform4f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1IPROC, glUniform1i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2IPROC, glUniform2i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3IPROC, glUniform3i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4IPROC, glUniform4i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUSEPROGRAMPROC, glUseProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1FVPROC, glUniform1fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2FVPROC, glUniform2fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3FVPROC, glUniform3fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4FVPROC, glUniform4fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1IVPROC, glUniform1iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2IVPROC, glUniform2iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3IVPROC, glUniform3iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4IVPROC, glUniform4iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDRAWBUFFERSPROC, glDrawBuffers, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETSHADERIVPROC, glGetShaderiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLLINKPROGRAMPROC, glLinkProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLATTACHSHADERPROC, glAttachShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCREATESHADERPROC, glCreateShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDELETESHADERPROC, glDeleteShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDETACHSHADERPROC, glDetachShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETPROGRAMIVPROC, glGetProgramiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETUNIFORMFVPROC, glGetUniformfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETUNIFORMIVPROC, glGetUniformiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSHADERSOURCEPROC, glShaderSource, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOMPILESHADERPROC, glCompileShader, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCREATEPROGRAMPROC, glCreateProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETSHADERSOURCEPROC, glGetShaderSource, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVALIDATEPROGRAMPROC, glValidateProgram, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC,
      glEnableVertexAttribArray, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBPOINTERVPROC,
      glGetVertexAttribPointerv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDISABLEVERTEXATTRIBARRAYPROC,
      glDisableVertexAttribArray, sym_loader);
  }

  void gl_functions::load_2_1(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 2.1 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv,
      sym_loader);
  }

  void gl_functions::load_3_0(symbol_loader *sym_loader)
  {
    std::cout << "Loading OpenGL 3.0 Functions " << std::endl;
    LOAD_GL_FUNCTION(PFNGLENABLEIPROC, glEnablei, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDISABLEIPROC, glDisablei, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOLORMASKIPROC, glColorMaski, sym_loader);
    LOAD_GL_FUNCTION(PFNGLISENABLEDIPROC, glIsEnabledi, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLAMPCOLORPROC, glClampColor, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1UIPROC, glUniform1ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2UIPROC, glUniform2ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3UIPROC, glUniform3ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4UIPROC, glUniform4ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM1UIVPROC, glUniform1uiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM2UIVPROC, glUniform2uiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM3UIVPROC, glUniform3uiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLUNIFORM4UIVPROC, glUniform4uiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERIVPROC, glClearBufferiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERFVPROC, glClearBufferfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERFIPROC, glClearBufferfi, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBINDBUFFERBASEPROC, glBindBufferBase, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLTRANSFORMFEEDBACKVARYINGSPROC,
      glTransformFeedbackVaryings, sym_loader);
    LOAD_GL_FUNCTION(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC,
      glGetTransformFeedbackVarying, sym_loader);
  }
}
