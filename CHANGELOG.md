## Game code fixes:
* Fixed a bug that positioned interiors too low
* _Experimental patch:_ fixed a bug in vehicle upgrade system that causes the fuel tank to become half empty when changing cars with an additional tank installed
* Fixed 1-second freezes when entering Greystone and improved loading times
* Corrected direction of dust particles flying from cars
* The collision handling parameters between dynamic objects have been reconfigured to reduce vehicles "sticking" during contacts
* The parameters of the external camera has been adjusted (it no longer flies away)
* Corrected behavior of road trains (reduced semi-trailer skidding in arcade mode, improved maneuverability in simulation mode)
* Improves traffic behavior on narrow roads (north road to Mercury)
* Partially fixed bugs in rendering rear-view mirrors that occurred when playing in 16x9

## Game resources fixes (only for 8.x/1.x):
### Vehicle files:
* Disabled vehicle LODs
* Corrected hood positions of Fiat, Avensis, Marera, Megan and Oka cars when interior view enabled
* Company logos displayed on trucks have been replaced with high-resolution textures from the main menu
* A new tank semi-trailer bumper has been made; fixed the coordinates of the glow of its lights
* Fixed the movement parameters of the dashboard indicator arrows for bonus cars
* Fixed the "bounciness" of the Safari car
* The height of the lower collision boundary of the "Bus" has been increased so that it gets stuck less on uneven roads
* The camera angles in the interiors are limited so that when playing in 16:9 resolutions, the voids behind the vehicle cabins are not visible

### Game world files:
* Disabled gameworld LODs
* Fixed collision holes near the dam behind the SouthGate (ch.b3d)
* Fixed geometry and collision of the blockage in the [secret tunnel on the way to GreyStone](https://github.com/aleko2144/KoTR_Modern_Patch/issues/12#issue-3800217861) (da.b3d)
* Fixed terrain collision on the [road behind WestWood](https://github.com/aleko2144/KoTR_Modern_Patch/issues/16) (ar.b3d, as.b3d)
* Fixed multiple collision issues on the [Mercury - Foothill road](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (av.b3d, aw.b3d, ax.b3d)
* Fixed multiple collision issues on the [Mercury - St. Helena road](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (ak.b3d)
* Fixed collision issues in the [area of the service station near SandyRanch](https://github.com/aleko2144/KoTR_Modern_Patch/issues/17#issuecomment-3907623594) (af.b3d)
