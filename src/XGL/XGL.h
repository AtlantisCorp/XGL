#ifndef __XGL_H__
#define __XGL_H__

#include "XGLIncludes.h"

namespace XGL
{
    class Main;
    class IPlugin;
    class Dynlib;
    class IRenderer;
}

#include "XGLClass.h"
#include "XGLError.h"

#include "XGLIPlugin.h"
#include "XGLDynlib.h"
#include "XGLPluginManager.h"
#include "XGLManager.h"
#include "XGLRendererManager.h"
#include "XGLFrame.h"
#include "XGLEventHandler.h"
#include "XGLEvent.h"
#include "XGLIWindow.h"
#include "XGLIBuffer.h"
#include "XGLClearBuffers.h"
#include "XGLAttrib.h"
#include "XGLDrawMode.h"
#include "XGLElements.h"
#include "XGLVertex.h"
#include "XGLIShader.h"
#include "XGLPixelFormat.h"
#include "XGLITexture.h"
#include "XGLSubMesh.h"
#include "XGLMesh.h"
#include "XGLLoader.h"
#include "XGLLoaderManager.h"
#include "XGLIMeshLoader.h"
#include "XGLMaterialUniform.h"
#include "XGLMaterial.h"
#include "XGLIShaderLibrary.h"
#include "XGLMaterialManager.h"
#include "XGLISurface.h"
#include "XGLIRenderer.h"
#include "XGLMain.h"
#include "XGLIRenderObject.h"
#include "XGLIdentifiable.h"
#include "XGLMeshManager.h"
#include "XGLLoaderNotFound.h"
#include "XGLCannotLoadAsset.h"
#include "XGLPipeline.h"
#include "XGLPipelineManager.h"
#include "XGLITextureLoader.h"
#include "XGLSceneNode.h"
#include "XGLFrustum.h"
#include "XGLAABB.h"
#include "XGLPositionable.h"
#include "XGLMeshSceneNode.h"
#include "XGLMaterialSceneNode.h"
#include "XGLEntitySceneNode.h"
#include "XGLScene.h"
#include "XGLCamera.h"

#endif // !__XGL_H__
