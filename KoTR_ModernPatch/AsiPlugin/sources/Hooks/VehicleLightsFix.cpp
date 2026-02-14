#include "VehicleLightsFix.h"
#include "..\Utils\CPatch.h"

void VehicleLightsFix::injectHooks(){
	//disable auto enable headlight glow on player car, as it was in 4.0 - 5.5
	CPatch::SetChar(0x546F8E, 184);

	//546F81
}