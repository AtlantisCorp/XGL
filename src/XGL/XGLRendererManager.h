#ifndef __XGL_RENDERERMANAGER_H__
#define __XGL_RENDERERMANAGER_H__

#include "XGLIncludes.h"
#include "XGLClass.h"
#include "XGLManager.h"
#include "XGLIRenderer.h"

namespace XGL
{
    /**
     *  @brief Defines a RendererManager.
     * 
     */
    class RendererManager : public Class < RendererManager >, 
                            public Manager < IRenderer >
    {
    public:

        //! @brief Finds the first available IRenderer.
        std::shared_ptr < IRenderer > first() const;

        //! @brief Finds a IRenderer by name.
        std::shared_ptr < IRenderer > findByName(const std::string& name) const;
    };
}

#endif // !__XGL_RENDERERMANAGER_H__