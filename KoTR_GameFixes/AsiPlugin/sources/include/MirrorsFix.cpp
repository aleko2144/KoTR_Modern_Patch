#include "MirrorsFix.h"
#include "Utils\CPatch.h"
#include <cmath>

/*
void MirrorsFix::sub_595230(int *_mirrors){
	typedef void (__fastcall * sub_595230)(int *_mirrors);
	return sub_595230(0x595230)(_mirrors);
}
*/

void __fastcall MirrorsFix::ProcessMirrors(int *_this, int* EDX){
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

	//((int(__thiscall *)(void *, CMatrix*, double))0x599FC0)(_this, mat, someParam); 
	//((void(*)(int*))0x51FF90)(vehicle);
	//MirrorsFix::sub_595230(_this);

	*isMirrorsProcessed = temp;

	return;
}

void MirrorsFix::injectHooks(){
	CPatch::SetPointer(0x650A28, &MirrorsFix::ProcessMirrors);
}