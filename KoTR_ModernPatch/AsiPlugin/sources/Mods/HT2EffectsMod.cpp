#include "HT2EffectsMod.h"

#include "..\Utils\CPatch.h"

#include "..\GameApp\Task.h"
#include "..\GameApp\Vehicle.h"
#include "..\GameApp\Particles.h"
#include "..\GameApp\GameResources.h"

//#include "..\Utils\CVector.h"
//#include "..\Utils\CMatrix.h"

#include <iostream>

bool disable_splash_emit;

void __fastcall CreateTaskWaterParticleSystem(float a1, float a2, float a3, float a4, float a5, float a6, double a7) {
    int* v8; // eax
    int* v9; // esi
    int* v10; // eax
    int* v12; // ecx

    int v13; // eax
    int v15; // [esp+20h] [ebp-1Ch]
    int v16; // [esp+24h] [ebp-18h]
    int v17; // [esp+28h] [ebp-14h]
    int v18; // [esp+2Ch] [ebp-10h]
    int v19; // [esp+38h] [ebp-4h]

    v8 = (int*)new_internal(0xA0u);
    v9 = v8;
    v19 = 0;
    if (v8)
    {
        //Particles::InitPointParticles(v8, *(int**)0x696244, "zero", 0);
        Particles::InitPointParticles(v8, *(int**)0x696244, "shadow", *(int**)0x696250);

        *v9   = (int)(int*)0x64FEEC;
        v9[8] = (int)(int*)0x64FEA0;

        ParticleColor splashesColors[2];

        splashesColors[0].R = 180;
        splashesColors[0].G = 180;
        splashesColors[0].B = 180;
        splashesColors[0].A = 255;

        splashesColors[1].R = 255;
        splashesColors[1].G = 255;
        splashesColors[1].B = 255;
        splashesColors[1].A = 128;

        v10 = (int*)new_internal(0x20u);

        //LOBYTE(v19) = 2;
        //v19 = 2;
        v19 = (v19 & ~0xFF) | 2;

        if (v10)
        {
            
            //            sub_5CEC00(v10, 10, a1, a2, a3, a4, a5, a6, a7 * 0.1428571428571428, v11, 2, 0); //gravel particles
            v9[24] = (int)Particles::emitPointParticles(v10, 5, a1, a2, a3, a4, a5, a6, a7, (int*)&splashesColors, 2, 0);
          //v9[24] = (int)sub_5CEC00(v10, 50, a1, a2, a3, a4, a5, a6, a7, v11, 4, 1); //5.5 particles
            v12 = v9;
        }
        else
        {
            v12 = v9;
            v9[24] = 0;
        }
    }
    else
    {
        v12 = 0;
    }
    v19 = -1;
    Task::ActivateTask(v12, 1);
}



void __cdecl doSplashParticles(float x1, float y1, float z1, float x2, float y2, float z2, double a7, int a8) {

    if (disable_splash_emit)
        return;

    float sndVolume;

    int* splashSound = *(int**)0x6F340C;
    double* dbl_6F34D8 = (double*)0x6F34D8;

    int* taskWeather = *(int**)0x6F33CC;
    float reflectionCoeff = *(float*)((char*)taskWeather + 0x218); //0x214 (532) in 5.5?


    double v9, v10;

    if (reflectionCoeff <= 0.2 || *(int*)0x6F33E0)
    {
        if (!(a8 & 1) && (a8 & 2)) {
            *dbl_6F34D8 = *dbl_6F34D8 * 0.95;
            return;
        }
    }

    if (a7 > 5.0) {
        v9 = sin(sin(y1 * 0.25) + x1 * 0.33333334);
        v10 = sin(sin(x1 * 0.25) + y1 * 0.33333334);
        if (v9 > 0.0 && v10 > 0.0 || a8 & 1)
        {
            double v19 = sqrt(a7);
            double v20 = v10 + v9;
            double a9 = reflectionCoeff * v20 * v19 * 0.1111111111111111;


            //water surface particles
            if (a8 & 1)
            {
                a9 = v19 * 0.3333333333333333;
                CreateTaskWaterParticleSystem(x1, y1, z1, x2, y2, z2, a9);

            //wet asphalt surface particles
            } else {
                CreateTaskWaterParticleSystem(x1, y1, z1, x2, y2, z2, a9);
            }

            //in the original game, the second block of code is executed without else, but in 8.2 this
            //causes crash with "Not enough blocks in user-defined heap for Task's activation(null)" error.

            if (a8 & 2)
            {
                double v15 = a7 * 0.05;

                if (a8 & 1)
                    *dbl_6F34D8 = v15 * 0.05 + *dbl_6F34D8 * 0.95;
                else
                    *dbl_6F34D8 = v15 * v20 * 0.1666666666666667;

                sndVolume = *dbl_6F34D8;
                playEffectSound2D(splashSound, sndVolume, sndVolume, 1);
            }
        }
        return;
    }
}

int __fastcall OnSTrailerMakeNewPos(int* veh, int edx) {
    //disable emitting splashes from semitrailer, because this makes game crash
    disable_splash_emit = true;
    int result = Vehicle::make_new_Pos(veh);
    disable_splash_emit = false;

    return result;
}

void HT2EffectsMod::injectHooks() {
    CPatch::SetPointer(0x64CB48, &OnSTrailerMakeNewPos);
    CPatch::RedirectCall(0x54C2F9, &doSplashParticles);
}