#include "AICarFix.h"
#include "..\utils\CPatch.h"
#include "..\utils\CVector.h"
#include "..\utils\ConfigUtils.h"

#include "..\GameApp\way.h"
//#include "..\GameApp\AI.h"

#include <iostream>

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

int funcAddr_sub_4CFD50;
int callAddr_sub_4CFD50;

int addr_dbl_dist1;
int addr_dbl_dist2;
int addr_dbl_incr;

int funcAddr_getPlayerPosId;
int funcAddr_getCoordinates;
int funcAddr_getRoadParams;



bool __cdecl sub_4CFD50(void* playerID) {
	typedef bool* (__cdecl* sub_4CFD50)(void* playerID);
	return sub_4CFD50(funcAddr_sub_4CFD50)(playerID);
}

PositionId* __cdecl getPlayerPositionId(PositionId* posID, void* playerID) {
	typedef PositionId* (__cdecl* getPlayerPositionId)(PositionId* posID, void* playerID);
	return getPlayerPositionId(funcAddr_getPlayerPosId)(posID, playerID);
}

CVector* __cdecl getCoordinates(CVector* vec, PositionId pos) {
	typedef CVector* (__cdecl* getCoordinates)(CVector* vec, PositionId pos);
	return getCoordinates(funcAddr_getCoordinates)(vec, pos);
}

int __cdecl getRoadParameters(PositionId pos, LocalRoadParameters* rp) {
	typedef int(__cdecl* getRoadParameters)(PositionId pos, LocalRoadParameters* rp);
	return getRoadParameters(funcAddr_getRoadParams)(pos, rp);
}


PositionId			posId;
LocalRoadParameters roadParams;

double dbl_dist = 150.0, dbl_incr = 30.0;
double new_dist, new_incr;
float  max_wdth;

bool __cdecl OnCall4CFD50(int *playerID){
	bool result = sub_4CFD50(playerID);

	if (result){
		//1. получаем PositionId текущего водителя
		//1. getting player position ID
		getPlayerPositionId(&posId, playerID);

		//2. получаем параметры дороги по PositionId
		//2. getting road parameters by position ID
		getRoadParameters(posId, &roadParams);

		//3. если дорога узкая (2-х полоска), то меняем параметры
		//3. if road is narrow (2 lanes or less) then change values
		if (roadParams.roadWidth < max_wdth){
			dbl_dist = new_dist;
			dbl_incr = new_incr;
		} else {
			//если нет, возвращаем параметры по умолчанию
			//default values
			dbl_dist = 150.0;
			dbl_incr = 30.0;
		}

		//std::cout << roadParams.roadWidth << std::endl;
	}

	return result;
}

bool AICarFix::getOffsets(int gameVersion) try {
	using namespace Memory::VP;
	using namespace hook::txn;

	// 7.4 - 8.2 ONLY
	// In other versions, the way AI cars navigate obstacles is implemented differently, so this patch is not relevant.
	
	// 0x4D4FC2 in 8.2
	callAddr_sub_4CFD50 = (int)pattern("8B 4C 24 14 8B C4 89 08 E8 ? ? ? ? 83 C4 04 84 C0").get_first(8);
	// 0x4CFD50 in 8.2
	funcAddr_sub_4CFD50 = (int)ReadCallFrom(callAddr_sub_4CFD50);

	// dist1=0x4D528E dist2=0x4D4EAF incr=0x4D5284 in 8.2
	addr_dbl_dist1 = (int)pattern("DD 44 24 60 DC 05 ? ? ? ? DD 54 24 60 DC 1D ? ? ? ? DF E0 F6 C4 01").get_first(16);
	addr_dbl_dist2 = (int)pattern("DC 1D ? ? ? ? DF E0 F6 C4 41 0F 84 ? ? ? ? 8D 8B ? ? ? ? 8B 93 ? ? ? ?").get_first(2);
	addr_dbl_incr  = addr_dbl_dist1 - 10;

	// 0x437790 in 8.2
	funcAddr_getPlayerPosId = (int)pattern("8B 95 ? ? ? ? 51 8B C4 8B 8A ? ? ? ? 8D 94 24 ? ? ? ? 52 89 08 E8 ? ? ? ? B9 ? ? ? ? 8B F0 8D BC 24 ? ? ? ? 83 C4 08").get_first(25);
	funcAddr_getPlayerPosId = (int)ReadCallFrom(funcAddr_getPlayerPosId);
	// 0x4397F0 in 8.2
	funcAddr_getCoordinates = (int)pattern("83 C4 04 B9 ? ? ? ? 8D B4 24 ? ? ? ? 8B FC 8D 54 24 68 F3 A5 52 E8 ? ? ? ?").get_first(24);
	funcAddr_getCoordinates = (int)ReadCallFrom(funcAddr_getCoordinates);
	// 0x438FE0 in 8.2
	funcAddr_getRoadParams = (int)pattern("8D 8C 24 ? ? ? ? 8D 74 24 70 51 B9 ? ? ? ? 83 EC 20 8B FC F3 A5 E8 ? ? ? ?").get_first(24);
	funcAddr_getRoadParams = (int)ReadCallFrom(funcAddr_getRoadParams);

	/*
	std::cout << "callAddr_sub_4CFD50=" << std::hex << callAddr_sub_4CFD50 << std::endl;
	std::cout << "funcAddr_sub_4CFD50=" << funcAddr_sub_4CFD50 << std::endl;

	std::cout << "addr_dbl_dist1=" << addr_dbl_dist1 << " 2=" << addr_dbl_dist2 << " incr=" << addr_dbl_incr << std::endl;

	std::cout << "getPlayerPosId=" << funcAddr_getPlayerPosId << std::endl;
	std::cout << "getCoordinates=" << funcAddr_getCoordinates << std::endl;
	std::cout << "getRoadParams =" << funcAddr_getRoadParams  << std::endl;
	*/

	bool result = funcAddr_sub_4CFD50 && callAddr_sub_4CFD50 && addr_dbl_dist1 && addr_dbl_dist2 && addr_dbl_incr && funcAddr_getPlayerPosId && funcAddr_getCoordinates && funcAddr_getRoadParams;
	return result;
}
catch (const hook::txn_exception&)
{
	return false;
}

//TO DO: исправить езду задним ходом AI-автомобилей по встречной полосе
//TO DO: fix jerky reverse movement of AI cars in the oncoming lane when entering the observer's line of sight

//в общем, на узких дорогах надо ограничивать зону сканирования препятствий соседней полосой, чтобы AI-машина не могла видеть встречное движение
//on narrow roads, it is necessary to somehow dynamically limit the obstacle scanning zone to the adjacent lane so that the AI-car cannot see oncoming traffic
bool AICarFix::injectHooks(int gameVersion){
	if (!getOffsets(gameVersion))
		return false;

	//return true;

	new_dist = GetPrivateProfileDouble("AI_CAR", "loop_dist", "150.0", ".\\KoTR_ModernPatch.ini");
	new_incr = GetPrivateProfileDouble("AI_CAR", "loop_incr", "30.0",  ".\\KoTR_ModernPatch.ini");
	max_wdth = GetPrivateProfileFloat ("AI_CAR", "max_width", "10.0",  ".\\KoTR_ModernPatch.ini");

	CPatch::SetPointer(addr_dbl_dist1, &dbl_dist);
	CPatch::SetPointer(addr_dbl_dist2, &dbl_dist);
	CPatch::SetPointer(addr_dbl_incr, &dbl_incr);
	
	//hook function before do/while cycle
	CPatch::RedirectCall(callAddr_sub_4CFD50, &OnCall4CFD50);

	//std::cout << "roadParamsAddr=" << std::hex << &roadParams << std::endl;
	return true;
}
