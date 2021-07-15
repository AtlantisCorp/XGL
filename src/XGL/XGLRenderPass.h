//
//  XGLRenderPass.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_RENDERPASS_H__
#define __XGL_RENDERPASS_H__

#include "XGLRenderPassColorAttachment.h"
#include "XGLRenderPassDepthAttachment.h"
#include "XGLRenderPassStencilAttachment.h"
#include "XGLIdentifiable.h"

namespace XGL
{
    /**
     *  @brief A group of render targets that hold the results of a render pass.
     *
     */
    struct RenderPass : public Identifiable < RenderPass >
    {
        //! @brief An array of state information for attachments that store
        //! color data.
        RenderPassColorAttachment colorAttachments[10];
        
        //! @brief State information for an attachment that stores depth data.
        RenderPassDepthAttachment depthAttachment;
        
        //! @brief State information for an attachment that stores stencil data.
        RenderPassStencilAttachment stencilAttachment;
    };
}

#endif /* __XGL_RENDERPASS_H__ */
