#pragma once

#include <Dolphin/types.h>
#include <SMS/collision/BGCheck.hxx>

class TBGWallCheckRecord {
public:
    u32 _00[0x14 / 4];
    size_t mNumWalls;
    u32 _18;
    TBGCheckData *mWalls;
};