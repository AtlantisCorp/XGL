#ifndef __XGL_MATERIAL_H__
#define __XGL_MATERIAL_H__

#include "XGLIncludes.h"
#include "XGLMaterialUniform.h"
#include "XGLClass.h"
#include "XGLIShader.h"
#include "XGLITexture.h"

namespace XGL
{
    class IRenderer;
    
    /**
     *  @brief Defines a collection of MaterialUniform.
     * 
     */
    class Material : public Class < Material >
    {
        //! @brief A list of MaterialUniform and their name.
        std::map < std::string, std::shared_ptr < MaterialUniform > > mUniforms;

        //! @brief The material name.
        std::string mName;

        //! @brief Mutex.
        mutable std::mutex mutex;

    public:
        //! @brief Constructs a new Material.
        Material(const std::string& name, const decltype(mUniforms)& uniforms = {});

        //! @brief Sets a new uniform.
        void setUniform(const std::string& name, const std::shared_ptr < MaterialUniform >& uniform);

        //! @brief Sets a new value.
        void setValue(const std::string& name, const std::any& value, ShaderType shader);

        //! @brief Sets a new texture.
        void setTexture(const std::string& name, const std::shared_ptr < ITexture >& texture, ShaderType shader);

        //! @brief Returns the uniform with name.
        std::shared_ptr < MaterialUniform > uniform(const std::string& name) const;

        //! @brief Returns all uniforms.
        auto uniforms() const { std::lock_guard l(mutex); return mUniforms; }

        //! @brief Removes a uniform.
        void removeUniform(const std::string& name);

        //! @brief Removes all uniforms.
        void clear();

        //! @brief Binds the Material into the specified renderer.
        void bind(const std::shared_ptr < IRenderer >& rhs) const;

        //! @brief Returns the material name.
        std::string name() const;

        //! @brief Changes the material name.
        void setName(const std::string& name);
    };
    
    typedef std::shared_ptr < Material > PMaterial;
}

#endif // !__XGL_MATERIAL_H__
