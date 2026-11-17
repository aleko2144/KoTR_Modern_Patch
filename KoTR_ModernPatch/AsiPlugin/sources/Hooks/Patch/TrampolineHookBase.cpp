#include "TrampolineHookBase.h"
#include "../../Utils/CPatch.h"
#include "../../Utils/ModUtils/Patterns.h"

bool TrampolineHookBase::InstallTrampoline()
{
    if (trampolineInfo_.isInstalled) {
        return false;
    }

    trampolineInfo_ = {};

    if (BytesCountToSteal() + redirectJumpInstructionSize > trampolineSizeLimit) {
        return false;
    }

    void *original = OriginalFunction();
    if (!original) {
        return false;
    }

    CPatch::SetBytes(reinterpret_cast<uintptr_t>(trampoline), original, BytesCountToSteal());
    CPatch::RedirectJump(reinterpret_cast<uintptr_t>(trampoline) + BytesCountToSteal(),
                         reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(original)
                                                  + BytesCountToSteal()));

    DWORD lpflOldProtect{};
    VirtualProtect(trampoline,
                   BytesCountToSteal() + redirectJumpInstructionSize,
                   PAGE_EXECUTE_READWRITE,
                   &lpflOldProtect);

    CPatch::RedirectJump(reinterpret_cast<uintptr_t>(original), HookFunction());

    trampolineInfo_ = {.isInstalled = true, .original = original};

    return true;
}

bool TrampolineHookBase::UninstallTrampoline()
{
    if (trampolineInfo_.isInstalled) {
        CPatch::SetBytes(reinterpret_cast<uintptr_t>(trampolineInfo_.original),
                         trampoline,
                         redirectJumpInstructionSize);
        trampolineInfo_ = {};
        return true;
    } else {
        return false;
    }
}

void *TrampolineHookBase::TrampolineFunction()
{
    if (trampolineInfo_.isInstalled) {
        return trampoline;
    } else {
        return nullptr;
    }
}

void *TrampolineHookBase::OriginalFunction()
{
    try {
        auto loc = OriginalFunctionLocation();
        auto patternMatcher = hook::txn::pattern(loc.pattern);
        if (patternMatcher.size() != 1) {
            return nullptr;
        }
        auto addr = patternMatcher.get_first(0);
        if (!addr) {
            return nullptr;
        }
        return reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(addr) + loc.offset);
    } catch (const hook::txn_exception &) {
        return nullptr;
    }
}

TrampolineHookBase::~TrampolineHookBase()
{
    UninstallTrampoline();
}
