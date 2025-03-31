#pragma once

#include <Dolphin/types.h>
#include <SMS/Enemy/SpineEnemy.hxx>

class TBossManta : public TSpineEnemy {

public:
    u32 _00[0x3C / 4];        // 0x0150
    u32 mGeneration;          // 0x018C
    f32 mSpeed;               // 0x0190
    f32 mAngularVelocity;     // 0x0194
    u32 _01;                  // 0x0198
    u32 mDamageCounter;       // 0x019C
    u32 mInvincibilityTimer;  // 0x01A0
};