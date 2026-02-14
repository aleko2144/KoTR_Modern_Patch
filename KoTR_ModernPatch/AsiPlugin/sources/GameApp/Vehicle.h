#ifndef VEHICLE_H
#define VEHICLE_H

#include "..\Utils\CVector.h"

namespace Vehicle {
	bool			isInSimulatorMode(int* vehicle);
	bool			isTrailerAttached(int *tractor);
	bool			isTrailerLoaded(int* tractor);
	bool			isRoadTrainLoaded(int* tractor);
	float			getMassCurrent(int* vehicle);
	float __fastcall makeVehI(int* veh);
	int   __fastcall make_new_Pos(int* veh);
	bool  __fastcall processRoadtrainMovement(int *tractor);
	void  __fastcall sub_545580(int* veh, float a2, CVector* a3);
	int   __fastcall sub_55CBC0(int* veh);
}

#endif
