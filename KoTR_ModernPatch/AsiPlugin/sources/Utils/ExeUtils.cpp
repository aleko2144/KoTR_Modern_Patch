#include "ExeUtils.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h"
#include "../Utils/CPatch.h"

//#include <Windows.h>
//#include <iostream>

int GetGameVersion() {
	try {

		using namespace Memory::VP;
		using namespace hook::txn;

		// v x.x (v 8.0, v 5.8, etc.)
		char* gameVersionStr = (char*)pattern("76 20 ? 2E ?").get_one().get_uintptr();

		float temp_flt;
		int scan = sscanf(gameVersionStr, "%*s %f", &temp_flt);

		int versionIdx = temp_flt * 10;

		//Check if version is 8.2
		if (CPatch::GetInt(0x6724FF) == 925904946)
			versionIdx = 82;

		//EU KotR releases (1.0 - 1.3)
		if (versionIdx <= 14 && versionIdx >= 10) {
			versionIdx = 80;
		}

		return versionIdx;

		//std::cout << gameVersionStr << std::endl;
		//std::cout << versionIdx << std::endl;

		//system("pause");
	}
	catch (const hook::txn_exception&)
	{
		return 0;
	}
}

char* UInt32toPattern(uint32_t value) {
	char result[24];
	sprintf(result, "%02X %02X %02X %02X", (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF));
	return result;
}