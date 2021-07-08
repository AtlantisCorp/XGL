#ifndef __XGL_VERTEX_H__
#define __XGL_VERTEX_H__

#include "XGLClass.h"
#include "XGLAttrib.h"
#include "XGLIBuffer.h"

namespace XGL
{
    /**
     *  @brief Holds multiple Attribs to describe a Vertex.
     * 
     *  This class describe a whole Vertex. You can use it to store your
     *  vertex structure. 
     * 
     */
    class Vertex : public Class < Vertex >
    {
        //! @brief The different attributes in the vertex.
        std::list < Attrib > mAttribs;

        //! @brief Mutex.
        mutable std::mutex mutex;

    public: 
        //! @brief Creates a new vertex from multiple attributes.
        Vertex(const std::list < Attrib >& attribs);

        //! @brief Copy constructor.
        Vertex(const Vertex& rhs);

        //! @brief Assignment operator.
        Vertex& operator = (const Vertex& rhs);

        //! @brief Returns the attribute for given name.
        Attrib get(const std::string& name) const;

        //! @brief Sets the attribute for a name.
        void set(const Attrib& attrib);

        //! @brief Removes an attribute.
        void remove(const std::string& name);

        //! @brief Clears all attributes.
        void clear();
    };

    //! @brief Defines a map of IBuffer and a name.
    typedef std::map < std::string, std::shared_ptr < IBuffer > > VertexBuffers;
}

#endif // !__XGL_VERTEX_H__