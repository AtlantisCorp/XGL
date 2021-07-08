#ifndef __XGL_ITEXTURE_H__
#define __XGL_ITEXTURE_H__

#include "XGLIncludes.h"
#include "XGLPixelFormat.h"
#include "XGLIRenderObject.h"

namespace XGL
{
    //! @brief Enumerates the different texture types.
    enum TextureType
    {
        Tex1d,
        Tex2d,
        Tex3d,
        Tex2dArr,
        Tex3dArr,
        Tex2dMS,
        Tex3dMS,
        Tex2dArrMS,
        Tex3dArrMS
    };

    /**
     *  @brief Defines an interface for a texture.
     * 
     */
    class ITexture : public IRenderObject
    {
    public:
        //! @brief Constructs a new texture.
        inline ITexture(IRenderer& rhs): IRenderObject(rhs) {}

        //! @brief Returns the texture type.
        virtual TextureType type() const = 0;

        //! @brief Returns the texture width.
        virtual size_t width() const = 0;

        //! @brief Returns the texture height.
        virtual size_t height() const = 0;

        //! @brief Returns the texture depth.
        virtual size_t depth() const = 0;

        //! @brief Returns the texture array size.
        virtual size_t layers() const = 0;

        //! @brief Returns the pixel format.
        virtual PixelFormat::_ format() const = 0;

        //! @brief Converts the data and copy it into a buffer.
        virtual std::vector < char > data(PixelFormat format) const = 0;

        //! @brief Sets the data into the texture.
        virtual void setData(PixelFormat format, const void* data) = 0;
    };
}

#endif // !__XGL_ITEXTURE_H__