#include "dllmain.h"
#include <Windows.h>

#include <iostream>

#include "Utils\ExeUtils.h"

//patches
#include "Hooks\MirrorsFix.h"
#include "Hooks\CollisionsFix.h"
#include "Hooks\DustParticlesFix.h"
#include "Hooks\CabinCamFix.h"
#include "Hooks\TechSystemFix.h"
#include "Hooks\FinesCorrection.h"
#include "Hooks\AICarFix.h"
#include "Hooks\STrailersPhysFix.h"
#include "Hooks\QueueSortingFix.h"
#include "Hooks\ExtCameraFix.h"
//

//#include "Hooks\HorizontalRainFix.h"
//#include "Utils\CPatch.h"

//mods
#include "Mods\HT2EffectsMod.h"
//

using namespace std;

bool printDebugInfo;
void printInfo(const char* text){
	if (printDebugInfo)
		cout << text << endl;
}
void printGameVersion(int version) {
	if (!printDebugInfo)
		return;

	cout << "Detected game version: ";

	if (version){
		//просто чтобы текст был красивый / just to make the text look nice :)
		cout << (version / 10) % 10 << "." << version % 10 << endl;
	} else {
		cout << "unknown (failed to detect)" << endl;
	}
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
			int gameVersion = GetGameVersion();

			printDebugInfo = GetPrivateProfileIntA("common", "DisplayConsole", 0, configName);
			if (printDebugInfo)
				displayConsole();

			printInfo("Modern Patch v1.03");
			printGameVersion(gameVersion);

			if (GetPrivateProfileIntA("patches", "QueueSortingFix", 0, configName)) {
				if (QueueSortingFix::injectHooks()) {
					printInfo("[PATCH]: applied queue sorting fixes");
				}
			}

			//needs to be fixed only in 8.x
			if (GetPrivateProfileIntA("patches", "CabinCamFix", 0, configName) && gameVersion >= 80){
				if (CabinCamFix::injectHooks()) {
					printInfo("[PATCH]: fixed cabins height");
				}
			}

			if (GetPrivateProfileIntA("patches", "MirrorsFix", 0, configName)){
				if (MirrorsFix::injectHooks(gameVersion)) {
					printInfo("[PATCH]: injected mirror system patches");
				}
			}

			//old game versions doesn't need collision coeffs correction
			if (GetPrivateProfileIntA("patches", "CollisionsFix", 0, configName) && gameVersion > 71) {
				if (CollisionsFix::injectHooks()) {
					printInfo("[PATCH]: applied collision corrections");
				}
			}

			if (GetPrivateProfileIntA("EXT_CAMERA", "HookEnabled", 0, configName)) {
				if (ExtCameraFix::injectHooks()) {
					printInfo("[PATCH]: applied external camera tweaks");
				}
			}

			if (GetPrivateProfileIntA("patches", "TechSystemFix", 0, configName) && gameVersion >= 80) {
				if (TechSystemFix::injectHooks())
					printInfo("[PATCH]: injected vehicle upgrade system patches");
			}

			if (GetPrivateProfileIntA("patches", "DustParticlesFix", 0, configName) && gameVersion >= 70) {
				if (DustParticlesFix::injectHooks(gameVersion))
					printInfo("[PATCH]: injected dust particle patches");
			}

			//patches for 8.2 only
			if (gameVersion == 82) {

				if (GetPrivateProfileIntA("AI_CAR", "HookEnabled", 0, configName)) {
					AICarFix::injectHooks();
					printInfo("[PATCH]: injected AI patches");
				}

				if (GetPrivateProfileIntA("STRAILER_PHY", "HookEnabled", 0, configName)) {
					STrailersPhysFix::injectHooks();
					printInfo("[PATCH]: applied roadtrain physics behaviour patches");
				}
			}

			//445AF4 infinity loop if trailer detached on mafia attack???//

			/////

			//if (GetPrivateProfileIntA("patches", "FinesCorrection", 0, configName)){
			//	FinesCorrection::injectHooks();
			//	printInfo("[PATCH]: applied fines corrections");
			//}

			//rain fix and affinity limit disable now exists in the D2GI
			//
			//if (GetPrivateProfileIntA("patches", "HorizontalRainFix", 0, configName)){
			//	HorizontalRainFix::injectHooks();
			//	printInfo("[PATCH]: applied horizontal rain fix");
			//}

			//if (GetPrivateProfileIntA("patches", "NoAffinityLimit", 0, configName)){
			//	CPatch::Nop(0x50C885, 15);
			//	printInfo("[PATCH]: affinity limit disabled");
			//}
			/////

			//if (GetPrivateProfileIntA("mods", "HT2Effects", 0, configName)) {
			//	HT2EffectsMod::injectHooks();
			//	printInfo("[MOD]: loaded HTruck 2 effects");
			//}

			break;
		}
		default:
			break;
	}

	return TRUE;
}