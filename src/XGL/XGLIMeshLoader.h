#ifndef __XGL_IMESHLOADER_H__
#define __XGL_IMESHLOADER_H__

#include "XGLMesh.h"
#include "XGLLoader.h"
#include "XGLLoaderManager.h"

namespace XGL
{
    class IRenderer;

    /**
     *  @brief Defines a loader for a Mesh.
     * 
     */
    struct IMeshLoader : public ILoader
    {
        //! @brief Destructor.
        virtual ~IMeshLoader() = default; 
        
        //! @brief Loads a new Mesh from a file.
        virtual std::shared_ptr < Mesh > load(const std::string& meshName, 
                                              const std::string& filename, 
                                              const std::shared_ptr < IRenderer >& renderer) = 0;
    };

    //! @brief Defines a Manager for IMeshLoader.
    typedef ILoaderManager < IMeshLoader > MeshLoaderManager;
}

#endif // !__XGL_IMESHLOADER_H__