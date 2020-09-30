### If you've found this repo in search of something similar, be warned this isn't allowed on the marketplace yet. I'm now talking with Epic about the viability of this as a solution. So do not try to use this yourself yet.

This is a simple example of how it could be possible to do optional dependencies in plugins on the UE4 marketplace.
While this has some boilerplate for it to work, it's necessary to handle all the plugin update orders correctly.
1. Updating any dependent without updating the base plugin. This is the simplest case and is really already supported just as a product of normal libraries.
2. Updating the base plugin and all dependents, this is the second simplest as all are kept in lock-step with eachother and on the same current API
3. Updating the dependent to a newer version of the base plugin but the base plugin isn't updated on the marketplace yet.  This is handled by the API versioning explained below.
3. Updating the base plugin without all dependents updating. This is the hardest one since this requires an API to not change after it's "published" so the API interface is versioned as explained below.


There are 3 plugins in this project.
OptionalPlugin is the base plugin that is optionally loaded into the two other plugins
DependentPluginOne is the first plugin that will optionally connect to OptionalPlugin if it is able to load it, and this dependent is on API version 2
DependentPluginTwo is the second plugin that will optional connect to OptionalPlugin if it is able to load it, and this dependent is on API version 1



The fundamental way this works is by sharing a copy of the interface header, and a simple loader logic to get the interface. The interface that is copied into the dependent carries a specific version of the API that the dependent is compiled against. Then at runtime it can attempt to load the plugin module by name, and if it succeeds then it can query for the API version its expecting. If either it cannot load the module at all or cannot get the API version it's expecting it will gracefully fail to get the API and the dependent can handle that case however it needs.

This allows two dependents to be on different versions of the API at the same time as long as the loaded plugin supports both.

The limitations on the API interfaces are as follows.
1. The API cannot expose UObjects as the reflection system is not designed to handle the case of a header in multiple libraries creating the same class.
2. The interface must be entirely pure-virtual, and not DLLIMPORTED/DLLEXPORTED

The requirements on updating the base plugin are as follows.
1. Any changes to an API after it's been published to the marketplace requires a new API interface and accompanying implementation. These can simply relay the calls to a shared library such that they're not really much implemented code individually.
2. Any API version released to an engine version must live on through all versions of the plugin for that engine version to not break other plugins being kept in a non-updated state. Only in the next engine version can old API versions be removed as here it's safe to assume dependent plugins will have to be at minimum recompiled but also likely updated for engine versions anyways.




The example in this repo.
Each of the dependents have different versions of the interface header
https://github.com/Koderz/OptionalDependencyPluginUE/blob/master/Plugins/DependentPluginOne/Source/DependentPluginOne/Public/OptionalPluginInterface.h
https://github.com/Koderz/OptionalDependencyPluginUE/blob/master/Plugins/DependentPluginTwo/Source/DependentPluginTwo/Public/OptionalPluginInterface.h

The base plugin implements both interfaces, and can return either of them on request.
https://github.com/Koderz/OptionalDependencyPluginUE/blob/master/Plugins/OptionalPlugin/Source/OptionalPlugin/Private/OptionalPlugin.cpp

Old API versions are moved out of the public header of the base plugin such that the base plugins main header is the current API version for simplicity of copying it to a dependent plugin.




This whole process relies on using the same compiler/options between engine and plugins and different compiles/updates of the various plugins which I believe is safe to assume in the case of the marketplace.
In the case of a user downloading each of these plugins into their own project and compiling them directly in the project, the compiler and options will for sure be the same and this should again be entirely safe.