#ifndef __XGL_LOADER_H__
#define __XGL_LOADER_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines an interface for a loader.
     * 
     */
    struct ILoader 
    {
        //! @brief Destructor.
        virtual ~ILoader() = default;

        //! @brief Returns the loader name.
        virtual std::string name() const = 0;
    };
}

#endif // !__XGL_LOADER_H__