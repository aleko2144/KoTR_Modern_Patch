#include "TrampolineHookBase.h"
#include "../../Utils/CPatch.h"
#include "../../Utils/ModUtils/Patterns.h"

bool TrampolineHookBase::InstallTrampoline()
{
    if (BytesCountToSteal() + jmpInstructionSize > trampolineSizeLimit) {
        return false;
    }

    void *original = reinterpret_cast<void *>(OriginalFunctionP());
    if (!original) {
        return false;
    }

    memcpy(trampoline, original, BytesCountToSteal());
    trampoline[BytesCountToSteal()] = jmpCode;
    CPatch::RedirectJump(reinterpret_cast<uintptr_t>(trampoline) + BytesCountToSteal(),
                         reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(original)
                                                  + BytesCountToSteal()));

    DWORD old{};
    VirtualProtect(trampoline,
                   BytesCountToSteal() + jmpInstructionSize,
                   PAGE_EXECUTE_READWRITE,
                   &old);

    CPatch::RedirectJump(reinterpret_cast<uintptr_t>(original), HookFunction());

    return true;
}

void *TrampolineHookBase::TrampolineFunction()
{
    return trampoline;
}

uintptr_t TrampolineHookBase::OriginalFunctionP()
{
    try {
        auto loc = OriginalFunctionLocation();
        auto addr = hook::txn::pattern(loc.pattern).count(1).get_first(0);
        if (!addr) {
            return 0;
        }
        return reinterpret_cast<uintptr_t>(addr) + loc.offset;
    } catch (const hook::txn_exception &) {
        return 0;
    }
}
