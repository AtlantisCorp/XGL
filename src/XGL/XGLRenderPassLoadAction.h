//
//  XGLRenderPassLoadAction.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_RENDERPASSLOADACTION_H__
#define __XGL_RENDERPASSLOADACTION_H__

namespace XGL
{
    /**
     *  @brief Types of actions performed for an attachment at the start of a
     *  rendering pass.
     *
     */
    enum class RenderPassLoadAction
    {
        //! @brief The GPU has permission to discard the existing contents of
        //! the attachment at the start of the render pass, replacing them with
        //! arbitrary data.
        DontCare = 0,
        
        //! @brief The GPU preserves the existing contents of the attachment at
        //! the start of the render pass.
        Load,
        
        //! @brief The GPU writes a value to every pixel in the attachment at the
        //! start of the render pass.
        Clear
    };
}

#endif /* __XGL_RENDERPASSLOADACTION_H__ */
