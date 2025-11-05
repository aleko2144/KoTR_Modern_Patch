#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_TabloMod.ini"))
				return TRUE;

			//timer
			CPatch::SetChar(0x569B24, 240);
			//handbrake timer - xor dword_696C68 instead HandBrakeTicking (0x6F3460)
			CPatch::SetInt(0x569B7A, 6909032);
			//set HandBrakeTicking value
			CPatch::SetInt(0x6F3460, 1);

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
