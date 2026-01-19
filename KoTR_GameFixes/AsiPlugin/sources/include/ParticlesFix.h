#ifndef PARTICLES_FIX_H
#define PARTICLES_FIX_H

namespace ParticlesFix {
	void __cdecl emitDustParticles(float* position, float* direction, float a3);
	void		 processDustParticles(int* vehicle, bool emitFromCenterOnly);
	void		 onProcessVehicleParticles(int *_vehicle, int *EDX);
	void __cdecl onDustEmitCall(float* position, float* direction, float a3);

	void injectHooks();
}

#endif
