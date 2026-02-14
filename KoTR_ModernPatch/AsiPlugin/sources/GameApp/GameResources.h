#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

void* __cdecl new_internal(size_t a1);
void* _malloc_internal(size_t _size);

void* GetLoadedResource(const char* name);

int __fastcall playEffectSound2D(int* resSnd, float a2, float a3, int a4);

void __cdecl SetCaseSwitch(void* node, int v);
void __cdecl SetCaseSwitch_s(void* node, int v);

#endif
