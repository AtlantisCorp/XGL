#ifndef __XGL_MAINMANAGER_H__
#define __XGL_MAINMANAGER_H__

#include "XGLManager.h"

namespace XGL
{
    class Main;

    /**
     *  @brief Defines a base class for a Manager owned by the Main
     *  object.
     * 
     *  This is a base class for every Manager in the Main instance, like
     *  MeshManager, PluginManager, MaterialManager, etc.
     * 
     */
    template < class T >
    class MainManager : public Manager < T > 
    {
    protected:
        //! @brief The Main object reference.
        Main& mMain;

    public: 
        //! @brief Constructs a new instance.
        MainManager(Main& lMain): mMain(lMain) {}

        //! @brief Returns the main instance.
        Main& mainRef() { return mMain; }
    };
}

#endif // !__XGL_MAINMANAGER_H__