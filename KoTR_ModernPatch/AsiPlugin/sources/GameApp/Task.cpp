#include "Task.h"

void __fastcall Task::ActivateTask(int* _this, int a2) {
    typedef void(__thiscall* sub_5D3330)(int* _this, int a2);
    return sub_5D3330(0x5D3330)(_this, a2);
}

void __fastcall Task::AddTaskToManager(int* _this, int a2) {
    typedef void(__thiscall* sub_5D3250)(int* _this, int a2);
    return sub_5D3250(0x5D3250)(_this, a2);
}