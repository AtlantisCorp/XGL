#include "XGLMaterialUniform.h"
#include "XGLError.h"

namespace XGL
{
    MaterialUniform::MaterialUniform(ShaderType shader, const std::shared_ptr < ITexture >& texture):
    mShader(shader),
    mTexture(texture),
    mType(Texture) 
    {

    }

    void MaterialUniform::setTexture(const std::shared_ptr < ITexture >& texture)
    {
        std::lock_guard l(mutex);
        mValue.reset();
        mTexture = texture;
        mType = Texture; 
    }

    std::any MaterialUniform::value() const 
    {
        std::lock_guard l(mutex);
        XGLThrowIf(mType != Value, "MaterialUniform is not a value.");
        return mValue;
    }

    std::shared_ptr < ITexture > MaterialUniform::texture() const 
    {
        std::lock_guard l(mutex);
        XGLThrowIf(mType != Texture, "MaterialUniform is not a texture.");
        return mTexture;
    }

    MaterialUniform::Type MaterialUniform::type() const 
    {
        std::lock_guard l(mutex);
        return mType;
    }

    ShaderType MaterialUniform::shader() const 
    {
        std::lock_guard l(mutex);
        return mShader;
    }

    void MaterialUniform::setShader(ShaderType shader) 
    {
        std::lock_guard l(mutex);
        mShader = shader;
    }
}