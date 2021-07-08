#ifndef __XGL_MESHMANAGER_H__
#define __XGL_MESHMANAGER_H__

#include "XGLMainManager.h"
#include "XGLMesh.h"

namespace XGL
{
    /**
     *  @brief Defines a Manager for Mesh instances.
     * 
     */
    struct MeshManager : public MainManager < Mesh >
    {
        using MainManager::MainManager;

        //! @brief Finds a Mesh by its name.
        inline auto findByName(const std::string& name) const { return this->find([&name](auto& rhs){ return rhs->name() == name; }); }

        //! @brief Finds a Mesh by its id.
        inline auto findById(size_t id) const { return this->find([id](auto& rhs){ return rhs->id() == id; }); }

        //! @brief Loads or Get a new Mesh from a file.
        std::shared_ptr < Mesh > loadOrGet(const std::string& name, 
                                           const std::string& filename, 
                                           const std::string& meshLoader, 
                                           const std::shared_ptr < IRenderer >& renderer);
    };
}

#endif // !__XGL_MESHMANAGER_H__