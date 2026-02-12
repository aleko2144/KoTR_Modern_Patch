#include "ExtCameraFix.h"
#include "..\Utils\CPatch.h"
#include "..\Utils\CMatrix.h"
#include "..\utils\ConfigUtils.h"

double camera_interp_coeff   = 0.85;
double camera_rotation_coeff = 1.04719753;

int* __fastcall OnCameraInstanceProcess(int* _this, int edx, CMatrix* a2, double interp_coeff){	
	//call original function
	return ((int* (__thiscall*)(int*, CMatrix*, double))0x599FC0)(_this, a2, camera_interp_coeff);
}

void ExtCameraFix::injectHooks() {
	camera_interp_coeff = 1.0 - GetPrivateProfileDouble("EXT_CAMERA", "interp_coeff", "0.15", ".\\KoTR_ModernPatch.ini");
	camera_rotation_coeff = GetPrivateProfileDouble("EXT_CAMERA", "rotation_coeff", "1.04719753", ".\\KoTR_ModernPatch.ini");

	CPatch::SetPointer(0x59A201, &camera_rotation_coeff);
	CPatch::SetPointer(0x59A229, &camera_rotation_coeff);
	CPatch::RedirectCall(0x53677C, &OnCameraInstanceProcess);
}
