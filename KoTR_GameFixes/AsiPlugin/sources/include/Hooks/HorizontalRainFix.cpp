#include "HorizontalRainFix.h"
#include "..\Utils\CPatch.h"

double rainSpeed = 50.0;
void __fastcall OnProcessRainDrop(int *_this, int* EDX){
	int* TheGame = (int*)((char*)_this + 0x20);
	double dt = *(double*)((char*)*TheGame + 0xB90); //delta time

	//default game value is dt * 50.0 = 1.5 at 30 FPS
	rainSpeed = 1.5 / dt;

	//limit value (original in-game value is 50.0)
	if (rainSpeed < 50.0)
		rainSpeed = 50.0;

	//call original function
	((int(__thiscall *)(int*))0x5A5ED0)(_this);
}

void HorizontalRainFix::injectHooks(){
	//replace function call pointer
	CPatch::SetPointer(0x651534, &OnProcessRainDrop);
	//replace rain drop moving down speed value
	CPatch::SetPointer(0x5A5EE4, &rainSpeed);
}