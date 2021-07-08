#ifndef __XGL_LOADERNOTFOUND_H__
#define __XGL_LOADERNOTFOUND_H__

#include "XGLError.h"

namespace XGL
{
    /**
     *  @brief Error thrown if a loader cannot be found.
     * 
     */
    struct LoaderNotFound : public Error 
    {
        //! @brief The loader name.
        std::string name;

        //! @brief Constructs a new instance.
        LoaderNotFound(const std::string& name): 
        Error("Cannot find XGL::ILoader: " + name),
        name(name) {}
    };
}

#endif // !__XGL_LOADERNOTFOUND_H__