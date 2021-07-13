//
//  XGLMaterialSceneNode.h
//  XGL
//
//  Created by luk2010 on 11/07/2021.
//

#ifndef __XGL_MATERIALSCENENODE_H__
#define __XGL_MATERIALSCENENODE_H__

#include "XGLSceneNode.h"
#include "XGLMaterial.h"

namespace XGL
{
    /**
     *  @brief Defines a SceneNode that binds a Material.
     *
     *  Uses this node as the parent of a MeshSceneNode or a group of
     *  nodes to bind a Material before their rendering.
     *
     */
    class MaterialSceneNode : public SceneNode
    {
        //! @brief Holds the material.
        std::shared_ptr < Material > mMaterial;
        
    public:
        //! @brief Constructs a new node.
        MaterialSceneNode(Scene& scene, const std::shared_ptr < Material >& material);
        
        //! @brief Returns the material.
        inline auto material() const { return std::atomic_load(&mMaterial); }
        
        //! @brief Stores another material.
        inline void setMaterial(const std::shared_ptr < Material >& material) { std::atomic_store(&mMaterial, material); }
        
        //! @brief Binds the material onto the specified renderer and renders
        //! children nodes.
        void handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const;
        
        //! @brief Returns always true.
        inline bool isVisible(const Frustum& frustum) const { return true; }
        
        //! @brief Returns always true.
        inline bool isInfiniteBox() const { return true; }
    };
    
    typedef std::shared_ptr < MaterialSceneNode > PMaterialSceneNode;
}

#endif /* XGLMaterialSceneNode_h */
