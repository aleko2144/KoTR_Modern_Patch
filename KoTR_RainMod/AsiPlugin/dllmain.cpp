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
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_RainMod.ini"))
				return TRUE;

			//address  size  orig   new
			//0057688F	0x2	 3B CB 	39 C9 
			CPatch::SetChar(0x57688F, 57);
			CPatch::SetChar(0x576890, 201);

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
