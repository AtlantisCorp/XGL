#include "XGLPositionable.h"

namespace XGL
{
    Positionable::Positionable():
    mPosition(0, 0, 0, 1.0),
    mOrientation(),
    mScale(1.0, 1.0, 1.0, 0.0),
    mMatrix(),
    mBuildMatrix(true)
    {
        
    }
    
    glm::mat4 Positionable::matrix() const
    {
        std::lock_guard l(mutex);
        
        if (mBuildMatrix)
        {
            mMatrix = glm::mat4();
            mMatrix = glm::translate(mMatrix, glm::vec3(mPosition));
            mMatrix = glm::toMat4(mOrientation) * mMatrix;
            mMatrix = glm::scale(mMatrix, glm::vec3(mScale));
            mBuildMatrix = false;
        }
        
        return mMatrix;
    }
    
    glm::vec4 Positionable::position() const
    {
        std::lock_guard l(mutex);
        return mPosition;
    }
    
    void Positionable::setPosition(float x, float y, float z)
    {
        std::lock_guard l(mutex);
        mPosition.x = x;
        mPosition.y = y;
        mPosition.z = z;
        mBuildMatrix = true;
    }
    
    void Positionable::translate(float x, float y, float z)
    {
        std::lock_guard l(mutex);
        mPosition += x;
        mPosition += y;
        mPosition += z;
        mBuildMatrix = true;
    }
    
    glm::quat Positionable::orientation() const
    {
        std::lock_guard l(mutex);
        return mOrientation;
    }
    
    void Positionable::rotate(const glm::vec3& axis, float angle)
    {
        std::lock_guard l(mutex);
        mOrientation *= glm::angleAxis(angle, axis);
        mBuildMatrix = true;
    }
    
    void Positionable::rotateX(float angle)
    {
        rotate(glm::vec3(1.0, 0, 0), angle);
    }
    
    void Positionable::rotateY(float angle)
    {
        rotate(glm::vec3(0, 1.0, 0), angle);
    }
    
    void Positionable::rotateZ(float angle)
    {
        rotate(glm::vec3(0, 0, 1.0), angle);
    }
    
    glm::vec4 Positionable::scale() const
    {
        std::lock_guard l(mutex);
        return mScale;
    }
    
    void Positionable::setScale(float x, float y, float z)
    {
        std::lock_guard l(mutex);
        mScale.x = x;
        mScale.y = y;
        mScale.z = z;
        mBuildMatrix = true;
    }
    
    void Positionable::scale(float x, float y, float z)
    {
        std::lock_guard l(mutex);
        mScale.x *= x;
        mScale.y *= y;
        mScale.z *= z;
        mBuildMatrix = true;
    }
}
