#include "MirrorsFix.h"
#include "..\Utils\CPatch.h"
#include "..\Utils\CMatrix.h"
#include <cmath>

void __fastcall ProcessMirrors(int *_this, int* EDX){
	int* isMirrorsProcessed = (int*)0x67E178;
	int temp = *isMirrorsProcessed;

	//camera min angle when side mirrors always disable;
	float camRotMin = 0.2;
	//interior camera rotation
	float cameraRot = *(float*)0x696D30;

	if (abs(cameraRot) < camRotMin)
		*isMirrorsProcessed = 0;

	//call original function
	((int(__thiscall *)(int*))0x595230)(_this);

	*isMirrorsProcessed = temp;

	return;
}

int* __fastcall OnCameraInstanceReset(int* _this, int edx) {
	int xres = *(int*)0x69688C;
	int yres = *(int*)0x696890;

	float aspect_rev = (float)yres / (float)xres;

	//if 16:9 then do things with matrix
	if (aspect_rev < 0.7) {
		CMatrix* cabineMtx  = (CMatrix*)((char*)*(int*)0x6D2098 + 0x208);
		CMatrix* mirrorsMtx = (CMatrix*)((char*)*(int*)0x6D2098 + 0x238);

		float addVal_y =  0.2;
		float addVal_z = -0.2;

		if (cabineMtx->pos.z < 1.0) {
			addVal_y =  0.3;
			addVal_z = -0.4;
		}
		//change mirrors matrix position if game running in 16x9
		mirrorsMtx->pos.y += addVal_y;
		mirrorsMtx->pos.z += addVal_z;
	}

	//call original function
	return ((int* (__thiscall*)(int*))0x598E00)(_this);
}

void MirrorsFix::injectHooks(){
	CPatch::SetPointer(0x650A28, &ProcessMirrors);
	CPatch::RedirectCall(0x531FEB, &OnCameraInstanceReset);
}
