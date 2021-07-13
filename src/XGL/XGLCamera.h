//
//  XGLCamera.h
//  XGL
//
//  Created by jacques tronconi on 14/07/2021.
//

#ifndef __XGL_CAMERA_H__
#define __XGL_CAMERA_H__

#include "XGLIncludes.h"
#include "XGLClass.h"

namespace XGL
{
    /**
     *  @brief Defines a classic Camera.
     *
     *  A Camera has only a position, a target and a up vector. This three
     *  components makes the view matrix of the Camera.
     *
     *  The Camera uses a deferred calculation for the view matrix: it is
     *  calculated only on request through Camera::matrix().
     *
     */
    class Camera : public Class < Camera >
    {
        glm::vec3 mPosition;
        
        glm::vec3 mForward;
        
        glm::vec3 mRight;
        
        glm::vec3 mUp;
        
        glm::vec3 mWorldUp;
        
        mutable glm::mat4 mMatrix;
        
        mutable std::atomic_bool mBuildMatrix;
        
        mutable std::mutex mutex;
        
    public:
        
        Camera(const glm::vec3& position,
               const glm::vec3& target,
               const glm::vec3& up = glm::vec3(0.0, 1.0, 0.0));
        
        void move(const glm::vec3& rhs);
        
        void rotate(const glm::vec3& axis, float angle);
        
        glm::vec3 position() const;
        
        glm::vec3 target() const;
        
        glm::vec3 forward() const;
        
        glm::vec3 backward() const;
        
        glm::vec3 right() const;
        
        glm::vec3 left() const;
        
        glm::vec3 up() const;
        
        glm::vec3 down() const;
        
        glm::mat4 matrix() const;
        
        bool isDirty() const;
        
        glm::vec3 worldUp() const;
        
        void setWorldUp(const glm::vec3& rhs);
    };
    
    typedef std::shared_ptr < Camera > PCamera;
}

#endif /* __XGL_CAMERA_H__ */
