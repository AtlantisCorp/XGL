#include "XGLMeshManager.h"
#include "XGLMain.h"
#include "XGLLoaderNotFound.h"
#include "XGLCannotLoadAsset.h"

namespace XGL
{
    std::shared_ptr < Mesh > MeshManager::loadOrGet(const std::string& name, const std::string& filename, const std::string& meshLoader, const std::shared_ptr < IRenderer >& renderer)
    {
        auto mesh = this->findByName(name);

        if (!mesh)
        {
            auto loader = mMain.meshLoaders().findByName(meshLoader);
            XGLThrowIf(!loader, LoaderNotFound(meshLoader));

            mesh = loader->load(name, filename, renderer);
            XGLThrowIf(!mesh, CannotLoadAsset(name, filename));

            this->add(mesh);
        }

        return mesh;
    }
}