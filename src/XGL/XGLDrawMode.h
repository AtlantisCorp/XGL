#ifndef __XGL_DRAWMODE_H__
#define __XGL_DRAWMODE_H__

#include "XGLIncludes.h"

namespace XGL
{
    //! @brief Defines the different draw mode.
    enum class DrawMode 
    {
        Points,
        Lines,
        Triangles,
        Quads, 
        Polygons
    };
}

#endif // !__XGL_DRAWMODE_H__