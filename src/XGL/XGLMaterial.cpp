#include "XGLMaterial.h"
#include "XGLError.h"
#include "XGLIRenderer.h"

namespace XGL
{
    Material::Material(const std::string& name, const decltype(mUniforms)& uniforms):
    mUniforms(uniforms),
    mName(name)
    {

    }

    void Material::setUniform(const std::string& name, const std::shared_ptr < MaterialUniform >& uniform)
    {
        XGLThrowIf(!uniform, "Null uniform");
        XGLThrowIf(name.empty(), "Empty uniform name");
        std::lock_guard l(mutex);
        mUniforms[name] = uniform;
    }

    void Material::setValue(const std::string& name, const std::any& value, ShaderType shader)
    {
        setUniform(name, MaterialUniform::New(shader, value));
    }

    void Material::setTexture(const std::string& name, const std::shared_ptr < ITexture >& texture, ShaderType shader)
    {
        setUniform(name, MaterialUniform::New(shader, texture));
    }

    std::shared_ptr < MaterialUniform > Material::uniform(const std::string& name) const 
    {
        XGLThrowIf(name.empty(), "Uniform name cannot be empty");
        std::lock_guard l(mutex);
        auto it = mUniforms.find(name);
        if (it == mUniforms.end())
            return nullptr;
        return it->second;
    }

    void Material::removeUniform(const std::string& name)
    {
        XGLThrowIf(name.empty(), "Uniform name cannot be empty");
        std::lock_guard l(mutex);
        auto it = mUniforms.find(name);
        if (it != mUniforms.end())
            mUniforms.erase(it);
    }

    void Material::clear() 
    {
        std::lock_guard l(mutex);
        mUniforms.clear();
    }

    void Material::bind(const std::shared_ptr < IRenderer >& rhs) const 
    {
        XGLThrowIf(!rhs, "Null IRenderer.");
        auto unifs = uniforms();

        for (auto& entree : unifs)
        {
            if (entree.second->type() == MaterialUniform::Value)
                rhs->setUniform(entree.second->shader(), entree.first, entree.second->value());
            else if (entree.second->type() == MaterialUniform::Texture)
                rhs->setTexture(entree.second->shader(), entree.first, entree.second->texture());
        }
    }

    std::string Material::name() const 
    {
        std::lock_guard l(mutex);
        return mName;
    }

    void Material::setName(const std::string& name) 
    {
        std::lock_guard l(mutex);
        mName = name;
    }
}