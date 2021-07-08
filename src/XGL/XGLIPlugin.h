#ifndef __XGL_IPLUGIN_H__
#define __XGL_IPLUGIN_H__

#include "XGLIncludes.h"

namespace XGL
{
    class Main;
    
    /// @brief Defines an interface for an XGL Plugin.
    ///
    /// When creating a new XGL Plugin, creates a derived class from
    /// this interface. Implements every methods and then, define a
    /// start function like this:
    ///
    /// extern "C" MyPlugin* PluginMain(void) 
    /// {
    ///     static MyPlugin plugin; return &plugin;
    /// }
    ///
    /// The PluginManager will never free your plugin memory, so it has
    /// to be allocated by the plugin library.
    struct IPlugin
    {
        /// @brief Destructor.
        virtual ~IPlugin() = default;

        /// @brief Returns the plugin name.
        virtual const char* name() const = 0;

        /// @brief Inscribes the plugin into the Main instance.
        virtual void inscribe(Main& main) = 0;

        /// @brief Unscribes the plugin from the main instance.
        virtual void unscribe(Main& main) = 0;
    };
}

#endif // !__XGL_IPLUGIN_H__