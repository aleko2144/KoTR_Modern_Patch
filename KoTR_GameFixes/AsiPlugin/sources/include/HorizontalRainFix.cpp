#include "HorizontalRainFix.h"
#include "utils\CPatch.h"

void __fastcall HorizontalRainFix::OnProcessRainDrop(int *_this, int* EDX){
	int* TheGame = (int*)((char*)_this + 0x20);
	double* dt = (double*)((char*)*TheGame + 0xB90);
	double prevDt = *dt;

	//std::cout << prevDt << std::endl;

	//if the game is running too fast, let the rain drop object instance think that the game is running at 25 FPS
	if (*dt < 0.04)
		*dt = 0.04;

	//call original function
	((int(__thiscall *)(int*))0x5A5ED0)(_this);

	//restore delta time value
	*dt = prevDt;
}

void HorizontalRainFix::injectHooks(){
	//replace function call pointers
	CPatch::SetPointer(0x651534, &OnProcessRainDrop);
}