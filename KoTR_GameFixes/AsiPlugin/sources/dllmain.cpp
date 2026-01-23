#include "dllmain.h"
#include <Windows.h>

#include <iostream>

#include "include\Hooks\MirrorsFix.h"
#include "include\Hooks\CollisionsFix.h"
#include "include\Hooks\ParticlesFix.h"
#include "include\Hooks\CabinCamFix.h"
#include "include\Hooks\TechSystemFix.h"
#include "include\Hooks\FinesCorrection.h"
#include "include\Hooks\AICarFix.h"

#include "include\Hooks\HorizontalRainFix.h"
#include "include\Utils\CPatch.h"

using namespace std;

bool printDebugInfo;
void printInfo(const char* text){
	if (printDebugInfo)
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
				printInfo("[HOOK]: injected mirror system patches");
			}

			if (GetPrivateProfileIntA("patches", "ParticlesFix", 0, configName)){
				ParticlesFix::injectHooks();
				printInfo("[HOOK]: injected vehicle particle patches");
			}

			if (GetPrivateProfileIntA("patches", "TechSystemFix", 0, configName)){
				TechSystemFix::injectHooks();
				printInfo("[HOOK]: injected vehicle upgrade system patches");
			}

			if (GetPrivateProfileIntA("patches", "CollisionsFix", 0, configName)){
				CollisionsFix::injectHooks();
				printInfo("[PATCH]: applied collision corrections");
			}

			if (GetPrivateProfileIntA("patches", "CabinCamFix", 0, configName)){
				CabinCamFix::injectHooks();
				printInfo("[PATCH]: applied interior camera tweaks");
			}

			if (GetPrivateProfileIntA("AI_CAR", "HookEnabled", 0, configName)){
				AICarFix::injectHooks();
				printInfo("[HOOK]: injected AI patches");
			}

			if (GetPrivateProfileIntA("patches", "FinesCorrection", 0, configName)){
				FinesCorrection::injectHooks();
				printInfo("[PATCH]: applied fines corrections");
			}

			//445AF4 infinity loop if trailer detached on mafia attack???

			/////
			if (GetPrivateProfileIntA("patches", "HorizontalRainFix", 0, configName)){
				HorizontalRainFix::injectHooks();
				printInfo("[HOOK]: applied horizontal rain fix");
			}

			if (GetPrivateProfileIntA("patches", "NoAffinityLimit", 0, configName)){
				CPatch::Nop(0x50C885, 15);
				printInfo("[PATCH]: affinity limit disabled");
			}
			/////

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