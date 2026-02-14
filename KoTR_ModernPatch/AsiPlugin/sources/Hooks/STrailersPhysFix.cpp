#include "STrailersPhysFix.h"
#include "..\utils\CPatch.h"
#include "..\utils\ConfigUtils.h"

#include "..\GameApp\Car_V.h"
#include "..\GameApp\Vehicle.h"

//#include <iostream>

int __fastcall OnCall4FABB0ForTractor(int* carV, int edx, CVector* a2, CVector* a3) {
	int* unk_is_trailer_attached = (int*)((char*)carV + 0x2778);
	*unk_is_trailer_attached = 0;

	return 0; 
}

int *is_in_sim_mode;
int __fastcall OnCall4FABB0ForSTrailer(int* carV, int edx, CVector* a2, CVector* a3) {
	//std::cout << "a2=" << a2->x << " " << a2->y << " " << a2->z << std::endl;
	//std::cout << "a3=" << a3->x << " " << a3->y << " " << a3->z << std::endl;

	CVector* trc_field_14C = (CVector*)(((char*)carV) + 0x2370);
	CVector* trc_field_194 = (CVector*)(((char*)carV) + 0x23B8);
	CVector* trc_techScaleVectorI = (CVector*)(((char*)carV) + 0x1F48);
	float* trc_mass = (float*)(((char*)carV) + 0x2640);

	CVector::FloatDivide(a2, trc_field_14C, *trc_mass);
	CVector::LinearDivide(a3, trc_field_194, trc_techScaleVectorI);

	/*
	if (*is_in_sim_mode) {
		a2->x *= 10.0;
		a2->y *= 10.0;
		a2->z *= 10.0;
	} else {
		a2->x *= 3.55;
		a2->y *= 3.55;
		a2->z *= 3.55;
	}
	*/

	a2->x *= 3.55;
	a2->y *= 3.55;
	a2->z *= 3.55;

	return Car_V::sub_4FABB0(carV, a2, a3);
}

bool __fastcall OnCallProcessRoadtrainMovement(int* tractor) {
	int* carV = (int*)(tractor[5400]);

	bool is_player_car = Car_V::isPlayerCarV(carV);
	is_in_sim_mode = (int*)(((char*)carV) + 10088);

	// "Crutch Code Technologies, LTD."
	// 
	//Since I still haven't found a good solution for the poor steering of road trains in simulator mode,
	//I switch the truck to arcade mode, and adjusting the trailer's behavior to imitate something similar to a simulator.

	if (is_player_car && *is_in_sim_mode) {
		//disable simulator mode and reduce arcade steering coeff
		*is_in_sim_mode = 0;
		*(float*)0x674404 = 1.5;

		bool result = Vehicle::processRoadtrainMovement(tractor);

		//restore values
		*(float*)0x674404 = 2.0;
		*is_in_sim_mode = 1;

		return result;
	}

	return Vehicle::processRoadtrainMovement(tractor);
}

void STrailersPhysFix::injectHooks(){
	CPatch::RedirectCall(0x55AFFF, &OnCall4FABB0ForTractor);
	CPatch::RedirectCall(0x55B01A, &OnCall4FABB0ForSTrailer);

	CPatch::SetInt(0x55A836, 0); //disable strailer detach on bad roads

	CPatch::RedirectCall(0x55D91C, &OnCallProcessRoadtrainMovement);
}
