#include "GameObjects.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

//universal patterns for any game version since 4.0
int* GetCWinAppPtr() try {
	return *(int**)hook::txn::pattern("68 ? ? ? ? 56 E8 ? ? ? ? 66 8B 0D ? ? ? ?").get_first(1);
}
catch (const hook::txn_exception&)
{
	return nullptr;
}

int* GetPlayerVehiclePtr() try {
	return *(int**)hook::txn::pattern("8B D9 55 56 8B 83 ? ? ? ? 33 F6 3B C6 57 0F 85 ? ? ? ? A1 ? ? ? ?").get_first(22);
}
catch (const hook::txn_exception&)
{
	return nullptr;
}

int* GetViewerPtr(int gameVersion) try {
	//pattern for 6.6 - 8.2
	if (gameVersion > 62)
		return *(int**)hook::txn::pattern("A3 ? ? ? ? 8B B0 ? ? ? ?").get_first(1);

	return nullptr;
}
catch (const hook::txn_exception&)
{
	return nullptr;
}

int GetCarVOffset(int gameVersion) {
	//7.3 - 8.2
	int result = 0x5460;

	//7.0 - 7.2
	if (gameVersion < 73 && gameVersion >= 70) {
		result = 0x5010;
	} else if (gameVersion == 69) {
		result = 0x5008;
	} else if (gameVersion == 66) {
		result = 0x4EB8;
	}

	return result;
}