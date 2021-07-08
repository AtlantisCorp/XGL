#ifndef __XGL_PIPELINE_H__
#define __XGL_PIPELINE_H__

#include "XGLIncludes.h"
#include "XGLIShader.h"
#include "XGLFrame.h"
#include "XGLIdentifiable.h"
#include "XGLClass.h"

namespace XGL
{
    /**
     *  @brief Defines a render pipeline.
     * 
     *  A render pipeline holds some states that can be bound to a IRenderer. The
     *  pipeline holds the differents shaders to use, and some fixed states like 
     *  the viewport, the stencil operations, etc.
     * 
     */
    class Pipeline : public Identifiable < Pipeline >, public Class < Pipeline >
    {
        //! @brief The different IShaders to use.
        std::map < ShaderType, std::shared_ptr < IShader > > mShaders;

        //! @brief The viewport frame.
        Frame mViewport;

        //! @brief Protects data.
        mutable std::mutex mutex;

    public: 
        //! @brief Constructs a new instance.
        Pipeline(const std::vector < std::shared_ptr < IShader > >& shaders, const Frame& viewport = { 0, 0, 0, 0 });

        //! @brief Returns the shader set for a particular type.
        std::shared_ptr < IShader > shader(ShaderType type) const;

        //! @brief Sets a shader for a particular type.
        void setShader(ShaderType type, const std::shared_ptr < IShader >& shader);

        //! @brief Returns the viewport.
        Frame viewport() const;

        //! @brief Sets the viewport. 
        void setViewport(const Frame& viewport);

        //! @brief Returns true if this Pipeline can be bound to a renderer.
        bool isValid() const;

        //! @brief Binds the pipeline into the IRenderer.
        void bind(const std::shared_ptr < IRenderer >& rhs) const;
    };
}

#endif // !__XGL_PIPELINE_H__