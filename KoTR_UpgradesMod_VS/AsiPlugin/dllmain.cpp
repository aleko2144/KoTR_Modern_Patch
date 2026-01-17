#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "dllmain.h"

#include "detours.h"

#include "include/input/input.h"

using namespace std;
bool debug_mode;

void WriteDebugLog(const char *text){
	FILE *file = fopen(".\\UpgradesMod.log", "a");
	if (file != NULL){
		fputs(text, file);
		fputs("\n", file);
		fclose(file);
	}
}

float GetPrivateProfileFloat(const char* selection, const char* varname, const char* default_val, const char* filename){
	char returnedString[256];
	GetPrivateProfileStringA(selection, varname, default_val, returnedString, 256, filename);
	return atof(returnedString);
}

string GetPrivateProfileStr(string selection, string varname, string default_val, string filename){
	char returnedString[256];
	GetPrivateProfileStringA(selection.c_str(), varname.c_str(), default_val.c_str(), returnedString, 256, filename.c_str());
	string result = returnedString;
	return result;
}


int getUpgradeWheelsInfo(DWORD* vehicle){
	DWORD* vehicleCar_V = (DWORD *)(vehicle[5400]);
	return *(int*)((char*)vehicleCar_V + 0x3F24 + 0x28);
}

int getUpgradeEngineInfo(DWORD* vehicle){
	DWORD* vehicleCar_V = (DWORD *)(vehicle[5400]);
	return *(int*)((char*)vehicleCar_V + 0x3EBC + 0x28);
}

int getUpgradeSnorkelInfo(DWORD* vehicle){
	DWORD* playerID = *(DWORD**)((char *)vehicle + 0x10 + 0x508C);
	DWORD* ptr1 = *(DWORD**)((char *)playerID + 0x204);
	DWORD* ptr2 = *(DWORD**)((char *)ptr1 + 0x10);
	DWORD* ptr3 = (DWORD*)((char*)ptr2 + 0x120);
	return *ptr3;
}

int getUpgradeLightsProtectionInfo(DWORD* vehicle){
	return *(int*)((char*)vehicle + 0x540C + 0x28);
}

bool is_player(DWORD *Car_V){
	DWORD* playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	DWORD* playerCar_V = (DWORD *)(playerVehicle[5400]);

	return Car_V == playerCar_V;
}

void DisplayScreenMessage(char* text){
	typedef int(*textcall2)(void* a1);
	int ret = textcall2(0x484050)(text);
}

DWORD* prev_Car_V;
char car_prefix[20];
char temp_str[32];

bool  use_mod_gearbox;
int   mod_gears_cnt;
float mod_rear_axle;
float mod_gear_coeffs[13];

void process_mod(DWORD *Car_V){
	char mod_config_path[32] = ".\\plugins\\KoTR_UpgradesMod.ini";
	bool is_engine_upgraded = *(int*)((char*)Car_V + 0x3EBC + 0x28);

	DWORD *playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	int playerTechID = playerVehicle[2605];

	int   *Car_V_gears_count = (int*)((char*)Car_V + 0x1E04);
	float *Car_V_rear_axle_c = (float*)((char*)Car_V + 0x1C80);
	float *Car_V_gear_coeffs = (float*)((char*)Car_V + 0x1C44 + 0x8); //+ 0x8 - сразу первая передача

	int tech_gears_cnt  = *((int*)((0x697888 + (2416 * playerTechID) + 0x90)));
	float tech_rear_axle = *((float*)((0x697888 + (2416 * playerTechID) + 0xCC)));
	float *tech_gear_coeffs = ((float*)((0x697888 + (2416 * playerTechID) + 0xD4 + 0x8))); //+ 0x8 - сразу первая передача

	//reload coeffs in debug mode if "J" key pressed
	if (debug_mode && IsKeyJustPressed(74)){
		prev_Car_V = 0;
		DisplayScreenMessage("coeffs reloaded");
	}

	if (prev_Car_V != Car_V){
		memcpy(&car_prefix, (((char *)0x697888 + (2416 * playerTechID) + 2342)), 20);

		use_mod_gearbox = GetPrivateProfileInt(car_prefix, "use_mod_gearbox", 0, mod_config_path);

		mod_gears_cnt   = GetPrivateProfileInt(car_prefix, "gears_count_new", 0, mod_config_path);
		mod_rear_axle   = GetPrivateProfileFloat(car_prefix, "rear_axle_coeff", "0.0", mod_config_path);

		if (!mod_gears_cnt)
			mod_gears_cnt = tech_gears_cnt - 1;

		if (!mod_rear_axle)
			mod_rear_axle = tech_rear_axle;
		
		
		for (int i = 0; i < 12; i++){
			sprintf(temp_str, "gear_trans_coeff%d", i + 1);
			mod_gear_coeffs[i] = GetPrivateProfileFloat(car_prefix, temp_str, "0.0", mod_config_path);
			if (!mod_gear_coeffs[i])
				mod_gear_coeffs[i] = tech_gear_coeffs[i];
		}
		
		prev_Car_V = Car_V;
	}

	if (debug_mode || (is_engine_upgraded && use_mod_gearbox)){
		*Car_V_gears_count = mod_gears_cnt + 1;
		*Car_V_rear_axle_c = mod_rear_axle;
		for (int i = 0; i < 12; i++){
			Car_V_gear_coeffs[i] = mod_rear_axle * mod_gear_coeffs[i];
		}
	} else {
		//*Car_V_gears_count_from_tech  = tech_gears_cnt;
		*Car_V_gears_count = tech_gears_cnt;
		*Car_V_rear_axle_c = tech_rear_axle;
		for (int i = 0; i < 12; i++){
			Car_V_gear_coeffs[i] = tech_rear_axle * tech_gear_coeffs[i];
		}
	}
}

// hooks
double _fastcall Car_V__sub_4F04A0(DWORD *Car_V, DWORD EDX){
	if (is_player(Car_V)){
		process_mod(Car_V);
	}

	return (Car_V[1677] + Car_V[1676]) * 0.5;
}

void DisplayConsole(){
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void PrintUpgradesInfo(){
	cout << "TestFunc\n";

	DWORD* vehicle = (DWORD*)*(DWORD*)0x6F6930;
	DWORD* vehicleCar_V = (DWORD *)(vehicle[5400]);

	//указатели на воздуховод
	DWORD* playerID = *(DWORD**)((char *)vehicle + 0x10 + 0x508C);
	//cout << "playerID  =" << playerID << endl;

	DWORD* ptr1 = *(DWORD**)((char *)playerID + 0x204);
	//cout << "ptr1=" << ptr1 << endl;

	DWORD* ptr2 = *(DWORD**)((char *)ptr1 + 0x10);
	//cout << "ptr2=" << ptr2 << endl;

	DWORD* ptr3 = (DWORD*)((char*)ptr2 + 0x120);
	//cout << "ptr3=" << ptr3 << endl;

	int upg_suspension = *(int*)((char*)vehicle + 0x52FC);
	int upg_vent_brake = *(int*)((char*)vehicleCar_V + 0x3F58 + 0x28);
	int upg_eng_brakes = *(int*)((char*)vehicleCar_V + 0x3FF4 + 0x28);
	int upg_frame      = *(int*)((char*)vehicle + 0x52A0 + 0x28);
	int upg_glass      = *(int*)((char*)vehicle + 0x5308 + 0x28);
	int upg_lights_pr  = *(int*)((char*)vehicle + 0x540C + 0x28);
	int upg_engine     = *(int*)((char*)vehicleCar_V + 0x3EBC + 0x28);
	int upg_prisadka   = *(int*)((char*)vehicleCar_V + 0x3FC0 + 0x28);
	int upg_snorkel    = *ptr3;
	int upg_wheels     = *(int*)((char*)vehicleCar_V + 0x3F24 + 0x28);
	int upg_fuel_t     = *(int*)((char*)vehicleCar_V + 0x3EF0 + 0x28);
	int upg_abs        = *(int*)((char*)vehicle + 0x53A4 + 0x28);
	int upg_radar      = *(int*)((char*)vehicle + 0x5400);
	int upg_fire_sys   = *(int*)((char*)vehicle + 0x5370 + 0x28);
	int upg_horn       = *(int*)((char*)vehicle + 0x533C + 0x28);

	cout << "suspension=" << upg_suspension << endl;
	cout << "vent_brake=" << upg_vent_brake << endl;
	cout << "eng_brakes=" << upg_eng_brakes << endl;
	cout << "upg_frame =" << upg_frame      << endl;
	cout << "upg_glass =" << upg_glass      << endl;
	cout << "lights_pr =" << upg_lights_pr  << endl;
	cout << "engine    =" << upg_engine     << endl;
	cout << "prisadka  =" << upg_prisadka   << endl;
	cout << "snorkel   =" << upg_snorkel    << endl;
	cout << "wheels    =" << upg_wheels     << endl;
	cout << "fuel tanks=" << upg_fuel_t     << endl;
	cout << "ABS       =" << upg_abs        << endl;
	cout << "radar     =" << upg_radar      << endl;
	cout << "fire_sys  =" << upg_fire_sys   << endl;
	cout << "horn      =" << upg_horn       << endl;
}

void AttachHooks(){
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

	DWORD addr_4F04A0 = 0x4F04A0;

	DetourAttach(&(LPVOID&)addr_4F04A0, &Car_V__sub_4F04A0);

    DetourTransactionCommit();

	cout << "UpgradesMod v0.2 (18.01.2025) started." << endl;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_UpgradesMod.ini"))
				return TRUE;

			if (GetPrivateProfileInt("mod", "display_console", 0, ".\\KoTR_UpgradesMod.ini")){
				DisplayConsole();
			}

			debug_mode = GetPrivateProfileInt("mod", "debug", 0, ".\\KoTR_UpgradesMod.ini");
			AttachHooks();

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
