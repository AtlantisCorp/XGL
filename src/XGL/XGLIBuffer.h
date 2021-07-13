#ifndef __XGL_IBUFFER_H__
#define __XGL_IBUFFER_H__

#include "XGLIncludes.h"
#include "XGLIRenderObject.h"

namespace XGL
{
    //! @brief Defines some predefined roles for an IBuffer.
    enum class BufferRole
    {
        None, Vertex, Index, Uniforms
    };

    /**
     *  @brief Defines an interface for a buffer.
     * 
     *  A buffer is a piece of data created by a renderer. Each buffer has
     *  a unique id. You can create a buffer with IRenderer::createBuffer().
     * 
     */
    class IBuffer : public IRenderObject
    {
    public:
        //! @brief Creates a new instance.
        IBuffer(IRenderer& rhs): IRenderObject(rhs) {}

        //! @brief Returns the buffer size.
        virtual size_t size() const = 0;

        //! @brief Returns a copy of the data in the buffer.
        virtual std::vector < char > data() const = 0;

        //! @brief Sets the data in the buffer.
        virtual void setData(size_t size, const void* data = NULL) = 0;
        
        //! @brief Sets the data in the buffer to a vector of T.
        template < typename T >
        inline void setData(const std::vector < T >& data) {
            setData(data.size() * sizeof(T), &data[0]);
        }
    };
}

#endif // !__XGL_IBUFFER_H__
