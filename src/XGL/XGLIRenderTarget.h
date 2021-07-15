//
//  XGLIRenderTarget.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_IRENDERTARGET_H__
#define __XGL_IRENDERTARGET_H__

#include "XGLIdentifiable.h"
#include "XGLITexture.h"
#include "XGLIRenderObject.h"
#include "XGLRenderPass.h"

namespace XGL
{
    /**
     *  @brief Defines an interface for a RenderTarget.
     *
     *  All RenderTargets have a common interface. You can 'begin' rendering
     *  on a render target with begin(), and 'end' the rendering through
     *  the end() function.
     *
     *  You have first to define a RenderPassDescriptor that defines some
     *  states for the render target when beginning render. This descriptor
     *  defines the behaviour to adopt for each ClearBuffers.
     *
     *  @warning
     *  This is not related to the RenderPipeline. The RenderPipeline can be
     *  changed dynamically with IRenderer::set*Shader().
     *
     */
    struct IRenderTarget : public Identifiable < IRenderTarget >,
                           public IRenderObject
    {
        using IRenderObject::IRenderObject;
        
        //! @brief Begins the rendering for a given RenderPass.
        virtual void begin(const RenderPass& rhs) = 0;
        
        //! @brief Ends the current RenderPass.
        virtual void end() = 0;
        
        //! @brief Returns a RenderPass suitable to render into this RenderTarget.
        virtual RenderPass createRenderPass() = 0;
    };
}

#endif /* __XGL_IRENDERTARGET_H__ */
