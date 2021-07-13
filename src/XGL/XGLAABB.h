#ifndef __XGL_AABB_H__
#define __XGL_AABB_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines an Axis Aligned Bounding Box.
     *
     */
    struct AABB
    {
        glm::vec4 min, max;
    };
}

#endif // !__XGL_AABB_H__
