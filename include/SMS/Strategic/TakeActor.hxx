#pragma once

#include <SMS/Strategic/HitActor.hxx>

class TTakeActor : public THitActor {
public:
    TTakeActor(const char *name) : THitActor(name), mHolder(nullptr), mHeldObject(nullptr) {}
    virtual ~TTakeActor();

    virtual Mtx44 *getTakingMtx() = 0;
    virtual void ensureTakeSituation();
    virtual u32 moveRequest(const TVec3f &destPosition);
    virtual f32 getRadiusAtY(f32) const;

    bool isTaken() const;

    TTakeActor *mHolder;      // 0x0068
    TTakeActor *mHeldObject;  // 0x006C
};