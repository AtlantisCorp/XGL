# XGL

Cross Platform Graphics Library

## INSTALL

You can use CMAKE to build/install the whole library, the Plugins
and your executable. Just type:

```sh
mkdir build && cd build && cmake .. && make && make install
```

## INSTALLING A PLUGIN

Once you found a Plugin, we advise you to clone its repository inside
the 'Plugins' directoy. Then, in the CMAKE file, adds the following 
lines to use the Plugin:

```cmake
XGLUsePlugin(YourPluginNameHere)
```

## CREATING A NEW PLUGIN

To create a new Plugin, uses the sh command line tool XGLTools.sh. You
can use it like this:

```sh
./Extras/XGLTools.sh --create-plugin --name "YourPluginName"
```

This will create a Plugin template inside the "Plugins/YourPluginName"
directory and initialize a new git repository there.
