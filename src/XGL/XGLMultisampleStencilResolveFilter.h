//
//  XGLMultisampleStencilResolveFilter.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_MULTISAMPLESTENCILRESOLVEFILTER_H__
#define __XGL_MULTISAMPLESTENCILRESOLVEFILTER_H__

namespace XGL
{
    /**
     *  @brief Constants used to control the multisample stencil resolve operation.
     *
     */
    enum class MultisampleStencilResolveFilter
    {
        //! @brief Chooses the first stencil sample in the pixel.
        Sample0 = 0,
        
        //! @brief Chooses the stencil sample corresponding to the depth sample
        //! selected by the depth resolve filter.
        DepthResolvedSample
    };
}

#endif /* __XGL_MULTISAMPLESTENCILRESOLVEFILTER_H__ */
