#include <iostream>
#include "CPatch.h"

#include "dllmain.h"

using namespace std;

double Upgrade_GetCurrentValue(float *upg){
	typedef double (__thiscall * Upgrade_GetCurrentValue)(float *upg);
	return Upgrade_GetCurrentValue(0x4EB720)(upg);
}

void Upgrade_SetCurrentValue(float *upg, float value){
	typedef void (__thiscall * Upgrade_SetCurrentValue)(float *upg, float value);
	return Upgrade_SetCurrentValue(0x4EB730)(upg, value);
}

void __cdecl Vehicle__SetUpgrades(int *vehicle){
	int* Car_V = (int *)(vehicle[5400]);
	float* fuelUpgrade = (float*)((char*)Car_V + 0x3EF0);

	//copy initial fuel level
	float prevFuelLevel = Upgrade_GetCurrentValue(fuelUpgrade);

	//call original function
	((void(*)(int*))0x51FF90)(vehicle);

	//restore previous fuel level
	Upgrade_SetCurrentValue(fuelUpgrade, prevFuelLevel);

	float newFuelLevel = Upgrade_GetCurrentValue(fuelUpgrade);

	//cout << "vehicle=" << vehicle << endl;
	//cout << "prev=" << prevFuelLevel << " new=" << newFuelLevel << endl;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_TechSystemFix.ini"))
				return TRUE;

			//called on vehicle buy/sell, load/unload and driver switch
			CPatch::RedirectCall(0x56F73F, &Vehicle__SetUpgrades);

			cout << "TechSystemFix v0.01 (17.01.2026) started." << endl;

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	return TRUE;
}