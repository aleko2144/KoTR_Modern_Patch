#include "Car_V.h"

char __fastcall Car_V::make_frs(void *carV, int a2){
	typedef char (__thiscall * sub_4F4FF0)(void *carV, int a2);
	return sub_4F4FF0(0x4F4FF0)(carV, a2);
}

bool Car_V::isPlayerCarV(void *carV){
	int* playerVehicle = (int*)(*(int*)0x6F6930);
	if (!playerVehicle)
		return false;

	int* playerCar_V   = (int *)(playerVehicle[5400]);
	if (!playerCar_V)
		return false;

	return carV == playerCar_V;
}

bool Car_V::isInSimulatorMode(void *carV){
	return *(int*)(((char*)carV) + 10088);
}

bool Car_V::isTrailerAttached(void *carV){
	return *(bool*)(((char*)carV) + 0x2778);
}

int* Car_V::getVehiclePointer(void *carV){
	return (int*)((char*)carV + 0x40C0);
}

double __cdecl sub_4F4DF0(int mode, float steer, float speed_ms){
	typedef double (__cdecl * sub_4F4DF0)(int mode, float steer, float speed_ms);
	return sub_4F4DF0(0x4F4DF0)(mode, steer, speed_ms);
}