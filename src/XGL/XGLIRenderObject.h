#ifndef __XGL_IRENDEROBJECT_H__
#define __XGL_IRENDEROBJECT_H__

#include "XGLIncludes.h"

namespace XGL
{
    class IRenderer;

    /**
     *  @brief Defines a base class for any object created by IRenderer.
     * 
     */
    class IRenderObject 
    {
        //! @brief Holds the renderer that created this object.
        IRenderer& mRenderer;

    public:
        //! @brief Constructs a new instance.
        inline IRenderObject(IRenderer& rhs): mRenderer(rhs) {}

        //! @brief Returns the IRenderer.
        inline IRenderer& renderer() { return mRenderer; }

        //! @brief Returns the IRenderer.
        inline const IRenderer& renderer() const { return mRenderer; }
    };
}

#endif // !__XGL_IRENDEROBJECT_H__