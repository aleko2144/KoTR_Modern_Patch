#include <iostream>
#include "CPatch.h"
#include "dllmain.h"

using namespace std;
	
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_CabinCamFix.ini"))
				return TRUE;

			CPatch::SetInt(0x531F9E, 6600784);

			cout << "CabinCamFix started." << endl;

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

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
