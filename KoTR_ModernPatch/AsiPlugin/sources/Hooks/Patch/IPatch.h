#ifndef I_PATCH_H
#define I_PATCH_H

#include <string>

class IPatch
{
public:
    virtual ~IPatch() = default;
    virtual bool InjectHooks() = 0;
    virtual std::string GetName() const = 0;
};

#endif
