#include "GameResources.h"

// in-game new() function
void* __cdecl new_internal(size_t _size) {
	typedef void* (__cdecl* sub_6326D3)(size_t _size);
	return sub_6326D3(0x6326D3)(_size);
}
// in-game malloc() function
void* _malloc_internal(size_t _size) {
	typedef void* (*sub_44BFB0)(size_t _size);
	return sub_44BFB0(0x44BFB0)(_size);
}

// returns loaded sound or texture resource //
void* GetLoadedResource(const char* name) {
	typedef void* (*sub_5EF380)(const char* name);
	return sub_5EF380(0x5EF380)(name);
}

// sound functions //
int __fastcall playEffectSound2D(int* resSnd, float a2, float a3, int a4) {
	typedef int(__thiscall * sub_5FD3F0)(int* resSnd, float a2, float a3, int a4);
	return sub_5FD3F0(0x5FD3F0)(resSnd, a2, a3, a4);
}

// b3d functions //
void __cdecl SetCaseSwitch_s(void* node, int v) {
	typedef void (__cdecl * sub_4E48AC)(void* node, int v);
	return sub_4E48AC(0x4E48AC)(node, v);
}

//same as SetCaseSwitch, but without safety checks
void __cdecl SetCaseSwitch(void* node, int v) {
	typedef void(__cdecl* sub_5E1980)(void* node, int v);
	return sub_5E1980(0x5E1980)(node, v);
}