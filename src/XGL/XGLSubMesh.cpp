#include "XGLSubMesh.h"
#include "XGLIRenderer.h"
#include "XGLError.h"

namespace XGL
{
    SubMesh::SubMesh(size_t count, size_t first, size_t numInstances, size_t firstInstance, DrawMode mode):
    mElements(count),
    mFirstElement(first),
    mInstances(numInstances),
    mFirstInstance(firstInstance),
    mMode(mode),
    mBuffer(nullptr),
    mType(Elements::Uint32)
    {

    }

    SubMesh::SubMesh(const std::shared_ptr < IBuffer >& buffer, Elements::Type type, size_t count, size_t first, size_t numInstances, size_t firstInstance, DrawMode mode):
    mElements(count),
    mFirstElement(first),
    mInstances(numInstances),
    mFirstInstance(firstInstance),
    mMode(mode),
    mBuffer(buffer),
    mType(type)
    {

    }

    void SubMesh::render(const std::shared_ptr < IRenderer >& rhs) const
    {
        XGLThrowIf(!rhs, "Null IRenderer.");
        std::lock_guard l(mutex);

        if (mBuffer)
            rhs->drawIndexedElements(mBuffer, mType, mMode, mFirstElement, mElements, mFirstInstance, mInstances);
        
        else  
            rhs->drawElements(mMode, mFirstElement, mElements, mFirstInstance, mInstances);
    }
}