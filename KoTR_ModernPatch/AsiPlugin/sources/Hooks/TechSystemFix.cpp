#include "TechSystemFix.h"
#include "../Utils/CPatch.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 


int* callAddr_SetUpgrades;

void __cdecl OnVehicleSetUpgrades(int *vehicle){
	return;

	//Do nothing!
	//It is unclear why the upgrade reinstallation function is called at all when loading / unloading
	//and changing cars, but it seems that without calling it everything works correctly.


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
	using namespace Memory::VP;
	using namespace hook::txn;

	callAddr_SetUpgrades = (int*)pattern("8B 0D ? ? ? ? 8B 91 ? ? ? ? 52 E8 ? ? ? ?").get_first(13);
	return callAddr_SetUpgrades != 0;
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