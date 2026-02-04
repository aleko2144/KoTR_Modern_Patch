#include "CarUpgrade.h"

double CarUpgrade::GetCurrentValue(void *upgrade){
	typedef double (__thiscall * CarUpgrade_GetCurrentValue)(void *upgrade);
	return CarUpgrade_GetCurrentValue(0x4EB720)(upgrade);
}

void CarUpgrade::SetCurrentValue(void *upgrade, float value){
	typedef void (__thiscall * CarUpgrade_SetCurrentValue)(void *upgrade, float value);
	return CarUpgrade_SetCurrentValue(0x4EB730)(upgrade, value);
}