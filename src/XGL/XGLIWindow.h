#ifndef __XGL_IWINDOW_H__
#define __XGL_IWINDOW_H__

#include "XGLIncludes.h"
#include "XGLEvent.h"
#include "XGLFrame.h"

namespace XGL
{
    /**
     *  @brief Defines args for the IWindow construction.
     * 
     */
    struct WindowArgs
    {
        //! @brief The window title.
        std::string title;

        //! @brief The window coords.
        size_t x = 0, y = 0, width = 0, height = 0;

        //! @brief Closable flag.
        bool closable = true;

        //! @brief Resizable flag.
        bool resizable = false;

        //! @brief Miniaturizable flag.
        bool miniaturizable = false;

        //! @brief Bordered flag.
        bool bordered = false;
    };

    /**
     *  @brief Defines an interface for a native window.
     * 
     *  You can either derive from this class and create your own
     *  native window class, or use IRenderer::createSurface() to 
     *  create directly a IWindow/ISurface pair.
     * 
     */
    class IWindow
    {
    public:
        //! @brief An event when the window will close.
        Event < IWindow& > WillClose;

        //! @brief An event when the window will enter user resizing.
        Event < IWindow& > WillResize;

        //! @brief An event when the window has been resized.
        Event < IWindow&, size_t, size_t > Resized;

        //! @brief An event when the window has been moved.
        Event < IWindow&, size_t, size_t > Moved;

        //! @brief An event when the window is miniaturized.
        Event < IWindow& > Miniaturized;

        //! @brief An event when the window is restored from miniaturization.
        Event < IWindow& > Restored;

    public:
        //! @brief Destructor.
        virtual ~IWindow() = default;

        //! @brief Returns the window frame.
        virtual Frame frame() const = 0;

        //! @brief Moves the window.
        virtual void move(size_t x, size_t y) = 0;

        //! @brief Resizes the window.
        virtual void resize(size_t width, size_t height) = 0;

        //! @brief Miniaturize the window.
        virtual void miniaturize() = 0;

        //! @brief Show the window.
        virtual void show() = 0;

        //! @brief Closes the window.
        virtual void close() = 0;

        //! @brief Returns the window title.
        virtual std::string title() const = 0;

        //! @brief Sets the window title.
        virtual void setTitle(const std::string& title) = 0;

        //! @brief Returns a handle to the native window type.
        virtual void* handle() const = 0;

        //! @brief Returns true if window has been marked closed.
        virtual bool isClosed() const = 0;

        //! @brief Updates the window.
        virtual void update() = 0;
    };
}

#endif // !__XGL_IWINDOW_H__