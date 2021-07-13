//
//  XGLScene.cpp
//  XGL
//
//  Created by jacques tronconi on 11/07/2021.
//

#include "XGLScene.h"
#include "XGLError.h"
#include "XGLMain.h"

namespace XGL
{
    Scene::Scene(Main& mMain, const glm::vec3& boundingLength):
    SceneNode(*this),
    mMain(mMain)
    {
        setBoundingLength(boundingLength);
    }
    
    PSceneNode Scene::createNode(const glm::vec3& position, const glm::vec3& boundingLength)
    {
        auto node = std::make_shared < SceneNode >(*this);
        node->setPosition(position.x, position.y, position.z);
        node->setBoundingLength(boundingLength);
        return node;
    }
    
    PMeshSceneNode Scene::createMeshNode(const PMesh& mesh, const glm::vec3& position, const glm::vec3& defaultBoundingLength)
    {
        XGLThrowIf(!mesh, std::runtime_error("Null mesh"));
        auto node = std::make_shared < MeshSceneNode >(*this, mesh);
        node->setPosition(position.x, position.y, position.z);
        if (!node->hasBoundingLength())
            node->setBoundingLength(defaultBoundingLength);
        return node;
    }
    
    PMeshSceneNode Scene::createMeshNode(const std::string& meshName,
                                         const std::string& meshPath,
                                         const std::string& loaderName,
                                         const PIRenderer& renderer,
                                         const glm::vec3& position,
                                         const glm::vec3& defBoundingLength)
    {
        auto mesh = mMain.meshes().loadOrGet(meshName, meshPath, loaderName, renderer);
        XGLThrowIf(!mesh, std::runtime_error("XGL:Scene:createMeshNode(): Cannot find Mesh '" + meshName + "'."));
        
        return createMeshNode(mesh, position, defBoundingLength);
    }
    
    PMaterialSceneNode Scene::createMaterialNode(const PMaterial& material)
    {
        XGLThrowIf(!material, std::runtime_error("Null material"));
        auto node = std::make_shared < MaterialSceneNode >(*this, material);
        return node;
    }
    
    PEntitySceneNode Scene::createEntityNode(const PMeshSceneNode& mesh,
                                             const std::list < PMaterialSceneNode >& materials,
                                             const glm::vec3& position)
    {
        auto node = std::make_shared < EntitySceneNode >(*this, mesh, materials);
        node->setPosition(position.x, position.y, position.z);
        return node;
    }
    
    void Scene::render(const PIRenderer& renderer, const Frustum& frustum) const
    {
        handle(renderer, frustum);
    }
}
