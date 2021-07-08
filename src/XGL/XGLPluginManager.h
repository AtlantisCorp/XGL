#ifndef __XGL_PLUGINMANAGER_H__
#define __XGL_PLUGINMANAGER_H__

#include "XGLIncludes.h"
#include "XGLIPlugin.h"
#include "XGLClass.h"
#include "XGLError.h"
#include "XGLDynlib.h"

namespace XGL 
{
    class Main;

    /// @brief Defines an entree in the plugin manager.
    struct PluginManagerEntree
    {
        /// @brief The dynlib for this entree.
        std::shared_ptr < Dynlib > dynlib;

        /// @brief The plugin pointer.
        IPlugin* plugin;
    };

    /// @brief Defines a manager for loaded plugins.
    class PluginManager : public Class < PluginManager >
    {
        /// @brief The Main instance.
        Main& mMain;

        /// @brief The list of plugins.
        std::list < PluginManagerEntree > mPlugins;

        /// @brief The mutex.
        mutable std::mutex mutex;

    public: 
        /// @brief Constructs a new manager.
        PluginManager(Main& main);

        /// @brief Loads a Plugin and calls inscribe.
        IPlugin* load(const std::string& filepath);

        /// @brief Unloads a Plugin and calls unscribe.
        void unload(IPlugin* plugin);

        /// @brief Unloads all plugins.
        void clear();
    };

    /// @brief Error fired if 'PluginMain' is not found in a Plugin.
    struct PluginMainNotFound : public Error 
    {
        /// @brief The file path.
        std::string filepath;

        /// @brief Constructs a new error.
        PluginMainNotFound(const std::string& filepath):
        Error("PluginMain function not found in file '" + filepath + "'."),
        filepath(filepath) {}
    };

    /// @brief Error fired if 'PluginMain' doesn't return a valid IPlugin pointer.
    struct PluginMainInvalid : public Error 
    {
        /// @brief The file path.
        std::string filepath;

        /// @brief Constructs a new error.
        PluginMainInvalid(const std::string& filepath):
        Error("PluginMain doesn't return a valid IPlugin pointer (file: '" + filepath + "')."),
        filepath(filepath) {}
    };
}

#endif // !__XGL_PLUGINMANAGER_H__