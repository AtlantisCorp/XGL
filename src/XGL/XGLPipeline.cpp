#include "XGLPipeline.h"
#include "XGLIRenderer.h"

namespace XGL
{
    Pipeline::Pipeline(const std::vector < std::shared_ptr < IShader > >& shaders, const Frame& viewport):
    mViewport(viewport)
    {   
        for (auto& shader : shaders) 
            mShaders[shader->type()] = shader;
    }

    std::shared_ptr < IShader > Pipeline::shader(ShaderType type) const 
    {
        std::lock_guard l(mutex);
        auto it = mShaders.find(type);
        return it == mShaders.end() ? nullptr : it->second;
    }

    void Pipeline::setShader(ShaderType type, const std::shared_ptr < IShader >& shader) 
    {
        std::lock_guard l(mutex);
        mShaders[type] = shader;
    }

    Frame Pipeline::viewport() const 
    {
        std::lock_guard l(mutex);
        return mViewport;
    }

    void Pipeline::setViewport(const Frame& viewport) 
    {
        std::lock_guard l(mutex);
        mViewport = viewport;
    }

    bool Pipeline::isValid() const 
    {
        return (shader(ShaderType::Vertex) && shader(ShaderType::Fragment)) 
            || shader(ShaderType::Compute);
    }

    void Pipeline::bind(const std::shared_ptr < IRenderer >& rhs) const 
    {
        std::lock_guard l(mutex);

        if (mViewport.width > 0 && mViewport.height > 0)
            rhs->setViewport(mViewport.x, mViewport.y, mViewport.width, mViewport.height);

        for (auto& entree : mShaders)
            rhs->setShader(entree.first, entree.second);
    }
}