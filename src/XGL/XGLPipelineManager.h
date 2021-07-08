#ifndef __XGL_PIPELINEMANAGER_H__
#define __XGL_PIPELINEMANAGER_H__

#include "XGLPipeline.h"
#include "XGLMainManager.h"

namespace XGL
{
    /**
     *  @brief Defines a manager for Pipeline.
     * 
     */
    struct PipelineManager : public MainManager < Pipeline >
    {
        using MainManager::MainManager;
        
        //! @brief Returns the pipeline designated by an id, or null if not found.
        auto findById(size_t id) const { return this->find([id](auto& rhs){ return rhs->id() == id; }); }
    };
}

#endif // !__XGL_PIPELINEMANAGER_H__