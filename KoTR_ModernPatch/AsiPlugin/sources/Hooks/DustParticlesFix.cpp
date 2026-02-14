#include "DustParticlesFix.h"
#include "..\Utils\CPatch.h"
#include "..\Utils\CVector.h"
#include "..\Utils\CMatrix.h"

#include "..\GameApp\Particles.h"

bool call_dust_emitters = false;

//TO DO: rewrite this function
void processDustParticles(int* vehicle, bool emitFromCenterOnly){
	if (vehicle < (int*)0x100)
		return;

	int *Car_V = (int *)(vehicle[5400]);

	if (Car_V < (int*)0x100)
		return;

	int wheelsCount = *(int *)((char*)vehicle + 0x28B8);

	if (!wheelsCount)
		return;

	if (wheelsCount > 4)
		wheelsCount = 4;

	CVector* wheelsPos = (CVector *)(((char*)Car_V) + 0x64);
	CVector* velocityVector = (CVector *)(((char*)Car_V) + 0x40);

	CMatrix vehicle_mtx;

	memcpy(&vehicle_mtx, (const void *)(((char*)Car_V) + 0x10), 0x30u);

	CVector vehiclePosition = vehicle_mtx.pos;
	CVector vehicleVelocity = velocityVector->normalize();
	CVector particlesDir;
	CVector axisDir;

	float* a3 = (float *)((char*)vehicle + 0x27F0);

	particlesDir.x = vehicleVelocity.y;
	particlesDir.y = -vehicleVelocity.x;
	particlesDir.z = vehicleVelocity.z;

	//cout << "pos=" << vehiclePos.x << " " << vehiclePos.y << " " << vehiclePos.z << endl;
	//cout << "dir=" << particlesDir.x << " " << particlesDir.y << " " << particlesDir.z << endl;

	*(float*)0x694850 = 0.5; //dust particles time?

	//particles from car center
	Particles::emitDustParticles(&vehiclePosition, &particlesDir, a3[0]);

	//all wheels
	if (!emitFromCenterOnly){
		for (int i = 0; i < wheelsCount; i++){
			Particles::emitDustParticles(&wheelsPos[i], &particlesDir, a3[i]);
		}
	}
	int trailerState = *(int *)(((char*)Car_V) + 0x2778);
	if (trailerState != 1)
		return;

	int* trailerPtr = (int *)vehicle[5470];
	if (trailerPtr)
		processDustParticles(trailerPtr, true);
}

void onProcessVehicleParticles(int *_vehicle, int *EDX){
	//if wrong pointer
	if (_vehicle < (int*)0x700000){
		if (EDX < (int*)0x700000){
			return;
		} else {
			_vehicle = EDX;
		}
	}

	call_dust_emitters = false;

	//call original function
	((int(__thiscall *)(int*))0x551900)(_vehicle);

	if (call_dust_emitters){
		processDustParticles(_vehicle, false);
	}
}

void __cdecl onDustEmitCall(float* position, float* direction, float a3){
	call_dust_emitters = true;
	return;
}

void DustParticlesFix::injectHooks(){
	//disable dust particles from original function
	CPatch::RedirectCall(0x551F5C, &onDustEmitCall);
	CPatch::RedirectCall(0x551D99, &onDustEmitCall);

	//hook vehicle particle func calls
	CPatch::RedirectCall(0x54D79C, &onProcessVehicleParticles);
	CPatch::RedirectCall(0x55065F, &onProcessVehicleParticles);
}