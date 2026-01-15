#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "CPatch.h"

#include "dllmain.h"

using namespace std;

void sub_595230(int *_mirrors){
	typedef void (__fastcall * sub_595230)(int *_mirrors);
	return sub_595230(0x595230)(_mirrors);
}

void __fastcall hook_650A28(int *_this, int* EDX){
	DWORD temp = *(DWORD*)0x67E178;

	//camera min angle when side mirrors always disable;
	float camRotMin = 0.2;
	//interior camera rotation
	float cameraRot = *(float*)0x696D30;

	if (abs(cameraRot) < camRotMin)
		*(DWORD*)0x67E178 = 0;

	//old variant - cameraRot value is integer != 0 if camera rotate key is pressed

	//DWORD* viewer = (DWORD*)*(DWORD*)0x6D2098;
	//int cameraRot = *(int *)((char*)viewer + 0x574);

	//disable side mirrors processing if camera not rotated
	//if (!cameraRot)
	//*(DWORD*)0x67E178 = 0;

	sub_595230(_this);

	*(DWORD*)0x67E178 = temp;

	return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_MirrorsFix.ini"))
				return TRUE;

			CPatch::SetPointer(0x650A28, &hook_650A28);

			cout << "MirrorsFix v0.011 (15.01.2026) started." << endl;

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
