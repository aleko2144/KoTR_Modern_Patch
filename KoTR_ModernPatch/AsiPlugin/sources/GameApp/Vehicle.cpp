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

bool Vehicle::isTrailerLoaded(int* tractor){
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

bool __fastcall Vehicle::processRoadtrainMovement(int *tractor){
	typedef bool (__thiscall * sub_558EB0)(int *tractor);
	return sub_558EB0(0x558EB0)(tractor);
}