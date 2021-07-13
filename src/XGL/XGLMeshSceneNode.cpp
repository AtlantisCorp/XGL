//
//  XGLMeshSceneNode.cpp
//  XGL
//
//  Created by luk2010 on 11/07/2021.
//

#include "XGLMeshSceneNode.h"

namespace XGL
{
    MeshSceneNode::MeshSceneNode(Scene& scene, const std::shared_ptr < Mesh >& mesh):
    SceneNode(scene),
    mMesh(mesh)
    {
        if (mesh)
        {
            const AABB box = mesh->boundingBox();
            setBoundingLength(box.max - box.min);
        }
    }
    
    std::shared_ptr < Mesh > MeshSceneNode::mesh() const
    {
        return std::atomic_load(&mMesh);
    }
    
    void MeshSceneNode::setMesh(const std::shared_ptr < Mesh >& mesh)
    {
        std::atomic_store(&mMesh, mesh);
        
        const AABB box = mesh ?
            mesh->boundingBox() :
            AABB{ glm::vec4(), glm::vec4() };
        
        setBoundingLength(box.max - box.min);
        
        auto lparent = parent();
        
        if (lparent)
        {
            auto lthis = shared_from_this();
            lparent->remove(lthis);
            lparent->append(lthis);
        }
    }
    
    void MeshSceneNode::handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const
    {
        auto lmesh = std::atomic_load(&mMesh);
        
        if (lmesh)
            lmesh->render(renderer);
        
        SceneNode::handle(renderer, frustum);
    }
}
