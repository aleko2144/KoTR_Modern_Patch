#include "AICarFix.h"
#include "..\utils\CPatch.h"
#include "..\utils\CVector.h"
#include "..\utils\ConfigUtils.h"

#include "..\GameApp\way.h"
#include "..\GameApp\AI.h"

#include <iostream>

PositionId			posId;
LocalRoadParameters roadParams;

double dbl_dist = 150.0, dbl_incr = 30.0;
double new_dist, new_incr;

bool __cdecl sub_4CFD50h(int *playerID){
	bool result = sub_4CFD50(playerID);

	if (result){
		//1. getting player position ID
		getPlayerPositionId(&posId, playerID);
		//2. getting road parameters by position ID
		getRoadParameters(posId, &roadParams);
		//3. if road is narrow (2 lanes or less) then change values
		if (roadParams.roadWidth < 10.0){
			dbl_dist = new_dist;
			dbl_incr = new_incr;
		} else {
			//default values
			dbl_dist = 150.0;
			dbl_incr = 30.0;
		}

		//std::cout << roadParams.roadWidth << std::endl;
	}

	return result;
}

void AICarFix::injectHooks(){
	new_dist = GetPrivateProfileDouble("AI_CAR", "loop_dist", "150.0", ".\\KoTR_ModernPatch.ini");
	new_incr = GetPrivateProfileDouble("AI_CAR", "loop_incr", "30.0", ".\\KoTR_ModernPatch.ini");

	CPatch::SetPointer(0x4D528E, &dbl_dist);
	CPatch::SetPointer(0x4D4EAF, &dbl_dist);
	CPatch::SetPointer(0x4D5284, &dbl_incr);
	
	//hook function before do/while cycle
	CPatch::RedirectCall(0x4D4FC2, &sub_4CFD50h);

	//std::cout << "roadParamsAddr=" << std::hex << &roadParams << std::endl;
}