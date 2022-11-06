#pragma once

#include <Dolphin/types.h>

class TMario;

class TDrawSyncCallback {
public:
    virtual void drawSyncCallback(u16) = 0;
};

struct TMarioAnimeData {
    enum FLUDD { FLUDD_ENABLED = 68, FLUDD_DISABLED = 200 };
    enum HAND { HAND_A, HAND_B, HAND_C };

    bool isPumpOK() const;

    u16 mAnimID;
    u16 mFluddEnabled;  // Note: ENUM? 68 = enabled, 200 = disabled
    u8 mAnmTexPattern;  // Note: 23 is the max value allowed
    u8 mMarioHand;      // Note: 1, 2, and 3 seem to be valid values, this determines
                        // the hand model used(?)
    u8 unk_1;           // Note: If bit 30 is set, it seems to activate a bit flag to
                        // multiple pointers, likely mtx related
    u8 unk_2;           // Note: Value seems to be set but is never used?
};

extern TMarioAnimeData gMarioAnimeData[336];
extern TMario *gpMarioForCallback;