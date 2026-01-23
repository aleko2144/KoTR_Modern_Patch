#include "TechSystemFix.h"
#include "..\Utils\CPatch.h"

double TechSystemFix::Upgrade_GetCurrentValue(float *upg){
	typedef double (__thiscall * Upgrade_GetCurrentValue)(float *upg);
	return Upgrade_GetCurrentValue(0x4EB720)(upg);
}

void TechSystemFix::Upgrade_SetCurrentValue(float *upg, float value){
	typedef void (__thiscall * Upgrade_SetCurrentValue)(float *upg, float value);
	return Upgrade_SetCurrentValue(0x4EB730)(upg, value);
}

void __cdecl TechSystemFix::OnVehicleSetUpgrades(int *vehicle){
	int* Car_V = (int *)(vehicle[5400]);
	float* fuelUpgrade = (float*)((char*)Car_V + 0x3EF0);

	//copy initial fuel level
	float prevFuelLevel = Upgrade_GetCurrentValue(fuelUpgrade);

	//call original function
	((void(*)(int*))0x51FF90)(vehicle);

	//restore previous fuel level
	Upgrade_SetCurrentValue(fuelUpgrade, prevFuelLevel);

	//float newFuelLevel = Upgrade_GetCurrentValue(fuelUpgrade);
	//cout << "vehicle=" << vehicle << endl;
	//cout << "prev=" << prevFuelLevel << " new=" << newFuelLevel << endl;
}

void TechSystemFix::injectHooks(){
	//called on vehicle buy/sell, load/unload and driver switch
	CPatch::RedirectCall(0x56F73F, &TechSystemFix::OnVehicleSetUpgrades);
}