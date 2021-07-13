//
//  XGLMaterialSceneNode.cpp
//  XGL
//
//  Created by jacques tronconi on 11/07/2021.
//

#include "XGLMaterialSceneNode.h"
#include "XGLError.h"

namespace XGL
{
    MaterialSceneNode::MaterialSceneNode(Scene& scene, const std::shared_ptr < Material >& material):
    SceneNode(scene),
    mMaterial(material)
    {
        
    }
    
    void MaterialSceneNode::handle(const std::shared_ptr < IRenderer >& renderer, const Frustum& frustum) const
    {
        XGLThrowIf(!renderer, std::runtime_error("Null renderer."));
        auto lmaterial = std::atomic_load(&mMaterial);
        
        if (lmaterial)
            lmaterial->bind(renderer);
        
        SceneNode::handle(renderer, frustum);
    }
}
