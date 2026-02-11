#include "dllmain.h"
#include <Windows.h>

#include <iostream>

#include "Hooks\MirrorsFix.h"
#include "Hooks\CollisionsFix.h"
#include "Hooks\ParticlesFix.h"
#include "Hooks\CabinCamFix.h"
#include "Hooks\TechSystemFix.h"
#include "Hooks\FinesCorrection.h"
#include "Hooks\AICarFix.h"
#include "Hooks\STrailersPhysFix.h"
#include "Hooks\QueueSortingFix.h"

#include "Hooks\HorizontalRainFix.h"
#include "Utils\CPatch.h"

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
				printInfo("[PATCH]: injected mirror system patches");
			}

			if (GetPrivateProfileIntA("patches", "ParticlesFix", 0, configName)){
				ParticlesFix::injectHooks();
				printInfo("[PATCH]: injected vehicle particle patches");
			}

			if (GetPrivateProfileIntA("patches", "TechSystemFix", 0, configName)){
				TechSystemFix::injectHooks();
				printInfo("[PATCH]: injected vehicle upgrade system patches");
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
				printInfo("[PATCH]: injected AI patches");
			}

			//if (GetPrivateProfileIntA("patches", "FinesCorrection", 0, configName)){
			//	FinesCorrection::injectHooks();
			//	printInfo("[PATCH]: applied fines corrections");
			//}

			if (GetPrivateProfileIntA("patches", "STrailersPhysCorrection", 0, configName)){
				STrailersPhysFix::injectHooks();
				printInfo("[PATCH]: applied roadtrain physics behaviour patches");
			}

			//445AF4 infinity loop if trailer detached on mafia attack???//

			/////
			if (GetPrivateProfileIntA("patches", "HorizontalRainFix", 0, configName)){
				HorizontalRainFix::injectHooks();
				printInfo("[PATCH]: applied horizontal rain fix");
			}

			if (GetPrivateProfileIntA("patches", "QueueSortingFix", 0, configName)){
				if (QueueSortingFix::injectHooks()) {
					printInfo("[PATCH]: applied queue sorting fixes");
				}
			}

			if (GetPrivateProfileIntA("patches", "NoAffinityLimit", 0, configName)){
				CPatch::Nop(0x50C885, 15);
				printInfo("[PATCH]: affinity limit disabled");
			}
			/////

			break;
		}
		default:
			break;
	}

	return TRUE;
}