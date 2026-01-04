#include <windows.h>
#include <iostream>
#include "dllmain.h"
#include "CPatch.h"

using namespace std;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\KoTR_CollisionMod.ini"))
				return TRUE;

			//replace default collision_coeff in truck.ini read function
			CPatch::SetFloat(0x4DFAE2, 0.75);

			//replace pointer of dbl 0.2 to 3.141 inside slide collision process function
			CPatch::SetInt(0x57FF08, 6600744);

			cout << "CollisionPatch v0.51 (04.01.2026) started." << endl;

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
