#include "XGLMain.h"

namespace XGL
{
    Main::Main():
    mPluginManager(*this),
    mMeshManager(*this)
    {

    }

    PluginManager& Main::plugins() 
    {
        return mPluginManager;
    }

    RendererManager& Main::renderers()
    {
        return mRendererManager;
    }
}