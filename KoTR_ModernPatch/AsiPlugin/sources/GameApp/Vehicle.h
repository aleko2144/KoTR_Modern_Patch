#ifndef VEHICLE_H
#define VEHICLE_H

namespace Vehicle {
	bool			isInSimulatorMode(int* vehicle);
	bool			isTrailerAttached(int *tractor);
	bool			isTrailerLoaded(int* tractor);
	float			getMassCurrent(int* vehicle);
	bool __fastcall processRoadtrainMovement(int *tractor);
}

#endif
