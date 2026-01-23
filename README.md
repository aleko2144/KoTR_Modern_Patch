# KoTR_Modern_Patch
King of the Road v8.2/v1.3 [patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) sources.

List of plugins:
* KoTR_GameFixes - the core of the patch contains all the fixes:
  * AICarFix - an attempt to correct the behavior of AI cars;
  * CabinCamFix - fixes interiors wrong height;
  * CollisionsFix - an attempt to fix dynamic objects “sticking” during contacts;
  * ParticlesFix - fixes direction of emitted dust particles from cars;
  * MirrorsFix - hides flickering mirrors when viewed from the interior (needed when playing at 16:9);
  * TechSystemFix - fixes some bugs in the vehicle upgrade system;

Sources:
* File "CPatch.h" and some game objects structures are included from [D2DInputWrapper](https://github.com/Voron295/rignroll-dinput-wrapper) by Voron295.
* D2GI sources are available here: https://github.com/REDPOWAR/D2GI
* ModuleLoader plugin sources are here: https://github.com/aleko2144/KoTR_ASI_Plugins/tree/main/KoTR_ModuleLoader
