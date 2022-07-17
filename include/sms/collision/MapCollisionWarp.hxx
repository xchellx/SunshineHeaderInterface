#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGeometry.hxx>

#include <SMS/actor/LiveActor.hxx>
#include <SMS/collision/MapCollisionBase.hxx>

class TMapCollisionWarp : TMapCollisionBase
{
public:
    TMapCollisionWarp();

    void init(const s8, u16, const TLiveActor *);
    void remove();
    void setUp();
    void setUpTrans(const TVec3f &);

    u16 _60;
    TLiveActor *mActor; //0x0064
};