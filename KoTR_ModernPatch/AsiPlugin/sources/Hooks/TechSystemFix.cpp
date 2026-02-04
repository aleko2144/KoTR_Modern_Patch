#include "TechSystemFix.h"
#include "..\Utils\CPatch.h"

#include "..\GameApp\CarUpgrade.h"


void __cdecl OnVehicleSetUpgrades(int *vehicle){
	int* Car_V = (int *)(vehicle[5400]);
	float* fuelUpgrade = (float*)((char*)Car_V + 0x3EF0);

	//copy initial fuel level
	float prevFuelLevel = CarUpgrade::GetCurrentValue(fuelUpgrade);

	//call original function
	((void(*)(int*))0x51FF90)(vehicle);

	//restore previous fuel level
	CarUpgrade::SetCurrentValue(fuelUpgrade, prevFuelLevel);

	//float newFuelLevel = Upgrade_GetCurrentValue(fuelUpgrade);
	//cout << "vehicle=" << vehicle << endl;
	//cout << "prev=" << prevFuelLevel << " new=" << newFuelLevel << endl;
}

void TechSystemFix::injectHooks(){
	//called on vehicle buy/sell, load/unload and driver switch
	CPatch::RedirectCall(0x56F73F, &OnVehicleSetUpgrades);
}