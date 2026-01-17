#include <windows.h>
#include <iostream>
#include "dllmain.h"
#include "CPatch.h"

using namespace std;

float GetPrivateProfileFloat(const char* selection, const char* varname, const char* default_val, const char* filename){
	char returnedString[256];
	GetPrivateProfileStringA(selection, varname, default_val, returnedString, 256, filename);
	return atof(returnedString);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\KoTR_CollisionMod.ini"))
				return TRUE;
			
			float friction_coeff  = GetPrivateProfileFloat("CAR", "friction_coeff", "1.4", ".\\KoTR_CollisionMod.ini");
			float collision_coeff = GetPrivateProfileFloat("CAR", "collision_coeff", "0.5", ".\\KoTR_CollisionMod.ini");

			//replace default collision_coeff in truck.ini read function
			CPatch::SetFloat(0x4DFAE2, collision_coeff);
			//replace default friction_coeff in truck.ini read function
			CPatch::SetFloat(0x4DFAD8, friction_coeff);

			cout << "CollisionPatch v0.5 (03.11.2025) started." << endl;

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
