#ifndef __XGL_ISHADER_H__
#define __XGL_ISHADER_H__

#include "XGLIncludes.h"
#include "XGLIRenderObject.h"

namespace XGL
{
    //! @brief Enumerates the different shaders type.
    enum class ShaderType
    {
        Vertex, TessControl, TessEval, Geometry, Fragment, Compute 
    };

    /**
     *  @brief Defines a shader interface.
     * 
     */
    struct IShader : public IRenderObject
    {
        //! @brief Constructs a new instance.
        inline IShader(IRenderer& rhs): IRenderObject(rhs) {}

        //! @brief Returns the shader filename, if from a filename.
        virtual std::string filename() const = 0;

        //! @brief Returns the entry function name.
        virtual std::string entry() const = 0;

        //! @brief Returns the shader type.
        virtual ShaderType type() const = 0;
    };
}

#endif // !__XGL_ISHADER_H__