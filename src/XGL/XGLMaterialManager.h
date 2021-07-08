#ifndef __XGL_MATERIALMANAGER_H__
#define __XGL_MATERIALMANAGER_H__

#include "XGLMaterial.h"
#include "XGLManager.h"
#include "XGLClass.h"

namespace XGL
{
    /**
     *  @brief Defines a MaterialManager.
     * 
     */
    struct MaterialManager : public Manager < Material >, public Class < MaterialManager > 
    {
        //! @brief Returns a Material by name, or nullptr if not found.
        inline auto findByName(const std::string& name) const {
            return find([&](auto& rhs){ return rhs->name() == name; });
        }
    };
}

#endif // !__XGL_MATERIALMANAGER_H__