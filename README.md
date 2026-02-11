# KoTR Modern Patch
King of the Road v8.2/v1.3 [patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) sources.</br>
Patch v1.00/v1.01 with mods sources are available [there](https://github.com/aleko2144/KoTR_Modern_Patch/tree/1.00).

List of plugins:
* KoTR_ModernPatch - the core of the patch contains all the fixes:
  * AICarFix - an attempt to correct the behavior of AI cars;
  * CabinCamFix - fixes interiors wrong height;
  * CollisionsFix - an attempt to fix dynamic objects “sticking” during contacts;
  * ParticlesFix - fixes direction of emitted dust particles from cars;
  * MirrorsFix - solves mirror render problems when playing at 16:9;
  * TechSystemFix - fixes some bugs in the vehicle upgrade system;
  * STrailersPhysFix - an attempt to fix semi-trailers physics behavior bugs;
  * QueueSortingFix - fixes 1-second freezes when entering Greystone and improves loading times.

Sources:
* File "CPatch.h" and some object structures are included from [D2DInputWrapper](https://github.com/Voron295/rignroll-dinput-wrapper) by [Voron295](https://github.com/Voron295)
* [ModUtils](https://github.com/CookiePLMonster/ModUtils) by [CookiePLMonster](https://github.com/CookiePLMonster)
* D2GI sources are [available here](https://github.com/REDPOWAR/D2GI)
* ModuleLoader plugin sources are [available here](https://github.com/aleko2144/KoTR_ASI_Plugins/tree/main/KoTR_ModuleLoader)
