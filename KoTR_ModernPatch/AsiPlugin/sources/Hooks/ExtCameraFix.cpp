#include "ExtCameraFix.h"

#include "../Utils/CPatch.h"
#include "../Utils/ConfigUtils.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

double forced_camera_interp_coeff   = 0.85;
double forced_camera_rotation_coeff = 1.04719753;

int funcAddr_CameraProcess; //0x599FC0
int callAddr_CameraProcess; //0x53677C
int* addr_CameraRotCoeff;

int* __fastcall OnCameraInstanceProcess(int* _this, int edx, int* matrix, double interp_coeff){	
	//call original function
	return ((int* (__thiscall*)(int*, int*, double))funcAddr_CameraProcess)(_this, matrix, forced_camera_interp_coeff);
}

bool ExtCameraFix::getOffsets() try {
	using namespace Memory::VP;
	using namespace hook::txn;

	callAddr_CameraProcess = (int)pattern("B9 ? ? ? ? E8 ? ? ? ? D9 06").get_first(5);
	funcAddr_CameraProcess = (int)ReadCallFrom(callAddr_CameraProcess);

	addr_CameraRotCoeff = *(int**)pattern("DD 81 ? ? ? ? DC 0D ? ? ? ? DC 43 70 DD 5B 70").get_first(8);

	bool result = callAddr_CameraProcess && funcAddr_CameraProcess && addr_CameraRotCoeff;
	return result;
}
catch (const hook::txn_exception&)
{
	return false;
}

bool ExtCameraFix::injectHooks() {
	if (!getOffsets())
		return false;


	forced_camera_interp_coeff   = 1.0 - GetPrivateProfileDouble("EXT_CAMERA", "interp_coeff", "0.15", ".\\KoTR_ModernPatch.ini");
	forced_camera_rotation_coeff = GetPrivateProfileDouble("EXT_CAMERA", "rotation_coeff", "1.04719753", ".\\KoTR_ModernPatch.ini");

	CPatch::SetDouble((int)addr_CameraRotCoeff, forced_camera_rotation_coeff);
	CPatch::RedirectCall((int)callAddr_CameraProcess, &OnCameraInstanceProcess);

	return true;
}