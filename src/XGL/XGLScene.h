//
//  XGLScene.h
//  XGL
//
//  Created by jacques tronconi on 11/07/2021.
//

#ifndef __XGL_SCENE_H__
#define __XGL_SCENE_H__

#include "XGLSceneNode.h"
#include "XGLMeshSceneNode.h"
#include "XGLMaterialSceneNode.h"
#include "XGLIRenderer.h"
#include "XGLFrustum.h"
#include "XGLEntitySceneNode.h"

namespace XGL
{
    class Main;
    
    /**
     *  @brief Defines a Scene structure.
     *
     *  The Scene is responsible for the creation of every SceneNode. Each
     *  SceneNode has the responsibility for rendering everything on the
     *  Scene.
     *
     *  You can derive the Scene class and override any create*Node() functions
     *  to return derived class of the different SceneNode derived. The default
     *  implementation is a simple one but you can create binary trees, octrees,
     *  etc.
     *
     */
    class Scene : public Class < Scene >, public SceneNode
    {
        //! @brief The Main instance.
        Main& mMain;
        
        //! @brief Mutex.
        mutable std::mutex mutex;
        
    public:
        //! @brief Constructs a new Scene.
        //! @param mMain The Main instance.
        //! @param boundingLength The main bounding length to set for the root
        //! node.
        Scene(Main& mMain, const glm::vec3& boundingLength);
        
        //! @brief Creates a new SceneNode.
        virtual PSceneNode createNode(const glm::vec3& position,
                                      const glm::vec3& boundingLength);
        
        //! @brief Creates a new Mesh SceneNode.
        virtual PMeshSceneNode createMeshNode(const PMesh& mesh,
                                              const glm::vec3& position,
                                              const glm::vec3& defaultBoundingLength = glm::vec3());
        
        //! @brief Creates a new Mesh SceneNode.
        virtual PMeshSceneNode createMeshNode(const std::string& meshName,
                                              const std::string& meshPath,
                                              const std::string& loaderName,
                                              const PIRenderer& renderer,
                                              const glm::vec3& position = {},
                                              const glm::vec3& defaultBoundingLength = {});
        
        //! @brief Creates a new Material SceneNode.
        virtual PMaterialSceneNode createMaterialNode(const PMaterial& material);
        
        //! @brief Creates a new Entity SceneNode.
        virtual PEntitySceneNode createEntityNode(const PMeshSceneNode& mesh,
                                                  const std::list < PMaterialSceneNode >& materials = {},
                                                  const glm::vec3& position = glm::vec3());
        
        //! @brief Renders the Scene using the specified Frustum.
        virtual void render(const PIRenderer& renderer, const Frustum& frustum) const;
    };
}

#endif /* __XGL_SCENE_H__ */
