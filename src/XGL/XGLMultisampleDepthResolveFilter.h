//
//  XGLMultisampleDepthResolveFilter.h
//  XGL
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_MULTISAMPLEDEPTHRESOLVEFILTER_H__
#define __XGL_MULTISAMPLEDEPTHRESOLVEFILTER_H__

namespace XGL
{
    /**
     *  @brief Filtering options for controlling an MSAA depth resolve operation.
     *
     */
    enum class MultisampleDepthResolveFilter
    {
        //! @brief No filter is applied.
        Sample0 = 0,
        
        //! @brief The GPU compares all depth samples in the pixel and selects the
        //! sample with the smallest value.
        Min,
        
        //! @brief The GPU compares all depth samples in the pixel and selects the
        //! sample with the largest value.
        Max
    };
}

#endif /* __XGL_MULTISAMPLEDEPTHRESOLVEFILTER_H__ */
