#include "LodFix.h"

inline LodFix005f2080::OriginalFuncSig LodFix005f2080::trampolineFunc_ = nullptr;

std::string ILodFix::GetName() const
{
    return "LodFix";
}

void __thiscall LodFix005f2080::OnCall005f2080(SceneNode *node,
                                               int lodSlot,
                                               int flags,
                                               int sceneViewP)
{
    switch (node->kind) {
    case SceneNode::nodeKind::lod:
        switch (node->lodDistanceCalcMode) {
        case SceneNode::lodDistanceCalcMode::projectedSize:
            lodSlot = 0;
            break;
        case SceneNode::lodDistanceCalcMode::alongTheViewAxis:
        case SceneNode::lodDistanceCalcMode::distanceToAPlane:
            if (node->lodArraySize > 0) {
                lodSlot = node->lodArraySize - 1;
            }
            break;
        }
        break;
    }
    trampolineFunc_(node, lodSlot, flags, sceneViewP);
}

bool LodFix005f2080::InjectHooks()
{
    if (InstallTrampoline()) {
        trampolineFunc_ = reinterpret_cast<LodFix005f2080::OriginalFuncSig>(TrampolineFunction());
        return true;
    } else {
        trampolineFunc_ = nullptr;
        return false;
    };
}

void *LodFix005f2080::HookFunction() const
{
    return reinterpret_cast<void *>(OnCall005f2080);
}

LodFix005f2080::functionLocation LodFix005f2080::OriginalFunctionLocation() const
{
    return {.pattern = FunctionStartBytes(), .offset = 0};
}

std::string LodFix_8_0::FunctionStartBytes() const
{
    return "8B 44 24 04 8B 51 34 53 56";
}

uintptr_t LodFix_8_0::BytesCountToSteal() const
{
    return 7;
}

std::unique_ptr<ILodFix> LodFixFactory::create(const int gameVersion)
{
    switch (gameVersion) {
    case 80:
    case 81:
    case 82:
        return std::unique_ptr<ILodFix>(new LodFix_8_0());
    default:
        return nullptr;
    }
}