#include <core/gl_functions.h>

#include <core/x11_display.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
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
    symbol_loader sym_loader("libGL.so");
    assert(sym_loader.get_good() && "Failed to load libGL.so");

    // NOTE: glext.h from https://www.opengl.org/registry/api/GL/glext.h
    // intitialy groups functions by versions. Then it groups by extensions.
    // Some extensions are duplicated. Duplicates have the appropiate suffix.
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
    LOAD_GL_FUNCTION(PFNGLBLENDCOLORPROC, glBlendColor, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXIMAGE3DPROC, glTexImage3D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLBLENDEQUATIONPROC, glBlendEquation, sym_loader);
    LOAD_GL_FUNCTION(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D, sym_loader);
    LOAD_GL_FUNCTION(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements,
      sym_loader);
    LOAD_GL_FUNCTION(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D,
      sym_loader);
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
    LOAD_GL_FUNCTION(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERIVPROC, glClearBufferiv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERFVPROC, glClearBufferfv, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERFIPROC, glClearBufferfi, sym_loader);
    LOAD_GL_FUNCTION(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv, sym_loader);
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
