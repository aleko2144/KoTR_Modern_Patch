#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "dllmain.h"

using namespace std;

int GetGameKeyState(int key) {
	typedef int (__thiscall * GetGameKeyState)(DWORD* _this, int key);
	return GetGameKeyState(0x530010)((DWORD*)0x6D1DD8, key);
}

int ModifierKey;
bool mod_enabled;

void LoadIni(){
	mod_enabled = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\KoTR_CameraMod.ini");
	ModifierKey = GetPrivateProfileIntA("KEYBINDINGS", "ModifierKey", 17, ".\\KoTR_CameraMod.ini");
}

float zoom;
float speed;
int cameraMode;

void ProcessCamera(){

	DWORD* vehicle = (DWORD*)*(DWORD*)0x6F6930;
	if (!vehicle)
		return;

	DWORD* vehicleCar_V = (DWORD *)(vehicle[5400]);

	float speed = *(float*)((char*)vehicleCar_V + 0x332C) * 3.6;

	cameraMode = *(DWORD *)(*(DWORD *)0x6D2098 + 1400);

	float mid_zoom = 13.35 - 0.15 * ((int)speed - 1);

	float max_zoom = mid_zoom - 5;
	float min_zoom = mid_zoom + 5;

	float cam_addval = 1.0;

	//if (!(GetTickCount() % 5)){ //сработает каждые 5 мс
	if (IsKeyPressed(ModifierKey)){
		cam_addval = 5.0;
	} else {
		cam_addval = 1.0;
	}

	if (GetGameKeyState(24)){ //home key
		zoom += 0.025 * cam_addval;
	}
	if (GetGameKeyState(25)){ //end key
		zoom -= 0.025 * cam_addval;
	}

	float camera_zoom = (min_zoom + zoom * (max_zoom - min_zoom));

	if (!cameraMode){
		zoom = 0.5;
	} else {
		*(double *)0x6F69F0 = camera_zoom;
	}

}

void CALLBACK OnTimer(HWND hwnd,   UINT msg, UINT_PTR idTimer, DWORD dwTime) {
	if (*(DWORD*)0x6D2098) {
		ProcessCamera();
	}
}
	
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			LoadIni();

			if (!mod_enabled)
				return TRUE;
			
			SetTimer(0, 0, 50, OnTimer);
			cout << "CameraMod v0.3 (04.11.2025) started." << endl;

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
