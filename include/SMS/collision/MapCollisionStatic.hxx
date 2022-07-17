#pragma once

#include <Dolphin/types.h>

#include <SMS/actor/LiveActor.hxx>
#include <SMS/collision/MapCollisionBase.hxx>

class TMapCollisionStatic : public TMapCollisionBase {
public:
    TMapCollisionStatic();

    void init(const s8, u16, const TLiveActor *);
    void remove();
    void setUp();

    TLiveActor *mActor;  // _60
};