#ifndef __XGL_SUBMESH_H__
#define __XGL_SUBMESH_H__

#include "XGLClass.h"
#include "XGLIBuffer.h"
#include "XGLElements.h"
#include "XGLDrawMode.h"

namespace XGL
{
    class IRenderer;
    
    /**
     *  @brief Defines an inner structure in a Mesh.
     * 
     */
    class SubMesh : public Class < SubMesh > 
    {
        //! @brief The number of elements to render.
        size_t mElements;  

        //! @brief The first element to begin with.
        size_t mFirstElement;

        //! @brief The number of instances to render.
        size_t mInstances;

        //! @brief The first instance to begin with.
        size_t mFirstInstance;

        //! @brief The index buffer, if this is an indexed draw.
        std::shared_ptr < IBuffer > mBuffer;

        //! @brief The index type, if this is an indexed draw.
        Elements::Type mType;

        //! @brief The draw mode.
        DrawMode mMode;

        //! @brief Mutex.
        mutable std::mutex mutex;

    public:
        //! @brief Creates a new SubMesh for non indexed elements.
        SubMesh(size_t count, 
                size_t first, 
                size_t numInstances = 1, 
                size_t firstInstance = 0, 
                DrawMode mode = DrawMode::Triangles);

        //! @brief Creates a new SubMesh for indexed elements.
        SubMesh(const std::shared_ptr < IBuffer >& buffer, 
                Elements::Type type, 
                size_t count, 
                size_t first, 
                size_t numInstances = 1, 
                size_t firstInstance = 0, 
                DrawMode mode = DrawMode::Triangles);

        //! @brief Renders a SubMesh.
        void render(const std::shared_ptr < IRenderer >& rhs) const;
    };
}

#endif // !__XGL_SUBMESH_H__