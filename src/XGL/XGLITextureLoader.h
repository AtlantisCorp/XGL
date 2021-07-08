#ifndef __XGL_ITEXTURELOADER_H__
#define __XGL_ITEXTURELOADER_H__

#include "XGLLoader.h"
#include "XGLITexture.h"
#include "XGLPixelFormat.h"
#include "XGLLoaderManager.h"

namespace XGL
{
    /**
     *  @brief Defines an interface for a texture loader.
     * 
     */
    struct ITextureLoader : public ILoader 
    {
        //! @brief Creates a new texture from a filename.
        //! @param name The texture name.
        //! @param filename The texture file where to look for the data.
        //! @param internalFormat The desired internal format.
        //! @param renderer The IRenderer to use to create the texture.
        virtual std::shared_ptr < ITexture > load(const std::string& name,  
                                                  const std::string& filename,
                                                  PixelFormat::_ internalFormat,
                                                  const std::shared_ptr < IRenderer >& renderer) = 0;
    };

    typedef ILoaderManager < ITextureLoader > TextureLoaderManager;
}

#endif // !__XGL_ITEXTURELOADER_H__