#ifndef __XGL_SCENENODE_H__
#define __XGL_SCENENODE_H__

#include "XGLIncludes.h"
#include "XGLClass.h"
#include "XGLFrustum.h"
#include "XGLIRenderer.h"
#include "XGLPositionable.h"
#include "XGLIdentifiable.h"

namespace XGL
{
    class Scene;
    
    /**
     *  @brief Defines a base for a SceneNode.
     *
     */
    class SceneNode : public std::enable_shared_from_this < SceneNode >,
                      public Positionable,
                      public Identifiable < SceneNode >
    {
        //! @brief The Scene that created this node.
        Scene& mScene;
        
        //! @brief The children.
        std::list < std::shared_ptr < SceneNode > > mChildren;
        
        //! @brief The parent.
        std::weak_ptr < SceneNode > mParent;
        
        //! @brief The size of the bounding box representing the SceneNode.
        glm::vec4 mBoundingLength;
        
        //! @brief Mutex.
        mutable std::mutex mutex;
        
    public:
        //! @brief Constructs a new SceneNode.
        SceneNode(Scene& scene);
        
        //! @brief Inserts a node as a child.
        virtual void insert(const std::shared_ptr < SceneNode >& node, const std::shared_ptr < SceneNode >& before);
        
        //! @brief Append a node as a child.
        virtual void append(const std::shared_ptr < SceneNode >& node);
        
        //! @brief Prepend a node.
        virtual void prepend(const std::shared_ptr < SceneNode >& node);
        
        //! @brief Removes a node.
        virtual void remove(const std::shared_ptr < SceneNode >& node);
        
        //! @brief Removes all nodes.
        virtual void removeAllChildren();
        
        //! @brief Returns the first child.
        virtual std::shared_ptr < SceneNode > firstChild() const;
        
        //! @brief Returns the last child.
        virtual std::shared_ptr < SceneNode > lastChild() const;
        
        //! @brief Returns a copy of all children.
        auto children() const { std::lock_guard l(mutex); return mChildren; }
        
        //! @brief Returns the parent.
        auto parent() const { std::lock_guard l(mutex); return mParent.lock(); }
        
        //! @brief Let the node do its thing for some IRenderer.
        //!
        //! Subclass uses this function to render or bind things onto the IRenderer,
        //! like MeshSceneNode renders a Mesh and MaterialSceneNode binds a
        //! Material.
        virtual void handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const;
        
        //! @brief Returns true if this node is visible from a Frustum.
        //!
        //! Subclass uses this function to conditionnally render its content if a
        //! frustum contains the node or not.
        virtual bool isVisible(const Frustum& frustum) const;
        
        //! @brief Updates the SceneNode.
        //!
        //! Function is called each time Scene::update() is. The delta parameter
        //! is the delta time between two calls to Scene::update().
        virtual void update(const std::chrono::milliseconds& delta);
        
        //! @brief Returns the bounding box.
        virtual AABB boundingBox() const;
        
        //! @brief Returns true if this SceneNode represents an infinite bounding box,
        //! or is not representable by a volume.
        virtual bool isInfiniteBox() const;
        
        //! @brief Sets the bounding box length for this node.
        virtual void setBoundingLength(const glm::vec3& length);
        
        //! @brief Returns true if this node has a bounding length.
        virtual bool hasBoundingLength() const;
        
        //! @brief Finds a child by its id.
        virtual std::shared_ptr < SceneNode > findById(size_t id) const;
        
        //! @brief Inserts a node as the parent of this one and adds the specified
        //! node as the child of this node parent.
        //!
        //! This function can be used when, inserting a MeshSceneNode, you want to
        //! set the Mesh material after: use this function to make this Mesh a
        //! particular Material.
        virtual void insertAsParent(const std::shared_ptr < SceneNode >& node);
        
        //! @brief Removes and readd the node into its parent children list.
        virtual void reinsertInParent();
        
        //! @brief Returns the Scene.
        inline Scene& scene() { return mScene; }
        
        //! @brief Returns the Scene.
        inline const Scene& scene() const { return mScene; }
    };
    
    typedef std::shared_ptr < SceneNode > PSceneNode;
}

#endif // ! __XGL_SCENENODE_H__
