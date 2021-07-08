#include "XGLDynlib.h"

namespace XGL
{
    Dynlib::Dynlib(const std::string& dynlib)
    {
        std::filesystem::path path(dynlib);
        path.replace_extension(XGLDynlibExt);

        mHandle = XGLDynlibOpen(path.c_str());
        mFilePath = path.string();
        
        XGLThrowIf(!mHandle, DynlibLoadError(path));
    }

    Dynlib::~Dynlib() 
    {
        XGLDynlibClose(mHandle);
    }

    void* Dynlib::symbol(const std::string& name) const 
    {
        return XGLDynlibSym(mHandle, name.c_str());
    }

    const std::string& Dynlib::filepath() const
    {
        return mFilePath;
    }
}