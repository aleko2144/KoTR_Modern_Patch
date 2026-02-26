#include "TechSystemFix.h"
#include "../Utils/CPatch.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

int* callAddr_SetUpgrades;

void __cdecl OnVehicleSetUpgrades(int* vehicle) {
	//Do nothing!
	//It is unclear why the upgrade reinstallation function is called at all when loading / unloading
	//and changing cars, but it seems that without calling it everything works correctly.
	return;
}

//8.2 only
void __cdecl OnVehicleSetUpgrades_RestoreFuelLevel(int* vehicle) {
	//Old code that fixed upgraded fuel tank level reducement on vehicle switch
	/*
	int* Car_V = (int *)(vehicle[5400]);
	float* fuelUpgrade = (float*)((char*)Car_V + 0x3EF0);

	//copy initial fuel level
	float prevFuelLevel = CarUpgrade::GetCurrentValue(fuelUpgrade);

	//call original function
	((void(*)(int*))0x51FF90)(vehicle);

	//restore previous fuel level
	CarUpgrade::SetCurrentValue(fuelUpgrade, prevFuelLevel);
	*/
}

bool TechSystemFix::getOffsets() try {
	using namespace hook::txn;
	callAddr_SetUpgrades = (int*)pattern("?  ? ? ? ? 8B  ? ? ? ? ? ?  E8 ? ? ? ? 8B 84 24 ? ? ? ? 8B BC 24 ? ? ? ? 83 C4 04 2B C7 74").get_first(12);

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}

bool TechSystemFix::injectHooks(){
	if (!getOffsets())
		return false;

	//called on vehicle buy/sell, load/unload and driver switch
	CPatch::RedirectCall((int)callAddr_SetUpgrades, &OnVehicleSetUpgrades);

	return true;
}