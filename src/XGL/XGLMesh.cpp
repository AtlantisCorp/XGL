#include "XGLMesh.h"
#include "XGLError.h"
#include "XGLIRenderer.h"

namespace XGL
{
    Mesh::Mesh(const std::string& name):
    mName(name),
    mVertex({})
    {

    }

    void Mesh::addSubMesh(const std::shared_ptr < SubMesh >& subMesh)
    {
        XGLThrowIf(!subMesh, std::runtime_error("Null subMesh"));
        std::lock_guard l(mutex);
        mSubMeshes.push_back(subMesh);
    }

    void Mesh::removeSubMesh(const std::shared_ptr < SubMesh >& subMesh)
    {
        XGLThrowIf(!subMesh, std::runtime_error("Null subMesh"));
        std::lock_guard l(mutex);
        auto it = std::find(mSubMeshes.begin(), mSubMeshes.end(), subMesh);
        if (it != mSubMeshes.end())
            mSubMeshes.erase(it);
    }

    void Mesh::clearSubMeshes() 
    {
        std::lock_guard l(mutex);
        mSubMeshes.clear();
    }

    void Mesh::setBuffer(const std::string& name, const std::shared_ptr < IBuffer >& buffer)
    {
        XGLThrowIf(name.empty(), "IBuffer name is empty");
        XGLThrowIf(!buffer, "IBuffer is null.");
        std::lock_guard l(mutex);
        mBuffers[name] = buffer;
    }

    void Mesh::clearBuffers() 
    {
        std::lock_guard l(mutex);
        mBuffers.clear();
    }

    void Mesh::setVertex(const Vertex& rhs)
    {
        std::lock_guard l(mutex);
        mVertex = rhs;
    }

    void Mesh::render(const std::shared_ptr < IRenderer >& rhs) const
    {
        XGLThrowIf(!rhs, "Null IRenderer.");
        std::lock_guard l(mutex);

        rhs->bindVertexBuffers(mVertex, mBuffers);

        for (auto& subMesh : mSubMeshes)
            subMesh->render(rhs);
    }

    std::string Mesh::name() const 
    {
        std::lock_guard l(mutex);
        return mName;
    }

    void Mesh::setName(const std::string& name)
    {
        std::lock_guard l(mutex);
        mName = name;
    }
    
    AABB Mesh::boundingBox() const
    {
        std::lock_guard l(mutex);
        return mBoundingBox;
    }
    
    void Mesh::setBoundingBox(const AABB& box)
    {
        std::lock_guard l(mutex);
        mBoundingBox = box;
    }
}
