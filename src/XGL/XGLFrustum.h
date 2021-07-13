#ifndef __XGL_FRUSTUM_H__
#define __XGL_FRUSTUM_H__

#include "XGLIncludes.h"
#include "XGLAABB.h"

namespace XGL
{
    /**
     *  @brief Defines a Frustum helper.
     *
     */
    class Frustum
    {
        //! @brief Holds a, b, c and d values for each frustum side.
        glm::vec4 mPlanes[6];
        
    public:
        //! @brief Enumerates the different Frustum Planes.
        enum Side
        {
            Right = 0, Left, Bottom, Top, Back, Front
        };
        
        //! @brief Enumerates the Planes data.
        enum Plane
        {
            A = 0, B, C, D
        };
        
    public:
        //! @brief Creates a new Frustum.
        Frustum(const glm::mat4& proj, const glm::mat4& view);
        
        //! @brief Returns true if a point is in the frustum.
        bool contains(const glm::vec4& point) const;
        
        //! @brief Returns true if a sphere is in the frustum.
        bool contains(const glm::vec4& center, float radius) const;
        
        //! @brief Returns true if a bounding box is in the frustum.
        bool contains(const AABB& box) const;
    };
}

#endif // ! __XGL_FRUSTUM_H__
