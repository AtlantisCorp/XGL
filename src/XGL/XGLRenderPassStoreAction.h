//
//  XGLRenderPassStoreAction.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_RENDERPASSSTOREACTION_H__
#define __XGL_RENDERPASSSTOREACTION_H__

namespace XGL
{
    /**
     *  @brief Types of actions performed for an attachment at the end of a
     *  rendering pass.
     *
     */
    enum class RenderPassStoreAction
    {
        //! @brief The GPU has permission to discard the rendered contents of the
        //! attachment at the end of the render pass, replacing them with arbitrary
        //! data.
        DontCare = 0,
        
        //! @brief The GPU stores the rendered contents to the texture.
        Store,
        
        //! @brief The GPU resolves the multisampled data to one sample per pixel
        //! and stores the data to the resolve texture, discarding the multisample
        //! data afterwards.
        MultisampleResolve,
        
        //! @brief The GPU stores the multisample data to the multisample texture,
        //! resolves the data to a sample per pixel, and stores the data to the resolve
        //! texture.
        StoreAndMultisampleResolve,
        
        //! @brief The app will specify the store action when it encodes the render pass.
        Unknown,
        
        //! @brief The GPU stores depth data in a sample-position–agnostic representation.
        CustomSampleDepthStore
    };
    
    /**
     *  @brief Options that modify a store action.
     *
     *  This property modifies the intended behavior of the store actions in the
     *  RenderPassStoreAction enumeration.
     *
     */
    enum class RenderPassStoreActionOption
    {
        //! @brief An option that doesn't modify the intended behavior of a store action.
        None = 0,
        
        //! @brief An option that stores data in a sample-position–agnostic representation.
        CustomSamplePositions
    };
}

#endif /* __XGL_RENDERPASSSTOREACTION_H__ */
