#include "XGLPluginManager.h"
#include "XGLMain.h"

namespace XGL
{
    PluginManager::PluginManager(Main& main): mMain(main)
    {

    }

    IPlugin* PluginManager::load(const std::string& filepath)
    {
        std::lock_guard l(mutex);

        for (auto& entree : mPlugins)
        {
            if (entree.dynlib->filepath() == filepath)
                return entree.plugin;
        }

        PluginManagerEntree entree;
        entree.dynlib = Class < Dynlib >::New(filepath);
        
        typedef IPlugin* (*PluginMainFn) (void);
        PluginMainFn PluginMain = (PluginMainFn) entree.dynlib->symbol("PluginMain");
        XGLThrowIf(!PluginMain, PluginMainNotFound(filepath));

        entree.plugin = PluginMain();
        XGLThrowIf(!entree.plugin, PluginMainInvalid(filepath));

        entree.plugin->inscribe(mMain);

        mPlugins.push_back(entree);
        return entree.plugin;
    }

    void PluginManager::unload(IPlugin* plugin)
    {
        XGLThrowIf(!plugin, std::runtime_error("plugin is null"));
        plugin->unscribe(mMain);

        std::lock_guard l(mutex);

        auto iter = std::find_if(mPlugins.begin(), mPlugins.end(), [plugin](auto& entree){ 
            return entree.plugin == plugin;
        });

        mPlugins.erase(iter);
    }

    void PluginManager::clear()
    {
        std::lock_guard l(mutex);

        for (auto& entree : mPlugins)
            entree.plugin->unscribe(mMain);

        mPlugins.clear();
    }
}