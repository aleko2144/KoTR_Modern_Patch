# KoTR_Modern_Patch
King of the Road v8.2/v1.4 [patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) sources.

List of plugins:
* KoTR_CameraMod - outdated plugin that partially corrects the position of the external camera (it no longer flies away);
* KoTR_CollisionMod - an attempt to fix dynamic objects “sticking” during contacts;
* KoTR_DustPatch - patch that fixes direction of emitted dust particles from cars;
* KoTR_InteriorMod - allows to use the mouse to control the steering and adds the ability to remap the built-in control keys
* KoTR_MirrorsFix - patch that hides flickering mirrors when viewed from the interior (needed when playing at 16:9);
* KoTR_PhysicsMod - an attempt to improve the movement of road trains;
* KoTR_RainMod - allows to enable rendering of falling raindrops when interior view enabled;
* KoTR_TabloMod - allows to enable real-time update of the top interface panel;
* KoTR_UpgradesMod - adds new gearboxes when an improved engine installed at a service station;
* KoTR_VehicleMod - adds working turn signals.

Extra:
* KoTR_CabinCamFix - NOT included in Modern Patch, but fixes interiors wrong height (in Modern Patch this not fixed by plugins, but just new cab positions are set inside vehicle.tech file)

Sources:
* File "CPatch.h" included from [D2DInputWrapper](https://github.com/Voron295/rignroll-dinput-wrapper) by Voron295.
* Files "detours.h", "detours.lib", "detver.h", "sigscan.h" included from [Detour](https://github.com/Zer0Mem0ry/Detour/tree/master/dll) by Zer0Mem0ry.
* D2GIv2 sources are here: https://github.com/aleko2144/D2GI_v2
* ModuleLoader plugin sources are here: https://github.com/aleko2144/KoTR_ASI_Plugins/tree/main/KoTR_ModuleLoader
