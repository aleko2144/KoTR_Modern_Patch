#ifndef PARTICLES_H
#define PARTICLES_H

#include "..\Utils\CVector.h"

typedef struct ParticleColor {
    char B;
    char G;
    char R;
    char A;
};

namespace Particles {
    int* __fastcall InitPointParticles(int* TaskParticleSystem, int* TheGame, const char* a3, int* a4);
    int* __fastcall emitPointParticles(int* _this, int a2, float a3, float a4, float a5, float a6, float a7, float a8, double a9, int* colors, int colorsCount, int a12);
   
    void __cdecl    emitDustParticles(CVector* position, CVector* direction, float a3);

    void __cdecl    emitEngineFlameParicles(CVector* position, CVector* direction, float firePercentage);
    void __cdecl    emitFlameParicles(CVector* position, CVector* direction, float firePercentage);
    void __cdecl    emitBlowParicles(CVector* position, CVector* a2);
    int* __cdecl    emitExhaustSmoke(CVector* position, CVector* direction);

    void __cdecl    emitWhiteBlackSmoke(CVector* position, CVector* direction, float blackSmokePercentage);
    int* __cdecl    emitBlackSmoke(CVector* position, CVector* direction, float scale, float jetSpread);

}

#endif
