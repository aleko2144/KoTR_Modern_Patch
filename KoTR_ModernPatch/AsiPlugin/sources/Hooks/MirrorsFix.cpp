#include "MirrorsFix.h"
#include "../Utils/CPatch.h"
#include "../Utils/CMatrix.h"
#include "../Utils/ExeUtils.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

#include "../GameApp/GameObjects.h"

#include <cmath>

#include <iostream>

int* ViewerPtr;
int* CWinAppPtr;

int* funcAddr_ProcessMirrors;
int* callAddr_ProcessMirrors;

int* funcAddr_CameraInstanceReset;
int* callAddr_CameraInstanceReset;

int* isMirrorsProcessed;
float* cabinCameraRotation;

//bool is_ui_hooks_enabled;


void __fastcall ProcessMirrors(int* _this, int* EDX) {
	//int* isMirrorsProcessed = (int*)0x67E178;
	int temp = *isMirrorsProcessed;

	//camera min angle when side mirrors always disable;
	float camRotMin = 0.2;
	//interior camera rotation
	float cameraRot = *cabinCameraRotation; // *(float*)0x696D30;

	if (abs(cameraRot) < camRotMin)
		*isMirrorsProcessed = 0;

	//call original function
	((int(__thiscall*)(int*))funcAddr_ProcessMirrors)(_this); //0x595230

	*isMirrorsProcessed = temp;

	return;
}


int* __fastcall OnCameraInstanceReset(int* _this, int edx) {
	int xres = *(int*)((char*)CWinAppPtr + 0x100);
	int yres = *(int*)((char*)CWinAppPtr + 0x104);

	float aspect_rev = (float)yres / (float)xres;

	//change mirrors matrix position if game running in 16x9
	if (aspect_rev < 0.7) {
		CMatrix* cabineMtx = (CMatrix*)((char*)*ViewerPtr + 0x208);
		CMatrix* mirrorsMtx = (CMatrix*)((char*)*ViewerPtr + 0x238);

		float addVal_y = 0.2;
		float addVal_z = -0.2;

		if (cabineMtx->pos.z < 1.0) {
			addVal_y = 0.3;
			addVal_z = -0.4;
		}

		mirrorsMtx->pos.y += addVal_y;
		mirrorsMtx->pos.z += addVal_z;
	}

	//call original function
	return ((int* (__thiscall*)(int*))funcAddr_CameraInstanceReset)(_this);
}

bool GetOffsets(int gameVersion) try {
	if (gameVersion < 62)
		return false;

	using namespace Memory::VP;
	using namespace hook::txn;


	ViewerPtr = GetViewerPtr(gameVersion);
	CWinAppPtr = GetCWinAppPtr();

	//std::cout << "ViewerPtr=" << ViewerPtr << std::endl;
	//std::cout << "CWinAppPtr=" << CWinAppPtr << std::endl;

	//std::cout << "xres = " << *(int*)((char*)CWinAppPtr + 0x100) << " yres = " << *(int*)((char*)CWinAppPtr + 0x104) << std::endl;

	callAddr_CameraInstanceReset = (int*)pattern("E8 ? ? ? ? 89 1D ? ? ? ? 8B 8D ? ? ? ? 51 8B CD ").get_first();
	funcAddr_CameraInstanceReset = (int*)ReadCallFrom(callAddr_CameraInstanceReset);

	//std::cout << "CameraInstanceResetCallAddr=" << callAddr_CameraInstanceReset << std::endl;
	//std::cout << "CameraInstanceResetAddr=" << funcAddr_CameraInstanceReset << std::endl;


	funcAddr_ProcessMirrors = (int*)pattern("55 8B EC 83 E4 F8 81 EC ? ? ? ? A1 ? ? ? ? 53 55 56 33 F6 57 3B C6 8B E9").get_first(0);
	// It won't be possible to create a pattern before finding function - the only call to this function occurs when
	// rendering viewport elements, i.e. there is a cycle with a call to obj->Draw(...)
	callAddr_ProcessMirrors = (int*)pattern(UInt32toPattern((int)funcAddr_ProcessMirrors)).get_first(0);

	//std::cout << "ProcessMirrors func addr=" << funcAddr_ProcessMirrors << std::endl;
	//std::cout << "ProcessMirrors call addr=" << callAddr_ProcessMirrors << std::endl;

	isMirrorsProcessed = *(int**)pattern("A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? D9 44 24 78").get_first(1);
	cabinCameraRotation = *(float**)pattern("D8 05 ? ? ? ? D9 44 24 00").get_first(2);

	//std::cout << "isMirrorsProcessed addr=" << isMirrorsProcessed << std::endl;
	//std::cout << "cabinCameraRotation addr=" << cabinCameraRotation << std::endl;

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}


bool MirrorsFix::injectHooks(int gameVersion){
	if (!GetOffsets(gameVersion))
		return false;

	bool can_apply_mirrors_transforms = callAddr_CameraInstanceReset && funcAddr_CameraInstanceReset && CWinAppPtr && ViewerPtr;
	bool can_apply_mirrors_switcher   = callAddr_ProcessMirrors && funcAddr_ProcessMirrors && isMirrorsProcessed && cabinCameraRotation;

	//is_ui_hooks_enabled = GetPrivateProfileIntA("HOOKS", "EnableUIFix", 0, ".\\d2gi.ini");

	if (can_apply_mirrors_transforms)
		CPatch::RedirectCall((int)callAddr_CameraInstanceReset, &OnCameraInstanceReset);

	if (can_apply_mirrors_switcher)
		CPatch::SetPointer((int)callAddr_ProcessMirrors, &ProcessMirrors);

	return (can_apply_mirrors_transforms || can_apply_mirrors_switcher);
}