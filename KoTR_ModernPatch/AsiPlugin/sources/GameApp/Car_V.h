#ifndef CAR_V_H
#define CAR_V_H

#include "..\Utils\CVector.h"

namespace Car_V {
	int	     run(int* Car_V);
	int      runSecondCar(int* Car_V);
	char     make_frs(void *carV, int a2);
	bool     isInSimulatorMode(void *carV);
	bool     isTrailerAttached(void *carV);
	bool     isPlayerCarV(void *carV);
	int*     getVehiclePointer(void *carV);

	void     SetVelocity(void* carV, CVector* a2);
	void     SetAngularVelocity(void* carV, CVector* a2);
	
	int		 sub_4FABB0(int* carV, CVector* a2, CVector* a3);
	CVector* sub_4F3980(int* carV, CVector* a2, CVector* a3);
}

double __cdecl sub_4F4DF0(int mode, float steer, float speed_ms);

#endif
