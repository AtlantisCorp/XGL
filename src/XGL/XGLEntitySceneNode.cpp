//
//  XGLEntitySceneNode.cpp
//  XGL
//
//  Created by jacques tronconi on 11/07/2021.
//

#include "XGLEntitySceneNode.h"
#include "XGLScene.h"
#include "XGLError.h"

namespace XGL
{
    EntitySceneNode::EntitySceneNode(Scene& scene, const PMeshSceneNode& mesh, const std::list < PMaterialSceneNode >& materials):
    SceneNode(scene),
    mMesh(mesh),
    mMaterials(materials)
    {
        for (auto& material : materials)
            SceneNode::insert(material, nullptr);
        
        if (mesh)
            SceneNode::insert(mesh, nullptr);
    }
    
    void EntitySceneNode::insert(const PSceneNode& node, const PSceneNode& before)
    {
        std::lock_guard l(mutex);
        bool nodeTFound = false;
        
        auto isMesh = std::dynamic_pointer_cast < MeshSceneNode >(node);
        
        if (isMesh)
        {
            if (mMesh)
                SceneNode::remove(mMesh);
            
            mMesh = isMesh;
            nodeTFound = true;
        }
        
        else
        {
            auto isMaterial = std::dynamic_pointer_cast < MaterialSceneNode >(node);
            
            if (isMaterial)
            {
                mMaterials.push_back(isMaterial);
                nodeTFound = true;
            }
        }
        
        XGLThrowIf(!nodeTFound, std::runtime_error("XGL:EntitySceneNode:insert(): SceneNode has invalid "
                                "node type. Only MeshSceneNode and MaterialSceneNode "
                                "are allowed."));
        SceneNode::insert(node, before);
    }
    
    void EntitySceneNode::remove(const PSceneNode& node)
    {
        std::lock_guard l(mutex);
        bool nodeTFound = false;
        
        auto isMesh = std::dynamic_pointer_cast < MeshSceneNode >(node);
        
        if (isMesh)
        {
            nodeTFound = true;
            mMesh = nullptr;
        }
        
        else
        {
            auto isMaterial = std::dynamic_pointer_cast < MaterialSceneNode >(node);
            
            if (isMaterial)
            {
                nodeTFound = true;
                mMaterials.erase(std::find(mMaterials.begin(), mMaterials.end(), isMaterial));
            }
        }
        
        XGLThrowIf(!nodeTFound, std::runtime_error("XGL:EntitySceneNode:remove(): Cannot remove SceneNode "
                                "because it is neither a MeshSceneNode nor a "
                                "MaterialSceneNode, which are allowed."));
        SceneNode::remove(node);
    }
    
    PMaterial EntitySceneNode::firstMaterial() const
    {
        std::lock_guard l(mutex);
        return mMaterials.empty() ? nullptr : mMaterials.front()->material();
    }
    
    PMaterialSceneNode EntitySceneNode::append(const PMaterial& material)
    {
        XGLThrowIf(!material, std::runtime_error("XGL:EntitySceneNode:append(): Cannot append a null "
                              "material instance."));
        
        auto lnode = scene().createMaterialNode(material);
        XGLThrowIf(!lnode, std::runtime_error("XGL:EntitySceneNode:append(): Cannot create a new "
                           "MaterialSceneNode for Material '" + material->name() + "'."));
        
        insert(lnode, nullptr);
        return lnode;
    }
    
    PMesh EntitySceneNode::mesh() const
    {
        std::lock_guard l(mutex);
        return mMesh ? mMesh->mesh() : nullptr;
    }
    
    PMeshSceneNode EntitySceneNode::setMesh(const PMesh& mesh)
    {
        XGLThrowIf(!mesh, std::runtime_error("XGL:EntitySceneNode:setMesh(): Cannot set a null Mesh."));
        
        auto lnode = scene().createMeshNode(mesh, glm::vec3());
        XGLThrowIf(!lnode, std::runtime_error("XGL:EntitySceneNode:setMesh(): Cannot create a new "
                           "MeshSceneNode for Mesh '" + mesh->name() + "'."));
        
        insert(lnode, nullptr);
        return lnode;
    }
    
    void EntitySceneNode::handle(const PIRenderer& renderer, const Frustum& frustum) const
    {
        XGLThrowIf(!renderer, std::runtime_error("XGL:EntitySceneNode:handle(): Null renderer."));
        std::lock_guard l(mutex);
        
        if (!mMesh)
            return;
        
        for (auto& lmaterial : mMaterials)
        {
            lmaterial->handle(renderer, frustum);
            mMesh->handle(renderer, frustum);
        }
    }
    
    AABB EntitySceneNode::boundingBox() const
    {
        std::lock_guard l(mutex);
        
        if (mMesh)
        {
            AABB box = mMesh->boundingBox();
            const glm::mat4 lmatrix = matrix();
            box.min = box.min * lmatrix;
            box.max = box.max * lmatrix;
            return box;
        }
        
        return SceneNode::boundingBox();
    }
}
