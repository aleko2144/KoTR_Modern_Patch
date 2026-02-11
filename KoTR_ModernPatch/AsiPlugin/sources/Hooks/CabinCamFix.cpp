#include "CabinCamFix.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h"

bool CabinCamFix::injectHooks() try {

	using namespace Memory::VP;
	using namespace hook::txn;

	//makes the extra cabin height lowering code unexecutable

	// The same code is present twice in 8.x, but once in older versions,
	// so we do a pattern match on two hits, and patch the second one out.
	auto cabin_cam_check = pattern("F6 C4 41 75 ? D9 44 24 ? D8 1D ? ? ? ? DF E0 F6 C4 01 74 ? D9 85").count(2).get(1);
	Patch<uint8_t>(cabin_cam_check.get<void>(3), 0xEB); // jmp

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}
