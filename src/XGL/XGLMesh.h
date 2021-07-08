#ifndef __XGL_MESH_H__
#define __XGL_MESH_H__

#include "XGLIncludes.h"
#include "XGLSubMesh.h"
#include "XGLVertex.h"
#include "XGLIdentifiable.h"

namespace XGL
{
    class IRenderer;
    
    /**
     *  @brief Defines a Mesh.
     * 
     *  A Mesh is a collection of SubMesh, associated to a Vertex and a set of Vertex 
     *  buffers. You can create your own mesh or you can use a MeshLoader.
     * 
     */
    class Mesh : public Class < Mesh >, public Identifiable < Mesh >
    {
        //! @brief Holds the vertex structure for the Mesh.
        Vertex mVertex;

        //! @brief Holds the different vertex buffers.
        VertexBuffers mBuffers;

        //! @brief Holds the different sub meshes.
        std::list < std::shared_ptr < SubMesh > > mSubMeshes;

        //! @brief The mesh name.
        std::string mName;

        //! @brief Mutex.
        mutable std::mutex mutex;

    public: 
        //! @brief Creates a new Mesh.
        Mesh(const std::string& name);

        //! @brief Adds a new SubMesh.
        void addSubMesh(const std::shared_ptr < SubMesh >& subMesh);

        //! @brief Removes a SubMesh.
        void removeSubMesh(const std::shared_ptr < SubMesh >& subMesh);

        //! @brief Returns a copy of the SubMeshes in this Mesh.
        auto subMeshes() const { std::lock_guard l(mutex); return mSubMeshes; }

        //! @brief Clears every SubMeshes.
        void clearSubMeshes();

        //! @brief Sets a buffer for an attribute.
        void setBuffer(const std::string& name, const std::shared_ptr < IBuffer >& buffer);

        //! @brief Returns a copy of the buffers in this Mesh.
        auto buffers() const { std::lock_guard l(mutex); return mBuffers; }

        //! @brief Clear the buffers.
        void clearBuffers();

        //! @brief Returns a copy of the Vertex structure.
        auto vertex() const { std::lock_guard l(mutex); return mVertex; }

        //! @brief Sets the Vertex structure.
        void setVertex(const Vertex& rhs);

        //! @brief Renders the Mesh with the specified IRenderer.
        void render(const std::shared_ptr < IRenderer >& rhs) const;

        //! @brief Returns the mesh name.
        std::string name() const;

        //! @brief Sets the mesh name.
        void setName(const std::string& name);
    };
}

#endif // !__XGL_MESH_H__