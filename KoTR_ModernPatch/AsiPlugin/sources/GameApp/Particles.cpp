#include "Particles.h"

int* __fastcall Particles::InitPointParticles(int* TaskParticleSystem, int* TheGame, const char* a3, int* a4) {
    typedef int* (__thiscall* sub_5CF0F0)(int* TaskParticleSystem, int* TheGame, const char* a3, int* a4);
    return sub_5CF0F0(0x5CF0F0)(TaskParticleSystem, TheGame, a3, a4);
}

int* __fastcall Particles::emitPointParticles(int* _this, int a2, float a3, float a4, float a5, float a6, float a7, float a8, double a9, int* colors, int colorsCount, int a12) {
    typedef int* (__thiscall* sub_5CEC00)(int* _this, int a2, float a3, float a4, float a5, float a6, float a7, float a8, double a9, int* colors, int colorsCount, int a12);
    return sub_5CEC00(0x5CEC00)(_this, a2, a3, a4, a5, a6, a7, a8, a9, colors, colorsCount, a12);
}

void __cdecl Particles::emitDustParticles(CVector* position, CVector* direction, float a3){
    typedef void(__cdecl* sub_4BB1B0)(CVector* position, CVector* direction, float a3);
    return sub_4BB1B0(0x4BB1B0)(position, direction, a3);
}

// firePercentage < 0.4 - no particles; firePercentage = 0.4 - white smoke; firePercentage = 1.0 - fire and dark smoke;
void __cdecl Particles::emitEngineFlameParicles(CVector* position, CVector* direction, float firePercentage) {
    typedef void(__cdecl* sub_4BA7C0)(CVector* position, CVector* direction, float firePercentage);
    return sub_4BA7C0(0x4BA7C0)(position, direction, firePercentage);
}

void __cdecl Particles::emitFlameParicles(CVector* position, CVector* direction, float firePercentage) {
    typedef void(__cdecl* sub_4BAA00)(CVector* position, CVector* direction, float firePercentage);
    return sub_4BAA00(0x4BAA00)(position, direction, firePercentage);
}

int* __cdecl Particles::emitExhaustSmoke(CVector* position, CVector* direction) {
    typedef int*(__cdecl* sub_4BADF0)(CVector* position, CVector* direction);
    return sub_4BADF0(0x4BADF0)(position, direction);
}

// blow particles, *(float*)0x69607C should be < 1.0 to work
void __cdecl Particles::emitBlowParicles(CVector* position, CVector* a2) {
    typedef void(__cdecl* sub_4BA470)(CVector* position, CVector* a2);
    return sub_4BA470(0x4BA470)(position, a2);
}

// jetSpread - at zero the jet closes, at high values, on the contrary, it creates a wide plume, as from a comet
int* __cdecl Particles::emitBlackSmoke(CVector * position, CVector * direction, float scale, float jetSpread) {
    typedef int* (__cdecl* sub_4BA980)(CVector* position, CVector* direction, float scale, float jetSpread);
    return sub_4BA980(0x4BA980)(position, direction, scale, jetSpread);
}

// smokePercentage = 0.0 - white smoke ; smokePercentage = 1.0 - black smoke
void __cdecl Particles::emitWhiteBlackSmoke(CVector* position, CVector* direction, float blackSmokePercentage) {
    typedef void(__cdecl* sub_4BAC40)(CVector* position, CVector* direction, float blackSmokePercentage);
    return sub_4BAC40(0x4BAC40)(position, direction, blackSmokePercentage);
}