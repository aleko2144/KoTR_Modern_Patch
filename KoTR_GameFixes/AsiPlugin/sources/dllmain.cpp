#include "dllmain.h"
#include <Windows.h>
#include <iostream>

#include "include\MirrorsFix.h"
#include "include\CollisionsFix.h"
#include "include\ParticlesFix.h"
#include "include\CabinCamFix.h"
#include "include\TechSystemFix.h"

using namespace std;

bool printDebugInfo;
void printInfo(const char* text){
	cout << text << endl;
}
void displayConsole(){
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			LPCSTR configName = ".\\KoTR_ModernPatch.ini";

			printDebugInfo = GetPrivateProfileIntA("common", "DisplayConsole", 0, configName);
			if (printDebugInfo){
				displayConsole();
				printInfo("Modern Patch v1.03");
			}

			if (GetPrivateProfileIntA("patches", "MirrorsFix", 0, configName)){
				MirrorsFix::injectHooks();
				printInfo("Injected mirrors fix hooks.");
			}

			if (GetPrivateProfileIntA("patches", "ParticlesFix", 0, configName)){
				ParticlesFix::injectHooks();
				printInfo("Injected vehicle particles fix hooks.");
			}

			if (GetPrivateProfileIntA("patches", "TechSystemFix", 0, configName)){
				TechSystemFix::injectHooks();
				printInfo("Injected vehicle upgrade system hooks.");
			}

			if (GetPrivateProfileIntA("patches", "CollisionsFix", 0, configName)){
				CollisionsFix::injectHooks();
				printInfo("Collision tweaks applied.");
			}

			if (GetPrivateProfileIntA("patches", "CabinCamFix", 0, configName)){
				CabinCamFix::injectHooks();
				printInfo("Interior camera patch applied.");
			}

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