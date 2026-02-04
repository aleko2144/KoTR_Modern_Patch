#ifndef CAR_V_H
#define CAR_V_H

namespace Car_V {
	char __fastcall make_frs(void *carV, int a2);
	bool			isInSimulatorMode(void *carV);
	bool			isTrailerAttached(void *carV);
	bool			isPlayerCarV(void *carV);
	int*			getVehiclePointer(void *carV);
}

double __cdecl sub_4F4DF0(int mode, float steer, float speed_ms);

#endif
