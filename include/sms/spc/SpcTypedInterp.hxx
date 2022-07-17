#pragma once

#include <Dolphin/types.h>
#include <SMS/spc/SpcInterp.hxx>

template <typename T> class TSpcTypedInterp : public TSpcInterp {
public:
    ~TSpcTypedInterp();

    void dispatchBuiltin(u32, u32);
};