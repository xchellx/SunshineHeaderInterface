#pragma once

#include <SMS/M3DUtil/M3UModel.hxx>
#include <SMS/Player/Mario.hxx>

class M3UModelCommonMario : public M3UModelCommon {
public:
    virtual M3UMtxCalcSetInfo *getMtxCalc(const M3UMtxCalcSetInfo &) const;
};

class TEnemyMario : public TMario {
public:
    enum CONTEXTS {
        UNK0,
        CAUTIONWAIT,
        REPEATJUMP,
        DELAYJUMP,
        UNK5,
        IDLE,
        IDLENOCOL,
        WARPAWAY,
        RUNTONODE,
        RUNWAIT,
        STARTRUN,
        FALLING,
        LAYWAITING,
        RUNAWAY,
        MOVETONEWGRAPH,  //?
        LAUGHATTARGET  = 16,
        LEAVEMAP       = 17,
        LAUGHATTARGET2 = 18,
    };

    s16 _00;
    s16 _02;
    s16 mEnemyHealth;
    s16 _06;
    u32 _08[0x38 / 4];
    f32 mWarpSpeed;
    u32 _44[0x38 / 4];
    void *mEnemyManager;  //?
};