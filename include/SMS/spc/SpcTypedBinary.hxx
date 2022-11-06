#pragma once

#include <SMS/actor/LiveActor.hxx>
#include <SMS/SPC/SpcBinary.hxx>
#include <SMS/SPC/SpcTypedInterp.hxx>

template <typename T> class TSpcTypedBinary : public TSpcBinary {
public:
    virtual ~TSpcTypedBinary();

    virtual void initUserBuiltin() override;
};

void linPushNerve(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBck(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBpk(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBtp(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBtk(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBlk(TSpcTypedInterp<TLiveActor> *, u32);
void linSetBls(TSpcTypedInterp<TLiveActor> *, u32);
void linSetSRT(TSpcTypedInterp<TLiveActor> *, u32);
void linGetSRT(TSpcTypedInterp<TLiveActor> *, u32);
void linSetAnmRate(TSpcTypedInterp<TLiveActor> *, u32);
