#ifndef __XGL_ERROR_H__
#define __XGL_ERROR_H__

#include "XGLIncludes.h"

namespace XGL
{
    /// @brief Defines an error from an exception.
    struct Error : public std::runtime_error 
    {
        using std::runtime_error::runtime_error;
        using std::runtime_error::what;
    };
}

#define XGLThrowIf(a, err) if ((a)) throw err

#endif // !__XGL_ERROR_H__