#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "dllmain.h"

using namespace std;

bool gameKeyStates[44];

int GetGameKeyState(int key) {
	typedef int (__thiscall * GetGameKeyState)(DWORD* _this, int key);
	return GetGameKeyState(0x530010)((DWORD*)0x6D1DD8, key);
}

bool IsGameKeyJustPressed(int key){
	if (GetGameKeyState(key)){
		if (!gameKeyStates[key]){
			gameKeyStates[key] = true;
			return true;
		}
	}
	else {
		gameKeyStates[key] = false;
	}
	return false;
}

float GetPrivateProfileFloat(string selection, string varname, string default_val, string filename){
	float to_return;
	char* returnedString = new char[256];
	GetPrivateProfileStringA(selection.c_str(), varname.c_str(), default_val.c_str(), returnedString, 256, filename.c_str());
	to_return = atof(returnedString);
	return to_return;
}

string GetPrivateProfileStr(string selection, string varname, string default_val, string filename){
	char* returnedString = new char[256];
	GetPrivateProfileStringA(selection.c_str(), varname.c_str(), default_val.c_str(), returnedString, 256, filename.c_str());
	string result = returnedString;
	return result;
}

DWORD *GetB3DBlock(DWORD *parent, const char *name){
	typedef DWORD*(*GetB3DBlock)(DWORD *a1, int *a2);
	DWORD *result = GetB3DBlock(0x5EF260)(parent, (int*)name);
	return result;
}
DWORD *GetB3DBlockOrExit(DWORD *parent, char *name, char *a3){
	typedef DWORD*(*GetB3DBlockOrExit)(DWORD *a1, char *a2, char *a3);
	DWORD *result = GetB3DBlockOrExit(0x4E47F0)(parent, name, a3);
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
}
void SetCaseSwitch_s(DWORD* offset, int state){
	if (offset && state < GetChildCount(offset)){
		SetCaseSwitch(offset, state);
	}
}

string cab_prefix; //префикс салона
int vehicleID;
int vehicle_offset;
int vehicle_task;
int vehicle_type;
bool is_day_KMeter_mode; //0 - общий пробег, 1 - суточный
DWORD *cab_ptr;
DWORD *AvtoKey;
DWORD *FuelLampKey;
DWORD *GearKey;
DWORD *ParkKey;
DWORD *TrailerKey;
DWORD *meter_ptr;
DWORD *KMeter0Key;
DWORD *KMeter1Key;
DWORD *KMeter2Key;
DWORD *KMeter3Key;
DWORD *KMeter4Key;
DWORD *KMeter5Key;
DWORD *KMeter6Key;

DWORD *DashboardKey;
DWORD *LightsLampKey;
DWORD *TestGlowKey;
DWORD *GlassDamKey;

void updatePointers(){
	vehicle_offset = *(int *)(*(int *)0x6D2098 + 0x268);
	vehicle_task = (vehicle_offset + 0x10);
	vehicleID = *(int *)(*(int *)0x6D2098 + 104);
	vehicle_type = *(int*)(((char *)0x697888 + (2416 * vehicleID) + 0x944)); //techdata -> vehicle type: 0 - car, 1 - lorry, 2 - tractor
	cab_prefix = (((char *)0x697888 + (2416 * vehicleID) + 2322));
	cab_prefix += "Cab";

	GlassDamKey = GetB3DBlock(0, "GlassDamageKey");
	//cout << "GlassDamageKey" << GlassDamKey << endl;

	AvtoKey = GetB3DBlock(0, "AvtoKey");
	FuelLampKey = GetB3DBlock(0, "FuelLampKey");
	GearKey = GetB3DBlock(0, "GearKey");
	ParkKey = GetB3DBlock(0, "ParkKey");
	TrailerKey = GetB3DBlock(0, "TrailerKey");

	DashboardKey = GetB3DBlock(0, "DashboardGlowKey");
	LightsLampKey = GetB3DBlock(0, "LightsLampKey");
	TestGlowKey = GetB3DBlock(0, "TestGlowKey");

	//meter_ptr = GetB3DBlock(0, "Meter");

	//if (!meter_ptr){
	//	return;
	//}

	KMeter0Key = GetB3DBlock(0, "KMeter0Key");
	KMeter1Key = GetB3DBlock(0, "KMeter1Key");
	KMeter2Key = GetB3DBlock(0, "KMeter2Key");
	KMeter3Key = GetB3DBlock(0, "KMeter3Key");
	KMeter4Key = GetB3DBlock(0, "KMeter4Key");
	KMeter5Key = GetB3DBlock(0, "KMeter5Key");
	KMeter6Key = GetB3DBlock(0, "KMeter6Key");
	//}

	/*
	cout << cab_prefix.c_str() << "=" << cab_ptr << endl;
	cout << "AvtoKey=" << AvtoKey << endl;
	cout << "FuelLampKey=" << FuelLampKey << endl;
	cout << "GearKey=" << GearKey << endl;
	cout << "ParkKey=" << ParkKey << endl;
	cout << "TrailerKey=" << TrailerKey << endl;
	cout << "KMeter0Key=" << KMeter0Key << endl;
	cout << "KMeter1Key=" << KMeter1Key << endl;
	cout << "KMeter2Key=" << KMeter2Key << endl;
	cout << "KMeter3Key=" << KMeter3Key << endl;
	cout << "KMeter4Key=" << KMeter4Key << endl;
	cout << "KMeter5Key=" << KMeter5Key << endl;
	cout << "KMeter6Key=" << KMeter6Key << endl;
	*/
}

int AvtoKeyValue;
float fuelLevel;
float carDamageLevel;
int FuelLampKeyValue;
int GearKeyValue;
int ParkKeyValue;
int TrailerKeyValue;
int kilometrage;
//int day_kilometrage;
//int day_kilometrage_prev;
int KMeter0KeyValue;
int KMeter1KeyValue;
int KMeter2KeyValue;
int KMeter3KeyValue;
int KMeter4KeyValue;
int KMeter5KeyValue;
int KMeter6KeyValue;

int LightsState;
int TestGlowState; //лампы при запуске ДВС
int engineState; //0-выключен, 1-запуск, 2-включён, 3-выключение

int GlassDamState; //0 - стёкла целые, 1 - разбитые

int blink_start_time;
int glow_start_time;

void getValues(){
	AvtoKeyValue = *(int *)0x6F3470;
	fuelLevel = *(float *)(vehicle_offset + 20988);
	carDamageLevel = *(float *)(vehicle_task + 0x51F0);
	engineState = *(int *)(vehicle_offset + 21012);

	//cout << carDamageLevel << endl;

	if (carDamageLevel > 0.1)
		GlassDamState = 1;
	else
		GlassDamState = 0;

	//cout << engineState << endl;

	if (fuelLevel < 0.20){
		if (GetTickCount() - blink_start_time < 500){
			FuelLampKeyValue = 1;
		} else if (GetTickCount() - blink_start_time < 1000) {
			FuelLampKeyValue = 0;
		} else {
			blink_start_time = GetTickCount();
		}
	} else{
		FuelLampKeyValue = 0;
	}

	//если нажата кнопка запуска ДВС
	if (IsGameKeyJustPressed(0x29) && !engineState){
		glow_start_time = GetTickCount();
	}

	//если ДВС запускается или запущен
	//if (engineState != 3){
	//engine_start_lamps
	if (glow_start_time){
		int diff = GetTickCount() - glow_start_time;
		if (diff < 1500){
			TestGlowState = 1;
		} else if (diff < 2500){
			TestGlowState = 2;
		} else {
			glow_start_time = 0;
			TestGlowState = 0;
		}
	}

	GearKeyValue = *(DWORD *)(vehicle_task + 20980);
	ParkKeyValue = *(DWORD *)(vehicle_task + 21004);

	LightsState = *(DWORD *)(vehicle_offset + 20920);


	if (*(int*)(*(int*)0x6F6930 + 0x5578) && vehicle_type == 2){ //если есть полуприцеп и ТС - тягач
		TrailerKeyValue = 1;
	} else {
		TrailerKeyValue = 0;
	}

	kilometrage = ((int)(*(float *)(vehicle_offset + 20980))); // / 10.0; //чтобы синие цифры показывали целую часть пробега, а красные - дробную
	//day_kilometrage += (kilometrage - day_kilometrage_prev);
	//day_kilometrage_prev = kilometrage;

	//if (IsKeyJustPressed(78)){ //N key
	//	is_day_KMeter_mode = !is_day_KMeter_mode;
	//	day_kilometrage = 0;
	//}

	KMeter6KeyValue = kilometrage / 1000000 % 10;
	KMeter5KeyValue = kilometrage / 100000 % 10;
	KMeter4KeyValue = kilometrage / 10000 % 10;
	KMeter3KeyValue = kilometrage / 1000 % 10;
	KMeter2KeyValue = kilometrage / 100 % 10;
	KMeter1KeyValue = kilometrage / 10 % 10;
	KMeter0KeyValue = kilometrage % 10;

	/*if (is_day_KMeter_mode){
		KMeter6KeyValue = day_kilometrage / 1000000 % 10;
		KMeter5KeyValue = day_kilometrage / 100000 % 10;
		KMeter4KeyValue = day_kilometrage / 10000 % 10;
		KMeter3KeyValue = day_kilometrage / 1000 % 10;
		KMeter2KeyValue = day_kilometrage / 100 % 10;
		KMeter1KeyValue = day_kilometrage / 10 % 10;
		KMeter0KeyValue = day_kilometrage % 10;

	} else {
		KMeter6KeyValue = kilometrage / 1000000 % 10;
		KMeter5KeyValue = kilometrage / 100000 % 10;
		KMeter4KeyValue = kilometrage / 10000 % 10;
		KMeter3KeyValue = kilometrage / 1000 % 10;
		KMeter2KeyValue = kilometrage / 100 % 10;
		KMeter1KeyValue = kilometrage / 10 % 10;
		KMeter0KeyValue = kilometrage % 10;
	}*/

	/*cout << "AvtoKeyValue=" << AvtoKeyValue << endl;
	cout << "FuelLampKeyValue=" << FuelLampKeyValue << endl;
	cout << "GearKeyValue=" << GearKeyValue << endl;
	cout << "ParkKeyValue=" << ParkKeyValue << endl;
	cout << "TrailerKeyValue=" << TrailerKeyValue << endl;
	cout << "kilometrage=" << kilometrage << endl;
	cout << "KMeter0KeyValue=" << KMeter0KeyValue << endl;
	cout << "KMeter1KeyValue=" << KMeter1KeyValue << endl;
	cout << "KMeter2KeyValue=" << KMeter2KeyValue << endl;
	cout << "KMeter3KeyValue=" << KMeter3KeyValue << endl;
	cout << "KMeter4KeyValue=" << KMeter4KeyValue << endl;
	cout << "KMeter5KeyValue=" << KMeter5KeyValue << endl;
	cout << "KMeter6KeyValue=" << KMeter6KeyValue << endl;*/

	//cout << "kilometrage=" << kilometrage << endl;
	//cout << "day_kilometrage=" << day_kilometrage << endl;
}

void processInterior(){
	SetCaseSwitch_s(AvtoKey, AvtoKeyValue);
	SetCaseSwitch_s(FuelLampKey, FuelLampKeyValue);
	SetCaseSwitch_s(GearKey, GearKeyValue);
	SetCaseSwitch_s(ParkKey, ParkKeyValue);
	SetCaseSwitch_s(TrailerKey, TrailerKeyValue);
	SetCaseSwitch_s(KMeter0Key, KMeter0KeyValue);
	SetCaseSwitch_s(KMeter1Key, KMeter1KeyValue);
	SetCaseSwitch_s(KMeter2Key, KMeter2KeyValue);
	SetCaseSwitch_s(KMeter3Key, KMeter3KeyValue);
	SetCaseSwitch_s(KMeter4Key, KMeter4KeyValue);
	SetCaseSwitch_s(KMeter5Key, KMeter5KeyValue);
	SetCaseSwitch_s(KMeter6Key, KMeter6KeyValue);
	
	if (LightsState)
		SetCaseSwitch_s(DashboardKey, 1);
	else
		SetCaseSwitch_s(DashboardKey, 0);

	SetCaseSwitch_s(LightsLampKey, LightsState);
	SetCaseSwitch_s(TestGlowKey, TestGlowState);

	//если ДВС запускается, то включить лампы ручника и топлива
	if (TestGlowState == 1){ //т.к. есть ещё и 2
		SetCaseSwitch_s(FuelLampKey, 1);
		SetCaseSwitch_s(ParkKey, 1);
	}

	SetCaseSwitch_s(GlassDamKey, GlassDamState);
}

DWORD *playerVehicle_prev;
void ProcessMod(){
	DWORD *playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);

	if (!playerVehicle)
		return;

	if (playerVehicle_prev != playerVehicle){
		playerVehicle_prev = playerVehicle;
		updatePointers();
			
		//day_kilometrage = 0;
		//day_kilometrage_prev = 0;
	}

	getValues();
	processInterior();

	//DWORD *SirenState = (DWORD *)((char*)playerVehicle + 0x51BC);

	//if (IsGameKeyJustPressed(21)){
	//	*SirenState = !*SirenState;
	//}
}

void DisplayConsole(){
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void CALLBACK OnTimer(HWND hwnd,   UINT msg, UINT_PTR idTimer, DWORD dwTime)
{
	//*(DWORD*)0x6D2098 - Viewer
	//*(DWORD*)0x6F6930 - playerVehicle

	if (*(DWORD*)0x6D2098) {
		ProcessMod();
	} //else {
	//}
}
	
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_InteriorMod.ini"))
				return TRUE;
			//DisplayConsole();
			cout << "InteriorMod v1.2 (03.11.2025) started." << endl;
			SetTimer(0, 0, 15, OnTimer);
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
