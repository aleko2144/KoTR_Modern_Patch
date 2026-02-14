#include "Car_V.h"

int Car_V::run(int* Car_V) {
	typedef int(__thiscall* sub_4FEF70)(int* Car_V);
	return sub_4FEF70(0x4FEF70)(Car_V);
}

int Car_V::runSecondCar(int* Car_V) {
	typedef int(__thiscall* sub_4D6590)(int* Car_V);
	return sub_4D6590(0x4D6590)(Car_V);
}

char Car_V::make_frs(void *carV, int a2){
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

double sub_4F4DF0(int mode, float steer, float speed_ms){
	typedef double (__cdecl * sub_4F4DF0)(int mode, float steer, float speed_ms);
	return sub_4F4DF0(0x4F4DF0)(mode, steer, speed_ms);
}

void Car_V::SetVelocity(void* carV, CVector* a2) {
	typedef void (__thiscall* sub_4F1E60)(void* carV, CVector* a2);
	return sub_4F1E60(0x4F1E60)(carV, a2);
}

void Car_V::SetAngularVelocity(void* carV, CVector* a2) {
	typedef void(__thiscall* sub_4F1F80)(void* carV, CVector* a2);
	return sub_4F1F80(0x4F1F80)(carV, a2);
}

int Car_V::sub_4FABB0(int* carV, CVector* a2, CVector* a3) {
	typedef int(__thiscall* sub_4FABB0)(void* carV, CVector* a2, CVector* a3);
	return sub_4FABB0(0x4FABB0)(carV, a2, a3);
}

CVector* Car_V::sub_4F3980(int* carV, CVector* a2, CVector* a3) {
	typedef CVector*(__thiscall* sub_4F3980)(void* carV, CVector* a2, CVector* a3);
	return sub_4F3980(0x4F3980)(carV, a2, a3);
}