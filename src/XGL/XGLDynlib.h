#ifndef __XGL_DYNLIB_H__
#define __XGL_DYNLIB_H__

#include "XGLClass.h"
#include "XGLError.h"

#if defined(__WIN32)
#include <Windows.h>
#define XGLDynlibHandle HMODULE
#define XGLDynlibOpen(a) LoadLibrary(a)
#define XGLDynlibClose(a) FreeLibrary(a)
#define XGLDynlibSym(a, b) GetProcAddress(a, b)
#define XGLDynlibExt ".dll"

#elif defined(__APPLE__)
#include <dlfcn.h>
#define XGLDynlibHandle void*
#define XGLDynlibOpen(a) dlopen(a, RTLD_LAZY)
#define XGLDynlibClose(a) dlclose(a)
#define XGLDynlibSym(a, b) dlsym(a, b)
#define XGLDynlibExt ".dylib"

#else  
#include <dlfcn.h>
#define XGLDynlibHandle void*
#define XGLDynlibOpen(a) dlopen(a, RTLD_LAZY)
#define XGLDynlibClose(a) dlclose(a)
#define XGLDynlibSym(a, b) dlsym(a, b)
#define XGLDynlibExt ".so"

#endif

namespace XGL
{
    /// @brief Defines a loader for dynamic libraries.
    ///
    /// This class only provides cross compatibility between systems with
    /// dlfcn.h and Windows.
    class Dynlib : public Class < Dynlib >
    {
        /// @brief The dynlib handle.
        XGLDynlibHandle mHandle;

        /// @brief The file associated to this dynlib.
        std::string mFilePath;

    public:  

        /// @brief Constructs a new instance.
        /// @param filepath The path to a dynlib file.
        Dynlib(const std::string& filepath);

        /// @brief Destructs the dynlib and releases the handle.
        ~Dynlib();

        /// @brief Returns the symbol for given name.
        void* symbol(const std::string& name) const;

        /// @brief Returns the file path.
        const std::string& filepath() const;
    };

    /// @brief Error fired if the Dynlib cannot be loaded.
    struct DynlibLoadError : public Error 
    {
        /// @brief The filepath.
        std::string filepath;

        /// @brief Constructs a new instance.
        inline DynlibLoadError(const std::string& filepath):
        Error("Cannot load library '" + filepath + "'."),
        filepath(filepath) {}
    };
}

#endif // !__XGL_DYNLIB_H__