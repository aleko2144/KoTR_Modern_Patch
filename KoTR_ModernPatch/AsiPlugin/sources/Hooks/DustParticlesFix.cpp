#include "DustParticlesFix.h"
#include "../Utils/CPatch.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

//#include <iostream>

int* particlesCodeStart;
float* dustParticlesLifetime;

bool DustParticlesFix::getOffsets(int gameVersion) try {
	using namespace Memory::VP;
	using namespace hook::txn;

	if (gameVersion >= 60 && gameVersion < 74) {
		particlesCodeStart = (int*)pattern("C7 44 24 ? ? ? ? ? DB 44 24 30 D9 C0 D8 0D").get_first(8);
	} else if (gameVersion >= 74) {
		//0x56F73F, 
		particlesCodeStart = (int*)pattern("C7 44 24 ? ? ? ? ? DB 44 24 2C 8B 4C 24 18").get_first(8);
	}

	//std::cout << "particlesCodeStart=" << particlesCodeStart << std::endl;


	//flt_675418 lifetime in 6.6
	
	if (gameVersion >= 71) {
		dustParticlesLifetime = *(float**)pattern("8B 0D ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 89 0D ? ? ? ?").get_first(2);
	} else {
		dustParticlesLifetime = *(float**)pattern("8B 0D ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 89 0D ? ? ? ?").get_first(2);
	}

	//int temp = (int)pattern("8B 0D ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 89 0D ? ? ? ?").get_first(0);
	//std::cout << "temp=" << temp << std::endl;

	//64C1C0 in 8.2
	//std::cout << "dustParticlesLifetime=" << dustParticlesLifetime << std::endl;

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}

uintptr_t particlesFunc_out_addr;

__declspec(naked) VOID applyAsmPatch_v82() {
	__asm {
		//указатель на Car_V (7.3 - 8.2)
		mov     ecx, dword ptr[esi + 5460h]

		//Car_V->vehicle_velocity.y
		fld     dword ptr[ecx + 44h]
		fstp    dword ptr[esp + 3Ch]


		//Car_V->vehicle_velocity.x
		fld     dword ptr[ecx + 40h]
		fchs
		fstp    dword ptr[esp + 40h]

		//Car_V->vehicle_velocity.z
		fld     dword ptr[ecx + 48h]
		fstp    dword ptr[esp + 44h]

		//???
		mov ecx, dword ptr[esp + 18h]

		//прыжок в оригинальную функцию
		jmp particlesFunc_out_addr
	}
}

__declspec(naked) VOID applyAsmPatch_v73() {
	__asm {
		//Car_V 7.3 - 8.2 pointer
		mov     eax, dword ptr[ebx + 5460h]

		//direction.x
		fld     dword ptr[eax + 44h] //Car_V->velocity.y
		fstp    dword ptr[esp + 4Ch] //dir.x

		//direction.y
		fld     dword ptr[eax + 40h]  //Car_V->velocity.x
		fchs                          //invert sign
		fstp    dword ptr[esp + 50h]  //dir.y

		//direction.z
		//fld     dword ptr[eax + 40h] //Car_V->velocity.z
		//fstp    dword ptr[esp + 54h] //dir.z

		//54F9E5     mov     eax, [esp+194h+var_160]
		mov eax, dword ptr[esp + 34h]

		//прыжок в оригинальную функцию
		//return to original function
		jmp particlesFunc_out_addr
	}
}

__declspec(naked) VOID applyAsmPatch_v71() {
	__asm {
		//Car_V 7.1 - 7.2 pointer
		mov     eax, dword ptr[ebx + 5010h]

		//direction.x
		fld     dword ptr[eax + 44h] //Car_V->velocity.y
		fstp    dword ptr[esp + 4Ch] //dir.x

		//direction.y
		fld     dword ptr[eax + 40h]  //Car_V->velocity.x
		fchs                          //invert sign
		fstp    dword ptr[esp + 50h]  //dir.y

		//direction.z
		//fld     dword ptr[eax + 40h] //Car_V->velocity.z
		//fstp    dword ptr[esp + 54h] //dir.z

		//54F9E5     mov     eax, [esp+194h+var_160]
		mov eax, dword ptr[esp + 34h]

		//прыжок в оригинальную функцию
		//return to original function
		jmp particlesFunc_out_addr
	}
}

bool DustParticlesFix::injectHooks(int gameVersion) {

	if (!getOffsets(gameVersion) || !particlesCodeStart)
		return false;

	//This patch makes the direction of movement of dust particles equal to the vehicle's movement vector (before calling the emitter).

	particlesFunc_out_addr = (int)particlesCodeStart + 5;

	//7.1 - 7.2
	if (gameVersion < 73) {
		CPatch::Nop((int)particlesCodeStart, 144);
		CPatch::RedirectJump((int)particlesCodeStart, &applyAsmPatch_v71);
		//std::cout << "applyAsmPatch_v71\n";

	} else if (gameVersion == 73) {
		CPatch::Nop((int)particlesCodeStart, 144);
		CPatch::RedirectJump((int)particlesCodeStart, &applyAsmPatch_v73);
		//std::cout << "applyAsmPatch_v73\n";

	} else {
		CPatch::Nop((int)particlesCodeStart, 126);
		CPatch::RedirectJump((int)particlesCodeStart, &applyAsmPatch_v82);
		//std::cout << "applyAsmPatch_v82\n";
	}

	if (dustParticlesLifetime)
		CPatch::SetFloat((int)dustParticlesLifetime, 0.35);

	return true;
	
}