# KoTR Modern Patch
King of the Road v8.2/v1.3 [patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) sources.</br>
Patch v1.00/v1.01 with mods sources are available [there](https://github.com/aleko2144/KoTR_Modern_Patch/tree/1.00).

## What is it?
A patch for the game that fixes some bugs and flaws in the original game, as well as introduces some improvements.</br>
The list of changes is [available here](CHANGELOG.md).

## Folder structure:
* KoTR_ModernPatch - the core of the patch contains all the fixes. Hooks description:
  * AICarFix - an attempt to correct the behavior of AI cars;
  * CabinCamFix - fixes interiors wrong height;
  * ExtCameraFix - corrects the external camera parameters;
  * CollisionsFix - corrects the collision handling parameters for dynamic objects;
  * ParticlesFix - corrects the direction of emitted dust particles from cars;
  * MirrorsFix - solves mirror render problems when playing at 16:9;
  * TechSystemFix - fixes some bugs in the vehicle upgrade system;
  * STrailersPhysFix - an attempt to fix semi-trailers physics behavior bugs;
  * QueueSortingFix - fixes 1-second freezes when entering Greystone and improves loading times.
 
## Compiling the project
* To build the current version of the project, VS2019 is required, for version 1.00/1.01 - VS2012.
* To load an asi file into the game, it is recommended to use [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) by [ThirteenAG](https://github.com/ThirteenAG)
* Modified game resources for the current version of the patch are published here: https://disk.yandex.ru/d/8vJAj0gO_5vukA

## Used sources
* File "CPatch.h" and some game structures are included from [D2DInputWrapper](https://github.com/Voron295/rignroll-dinput-wrapper) by [Voron295](https://github.com/Voron295)
* [ModUtils](https://github.com/CookiePLMonster/ModUtils) by [CookiePLMonster](https://github.com/CookiePLMonster)
* D2GI sources are [available here](https://github.com/REDPOWAR/D2GI)

## Acknowledgments
* [Voron295](https://github.com/Voron295)
* [CookiePLMonster](https://github.com/CookiePLMonster)
* [Duude92](https://github.com/Duude92)
* [AlexKimov](https://github.com/AlexKimov)
* [LabVaKars](https://github.com/LabVaKars)
