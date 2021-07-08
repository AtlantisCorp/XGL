#ifndef __XGL_ISURFACE_H__
#define __XGL_ISURFACE_H__

#include "XGLIncludes.h"
#include "XGLEvent.h"
#include "XGLClearBuffers.h"
#include "XGLFrame.h"
#include "XGLIWindow.h"
#include "XGLIRenderObject.h"

namespace XGL 
{
    class IRenderer;

    /**
     *  @brief Defines an interface for a render surface.
     * 
     *  The render surface has two 'versions': one where the user provides a
     *  IWindow. The surface doesn't own the IWindow and events from the IWindow
     *  are not transmitted by the surface. And a version where the user provides
     *  a WindowArgs structure. The surface then owns the IWindow, and transmits
     *  events from this IWindow as if it was its own events.
     * 
     *  To create a custom IWindow, either derive from IWindow or use 
     *  IRenderer::createWindow(). 
     * 
     */
    class ISurface : public IRenderObject
    {
    public:
        //! @brief An event when the surface is resized.
        Event < ISurface&, size_t, size_t > Resized;

        //! @brief An event when the surface shall be rendered.
        Event < ISurface& > Render;

    public:
        //! @brief Constructs a new instance.
        ISurface(IRenderer& renderer): IRenderObject(renderer) {}

        //! @brief Destructor.
        virtual ~ISurface() = default;

        //! @brief Returns the surface frame.
        virtual Frame frame() const = 0;

        //! @brief Returns the associated IWindow.
        virtual std::shared_ptr < IWindow > window() const = 0;

        //! @brief Returns true if this surface owns the IWindow.
        virtual bool ownsWindow() const = 0;

        //! @brief Clears the specified buffers.
        virtual void clearBuffers(ClearBuffers buffers = ClearBuffers::All) = 0;

        //! @brief Swaps the buffers in the swap chain.
        virtual void swapBuffers() = 0;
    };
}

#endif // !__XGL_ISURFACE_H__