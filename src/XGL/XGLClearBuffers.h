#ifndef __XGL_CLEARBUFFERS_H__
#define __XGL_CLEARBUFFERS_H__

#include "XGLIncludes.h"

namespace XGL
{
    //! @brief Enumerates the buffers clearable.
    enum class ClearBuffers
    {
        None = 0,

        Stencil = 1 << 0,
        Depth = 1 << 1,
        Color0 = 1 << 2,
        Color1 = 1 << 3,
        Color2 = 1 << 4,
        Color3 = 1 << 5,
        Color4 = 1 << 6,
        Color5 = 1 << 7,
        Color6 = 1 << 8,
        Color7 = 1 << 9,
        Color8 = 1 << 10,
        Color9 = 1 << 11,

        All = 0xFFFF
    };
}

#endif // !__XGL_CLEARBUFFERS_H__