#ifndef __XGL_SHADERLIBRARY_H__
#define __XGL_SHADERLIBRARY_H__

#include "XGLIShader.h"
#include "XGLIRenderObject.h"

namespace XGL
{
    /**
     *  @brief Defines a library of multiple shader functions.
     * 
     *  Shader Library is an attempt to generalize the Metal MTLLibrary class,
     *  and let implementors define a library type for other shader language
     *  like SPIR-V.
     * 
     *  You can load a library with IRenderer::createShaderLibrary() or you
     *  can try to access the 'default' library with IRenderer::defaultShaderLibrary().
     * 
     *  @see MTLLibrary documentations.
     * 
     */
    struct IShaderLibrary : public IRenderObject
    {
        //! @brief Constructs a new instance.
        inline IShaderLibrary(IRenderer& rhs): IRenderObject(rhs) {}

        //! @brief Returns a IShader with name and type.
        //! @param name The function name in the library.
        //! @param type The function type in the library.
        virtual std::shared_ptr < IShader > find(const std::string& name, ShaderType type) = 0;
    };
}

#endif // !__XGL_SHADERLIBRARY_H__