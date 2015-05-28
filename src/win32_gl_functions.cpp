#include <core/gl_functions.h>

#include <core/win32_error_handler.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <functional>
#include <string>
#include <sstream>

PFNGLCOPYTEXSUBIMAGE3DPROC opengl_core_CopyTexSubImage3D = NULL;
PFNGLDRAWRANGEELEMENTSPROC opengl_core_DrawRangeElements = NULL;
PFNGLTEXIMAGE3DPROC opengl_core_TexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC opengl_core_TexSubImage3D = NULL;

PFNGLACTIVETEXTUREPROC opengl_core_ActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTUREPROC opengl_core_ClientActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC opengl_core_CompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC opengl_core_CompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC opengl_core_CompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC opengl_core_CompressedTexSubImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC opengl_core_CompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC opengl_core_CompressedTexSubImage3D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC opengl_core_GetCompressedTexImage = NULL;
PFNGLLOADTRANSPOSEMATRIXDPROC opengl_core_LoadTransposeMatrixd = NULL;
PFNGLLOADTRANSPOSEMATRIXFPROC opengl_core_LoadTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXDPROC opengl_core_MultTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXFPROC opengl_core_MultTransposeMatrixf = NULL;
PFNGLMULTITEXCOORD1DPROC opengl_core_MultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DVPROC opengl_core_MultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1FPROC opengl_core_MultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FVPROC opengl_core_MultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1IPROC opengl_core_MultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IVPROC opengl_core_MultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1SPROC opengl_core_MultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SVPROC opengl_core_MultiTexCoord1sv = NULL;
PFNGLMULTITEXCOORD2DPROC opengl_core_MultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DVPROC opengl_core_MultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2FPROC opengl_core_MultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FVPROC opengl_core_MultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2IPROC opengl_core_MultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IVPROC opengl_core_MultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2SPROC opengl_core_MultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SVPROC opengl_core_MultiTexCoord2sv = NULL;
PFNGLMULTITEXCOORD3DPROC opengl_core_MultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DVPROC opengl_core_MultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3FPROC opengl_core_MultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FVPROC opengl_core_MultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3IPROC opengl_core_MultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IVPROC opengl_core_MultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3SPROC opengl_core_MultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SVPROC opengl_core_MultiTexCoord3sv = NULL;
PFNGLMULTITEXCOORD4DPROC opengl_core_MultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DVPROC opengl_core_MultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4FPROC opengl_core_MultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FVPROC opengl_core_MultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4IPROC opengl_core_MultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IVPROC opengl_core_MultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4SPROC opengl_core_MultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SVPROC opengl_core_MultiTexCoord4sv = NULL;
PFNGLSAMPLECOVERAGEPROC opengl_core_SampleCoverage = NULL;

PFNGLBLENDCOLORPROC opengl_core_BlendColor = NULL;
PFNGLBLENDEQUATIONPROC opengl_core_BlendEquation = NULL;
PFNGLBLENDFUNCSEPARATEPROC opengl_core_BlendFuncSeparate = NULL;
PFNGLFOGCOORDPOINTERPROC opengl_core_FogCoordPointer = NULL;
PFNGLFOGCOORDDPROC opengl_core_FogCoordd = NULL;
PFNGLFOGCOORDDVPROC opengl_core_FogCoorddv = NULL;
PFNGLFOGCOORDFPROC opengl_core_FogCoordf = NULL;
PFNGLFOGCOORDFVPROC opengl_core_FogCoordfv = NULL;
PFNGLMULTIDRAWARRAYSPROC opengl_core_MultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTSPROC opengl_core_MultiDrawElements = NULL;
PFNGLPOINTPARAMETERFPROC opengl_core_PointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC opengl_core_PointParameterfv = NULL;
PFNGLPOINTPARAMETERIPROC opengl_core_PointParameteri = NULL;
PFNGLPOINTPARAMETERIVPROC opengl_core_PointParameteriv = NULL;
PFNGLSECONDARYCOLOR3BPROC opengl_core_SecondaryColor3b = NULL;
PFNGLSECONDARYCOLOR3BVPROC opengl_core_SecondaryColor3bv = NULL;
PFNGLSECONDARYCOLOR3DPROC opengl_core_SecondaryColor3d = NULL;
PFNGLSECONDARYCOLOR3DVPROC opengl_core_SecondaryColor3dv = NULL;
PFNGLSECONDARYCOLOR3FPROC opengl_core_SecondaryColor3f = NULL;
PFNGLSECONDARYCOLOR3FVPROC opengl_core_SecondaryColor3fv = NULL;
PFNGLSECONDARYCOLOR3IPROC opengl_core_SecondaryColor3i = NULL;
PFNGLSECONDARYCOLOR3IVPROC opengl_core_SecondaryColor3iv = NULL;
PFNGLSECONDARYCOLOR3SPROC opengl_core_SecondaryColor3s = NULL;
PFNGLSECONDARYCOLOR3SVPROC opengl_core_SecondaryColor3sv = NULL;
PFNGLSECONDARYCOLOR3UBPROC opengl_core_SecondaryColor3ub = NULL;
PFNGLSECONDARYCOLOR3UBVPROC opengl_core_SecondaryColor3ubv = NULL;
PFNGLSECONDARYCOLOR3UIPROC opengl_core_SecondaryColor3ui = NULL;
PFNGLSECONDARYCOLOR3UIVPROC opengl_core_SecondaryColor3uiv = NULL;
PFNGLSECONDARYCOLOR3USPROC opengl_core_SecondaryColor3us = NULL;
PFNGLSECONDARYCOLOR3USVPROC opengl_core_SecondaryColor3usv = NULL;
PFNGLSECONDARYCOLORPOINTERPROC opengl_core_SecondaryColorPointer = NULL;
PFNGLWINDOWPOS2DPROC opengl_core_WindowPos2d = NULL;
PFNGLWINDOWPOS2DVPROC opengl_core_WindowPos2dv = NULL;
PFNGLWINDOWPOS2FPROC opengl_core_WindowPos2f = NULL;
PFNGLWINDOWPOS2FVPROC opengl_core_WindowPos2fv = NULL;
PFNGLWINDOWPOS2IPROC opengl_core_WindowPos2i = NULL;
PFNGLWINDOWPOS2IVPROC opengl_core_WindowPos2iv = NULL;
PFNGLWINDOWPOS2SPROC opengl_core_WindowPos2s = NULL;
PFNGLWINDOWPOS2SVPROC opengl_core_WindowPos2sv = NULL;
PFNGLWINDOWPOS3DPROC opengl_core_WindowPos3d = NULL;
PFNGLWINDOWPOS3DVPROC opengl_core_WindowPos3dv = NULL;
PFNGLWINDOWPOS3FPROC opengl_core_WindowPos3f = NULL;
PFNGLWINDOWPOS3FVPROC opengl_core_WindowPos3fv = NULL;
PFNGLWINDOWPOS3IPROC opengl_core_WindowPos3i = NULL;
PFNGLWINDOWPOS3IVPROC opengl_core_WindowPos3iv = NULL;
PFNGLWINDOWPOS3SPROC opengl_core_WindowPos3s = NULL;
PFNGLWINDOWPOS3SVPROC opengl_core_WindowPos3sv = NULL;

PFNGLBEGINQUERYPROC opengl_core_BeginQuery = NULL;
PFNGLBINDBUFFERPROC opengl_core_BindBuffer = NULL;
PFNGLBUFFERDATAPROC opengl_core_BufferData = NULL;
PFNGLBUFFERSUBDATAPROC opengl_core_BufferSubData = NULL;
PFNGLDELETEBUFFERSPROC opengl_core_DeleteBuffers = NULL;
PFNGLDELETEQUERIESPROC opengl_core_DeleteQueries = NULL;
PFNGLENDQUERYPROC opengl_core_EndQuery = NULL;
PFNGLGENBUFFERSPROC opengl_core_GenBuffers = NULL;
PFNGLGENQUERIESPROC opengl_core_GenQueries = NULL;
PFNGLGETBUFFERPARAMETERIVPROC opengl_core_GetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC opengl_core_GetBufferPointerv = NULL;
PFNGLGETBUFFERSUBDATAPROC opengl_core_GetBufferSubData = NULL;
PFNGLGETQUERYOBJECTIVPROC opengl_core_GetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIVPROC opengl_core_GetQueryObjectuiv = NULL;
PFNGLGETQUERYIVPROC opengl_core_GetQueryiv = NULL;
PFNGLISBUFFERPROC opengl_core_IsBuffer = NULL;
PFNGLISQUERYPROC opengl_core_IsQuery = NULL;
PFNGLMAPBUFFERPROC opengl_core_MapBuffer = NULL;
PFNGLUNMAPBUFFERPROC opengl_core_UnmapBuffer = NULL;

PFNGLATTACHSHADERPROC opengl_core_AttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC opengl_core_BindAttribLocation = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC opengl_core_BlendEquationSeparate = NULL;
PFNGLCOMPILESHADERPROC opengl_core_CompileShader = NULL;
PFNGLCREATEPROGRAMPROC opengl_core_CreateProgram = NULL;
PFNGLCREATESHADERPROC opengl_core_CreateShader = NULL;
PFNGLDELETEPROGRAMPROC opengl_core_DeleteProgram = NULL;
PFNGLDELETESHADERPROC opengl_core_DeleteShader = NULL;
PFNGLDETACHSHADERPROC opengl_core_DetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC opengl_core_DisableVertexAttribArray = NULL;
PFNGLDRAWBUFFERSPROC opengl_core_DrawBuffers = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC opengl_core_EnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIBPROC opengl_core_GetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC opengl_core_GetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERSPROC opengl_core_GetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC opengl_core_GetAttribLocation = NULL;
PFNGLGETPROGRAMINFOLOGPROC opengl_core_GetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC opengl_core_GetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC opengl_core_GetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCEPROC opengl_core_GetShaderSource = NULL;
PFNGLGETSHADERIVPROC opengl_core_GetShaderiv = NULL;
PFNGLGETUNIFORMLOCATIONPROC opengl_core_GetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC opengl_core_GetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC opengl_core_GetUniformiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC opengl_core_GetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBDVPROC opengl_core_GetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFVPROC opengl_core_GetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC opengl_core_GetVertexAttribiv = NULL;
PFNGLISPROGRAMPROC opengl_core_IsProgram = NULL;
PFNGLISSHADERPROC opengl_core_IsShader = NULL;
PFNGLLINKPROGRAMPROC opengl_core_LinkProgram = NULL;
PFNGLSHADERSOURCEPROC opengl_core_ShaderSource = NULL;
PFNGLSTENCILFUNCSEPARATEPROC opengl_core_StencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATEPROC opengl_core_StencilMaskSeparate = NULL;
PFNGLSTENCILOPSEPARATEPROC opengl_core_StencilOpSeparate = NULL;
PFNGLUNIFORM1FPROC opengl_core_Uniform1f = NULL;
PFNGLUNIFORM1FVPROC opengl_core_Uniform1fv = NULL;
PFNGLUNIFORM1IPROC opengl_core_Uniform1i = NULL;
PFNGLUNIFORM1IVPROC opengl_core_Uniform1iv = NULL;
PFNGLUNIFORM2FPROC opengl_core_Uniform2f = NULL;
PFNGLUNIFORM2FVPROC opengl_core_Uniform2fv = NULL;
PFNGLUNIFORM2IPROC opengl_core_Uniform2i = NULL;
PFNGLUNIFORM2IVPROC opengl_core_Uniform2iv = NULL;
PFNGLUNIFORM3FPROC opengl_core_Uniform3f = NULL;
PFNGLUNIFORM3FVPROC opengl_core_Uniform3fv = NULL;
PFNGLUNIFORM3IPROC opengl_core_Uniform3i = NULL;
PFNGLUNIFORM3IVPROC opengl_core_Uniform3iv = NULL;
PFNGLUNIFORM4FPROC opengl_core_Uniform4f = NULL;
PFNGLUNIFORM4FVPROC opengl_core_Uniform4fv = NULL;
PFNGLUNIFORM4IPROC opengl_core_Uniform4i = NULL;
PFNGLUNIFORM4IVPROC opengl_core_Uniform4iv = NULL;
PFNGLUNIFORMMATRIX2FVPROC opengl_core_UniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC opengl_core_UniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC opengl_core_UniformMatrix4fv = NULL;
PFNGLUSEPROGRAMPROC opengl_core_UseProgram = NULL;
PFNGLVALIDATEPROGRAMPROC opengl_core_ValidateProgram = NULL;
PFNGLVERTEXATTRIB1DPROC opengl_core_VertexAttrib1d = NULL;
PFNGLVERTEXATTRIB1DVPROC opengl_core_VertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB1FPROC opengl_core_VertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC opengl_core_VertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1SPROC opengl_core_VertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1SVPROC opengl_core_VertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB2DPROC opengl_core_VertexAttrib2d = NULL;
PFNGLVERTEXATTRIB2DVPROC opengl_core_VertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB2FPROC opengl_core_VertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FVPROC opengl_core_VertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2SPROC opengl_core_VertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2SVPROC opengl_core_VertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB3DPROC opengl_core_VertexAttrib3d = NULL;
PFNGLVERTEXATTRIB3DVPROC opengl_core_VertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB3FPROC opengl_core_VertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FVPROC opengl_core_VertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3SPROC opengl_core_VertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3SVPROC opengl_core_VertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB4NBVPROC opengl_core_VertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NIVPROC opengl_core_VertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NSVPROC opengl_core_VertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NUBPROC opengl_core_VertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB4NUBVPROC opengl_core_VertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUIVPROC opengl_core_VertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIB4NUSVPROC opengl_core_VertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4BVPROC opengl_core_VertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4DPROC opengl_core_VertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4DVPROC opengl_core_VertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4FPROC opengl_core_VertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FVPROC opengl_core_VertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4IVPROC opengl_core_VertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4SPROC opengl_core_VertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4SVPROC opengl_core_VertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4UBVPROC opengl_core_VertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UIVPROC opengl_core_VertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4USVPROC opengl_core_VertexAttrib4usv = NULL;
PFNGLVERTEXATTRIBPOINTERPROC opengl_core_VertexAttribPointer = NULL;

PFNGLUNIFORMMATRIX2X3FVPROC opengl_core_UniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC opengl_core_UniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC opengl_core_UniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC opengl_core_UniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC opengl_core_UniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC opengl_core_UniformMatrix4x3fv = NULL;

PFNGLBEGINCONDITIONALRENDERPROC opengl_core_BeginConditionalRender = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC opengl_core_BeginTransformFeedback = NULL;
PFNGLBINDFRAGDATALOCATIONPROC opengl_core_BindFragDataLocation = NULL;
PFNGLCLAMPCOLORPROC opengl_core_ClampColor = NULL;
PFNGLCLEARBUFFERFIPROC opengl_core_ClearBufferfi = NULL;
PFNGLCLEARBUFFERFVPROC opengl_core_ClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC opengl_core_ClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC opengl_core_ClearBufferuiv = NULL;
PFNGLCOLORMASKIPROC opengl_core_ColorMaski = NULL;
PFNGLDISABLEIPROC opengl_core_Disablei = NULL;
PFNGLENABLEIPROC opengl_core_Enablei = NULL;
PFNGLENDCONDITIONALRENDERPROC opengl_core_EndConditionalRender = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC opengl_core_EndTransformFeedback = NULL;
PFNGLGETBOOLEANI_VPROC opengl_core_GetBooleani_v = NULL;
PFNGLGETFRAGDATALOCATIONPROC opengl_core_GetFragDataLocation = NULL;
PFNGLGETSTRINGIPROC opengl_core_GetStringi = NULL;
PFNGLGETTEXPARAMETERIIVPROC opengl_core_GetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIUIVPROC opengl_core_GetTexParameterIuiv = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC opengl_core_GetTransformFeedbackVarying =
  NULL;
PFNGLGETUNIFORMUIVPROC opengl_core_GetUniformuiv = NULL;
PFNGLGETVERTEXATTRIBIIVPROC opengl_core_GetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC opengl_core_GetVertexAttribIuiv = NULL;
PFNGLISENABLEDIPROC opengl_core_IsEnabledi = NULL;
PFNGLTEXPARAMETERIIVPROC opengl_core_TexParameterIiv = NULL;
PFNGLTEXPARAMETERIUIVPROC opengl_core_TexParameterIuiv = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC opengl_core_TransformFeedbackVaryings = NULL;
PFNGLUNIFORM1UIPROC opengl_core_Uniform1ui = NULL;
PFNGLUNIFORM1UIVPROC opengl_core_Uniform1uiv = NULL;
PFNGLUNIFORM2UIPROC opengl_core_Uniform2ui = NULL;
PFNGLUNIFORM2UIVPROC opengl_core_Uniform2uiv = NULL;
PFNGLUNIFORM3UIPROC opengl_core_Uniform3ui = NULL;
PFNGLUNIFORM3UIVPROC opengl_core_Uniform3uiv = NULL;
PFNGLUNIFORM4UIPROC opengl_core_Uniform4ui = NULL;
PFNGLUNIFORM4UIVPROC opengl_core_Uniform4uiv = NULL;
PFNGLVERTEXATTRIBI1IPROC opengl_core_VertexAttribI1i = NULL;
PFNGLVERTEXATTRIBI1IVPROC opengl_core_VertexAttribI1iv = NULL;
PFNGLVERTEXATTRIBI1UIPROC opengl_core_VertexAttribI1ui = NULL;
PFNGLVERTEXATTRIBI1UIVPROC opengl_core_VertexAttribI1uiv = NULL;
PFNGLVERTEXATTRIBI2IPROC opengl_core_VertexAttribI2i = NULL;
PFNGLVERTEXATTRIBI2IVPROC opengl_core_VertexAttribI2iv = NULL;
PFNGLVERTEXATTRIBI2UIPROC opengl_core_VertexAttribI2ui = NULL;
PFNGLVERTEXATTRIBI2UIVPROC opengl_core_VertexAttribI2uiv = NULL;
PFNGLVERTEXATTRIBI3IPROC opengl_core_VertexAttribI3i = NULL;
PFNGLVERTEXATTRIBI3IVPROC opengl_core_VertexAttribI3iv = NULL;
PFNGLVERTEXATTRIBI3UIPROC opengl_core_VertexAttribI3ui = NULL;
PFNGLVERTEXATTRIBI3UIVPROC opengl_core_VertexAttribI3uiv = NULL;
PFNGLVERTEXATTRIBI4BVPROC opengl_core_VertexAttribI4bv = NULL;
PFNGLVERTEXATTRIBI4IPROC opengl_core_VertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI4IVPROC opengl_core_VertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI4SVPROC opengl_core_VertexAttribI4sv = NULL;
PFNGLVERTEXATTRIBI4UBVPROC opengl_core_VertexAttribI4ubv = NULL;
PFNGLVERTEXATTRIBI4UIPROC opengl_core_VertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI4UIVPROC opengl_core_VertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBI4USVPROC opengl_core_VertexAttribI4usv = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC opengl_core_VertexAttribIPointer = NULL;

PFNGLDRAWARRAYSINSTANCEDPROC opengl_core_DrawArraysInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC opengl_core_DrawElementsInstanced = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC opengl_core_PrimitiveRestartIndex = NULL;
PFNGLTEXBUFFERPROC opengl_core_TexBuffer = NULL;

PFNGLFRAMEBUFFERTEXTUREPROC opengl_core_FramebufferTexture = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC opengl_core_GetBufferParameteri64v = NULL;
PFNGLGETINTEGER64I_VPROC opengl_core_GetInteger64i_v = NULL;

PFNGLVERTEXATTRIBDIVISORPROC opengl_core_VertexAttribDivisor = NULL;

PFNGLBLENDEQUATIONSEPARATEIPROC opengl_core_BlendEquationSeparatei = NULL;
PFNGLBLENDEQUATIONIPROC opengl_core_BlendEquationi = NULL;
PFNGLBLENDFUNCSEPARATEIPROC opengl_core_BlendFuncSeparatei = NULL;
PFNGLBLENDFUNCIPROC opengl_core_BlendFunci = NULL;
PFNGLMINSAMPLESHADINGPROC opengl_core_MinSampleShading = NULL;

PFNGLGETGRAPHICSRESETSTATUSPROC opengl_core_GetGraphicsResetStatus = NULL;

namespace opengl_core
{
  void gl_functions::configure(const render_context &context)
  {
    symbol_loader sym_loader("OpenGL32.dll");
    if (!sym_loader.get_good()) {
      print_last_error_and_assert();
    }

    // NOTE: glext.h from https://www.opengl.org/registry/api/GL/glext.h
    // intitially groups functions by versions. Then it groups by extensions.
    // Some extensions are duplicated. Duplicates have the appropriate suffix.
    // e.g. ARB, NV, ..., etc.
    typedef std::function<void(symbol_loader *)> load_func;
    std::pair<std::vector<int>, load_func> versions[] =
    {
      std::make_pair<std::vector<int>, load_func>({ 3, 0 }, std::bind(
      &opengl_core::gl_functions::load_3_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 2, 1 }, std::bind(
      &opengl_core::gl_functions::load_2_1, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 2, 0 }, std::bind(
      &opengl_core::gl_functions::load_2_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 1, 5 }, std::bind(
      &opengl_core::gl_functions::load_1_5, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 1, 4 }, std::bind(
      &opengl_core::gl_functions::load_1_4, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 1, 3 }, std::bind(
      &opengl_core::gl_functions::load_1_3, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({ 1, 2 }, std::bind(
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
      glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");
      if (!glGetStringi || glGetStringi == (void*)-1) {
        print_last_error_and_assert();
      }

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

#define LOAD_GL_FUNCTION(type, name) \
  name = (type)wglGetProcAddress(#name); \
  if (name == nullptr || name == (void*)-1) { \
    print_last_error_and_assert(); \
  } else { \
    std::cout << "Successfully Loaded " << (#name) << " @" << std::hex \
    << (&name) << std::dec << std::endl; \
  }

namespace opengl_core
{
  void gl_functions::load_1_2(symbol_loader *sym_loader)
  {
  }

  void gl_functions::load_1_3(symbol_loader *sym_loader)
  {
    LOAD_GL_FUNCTION(PFNGLACTIVETEXTUREPROC, glActiveTexture);
  }

  void gl_functions::load_1_4(symbol_loader *sym_loader)
  {
  }

  void gl_functions::load_1_5(symbol_loader *sym_loader)
  {
  }

  void gl_functions::load_2_0(symbol_loader *sym_loader)
  {
  }

  void gl_functions::load_2_1(symbol_loader *sym_loader)
  {
  }

  void gl_functions::load_3_0(symbol_loader *sym_loader)
  {
  }
}
