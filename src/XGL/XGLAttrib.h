#ifndef __XGL_ATTRIB_H__
#define __XGL_ATTRIB_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines an Attribute.
     * 
     */
    class Attrib
    {
    public:
        //! @brief Enumerates the different attribute type.
        enum Type 
        {
            None,
            Float1,
            Float2,
            Float3,
            Float4
        };

    private:
        //! @brief The attrib name.
        std::string mName;  

        //! @brief The attrib type.
        Type mType;

        //! @brief The stride between two elements of this attribute.
        size_t mStride;

    public:
        //! @brief Constructs a new instance.
        inline Attrib(const std::string& name, Type type, size_t stride):
        mName(name),
        mType(type),
        mStride(stride) {}

        //! @brief Returns the attrib name.
        inline const std::string& name() const { return mName; }

        //! @brief Returns the attrib type.
        inline Type type() const { return mType; }

        //! @brief Returns the attrib stride.
        inline size_t stride() const { return mStride; }
    };
}

#endif // !__XGL_ATTRIB_H__