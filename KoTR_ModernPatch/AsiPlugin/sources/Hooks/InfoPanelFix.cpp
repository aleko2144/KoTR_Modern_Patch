#include "InfoPanelFix.h"
#include "../Utils/CPatch.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

int* callAddr_sprintf_gearbox;
int __cdecl sprintf_hook(char* buf, const char* format, int gear) {
	//gears: R=82, N=78, 1=49, 2=50, ...
	int gearIdx = gear - 48;

	if (gearIdx > 9 && gearIdx < 15) {
		// at this moment buf = "АКПП  %c" / "GEAR %c"
		sprintf(buf, format, 49); //sprintf "GEAR 1"

		char temp[20];
		memcpy(temp, buf, 20); //copy "АКПП  1" / "GEAR 1" to buffer

		// sprintf "АКПП  1" / "GEAR 1" + gear second digit
		return sprintf(buf, "%s%c", temp, (gearIdx - 10) + 48);
	} else {
		return sprintf(buf, format, gear);
	}
}


bool InfoPanelFix::getOffsets() try {
	using namespace hook::txn;
	//v 6.7 - 8.2
	try {
		callAddr_sprintf_gearbox = (int*)pattern("E8 ? ? ? ? 83 C4 04 8D 4C 24 ?  ?  50 51 E8 ? ? ? ?").get_first(15);
	//v 6.6
	} catch (const hook::txn_exception&) {
		callAddr_sprintf_gearbox = (int*)pattern("E8 ? ? ? ? 83 C4 04 57 50 8D 44 24 40 50 E8 ? ? ? ?").get_first(15);
	}

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}

bool InfoPanelFix::injectHooks(){
	if (!getOffsets())
		return false;

	CPatch::RedirectCall((int)callAddr_sprintf_gearbox, &sprintf_hook);

	return true;
}