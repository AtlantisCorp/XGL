//
//  XGLEntitySceneNode.h
//  XGL
//
//  Created by jacques tronconi on 11/07/2021.
//

#ifndef __XGL_ENTITYSCENENODE_H__
#define __XGL_ENTITYSCENENODE_H__

#include "XGLMeshSceneNode.h"
#include "XGLMaterialSceneNode.h"

namespace XGL
{
    /**
     *  @brief Defines a SceneNode to render a Mesh with one or more Materials.
     *
     *  The EntitySceneNode defines a collection of MaterialSceneNode and one
     *  MeshSceneNode. When rendering, for each MaterialSceneNode, the Material
     *  is bound and the Mesh is rendered.
     *
     *  @warning This means that the Mesh will actually be rendered once for
     *  each Material.
     *
     *  @note The EntitySceneNode will allow you to append only MaterialSceneNodes
     *  or a MeshSceneNode. Any other SceneNodes will throw an exception.
     *
     */
    class EntitySceneNode : public SceneNode
    {
        //! @brief The Materials SceneNode.
        std::list < PMaterialSceneNode > mMaterials;
        
        //! @brief The Mesh SceneNode.
        PMeshSceneNode mMesh;
        
        //! @brief Mutex.
        mutable std::mutex mutex;
        
    public:
        //! @brief Constructs a new node.
        EntitySceneNode(Scene& scene,
                        const PMeshSceneNode& mesh,
                        const std::list < PMaterialSceneNode >& materials = {});
        
        //! @brief Inserts a node.
        virtual void insert(const PSceneNode& node, const PSceneNode& before);
        
        //! @brief Removes a node.
        virtual void remove(const PSceneNode& node);
        
        //! @brief Returns the first Material in this node.
        virtual PMaterial firstMaterial() const;
        
        //! @brief Appends a new Material.
        virtual PMaterialSceneNode append(const PMaterial& material);
        
        //! @brief Returns the Mesh.
        virtual PMesh mesh() const;
        
        //! @brief Sets the Mesh in this node.
        virtual PMeshSceneNode setMesh(const PMesh& mesh);
        
        //! @brief Renders the node.
        virtual void handle(const PIRenderer& renderer, const Frustum& frustum) const;
        
        //! @brief Returns the mesh bounding box.
        virtual AABB boundingBox() const;
    };
    
    typedef std::shared_ptr < EntitySceneNode > PEntitySceneNode;
}

#endif /* __XGL_ENTITYSCENENODE_H__ */
