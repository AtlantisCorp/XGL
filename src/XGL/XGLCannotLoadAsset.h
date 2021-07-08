#ifndef __XGL_CANNOTLOADASSET_H__
#define __XGL_CANNOTLOADASSET_H__

#include "XGLError.h"

namespace XGL
{
    /**
     *  @brief Error thrown if an asset (a mesh, a texture, ...) canont be load.
     * 
     */
    struct CannotLoadAsset : public Error 
    {
        //! @brief The asset name.
        std::string name;
        //! @brief The asset file.
        std::string filename;

        //! @brief Constructs a new instance.
        CannotLoadAsset(const std::string& name, const std::string& filename): 
        Error("Cannot load Asset '" + name + "': " + filename),
        name(name),
        filename(filename) {}
    };
}

#endif // !__XGL_CANNOTLOADASSET_H__