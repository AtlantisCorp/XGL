#include "XGLFrustum.h"

namespace XGL
{
    Frustum::Frustum(const glm::mat4& proj, const glm::mat4& view)
    {
        const glm::mat4 vp = view * proj;
        const float* clip = glm::value_ptr(vp);
        
        // Right side
        mPlanes[Right][A] = clip[ 3] - clip[ 0];
        mPlanes[Right][B] = clip[ 7] - clip[ 4];
        mPlanes[Right][C] = clip[11] - clip[ 8];
        mPlanes[Right][D] = clip[15] - clip[12];
        mPlanes[Right] = glm::normalize(mPlanes[Right]);
        
        // Left side.
        mPlanes[Left][A] = clip[ 3] + clip[ 0];
        mPlanes[Left][B] = clip[ 7] + clip[ 4];
        mPlanes[Left][C] = clip[11] + clip[ 8];
        mPlanes[Left][D] = clip[15] + clip[12];
        mPlanes[Right] = glm::normalize(mPlanes[Right]);
        
        // Bottom side.
        mPlanes[Bottom][A] = clip[ 3] + clip[ 1];
        mPlanes[Bottom][B] = clip[ 7] + clip[ 5];
        mPlanes[Bottom][C] = clip[11] + clip[ 9];
        mPlanes[Bottom][D] = clip[15] + clip[13];
        mPlanes[Bottom] = glm::normalize(mPlanes[Bottom]);
        
        // Top side
        mPlanes[Top][A] = clip[ 3] - clip[ 1];
        mPlanes[Top][B] = clip[ 7] - clip[ 5];
        mPlanes[Top][C] = clip[11] - clip[ 9];
        mPlanes[Top][D] = clip[15] - clip[13];
        mPlanes[Top] = glm::normalize(mPlanes[Top]);
        
        // Back side
        mPlanes[Back][A] = clip[ 3] - clip[ 2];
        mPlanes[Back][B] = clip[ 7] - clip[ 6];
        mPlanes[Back][C] = clip[11] - clip[10];
        mPlanes[Back][D] = clip[15] - clip[14];
        mPlanes[Back] = glm::normalize(mPlanes[Back]);
        
        // Front side
        mPlanes[Front][A] = clip[ 3] + clip[ 2];
        mPlanes[Front][B] = clip[ 7] + clip[ 6];
        mPlanes[Front][C] = clip[11] + clip[10];
        mPlanes[Front][D] = clip[15] + clip[14];
        mPlanes[Front] = glm::normalize(mPlanes[Front]);
    }
    
    bool Frustum::contains(const glm::vec4& point) const
    {
        for (int i = 0; i < 6; ++i)
        {
            if (mPlanes[i][A] * point.x +
                mPlanes[i][B] * point.y +
                mPlanes[i][C] * point.z +
                mPlanes[i][D] <= 0)
                return false;
        }
        
        return true;
    }
    
    bool Frustum::contains(const glm::vec4& center, float radius) const
    {
        for (int i = 0; i < 6; ++i)
        {
            if (mPlanes[i][A] * center.x +
                mPlanes[i][B] * center.y +
                mPlanes[i][C] * center.z +
                mPlanes[i][D] <= -radius)
                return false;
        }
        
        return true;
    }
    
    bool Frustum::contains(const AABB& box) const
    {
        const glm::vec4 length = box.max - box.min;
        
        const glm::vec4 points[8] =
        {
            box.min,
            box.min + glm::vec4(length.x, 0, 0, 1),
            box.min + glm::vec4(0, length.y, 0, 1),
            box.min + glm::vec4(0, 0, length.z, 1),
            box.max,
            box.max - glm::vec4(length.x, 0, 0, 1),
            box.max - glm::vec4(0, length.y, 0, 1),
            box.max - glm::vec4(0, 0, length.z, 1)
        };
        
        for (int i = 0; i < 6; ++i)
        {
            bool ok = false;
            
            for (int j = 0; j < 8; ++j)
            {
                if (mPlanes[i][A] * points[j].x +
                    mPlanes[i][B] * points[j].y +
                    mPlanes[i][C] * points[j].z +
                    mPlanes[i][D] > 0)
                {
                    ok = true;
                    break;
                }
            }
            
            if (!ok)
                return false;
        }
        
        return true;
    }
}
