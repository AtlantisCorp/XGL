#ifndef __XGL_PIXELFORMAT_H__
#define __XGL_PIXELFORMAT_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Class to hold the pixel formats.
     * 
     */
    class PixelFormat 
    {
    public:
        enum _
        {
            RGB8,
            RGB16,
            RGB32,

            RGBA8,
            RGBA16,
            RGBA32
        };
    };
}

#endif // !__XGL_PIXELFORMAT_H__