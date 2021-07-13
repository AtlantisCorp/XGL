#ifndef __XGL_POSITIONABLE_H__
#define __XGL_POSITIONABLE_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines a base class for an object that can be positionned,
     *  through a triplet position/scale/orientation.
     *
     *  The transformation matrix is build upon request only when position, scale
     *  or orientation has been changed.
     *
     */
    class Positionable
    {
        //! @brief The size of the bounding box representing the SceneNode.
        glm::vec4 mBoundingLength;
        
        //! @brief The position of this SceneNode.
        glm::vec4 mPosition;
        
        //! @brief The orientation of this SceneNode.
        glm::quat mOrientation;
        
        //! @brief The scale of this SceneNode.
        glm::vec4 mScale;
        
        //! @brief The updated Matrix4x4 for the Model Matrix.
        mutable glm::mat4 mMatrix;
        
        //! @brief boolean true if we should compute the model matrix.
        mutable bool mBuildMatrix;
        
        //! @brief Mutex.
        mutable std::mutex mutex;
        
    public:
        //! @brief Creates a new instance.
        Positionable();
        
        //! @brief Returns the local model matrix.
        virtual glm::mat4 matrix() const;
        
        //! @brief Returns the node position.
        virtual glm::vec4 position() const;
        
        //! @brief Sets the node position.
        virtual void setPosition(float x, float y, float z);
        
        //! @brief Translates the node.
        virtual void translate(float x, float y, float z);
        
        //! @brief Returns the node orientation.
        virtual glm::quat orientation() const;
        
        //! @brief Rotates the node around an axis.
        virtual void rotate(const glm::vec3& axis, float angle);
        
        //! @brief Rotates the node around the X axis.
        virtual void rotateX(float angle);
        
        //! @brief Rotates the node around the Y axis.
        virtual void rotateY(float angle);
        
        //! @brief Rotates the node around the Z axis.
        virtual void rotateZ(float angle);
        
        //! @brief Returns the node scale factor.
        virtual glm::vec4 scale() const;
        
        //! @brief Scales the node.
        virtual void scale(float x, float y, float z);
        
        //! @brief Sets the node scale.
        virtual void setScale(float x, float y, float z);
    };
}

#endif // !__XGL_POSITIONABLE_H__
