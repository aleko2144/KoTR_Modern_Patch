#include "Car_V.h"
#include "Vehicle.h"

bool Vehicle::isInSimulatorMode(int* vehicle){
	int* carV = (int*)(vehicle[5400]);
	if (!*carV)
		return false;

	return Car_V::isInSimulatorMode(carV);
}

bool Vehicle::isTrailerAttached(int *tractor){
	return (int *)tractor[5470] != 0;
}

float Vehicle::getMassCurrent(int* vehicle){
	if (!*vehicle)
		return 0;

	return *(float*)((char*)vehicle + 0x19C);
}

bool Vehicle::isRoadTrainLoaded(int* tractor){
	if (!tractor)
		return false;

	int *trailer = (int *)tractor[5470];

	if (!trailer)
		return false;

	float current_mass = *(float*)((char*)trailer + 0x19C);
	float empty_mass   = *(float*)((char*)trailer + 0x2550);
	float body_mass    = *(float*)((char*)trailer + 0x2584);

	bool result = current_mass > (empty_mass + body_mass);

	//std::cout << "current_mass=" << current_mass << " empty=" << empty_mass << " body=" << body_mass << std::endl;
	//std::cout << "r=" << result << std::endl;

	return result;
}

bool Vehicle::isTrailerLoaded(int* trailer) {
	if (!trailer)
		return false;

	float current_mass = *(float*)((char*)trailer + 0x19C);
	float empty_mass = *(float*)((char*)trailer + 0x2550);
	float body_mass = *(float*)((char*)trailer + 0x2584);

	bool result = current_mass > (empty_mass + body_mass);

	return result;
}

bool __fastcall Vehicle::processRoadtrainMovement(int *tractor){
	typedef bool (__thiscall * sub_558EB0)(int *tractor);
	return sub_558EB0(0x558EB0)(tractor);
}

float __fastcall Vehicle::makeVehI(int* veh) {
	typedef float(__thiscall* sub_542530)(int* veh);
	return sub_542530(0x542530)(veh);
}

void __fastcall Vehicle::sub_545580(int* veh, float a2, CVector* a3) {
	typedef void(__thiscall* sub_545580)(int* veh, float a2, CVector* a3);
	return sub_545580(0x545580)(veh, a2, a3);
}

int __fastcall Vehicle::sub_55CBC0(int* veh) {
	typedef int(__thiscall* sub_55CBC0)(int* veh);
	return sub_55CBC0(0x55CBC0)(veh);
}

int __fastcall Vehicle::make_new_Pos(int* veh) {
	typedef int(__thiscall* sub_54A310)(int* veh);
	return sub_54A310(0x54A310)(veh);
}