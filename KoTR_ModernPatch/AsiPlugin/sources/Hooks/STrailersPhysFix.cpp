#include "STrailersPhysFix.h"
#include "..\utils\CPatch.h"
#include "..\utils\ConfigUtils.h"

#include "..\GameApp\Car_V.h"
#include "..\GameApp\Vehicle.h"

float tractor_steer_coeff = 1.5;
float tractor_mass_coeff  = 1.0;
float strailer_mass_coeff = 3.5;

int __fastcall OnCall4FABB0ForTractor(int* carV, int edx, CVector* a2, CVector* a3) {
	a2->x *= tractor_mass_coeff;
	a2->y *= tractor_mass_coeff;
	a2->z *= tractor_mass_coeff;

	return Car_V::sub_4FABB0(carV, a2, a3);
	/*
	int* unk_is_trailer_attached = (int*)((char*)carV + 0x2778);
	*unk_is_trailer_attached = 0;

	return 0;
	*/
}

int __fastcall OnCall4FABB0ForSTrailer(int* carV, int edx, CVector* a2, CVector* a3) {
	a2->x *= strailer_mass_coeff;
	a2->y *= strailer_mass_coeff;
	a2->z *= strailer_mass_coeff;

	return Car_V::sub_4FABB0(carV, a2, a3);
}

bool __fastcall OnCallProcessRoadtrainMovement(int* tractor) {
	int* carV = (int*)(tractor[5400]);

	bool is_player_car = Car_V::isPlayerCarV(carV);
	int* is_in_sim_mode = (int*)(((char*)carV) + 10088);

	// "Crutch Code Technologies, LTD."
	// 
	//Since I still haven't found a good solution for the poor steering of road trains in simulator mode,
	//I switch the truck to arcade mode, and adjusting the trailer's behavior to imitate something similar to a simulator.

	if (is_player_car && *is_in_sim_mode) {
		//disable simulator mode and reduce arcade steering coeff
		*is_in_sim_mode = 0;
		*(float*)0x674404 = tractor_steer_coeff;

		bool result = Vehicle::processRoadtrainMovement(tractor);

		//restore values to default
		*(float*)0x674404 = 2.0;
		*is_in_sim_mode = 1;

		return result;
	}

	return Vehicle::processRoadtrainMovement(tractor);
}

void STrailersPhysFix::injectHooks(){
	tractor_steer_coeff = GetPrivateProfileFloat("STRAILER_PHY", "tractor_steer_coeff", "1.5", ".\\KoTR_ModernPatch.ini");
	tractor_mass_coeff  = GetPrivateProfileFloat("STRAILER_PHY", "tractor_coeff", "1.0", ".\\KoTR_ModernPatch.ini");
	strailer_mass_coeff = GetPrivateProfileFloat("STRAILER_PHY", "strailer_coeff", "3.5", ".\\KoTR_ModernPatch.ini");

	CPatch::RedirectCall(0x55AFFF, &OnCall4FABB0ForTractor);
	CPatch::RedirectCall(0x55B01A, &OnCall4FABB0ForSTrailer);

	CPatch::SetInt(0x55A836, 0); //disable strailer detach on bad roads

	CPatch::RedirectCall(0x55D91C, &OnCallProcessRoadtrainMovement);
}
