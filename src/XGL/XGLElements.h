#ifndef __XGL_ELEMENTS_H__
#define __XGL_ELEMENTS_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines a class for holding elements infos.
     * 
     */
    class Elements 
    {
    public:
        //! @brief Enumerates the available elements type.
        enum Type
        {
            Uint8,
            Uint16,
            Uint32
        };
    };
}

#endif // !__XGL_ELEMENTS_H__