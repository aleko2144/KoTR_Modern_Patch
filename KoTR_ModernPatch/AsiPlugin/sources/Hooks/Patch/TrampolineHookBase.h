#ifndef TRAMPOLINE_HOOK_BASE_H
#define TRAMPOLINE_HOOK_BASE_H

#include <cstdint>
#include <string>

class TrampolineHookBase
{
public:
    virtual ~TrampolineHookBase() = default;

protected:
    struct functionLocation
    {
        std::string pattern;
        int offset;
    };

    bool InstallTrampoline();

    virtual functionLocation OriginalFunctionLocation() const = 0;

    // 5+ bytes; near relative JMP size (5), rounded up to whole instruction boundary
    virtual uintptr_t BytesCountToSteal() const = 0;

    virtual void *HookFunction() const = 0;

    void *TrampolineFunction();

private:
    static const uintptr_t jmpInstructionSize = 5;
    static const uint8_t jmpCode = 0xE9;

    static const int trampolineSizeLimit = 32;
    uint8_t trampoline[trampolineSizeLimit];

    virtual uintptr_t OriginalFunctionP();
};

#endif