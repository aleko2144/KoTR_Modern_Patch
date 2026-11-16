#ifndef LOD_FIX_H
#define LOD_FIX_H

#include "Patch/IPatch.h"
#include "Patch/TrampolineHookBase.h"
#include <memory>

class ILodFix : public IPatch
{
public:
    virtual ~ILodFix() = default;

    std::string GetName() const override;
};

class LodFix005f2080 : public ILodFix, public TrampolineHookBase
{
public:
    virtual ~LodFix005f2080() = default;

    bool InjectHooks() override;

protected:
    virtual std::string FunctionStartBytes() const = 0;

    void *HookFunction() const override;

    functionLocation OriginalFunctionLocation() const override;

private:
    struct SceneNode
    {
        uint32_t undefined0;
        uint32_t undefined1;
        uint32_t undefined2;
        uint32_t undefined3;
        uint32_t kind;
        uint32_t undefined5;
        uint32_t undefined6;
        uint32_t undefined7;
        uint32_t undefined8;
        uint32_t undefined9;
        uint32_t undefined10;
        uint32_t undefined11;
        uint32_t undefined12;
        uint32_t lodArraySize;
        uint32_t lodDistanceCalcMode;

        struct lodDistanceCalcMode
        {
            enum : int { alongTheViewAxis = 0, projectedSize = 1, distanceToAPlane = 2, five = 5 };
        };

        struct nodeKind
        {
            enum : int { lod = 8 };
        };
    };

    typedef void(__thiscall *OriginalFuncSig)(SceneNode *node,
                                              int lodSlot,
                                              int flags,
                                              int sceneViewP);

    static OriginalFuncSig trampolineFunc_;

    static void __thiscall OnCall005f2080(SceneNode *node, int lodSlot, int flags, int sceneViewP);
};

class LodFix_8_0 final : public LodFix005f2080
{
public:
    virtual ~LodFix_8_0() = default;

protected:
    std::string FunctionStartBytes() const override;

    uintptr_t BytesCountToSteal() const override;

private:
    LodFix_8_0() = default;
    friend class LodFixFactory;
};

class LodFixFactory
{
public:
    static std::unique_ptr<ILodFix> create(const int gameVersion);
};

#endif