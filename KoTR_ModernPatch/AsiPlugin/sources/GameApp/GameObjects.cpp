#include "GameObjects.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

//universal pattern for any game version since 4.0
int* GetCWinAppPtr() try {
	return *(int**)hook::txn::pattern("68 ? ? ? ? 56 E8 ? ? ? ? 66 8B 0D ? ? ? ?").get_first(1);
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