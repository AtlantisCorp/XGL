//
//  XGLRenderPassAttachment.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_RENDERPASSATTACHMENT_H__
#define __XGL_RENDERPASSATTACHMENT_H__

#include "XGLRenderPassLoadAction.h"
#include "XGLRenderPassStoreAction.h"
#include "XGLIncludes.h"
#include "XGLITexture.h"

namespace XGL
{
    /**
     *  @brief Defines an attachment.
     *
     */
    struct RenderPassAttachment
    {
        //! @brief The texture used to render to this attachment.
        PITexture texture = nullptr;
        
        //! @brief The mipmap level of the texture used for rendering to the
        //! attachment.
        size_t level = 0;
        
        //! @brief The slice of the texture used for rendering to the attachment.
        size_t slice = 0;
        
        //! @brief The depth plane of the texture used for rendering to the
        //! attachment.
        size_t depthPlane = 0;
        
        //! @brief The action performed by this attachment at the start of a
        //! rendering pass for a render command encoder.
        RenderPassLoadAction loadAction = RenderPassLoadAction::Clear;
        
        //! @brief The action performed by this attachment at the end of a
        //! rendering pass for a render command encoder.
        RenderPassStoreAction storeAction = RenderPassStoreAction::Store;
        
        //! @brief The options that modify the store action performed by this
        //! attachment.
        RenderPassStoreActionOption storeActionOption = RenderPassStoreActionOption::None;
        
        //! @brief The destination texture used when resolving multisampled texture
        //! data into single sample values.
        PITexture resolveTexture = nullptr;
        
        //! @brief The mipmap level of the texture used for the multisample resolve
        //! action.
        size_t resolveLevel = 0;
        
        //! @brief The slice of the texture used for the multisample resolve action.
        size_t resolveSlice = 0;
        
        //! @brief The depth plane of the texture used for the multisample resolve action.
        size_t resolveDepthPlane = 0;
    };
}

#endif /* __XGL_RENDERPASSATTACHMENT_H__ */
