#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <fstream>

#include "dllmain.h"

#include "CPatch.h"

using namespace std;

float GetPrivateProfileFloat(string selection, string varname, string default_val, string filename){
	float to_return;
	char* returnedString = new char[256];
	GetPrivateProfileStringA(selection.c_str(), varname.c_str(), default_val.c_str(), returnedString, 256, filename.c_str());
	to_return = atof(returnedString);
	return to_return;
}


float friction_coeff = 1.4;
float collision_coeff = 0.5;

float* friction_coeff_ptr = (float*)0x696BFC;
float* collision_coeff_ptr = (float*)0x696C00; 

void CALLBACK OnTimer(HWND hwnd, UINT msg, UINT_PTR idTimer, DWORD dwTime)
{
	if (*friction_coeff_ptr != friction_coeff) {
		*friction_coeff_ptr = friction_coeff;
	}

	if (*collision_coeff_ptr != collision_coeff) {
		*collision_coeff_ptr = collision_coeff;
	}
}

int *__cdecl sub_52EF20(int *a1, int a2, int a3, int a4, int a5, int a6, int a7){
	typedef int *(*sub_52EF20)(int *a1, int a2, int a3, int a4, int a5, int a6, int a7);
	return sub_52EF20(0x52EF20)(a1, a2, a3, a4, a5, a6, a7);
}

int *__cdecl sub_52EF20_hook(int *a1, int EDX, int a2, int a3, int a4, int a5, int a6, int a7){
	return 0;
}

signed int __cdecl sub_5C88F0(DWORD *a1, int a2){
	typedef signed int(*sub_5C88F0)(DWORD *a1, int a2);
	return sub_5C88F0(0x5C88F0)(a1, a2);
}

signed int __cdecl sub_5C88F0_hook(DWORD *a1, int *EDX, int a2){
	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\KoTR_CollisionMod.ini"))
				return TRUE;

			SetTimer(0, 0, 50, OnTimer);

			friction_coeff = GetPrivateProfileFloat("CAR", "friction_coeff", "1.4", ".\\KoTR_CollisionMod.ini");
			collision_coeff = GetPrivateProfileFloat("CAR", "collision_coeff", "0.5", ".\\KoTR_CollisionMod.ini");

			CPatch::RedirectJump(0x5C88F0, sub_5C88F0_hook);

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

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
