#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "CPatch.h"

#include "dllmain.h"

using namespace std;

//internal classes
class CVector {
public:
	float x;
	float y;
	float z;
	CVector(){
		x = 0;
		y = 0;
		z = 0;
	}
	void setFromArgs(float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}
	void setFromPtr(float* ptr){
		x = ptr[0];
		y = ptr[1];
		z = ptr[2];
	}
	long double getLength(){
		return sqrt(x * x + y * y + z * z);
	}
	CVector CVector::normalize(){
		CVector result;
		float coeff = (1.0 / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
		result.x = this->x * coeff;
		result.y = this->y * coeff;
		result.z = this->z * coeff;
		return result;
	}
	CVector CVector::operator+ (const CVector& rhs){
		CVector result;
		result.x = this->x + rhs.x;
		result.y = this->y + rhs.y;
		result.z = this->z + rhs.z;
		return result;
	}
	CVector CVector::operator- (const CVector& rhs){
		CVector result;
		result.x = this->x - rhs.x;
		result.y = this->y - rhs.y;
		result.z = this->z - rhs.z;
		return result;
	}
	CVector CVector::operator* (const long double& rhs){
		CVector result;
		result.x = this->x * rhs;
		result.y = this->y * rhs;
		result.z = this->z * rhs;
		return result;
	}
	CVector CVector::operator* (const CVector& rhs){
		CVector result;
		result.x = this->x * rhs.x;
		result.y = this->y * rhs.y;
		result.z = this->z * rhs.z;
		return result;

	}
};

class CMatrix {
public:
	CVector right;
	CVector top;
	CVector at;
	CVector pos;
	CMatrix(){
		right.x = 0;
		right.y = 0;
		right.z = 0;

		top.x = 0;
		top.y = 0;
		top.z = 0;

		at.x = 0;
		at.y = 0;
		at.z = 0;

		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
	}
	CVector GetRadians(){
		CVector result;

		double cy = sqrt(this->at.z*this->at.z + this->at.x*this->at.x);

		if (cy > 16*FLT_EPSILON)
		{
			result.z = (float) atan2(this->right.y, this->top.y);
			result.x = (float) atan2(- this->at.y, (float) cy);
			result.y = (float) atan2(this->at.x, this->at.z);
		}
		else
		{
			result.z = (float) atan2(- this->top.x, this->right.x);
			result.x = (float) atan2(- this->at.y, (float) cy);
			result.y = 0;
		}

		return result;
	}
};

/////

bool call_dust_emitters = false;

//particles functions
void __cdecl sub_4BB1B0(float* position, float* direction, float a3){
	typedef void (__cdecl * sub_4BB1B0)(float* position, float* direction, float a3);
	return sub_4BB1B0(0x4BB1B0)(position, direction, a3);
}

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
	//Car_V + 0x64 - wheel col vectors

	//cout << "w0=" << wheelsPos[0].x << " " << wheelsPos[0].y << " " << wheelsPos[0].z << endl;
	//cout << "w3=" << wheelsPos[3].x << " " << wheelsPos[3].y << " " << wheelsPos[3].z << endl;
	//cout << endl;

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
	sub_4BB1B0((float*)&vehiclePosition, (float*)&particlesDir, a3[0]);

	//all wheels
	if (!emitFromCenterOnly){
		for (int i = 0; i < wheelsCount; i++){
			sub_4BB1B0((float*)&wheelsPos[i], (float*)&particlesDir, a3[i]);
		}
	}
	int trailerState = *(int *)(((char*)Car_V) + 0x2778);
	if (trailerState != 1)
		return;

	int* trailerPtr = (int *)vehicle[5470];
	if (trailerPtr)
		processDustParticles(trailerPtr, true);
}

//vehicle::process_emitters
void sub_551900(int *_vehicle){
	typedef void (__fastcall * sub_551900)(int *_vehicle);
	return sub_551900(0x551900)(_vehicle);
}

void sub_551900_hook(int *_vehicle, int *EDX){
	//if wrong pointer
	if (_vehicle < (int*)0x700000){
		if (EDX < (int*)0x700000){
			return;
		} else {
			_vehicle = EDX;
		}
	}

	call_dust_emitters = false;
	sub_551900(_vehicle);
	if (call_dust_emitters){
		processDustParticles(_vehicle, false);
	}
}

void __cdecl sub_4BB1B0_hooks(float* position, float* direction, float a3){
	call_dust_emitters = true;
	return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileIntA("mod", "Enabled", 0, ".\\KoTR_DustPatch.ini"))
				return TRUE;

			//disable dust particles from original function
			CPatch::RedirectCall(0x551F5C, sub_4BB1B0_hooks);
			CPatch::RedirectCall(0x551D99, sub_4BB1B0_hooks);

			//hook vehicle particle func calls
			CPatch::RedirectCall(0x54D79C, sub_551900_hook);
			CPatch::RedirectCall(0x55065F, sub_551900_hook);

			cout << "DustPatch v0.03 (03.11.2025) started." << endl;

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}