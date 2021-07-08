#ifndef __XGL_FRAME_H__
#define __XGL_FRAME_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines a Frame for a surface.
     * 
     */
    struct Frame
    {
        uint32_t width, height, x, y;
    };
}

#endif // !__XGL_FRAME_H__