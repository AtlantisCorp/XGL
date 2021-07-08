#ifndef __XGL_MAIN_H__
#define __XGL_MAIN_H__

#include "XGLIncludes.h"
#include "XGLPluginManager.h"
#include "XGLRendererManager.h"
#include "XGLIMeshLoader.h"
#include "XGLMaterialManager.h"
#include "XGLMeshManager.h"
#include "XGLPipelineManager.h"
#include "XGLITextureLoader.h"

namespace XGL
{
    /// @brief Defines the Main XGL object.
    class Main : public Class < Main >
    {
        /// @brief The PluginManager in charge.
        PluginManager mPluginManager;

        //! @brief The RendererManager.
        RendererManager mRendererManager;

        //! @brief The MeshLoaderManager.
        MeshLoaderManager mMeshLoaderManager;

        //! @brief The Material Manager.
        MaterialManager mMaterialManager;

        //! @brief The Mesh manager.
        MeshManager mMeshManager;

        //! @brief The Pipeline manager.
        PipelineManager mPipelineManager;

        //! @brief The texture loader manager.
        TextureLoaderManager mTextureLoaderManager;

    public:

        /// @brief Constructs a new Main instance.
        Main();

        /// @brief Returns the PluginManager.
        PluginManager& plugins();

        //! @brief Returns the RendererManager.
        RendererManager& renderers();

        //! @brief Returns the MeshLoaderManager.
        inline MeshLoaderManager& meshLoaders() { return mMeshLoaderManager; }

        //! @brief Returns the Material Manager.
        inline MaterialManager& materials() { return mMaterialManager; }

        //! @brief Returns the MeshManager.
        inline MeshManager& meshes() { return mMeshManager; }

        //! @brief Returns the PipelineManager.
        inline PipelineManager& pipelines() { return mPipelineManager; }

        //! @brief Returns the TextureLoaderManager.
        inline TextureLoaderManager& textureLoaders() { return mTextureLoaderManager; }
    };
}

#endif // !__XGL_MAIN_H__