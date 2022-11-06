#pragma once

#include <Dolphin/types.h>
#include <SMS/Map/BGCheck.hxx>

class TBGWallCheckRecord {
public:
    u32 _00[0x14 / 4];
    size_t mNumWalls;
    u32 _18;
    TBGCheckData *mWalls;
};