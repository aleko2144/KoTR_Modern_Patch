#include "AI.h"

bool __cdecl sub_4CFD50(void *playerID){
	typedef bool * (__cdecl * sub_4CFD50)(void *playerID);
	return sub_4CFD50(0x4CFD50)(playerID);
}

PositionId *__cdecl getPlayerPositionId(PositionId *posID, void *playerID){
	typedef PositionId * (__cdecl * getPlayerPositionId)(PositionId *posID, void *playerID);
	return getPlayerPositionId(0x437790)(posID, playerID);
}

CVector *__cdecl getCoordinates(CVector *vec, PositionId pos){
	typedef CVector * (__cdecl * getCoordinates)(CVector *vec, PositionId pos);
	return getCoordinates(0x4397F0)(vec, pos);
}

int __cdecl getRoadParameters(PositionId pos, LocalRoadParameters * rp){
	typedef int (__cdecl * getRoadParameters)(PositionId pos, LocalRoadParameters * rp);
	return getRoadParameters(0x438FE0)(pos, rp);
}