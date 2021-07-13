#include "XGLSceneNode.h"
#include "XGLError.h"

namespace XGL
{
    SceneNode::SceneNode(Scene& scene):
    mScene(scene)
    {
        mBoundingLength = glm::vec4(0.0, 0.0, 0.0, 0.0);
    }
    
    void SceneNode::insert(const std::shared_ptr < SceneNode >& node, const std::shared_ptr < SceneNode >& before)
    {
        XGLThrowIf(!node, std::runtime_error("Null node"));
        
        std::scoped_lock l(mutex, node->mutex);
        auto it = std::find(mChildren.begin(), mChildren.end(), before);
        
        mChildren.insert(it, node);
        node->mParent = shared_from_this();
    }
    
    void SceneNode::append(const std::shared_ptr < SceneNode >& node)
    {
        insert(node, nullptr);
    }
    
    void SceneNode::prepend(const std::shared_ptr < SceneNode >& node)
    {
        insert(node, firstChild());
    }
    
    void SceneNode::remove(const std::shared_ptr < SceneNode >& node)
    {
        std::lock_guard l(mutex);
        auto it = std::find(mChildren.begin(), mChildren.end(), node);
        if (it != mChildren.end())
            mChildren.erase(it);
    }
    
    void SceneNode::removeAllChildren()
    {
        std::lock_guard l(mutex);
        mChildren.clear();
    }
    
    std::shared_ptr < SceneNode > SceneNode::firstChild() const
    {
        std::lock_guard l(mutex);
        return mChildren.empty() ? nullptr : mChildren.front();
    }
    
    std::shared_ptr < SceneNode > SceneNode::lastChild() const
    {
        std::lock_guard l(mutex);
        return mChildren.empty() ? nullptr : mChildren.back();
    }
    
    void SceneNode::handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const
    {
        auto children = this->children();
        for (auto& child : children)
            if (child->isVisible(frustum))
                child->handle(renderer, frustum);
    }
    
    bool SceneNode::isVisible(const Frustum& frustum) const
    {
        return frustum.contains(this->boundingBox());
    }
    
    void SceneNode::update(const std::chrono::milliseconds& delta)
    {
        std::lock_guard l(mutex);
        for (auto& child : mChildren)
            child->update(delta);
    }
    
    AABB SceneNode::boundingBox() const
    {
        std::lock_guard l(mutex);
        
        const glm::vec4 lposition = position();
        AABB box = { .min = lposition, .max = lposition + mBoundingLength };
        const glm::mat4 mat = matrix();
        
        box.min = mat * box.min;
        box.max = mat * box.max;
        
        return box;
    }
    
    bool SceneNode::isInfiniteBox() const
    {
        const AABB box = this->boundingBox();
        const glm::vec4 diag = box.max - box.min;
        return glm::length(diag) == 0;
    }
    
    void SceneNode::setBoundingLength(const glm::vec3& length)
    {
        std::lock_guard l(mutex);
        mBoundingLength.x = length.x;
        mBoundingLength.y = length.y;
        mBoundingLength.z = length.z;
    }
    
    bool SceneNode::hasBoundingLength() const
    {
        std::lock_guard l(mutex);
        return glm::length(mBoundingLength) > 0.0;
    }
    
    std::shared_ptr < SceneNode > SceneNode::findById(size_t id) const
    {
        auto lchildren = children();
        
        for (auto& child : lchildren)
        {
            if (child->id() == id)
                return child;
        }
        
        for (auto& child : lchildren)
        {
            auto res = child->findById(id);
            
            if (res)
                return res;
        }
        
        return nullptr;
    }
    
    void SceneNode::insertAsParent(const std::shared_ptr < SceneNode >& node)
    {
        XGLThrowIf(!node, std::runtime_error("Null node."));
        
        auto lparent = parent();
        
        if (lparent)
        {
            lparent->insert(node, shared_from_this());
            lparent->remove(shared_from_this());
        }
        
        node->append(shared_from_this());
    }
    
    void SceneNode::reinsertInParent()
    {
        auto lparent = parent();
        auto lthis = shared_from_this();
        
        if (lparent)
        {
            lparent->remove(lthis);
            lparent->append(lthis);
        }
    }
}
