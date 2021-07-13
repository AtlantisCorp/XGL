//
//  XGLCamera.cpp
//  XGL
//
//  Created by jacques tronconi on 14/07/2021.
//

#include "XGLCamera.h"

namespace XGL
{
    Camera::Camera(const glm::vec3& position,
                   const glm::vec3& target,
                   const glm::vec3& up):
    mPosition(position),
    mUp(up),
    mWorldUp(up)
    {
        mForward = glm::normalize(position - target);
        mRight = glm::normalize(glm::cross(mUp, mRight));
        mMatrix = glm::lookAt(mPosition, target, up);
        mBuildMatrix = false;
    }
    
    void Camera::move(const glm::vec3& rhs)
    {
        std::lock_guard l(mutex);
        mPosition += rhs;
        mBuildMatrix = true;
    }
    
    void Camera::rotate(const glm::vec3& axis, float angle)
    {
        std::lock_guard l(mutex);
        glm::vec4 target = glm::vec4(mPosition - mForward, 0.0);
        target = target * glm::rotate(glm::mat4(), angle, axis + mPosition);
        mForward = mPosition - glm::vec3(target);
        mRight = glm::cross(mForward, mWorldUp);
        mUp = glm::cross(mForward, mRight);
        mBuildMatrix = true;
    }
    
    glm::vec3 Camera::position() const
    {
        std::lock_guard l(mutex);
        return mPosition;
    }
    
    glm::vec3 Camera::target() const
    {
        std::lock_guard l(mutex);
        return mPosition - mForward;
    }
    
    glm::vec3 Camera::forward() const
    {
        std::lock_guard l(mutex);
        return mForward;
    }
    
    glm::vec3 Camera::backward() const
    {
        std::lock_guard l(mutex);
        return -mForward;
    }
    
    glm::vec3 Camera::right() const
    {
        std::lock_guard l(mutex);
        return mRight;
    }
    
    glm::vec3 Camera::left() const
    {
        std::lock_guard l(mutex);
        return -mRight;
    }
    
    glm::vec3 Camera::up() const
    {
        std::lock_guard l(mutex);
        return mUp;
    }
    
    glm::vec3 Camera::down() const
    {
        std::lock_guard l(mutex);
        return -mUp;
    }
    
    glm::mat4 Camera::matrix() const
    {
        std::lock_guard l(mutex);
        
        if (mBuildMatrix)
        {
            mMatrix = glm::lookAt(mPosition,
                                  mPosition - mForward,
                                  mUp);
            mBuildMatrix = false;
        }
        
        return mMatrix;
    }
    
    bool Camera::isDirty() const
    {
        return mBuildMatrix;
    }
    
    glm::vec3 Camera::worldUp() const
    {
        std::lock_guard l(mutex);
        return mWorldUp;
    }
    
    void Camera::setWorldUp(const glm::vec3& rhs)
    {
        std::lock_guard l(mutex);
        mWorldUp = rhs;
        mRight = glm::cross(mForward, mWorldUp);
        mUp = glm::cross(mForward, mRight);
        mBuildMatrix = true;
    }
}
