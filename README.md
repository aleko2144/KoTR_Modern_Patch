# KoTR Modern Patch
King of the Road [Modern Patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) sources.</br>
Patch v1.00/v1.01 with mods sources are available [there](https://github.com/aleko2144/KoTR_Modern_Patch/tree/1.00).

[Описание на русском языке доступно здесь](README-RU.md)

## What is it?
A patch for the game that fixes some bugs and flaws in the original game, as well as introduces some improvements.</br>
The list of changes is [available here](CHANGELOG.md).

## Compatibility with game versions
|Patch|Description|Supported game versions|
|-----|-----------|-----------------------|
|QueueSortingFix|Fixes 1-second freezes when entering Greystone and improves loading times|6.6 - 8.2|
|ExtCameraFix|Corrects external camera movement behind the player’s vehicle| |
|CollisionsFix|Corrects the collision handling parameters for dynamic objects| |
|InfoPanelFix|Corrects the display of gears > 9 in the top interface bar| |
|TechSystemFix*|Fixes bugs in the upgrade system, such as fuel disappearing when vehicles switches with an additional tank is installed, visual disappearance of installed upgrades, etc.| |
|DustParticlesFix|Corrects the direction of emitted dust particles from cars|6.9 - 8.2|
|STrailersPhysFix|Corrects semi-trailer physics behavior|7.0 - 8.2|
|MirrorsFix**|Solves mirror render problems when playing at 16:9|7.2 - 8.2|
|AICarFix|Corrects traffic behavior on narrow two-lane roads|7.4 - 8.2|
|CabinCamFix|Fixes a bug that causes cabins to be positioned too low|8.0 - 8.2|

*_Experimental patch - the impact on the game is not fully understood_</br>
**_Works correctly only with [D2GI](https://github.com/REDPOWAR/D2GI/) with hooks enabled_</br>


__Versions 8.x are compatible with European 1.x. So patches for 8.2 work on 1.3.__

## Compiling the project
* To build the current version of the project, VS2019 is required, for version 1.00/1.01 - VS2012.
* To load an asi file into the game, it is recommended to use [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) by [ThirteenAG](https://github.com/ThirteenAG)
* Modified game resources for the current version of the patch are published here __(only for 8.x/1.x)__: https://disk.yandex.ru/d/8vJAj0gO_5vukA

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
