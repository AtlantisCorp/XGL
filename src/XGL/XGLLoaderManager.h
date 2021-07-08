#ifndef __XGL_LOADERMANAGER_H__
#define __XGL_LOADERMANAGER_H__

#include "XGLIncludes.h"
#include "XGLManager.h"

namespace XGL
{
    /**
     *  @brief Defines an interface for a ILoader class.
     * 
     */
    template < class T > 
    struct ILoaderManager : public Manager < T >
    {
        auto findByName(const std::string& name) const {
            return this->find([&name](auto& rhs){ return rhs->name() == name; });
        }
    };
}

#endif // !__XGL_LOADERMANAGER_H__