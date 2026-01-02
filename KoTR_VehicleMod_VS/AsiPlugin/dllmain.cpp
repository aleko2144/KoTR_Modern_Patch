#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "dllmain.h"

#include "detours.h"

#include "include/input/input.h"

using namespace std;

void WriteDebugLog(const char *text){
	FILE *file = fopen(".\\VehicleMod.log", "a");
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

string GetPrivateProfileStr(const char* selection, const char* varname, const char* default_val, const char* filename){
	char returnedString[256];
	GetPrivateProfileStringA(selection, varname, default_val, returnedString, 256, filename);
	return returnedString;
}

DWORD *GetBlockByName(DWORD *parent, const char *name){
	typedef DWORD*(*GetBlockByName)(DWORD *a1, int *a2);
	DWORD *result = GetBlockByName(0x5EF260)(parent, (int*)name);
	return result;
}

void SetCaseSwitch(DWORD* offset, int state){
	typedef int(*SetCaseSwitch)(DWORD *offset, int state);
	int ret = SetCaseSwitch(0x4E48AC)(offset, state);
}
int GetChildCount(DWORD* offset){
	if (offset){
		return *(int*)((int)offset + 52);
	}
	return 0;
}
void SetCaseSwitch_s(DWORD* offset, int state){
	if (offset && state < GetChildCount(offset)){
		SetCaseSwitch(offset, state);
	}
}

void CBlockRef__SetOffset(DWORD* offset, int state){
	typedef int(*CBlockRef__SetOffset)(DWORD *offset, int state);
	int ret = CBlockRef__SetOffset(0x5E1980)(offset, state);
}

void CBlockSpace__SetOffset(DWORD* offset, int state){
	typedef int(*CBlockSpace__SetOffset)(DWORD *offset, int state);
	int ret = CBlockSpace__SetOffset(0x4E4942)(offset, state);
}

//***** TurnSignals *****//
bool TurnSignalR_enable = false;
bool TurnSignalL_enable = false;
bool TurnSignalH_enable = false;

int TurnSignalRKey = 0;
int TurnSignalLKey = 0;
int TurnSignalHKey = 0;
bool UseTurnSignals = false;

int TurnSignalsKey_state;

float ai_signals_rotation_lim = 0.5;
float ai_max_damage = 0.5;

DWORD* blinker_onSound;
DWORD* blinker_offSound;
DWORD* blinker_relayOnSound;
DWORD* blinker_relayOffSound;

DWORD* SearchRESSound(char *a1){
	typedef DWORD*(*SearchRESSound)(char *a1);
	DWORD* ret = SearchRESSound(0x5EF380)(a1);
	return ret;
}

void PlayWAV(DWORD* sound, float volume){
	//если нет звука или вид снаружи
	if (!sound || *(int *)(*(int *)0x6D2098 + 1400)){
		return;
	}
	typedef int(*PlayResSound)(DWORD* sound, float volume);
	int ret = PlayResSound(0x52F6B0)(sound, volume);
}

int signals_time_start = 0;
int signals_time_blink;
int signals_time_blink_2;

bool SignalsBlinkEvent(){
	return (GetTickCount() - signals_time_start) % signals_time_blink < signals_time_blink_2;
}

int prev_signals_state = 0;

void ProcessTurnSignalsState(){
	bool blinked = SignalsBlinkEvent();

	if (TurnSignalR_enable) {
		if (blinked) {
			TurnSignalsKey_state = 1;
		} else {
			TurnSignalsKey_state = 0;
		}
	} else if (TurnSignalL_enable) {
		if (blinked) {
			TurnSignalsKey_state = 2;
		} else {
			TurnSignalsKey_state = 0;
		}
	} else if (TurnSignalH_enable) {
		if (blinked) {
			TurnSignalsKey_state = 3;
		} else {
			TurnSignalsKey_state = 0;
		}
	} else {
		TurnSignalsKey_state = 0;
	}


	if (prev_signals_state != TurnSignalsKey_state){
		prev_signals_state = TurnSignalsKey_state;

		if (TurnSignalsKey_state){
			PlayWAV(blinker_relayOnSound, 1.0);
			//cout << "1 blink\n";
		} else {
			PlayWAV(blinker_relayOffSound, 1.0);
			//cout << "0 blink\n";
		}
	}

}

int GetAITurnSignalsState(DWORD* vehicle){
	if (!UseTurnSignals)
		return 0;
	
	// -1=право, 1=лево
	float rule_rotation = *(float *)((char *)(vehicle[5400]) + 0x29E0);
	float damage_level = *(float *)((char *)vehicle + 0x5200);

	bool blinked = SignalsBlinkEvent();

	if (damage_level >= ai_max_damage){
		if (blinked) {
			return 3;
		} else {
			return 0;
		}
	} else if (rule_rotation < -ai_signals_rotation_lim) {
		if (blinked) {
			return 1;
		} else {
			return 0;
		}
	} else if (rule_rotation > ai_signals_rotation_lim) {
		if (blinked) {
			return 2;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}


//*****//


DWORD *m_carNodes[32767]; //9600 = 0x78 * 80
DWORD *m_carNodes_TurnSignalsKey[32767]; //0-off, 1-R, 2-L, 3-hazard
DWORD *m_carNodes_upgrWheelsKey[32767]; //0-std, 1-highway, 2-offroad
DWORD *m_carNodes_upgrEngineKey[32767]; //0-std, 1-forced
//DWORD *m_carNodes_upgrSnorkelKey[32767]; //0-off, 1-on //приводит к вылету
DWORD *m_carNodes_upgrLightsPrKey[32767]; //0-off, 1-on

DWORD *m_TSLampKey; //указатель на TurnSignalsLampKey (для салонов)

void InitVehicleNodes(){
	int currentID = 0;
	int techItemsCount = *(DWORD *)0x6CE34C;

	//cout << techItemsCount << " tech objects total\n";

	//vehicle + 28B4 = vehicleID (VolvoR=23)
	do {
		DWORD *carNode = GetBlockByName(0, (((char *)0x697888 + (2416 * currentID) + 2342)));
		//cout << carNode << "<- carNode\n";

		DWORD someOffset = 0x5D0 * currentID;
		m_carNodes[0x174 * currentID] = carNode;

		m_carNodes_TurnSignalsKey[someOffset / 4] = GetBlockByName(m_carNodes[someOffset / 4], "TurnSignalsKey");

		m_carNodes_upgrWheelsKey[someOffset / 4] = GetBlockByName(m_carNodes[someOffset / 4], "upgr_WheelsKey");
		m_carNodes_upgrEngineKey[someOffset / 4] = GetBlockByName(m_carNodes[someOffset / 4], "upgr_EngineKey");
		//m_carNodes_upgrSnorkelKey[someOffset / 4] = GetBlockByName(m_carNodes[someOffset / 4], "upgr_SnorkelKey");
		m_carNodes_upgrLightsPrKey[someOffset / 4] = GetBlockByName(m_carNodes[someOffset / 4], "upgr_LightsPrKey");

		++currentID;
	}
	while ( currentID < techItemsCount );

	m_TSLampKey = GetBlockByName(0, "TSLampKey");

	//в cabines.b3d объект refer_TSLampKey распологать после руля (чтобы лампы не светились перед рулём,
	//если используется mat_pribor), т.к. в cabines.res прописан noz для материалов стандартных салонов
}

//sub_53FCA0->sub_57C980
static void (*original_sub_57C980)(short) = (void(*)(short))0x57C980;
void sub_57C980(__int16 a1){
	//вставка
	InitVehicleNodes();
	//

	//вставка 2
	blinker_onSound       = SearchRESSound("blinker_onSound");
	blinker_offSound      = SearchRESSound("blinker_offSound");
	blinker_relayOnSound  = SearchRESSound("blinker_relayOnSound");
	blinker_relayOffSound = SearchRESSound("blinker_relayOffSound");
	//

	original_sub_57C980(a1);
}

void DisplayConsole(){
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//cout << "Mod debug window started" << endl;
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

void PrintUpgradesInfo(){
	cout << "TestFunc\n";

	DWORD* vehicle = (DWORD*)*(DWORD*)0x6F6930;
	DWORD* vehicleCar_V = (DWORD *)(vehicle[5400]);
	//vehicleCar_V[2446] = 3; - hi_fi

	//указатели на воздуховод
	DWORD* playerID = *(DWORD**)((char *)vehicle + 0x10 + 0x508C); //работает
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

	//horn upg = vehicle + 0x5364

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


	//playerVehicle = (DWORD*)(*(DWORD*)0x6F6930); //playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	//playerCar_V = (DWORD *)(playerVehicle[5400]);
	//trailerVehicle = (DWORD *)playerVehicle[5470]; //(DWORD *)(playerVehicle[5470]);
	//trailerCar_V = *(DWORD **)(playerVehicle[5470] + 21600);
}

void TestFunction(){
	if (IsKeyPressed(73)){ //i
		cout << "TestFunction()\n";
	}
	if (IsKeyPressed(74)){ //j
		PrintUpgradesInfo();
	}
	//if (IsKeyPressed(75)){ //k
	//	test_state = 1;
	//}
}

static void (__thiscall* original_ProcessVehicleLights)(void* _this) = (void(__thiscall*)(void*))0x546CA0;
void __fastcall ProcessVehicleLights(void* _this){
	DWORD* vehicle = (DWORD*)_this;

	DWORD techID = vehicle[2605];

	//vehicleCar_V[2446] = 3; //hi_fi (1 - simplified, 3 - std)

	const bool is_player_vehicle = _this == (DWORD*)(*(DWORD*)0x6F6930);

	//***** переключение объектов *****//
	original_ProcessVehicleLights(_this);

	//***** новые объекты *****//
	DWORD* node;

	//*** TurnSignalsKey ***//
	node = (DWORD*)m_carNodes_TurnSignalsKey[372 * techID];
	CBlockSpace__SetOffset(node, 0);

	if (is_player_vehicle){
		CBlockSpace__SetOffset(node, TurnSignalsKey_state);

		// -1=право, 1=лево
		//cout << "RuleRotation=" <<  *(float *)((char *)(vehicle[5400]) + 0x29E0) << endl;
		//cout << "VehicleState=" << *(float *)((char *)vehicle + 0x5200) << endl;
	} else {
		CBlockSpace__SetOffset(node, GetAITurnSignalsState(vehicle)); //на других машинах ставить от поворота руля
	}

	//*** улучшения ***//
	//wheels
	node = (DWORD*)m_carNodes_upgrWheelsKey[372 * techID];
	SetCaseSwitch_s(node, getUpgradeWheelsInfo(vehicle));
	//forced engine
	node = (DWORD*)m_carNodes_upgrEngineKey[372 * techID];
	SetCaseSwitch_s(node, getUpgradeEngineInfo(vehicle));
	//lights protection
	node = (DWORD*)m_carNodes_upgrLightsPrKey[372 * techID];
	SetCaseSwitch_s(node, getUpgradeLightsProtectionInfo(vehicle));
	//snorkel (вызывает вылеты?)
	//node = (DWORD*)m_carNodes_upgrSnorkelKey[372 * techID];
	//SetCaseSwitch_s(node, getUpgradeSnorkelInfo(vehicle));

	//test
	//node = (DWORD*)m_carNodes_GlowFRKey[372 * techID];
	//CBlockSpace__SetOffset(node, 0);
	//
	//if (is_player_vehicle){
	//	CBlockSpace__SetOffset(node, test_state);
	//}
};

void AttachHooks(){
    //cout << "Try to attach hooks" << endl;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

	DetourAttach(&(LPVOID&)original_sub_57C980, &sub_57C980);
	DetourAttach(&(LPVOID&)original_ProcessVehicleLights, &ProcessVehicleLights);

    DetourTransactionCommit();

    //cout << "Hooks attached!" << endl;
	//cout << "VehicleMod v0.3 (03.11.2025) started\n";
}

//in-game keys:
//KeyViewLeft = 0x1A,
//KeyViewRight = 0x1B,

void GetInput(){
	if (UseTurnSignals) {
		if (IsKeyJustPressed(TurnSignalRKey)) {
		//if (IsGameKeyJustPressed(0x1B)) {
			TurnSignalR_enable = !TurnSignalR_enable;
			TurnSignalL_enable = false;
			TurnSignalH_enable = false;

			if (TurnSignalR_enable){
				PlayWAV(blinker_onSound, 1.0);
				//cout << "on\n";
			} else {
				PlayWAV(blinker_offSound, 1.0);
				//cout << "off\n";
			}

		} else if (IsKeyJustPressed(TurnSignalLKey)) {
		//} else if (IsGameKeyJustPressed(0x1A)) {
			TurnSignalL_enable = !TurnSignalL_enable; 
			TurnSignalR_enable = false;
			TurnSignalH_enable = false;

			if (TurnSignalL_enable){
				PlayWAV(blinker_onSound, 1.0);
				//cout << "on\n";
			} else {
				PlayWAV(blinker_offSound, 1.0);
				//cout << "off\n";
			}
		} else if (IsKeyJustPressed(TurnSignalHKey)) {
		//} else if (IsGameKeyJustPressed(0x1A) && IsGameKeyJustPressed(0x1B)) {
			TurnSignalH_enable = !TurnSignalH_enable; 
			TurnSignalR_enable = false;
			TurnSignalL_enable = false;

			if (TurnSignalH_enable){
				PlayWAV(blinker_onSound, 1.0);
				//cout << "on\n";
			} else {
				PlayWAV(blinker_offSound, 1.0);
				//cout << "off\n";
			}
		}
	}
}

/*void SearchSounds(){
	//поиск звуков
	blinker_onSound       = SearchRESSound("blinker_onSound");
	blinker_offSound      = SearchRESSound("blinker_offSound");
	blinker_relayOnSound  = SearchRESSound("blinker_relayOnSound");
	blinker_relayOffSound = SearchRESSound("blinker_relayOffSound");
	cout << "get sounds\n";
	cout << blinker_onSound << endl;
}

DWORD* prev_player_ptr;*/

void OnTimer(HWND hwnd, UINT msg, UINT idTimer, DWORD dwTime){
	if (*(DWORD *)0x6D2098){
		//TestFunction();
		GetInput();
		if (UseTurnSignals){
			//салонная лампа
			SetCaseSwitch_s(m_TSLampKey, TurnSignalsKey_state);
			ProcessTurnSignalsState();

			//if (prev_player_ptr != (DWORD*)(*(DWORD*)0x6F6930)){
			//	prev_player_ptr = (DWORD*)(*(DWORD*)0x6F6930);
			//	SearchSounds();
			//}
		} else {
			SetCaseSwitch_s(m_TSLampKey, 4); //отключение отрисовки ламп в салонах
		}
	} else {
		signals_time_start = GetTickCount();
	}
}

void ReadConfig(){
	//UseTurnSignals = GetPrivateProfileIntA("COMMON", "TurnSignals", 0, ".\\KoTR_VehicleMod.ini");

	//может не работать из-за кодировки! жесть какая!
	UseTurnSignals = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\KoTR_VehicleMod.ini") != 0;

	if (UseTurnSignals)
		cout << "VehicleMod v0.3 (03.11.2025) started.\n";

	TurnSignalRKey = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalRKey", 190, ".\\KoTR_VehicleMod.ini");
	TurnSignalLKey = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalLKey", 188, ".\\KoTR_VehicleMod.ini");
	TurnSignalHKey = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalHKey", 191, ".\\KoTR_VehicleMod.ini");

	signals_time_blink = GetPrivateProfileIntA("COMMON", "TurnSignalsBlinkTime", 800, ".\\KoTR_VehicleMod.ini");
	signals_time_blink_2 = signals_time_blink / 2;

	ai_max_damage           = GetPrivateProfileFloat("COMMON", "AI_max_damage", "0.5", ".\\KoTR_VehicleMod.ini");
	ai_signals_rotation_lim = GetPrivateProfileFloat("COMMON", "AI_signals_rotation_lim", "0.5", ".\\KoTR_VehicleMod.ini");
	//cout << "ai_signals_rotation_lim=" << ai_signals_rotation_lim << endl;
}
	
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			DisplayConsole();

			ReadConfig();

			AttachHooks();

			SetTimer(0, 0, 10, (TIMERPROC)OnTimer);

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
