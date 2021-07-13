//
//  XGLMeshSceneNode.h
//  XGL
//
//  Created by luk2010 on 11/07/2021.
//

#ifndef __XGL_MESHSCENENODE_H__
#define __XGL_MESHSCENENODE_H__

#include "XGLSceneNode.h"
#include "XGLMesh.h"

namespace XGL
{
    /**
     *  @brief Defines a SceneNode that renders a Mesh.
     *
     *  This is a very simple SceneNode. Sets a Mesh and let the SceneNode
     *  manages its bounding box and renders the Mesh if visible from the
     *  current Frustum.
     *
     *  @note If the Mesh doesn't have any bounding box, consider adding
     *  one by yourself to provide culling facilities. Use
     *  SceneNode::setBoundingLength() to do the job.
     *
     */
    class MeshSceneNode : public SceneNode
    {
        //! @brief Holds the Mesh.
        std::shared_ptr < Mesh > mMesh;
        
    public:
        //! @brief Constructs a new instance.
        MeshSceneNode(Scene& scene, const std::shared_ptr < Mesh >& mesh);
        
        //! @brief Returns the mesh.
        virtual std::shared_ptr < Mesh > mesh() const;
        
        //! @brief Sets the mesh to be rendered.
        //! @note As the bounding box may change, the node is (re)added to
        //! its parent so the parent can perform any change it wants to the
        //! node tree.
        virtual void setMesh(const std::shared_ptr < Mesh >& mesh);
        
        //! @brief Renders the Mesh.
        virtual void handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const;
    };
    
    typedef std::shared_ptr < MeshSceneNode > PMeshSceneNode;
}

#endif // !__XGL_MESHSCENENODE_H__
