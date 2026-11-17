#ifndef TRAMPOLINE_HOOK_BASE_H
#define TRAMPOLINE_HOOK_BASE_H

#include <cstdint>
#include <string>

class TrampolineHookBase
{
public:
    virtual ~TrampolineHookBase();

protected:
    struct functionLocation
    {
        std::string pattern;
        int offset;
    };

    bool InstallTrampoline();
    bool UninstallTrampoline();

    void *TrampolineFunction();

    virtual functionLocation OriginalFunctionLocation() const = 0;

    // 5+ bytes; near relative JMP size (5) for RedirectJump; rounded up to whole instruction boundary
    virtual uintptr_t BytesCountToSteal() const = 0;

    virtual void *HookFunction() const = 0;

private:
    static const uintptr_t redirectJumpInstructionSize = 5;

    static const int trampolineSizeLimit = 32;
    uint8_t trampoline[trampolineSizeLimit];

    struct trampolineInfo
    {
        bool isInstalled{false};
        void *original{nullptr};
    } trampolineInfo_{};

    void *OriginalFunction();
};

#endif