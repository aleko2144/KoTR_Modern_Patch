#include "STrailersPhysFix.h"
#include "../Utils/CPatch.h"
#include "../Utils/ConfigUtils.h"
#include "../Utils/CVector.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h"

#include "../GameApp/GameObjects.h"

#include <iostream>

float tractor_steer_coeff = 1.5;
float tractor_mass_coeff  = 1.0;
float strailer_mass_coeff = 3.5;


int funcAddr_4FABB0;
int callAddr_4FABB0_tractor;
int callAddr_4FABB0_strailer;

int funcAddr_processRDtrains;
int callAddr_processRDtrains;

int addr_strailer_detach;
float* steering_help;

int Car_V_offset;
int** playerVehicle;

int sub_4FABB0(int* carV, CVector* a2, CVector* a3) {
	typedef int(__thiscall* sub_4FABB0)(void* carV, CVector* a2, CVector* a3);
	return sub_4FABB0(funcAddr_4FABB0)(carV, a2, a3);
}

bool __fastcall processRoadtrainMovement(int* tractor) {
	typedef bool(__thiscall* sub_558EB0)(int* tractor);
	return sub_558EB0(funcAddr_processRDtrains)(tractor);
}

int __fastcall OnCall4FABB0ForTractor(int* carV, int edx, CVector* a2, CVector* a3) {
	a2->x *= tractor_mass_coeff;
	a2->y *= tractor_mass_coeff;
	a2->z *= tractor_mass_coeff;

	return sub_4FABB0(carV, a2, a3);
}

int __fastcall OnCall4FABB0ForSTrailer(int* carV, int edx, CVector* a2, CVector* a3) {
	a2->x *= strailer_mass_coeff;
	a2->y *= strailer_mass_coeff;
	a2->z *= strailer_mass_coeff;

	return sub_4FABB0(carV, a2, a3);
}

bool __fastcall OnCallProcessRoadtrainMovement(int* tractor) {
	int* carV = (int*)((char*)tractor + Car_V_offset);

	bool is_player_car = tractor == *playerVehicle;
	int* is_in_sim_mode = (int*)(((char*)*carV) + 0x2768);

	// "Crutch Code Technologies, LTD."
	// 
	//Since I still haven't found a good solution for the poor steering of road trains in simulator mode,
	//I switch the truck to arcade mode, and adjusting the trailer's behavior to imitate something similar to a simulator.

	if (is_player_car && *is_in_sim_mode) {
		//disable simulator mode and reduce arcade steering coeff
		*is_in_sim_mode = 0;
		*steering_help = tractor_steer_coeff;

		bool result = processRoadtrainMovement(tractor);

		//restore values to default
		*steering_help = 2.0;
		*is_in_sim_mode = 1;

		return result;
	}

	return processRoadtrainMovement(tractor);
}

bool STrailersPhysFix::getOffsets(int gameVersion) try {
	using namespace Memory::VP;
	using namespace hook::txn;

	if (gameVersion >= 74) {
		funcAddr_4FABB0 = (int)pattern("83 EC 3C 8B 44 24 40 53 56 8B F1 57 D9 86 ? ? ? ? D9 C0 D8 08 8D BE").get_first();

		int call_4FABB0_start = (int)pattern("83 C4 0C 8D 84 24 ? ? ? ? 8D 8C 24 ? ? ? ? 50 51 8B 8B ? ? ? ? E8 ? ? ? ? 8B 8D ? ? ? ? 8D 94 24 ? ? ? ? 8D 84 24 ? ? ? ? 52 50 E8 ? ? ? ? E9 ? ? ? ? ").get_first();
		
		//0x55AFFF in 8.2
		callAddr_4FABB0_tractor = call_4FABB0_start + 25;
		//0x55B01A in 8.2
		callAddr_4FABB0_strailer = call_4FABB0_start + 52;
		
		//0x558EB0 in 8.2
		callAddr_processRDtrains = (int)pattern("E8 ? ? ? ? EB 07 8B CD E8 ? ? ? ? 89 44 24 10").get_first();
		//0x55D91C in 8.2
		funcAddr_processRDtrains = (int)ReadCallFrom(callAddr_processRDtrains);

		//0x55A836 in 8.2
		addr_strailer_detach = (int)pattern("8B 50 04 89 51 04 8B 40 08 89 41 08 DF E0 F6 C4 41 0F 85 ? ? ? ? C7 44 24 ? ? ? ? ? E9 ? ? ? ?").get_first(27);
		//0x674404 in 8.2
		steering_help = *(float**)pattern("8B 86 ? ? ? ? 83 C4 0C 85 C0 D9 13 75 0A D8 0D ? ? ? ? ").get_first(17);

	//7.1 - 7.3
	} else {
		funcAddr_4FABB0 = (int)pattern("83 EC 30 8B 44 24 34 53 55 56 8B F1 57 D9 86 ? ? ? ? D9 C0 D8 08 8D BE").get_first();

		int call_4FABB0_start = (int)pattern("83 C4 0C 89 8C 24 ? ? ? ? 8D 8C 24 ? ? ? ? 8B 50 04 51 8B 8B ? ? ? ? 89 94 24 ? ? ? ? ").get_first();
		std::cout << "call_4FABB0_start       =" << std::hex << call_4FABB0_start << std::endl;

		//0x55AFFF in 8.2
		callAddr_4FABB0_tractor = call_4FABB0_start + 198;
		//0x55B01A in 8.2
		callAddr_4FABB0_strailer = call_4FABB0_start + 225;

		//0x558EB0 in 8.2
		callAddr_processRDtrains = (int)pattern("E8 ? ? ? ? EB 07 8B CD E8 ? ? ? ? 89 44 24 10").get_first();
		//0x55D91C in 8.2
		funcAddr_processRDtrains = (int)ReadCallFrom(callAddr_processRDtrains);

		//0x55A836 in 8.2
		addr_strailer_detach = (int)pattern("8B 50 04 89 51 04 8B 40 08 89 41 08 DF E0 F6 C4 41 0F 85 ? ? ? ? C7 44 24 ? ? ? ? ? E9 ? ? ? ?").get_first(27);
		//0x674404 in 8.2
		steering_help = *(float**)pattern("8B 86 ? ? ? ? 83 C4 0C 85 C0 D9 13 75 0A D8 0D ? ? ? ? ").get_first(17);
	}

	//0x6F6930 in 8.2
	playerVehicle = (int**)GetPlayerVehiclePtr();
	Car_V_offset  = GetCarVOffset(gameVersion);

	std::cout << "funcAddr_4FABB0         =" << std::hex << funcAddr_4FABB0 << std::endl;
	std::cout << "callAddr_4FABB0_tractor =" << callAddr_4FABB0_tractor << std::endl;
	std::cout << "callAddr_4FABB0_strailer=" << callAddr_4FABB0_strailer << std::endl;
	std::cout << "callAddr_processRDtrains=" << callAddr_processRDtrains << std::endl;
	std::cout << "funcAddr_processRDtrains=" << funcAddr_processRDtrains << std::endl;
	std::cout << "addr_strailer_detach    =" << addr_strailer_detach << std::endl;
	std::cout << "steering_help           =" << steering_help << std::endl;
	std::cout << "playerVehicle           =" << playerVehicle << std::endl;

	bool result = funcAddr_4FABB0 && callAddr_4FABB0_tractor && callAddr_4FABB0_strailer && callAddr_processRDtrains && funcAddr_processRDtrains && addr_strailer_detach && steering_help && playerVehicle;
	return result;
}
catch (const hook::txn_exception&)
{
	return false;
}

bool STrailersPhysFix::injectHooks(int gameVersion){
	if (!getOffsets(gameVersion))
		return false;

	tractor_steer_coeff = GetPrivateProfileFloat("STRAILER_PHY", "tractor_steer_coeff", "1.5", ".\\KoTR_ModernPatch.ini");
	tractor_mass_coeff  = GetPrivateProfileFloat("STRAILER_PHY", "tractor_coeff", "1.0", ".\\KoTR_ModernPatch.ini");
	strailer_mass_coeff = GetPrivateProfileFloat("STRAILER_PHY", "strailer_coeff", "3.5", ".\\KoTR_ModernPatch.ini");

	//0x55AFFF, 0x55B01A
	CPatch::RedirectCall(callAddr_4FABB0_tractor, &OnCall4FABB0ForTractor);
	CPatch::RedirectCall(callAddr_4FABB0_strailer, &OnCall4FABB0ForSTrailer);

	//0x55A836
	CPatch::SetInt(addr_strailer_detach, 0); //disable strailer detach on bad roads

	//0x55D91C
	CPatch::RedirectCall(callAddr_processRDtrains, &OnCallProcessRoadtrainMovement);

	return true;
}
