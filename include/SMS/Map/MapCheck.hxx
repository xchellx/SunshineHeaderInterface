#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGeometry.hxx>
#include <SMS/Map/BGCheck.hxx>

class TBGWallCheckRecord {
public:
    TVec3f mPosition;
    f32 _0C;
    size_t mCollideMax;
    size_t mNumWalls;
    size_t _18;
    TBGCheckData *mWalls;
};