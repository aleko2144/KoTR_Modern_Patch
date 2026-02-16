## Resource fixes:
* Disabled vehicle LODs
* Corrected hood positions of Fiat, Avensis, Marera, Megan and Oka cars when interior view enabled
* Company logos displayed on trucks have been replaced with high-resolution textures from the main menu
* A new tank semi-trailer bumper has been made; fixed the coordinates of the glow of its lights
* Fixed the movement parameters of the dashboard indicator arrows for bonus cars
* Fixed the "bounciness" of the Safari car
* The height of the lower collision boundary of the "Bus" has been increased so that it gets stuck less on uneven roads

## Game world fixes:
* Disabled gameworld LODs
* Fixed collision holes near the dam behind the SouthGate (ch.b3d)
* Fixed geometry and collision of the blockage in the [secret tunnel on the way to GreyStone](https://github.com/aleko2144/KoTR_Modern_Patch/issues/12#issue-3800217861) (da.b3d)
* Fixed terrain collision on the [road behind WestWood](https://github.com/aleko2144/KoTR_Modern_Patch/issues/16) (ar.b3d, as.b3d)
* Fixed multiple collision issues on the [Mercury - Foothill road](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (av.b3d, aw.b3d, ax.b3d)
* Fixed multiple collision issues on the [Mercury - St. Helena road](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (ak.b3d)
* Fixed collision issues in the [area of the service station near SandyRanch](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (af.b3d)

## Game code fixes:
* Fixed a bug that positioned interiors too low
* Fixed a bug that causes the fuel tank to become half empty when changing cars with an additional tank installed
* Fixed 1-second freezes when entering Greystone and improved loading times
* Corrected direction of dust particles flying from cars
* The collision handling parameters between dynamic objects have been reconfigured to reduce vehicles "sticking" during contacts
* The parameters of the external camera has been adjusted (it no longer flies away)
* A workaround has been made to correct the behavior of road trains (reduced semi-trailer skidding in arcade mode, improved maneuverability in simulation mode)
* A workaround has been made that slightly improves traffic behavior on narrow roads (north road to Mercury)

## Improvements for playing the game in 16x9 resolutions:
* The camera angles in the interiors are limited so that when playing in 16:9 resolutions, the voids behind the vehicle cabins are not visible
* Partially fixed bugs in rendering rear-view mirrors that occurred when playing in 16x9
