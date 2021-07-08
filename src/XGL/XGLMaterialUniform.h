#ifndef __XGL_MATERIALUNIFORM_H__
#define __XGL_MATERIALUNIFORM_H__

#include "XGLIncludes.h"
#include "XGLClass.h"
#include "XGLIShader.h"
#include "XGLITexture.h"

namespace XGL
{
    /**
     *  @brief Defines a MaterialUniform.
     * 
     *  A MaterialUniform can hold a value, a texture, a sampler or even 
     *  a buffer. The uniform is then bound to the renderer by using the
     *  correct function, setUniform(), setTexture(), ...
     *  
     *  Each MaterialUniform is created as shared pointers. You can share
     *  uniforms between Materials.
     * 
     */
    class MaterialUniform : public Class < MaterialUniform >
    {
    public: 

        //! @brief Enumerates the MaterialUniform types.
        enum Type
        {
            Value, Texture
        };

    private:
        //! @brief The value, if this is a value.
        std::any mValue;

        //! @brief The texture, if this is a texture.
        std::shared_ptr < ITexture > mTexture;

        //! @brief The uniform type.
        Type mType;

        //! @brief The ShaderType where this uniform belongs.
        ShaderType mShader;

        //! @brief The mutex.
        mutable std::mutex mutex;

    public:
        //! @brief Constructs a new instance from a texture.
        MaterialUniform(ShaderType shader, const std::shared_ptr < ITexture >& texture);

        //! @brief Constructs a new instance from a value.
        MaterialUniform(ShaderType shader, const auto& value): 
        mShader(shader), 
        mValue(value), 
        mType(Value) {}

        //! @brief Sets a new value for the uniform.
        void setValue(const auto& value) 
        {
            std::lock_guard l(mutex);
            mValue = value;
            mTexture = nullptr;
            mType = Value;
        }

        //! @brief Sets a new texture for the uniform.
        void setTexture(const std::shared_ptr < ITexture >& texture);

        //! @brief Returns the value.
        std::any value() const;

        //! @brief Returns the texture.
        std::shared_ptr < ITexture > texture() const;

        //! @brief Returns the type.
        Type type() const;

        //! @brief Returns the shader type.
        ShaderType shader() const;

        //! @brief Changes the shader where this uniform belongs to.
        void setShader(ShaderType shader);
    };
}

#endif // !__XGL_MATERIALUNIFORM_H__