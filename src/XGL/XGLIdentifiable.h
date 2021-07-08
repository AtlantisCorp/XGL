#ifndef __XGL_IDENTIFIABLE_H__
#define __XGL_IDENTIFIABLE_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines a base class for objects that holds an id.
     * 
     *  This class uses CRTP to provide derived class specific id. Thus,
     *  you can identify an instance of a class with this id but the id is
     *  not portable between multiple classes.
     * 
     */
    template < class T > class Identifiable 
    {
        //! @brief The instance id.
        size_t mId;

        //! @brief The next id.
        static std::atomic_size_t mGlobalId;

    public:
        //! @brief Constructs a new instance.
        Identifiable(): mId(++mGlobalId) {}

        //! @brief Returns the instance id.
        inline size_t id() const { return mId; }
    };

    template < class T > std::atomic_size_t Identifiable < T >::mGlobalId(0);
}

#endif // !__XGL_IDENTIFIABLE_H__