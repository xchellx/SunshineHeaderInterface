#pragma once

#include <Dolphin/types.h>
#include <JSystem/JDrama/JDRGraphics.hxx>
#include <JSystem/JDrama/JDRNameRef.hxx>
#include <JSystem/JUtility/JUTRect.hxx>
#include <SMS/GC2D/OptionControl.hxx>
#include <SMS/System/CardManager.hxx>

enum TEProgress {
    PROGRESS_UNK_0,
    PROGRESS_UNK_1,
    PROGRESS_UNK_2,
    PROGRESS_UNK_3,
    PROGRESS_UNK_4,
    PROGRESS_UNK_5,
    PROGRESS_UNK_6
};

class TCardLoad : public JDrama::TNameRef {
public:
    TCardLoad(const char *);
    virtual ~TCardLoad();
    virtual void load(JSUMemoryInputStream &) override;
    virtual void loadAfter() override;
    virtual void perform(u32, JDrama::TGraphics *);

    u32 changeMode(s32);
    void changeScene();
    s8 drawMessage(TEProgress);
    s8 drawMessageBM(TEProgress);
    s8 selectBookmark(TEProgress, TEProgress, bool);
    void setSelected(u8);
    void setupScoreScreen();
    bool titleDraw();
    s8 waitForAnyKey(TEProgress);
    s8 waitForAnyKeyBM(TEProgress);
    s8 waitForChoice(TEProgress, TEProgress, int);
    s8 waitForChoiceBM(TEProgress, TEProgress, int);
    s8 waitForStart(TEProgress);

    u16 _0C;
    TEProgress mProgress;
    u32 mState;                       // 0x0014
    u32 _18[0x28 / 4];                // 0x0018
    TCardBookmarkInfo mBookmarkInfo;  // 0x0040
    u32 _A4[0xC / 4];                 // 0x00A4
    u8 mSelected;                     // 0x00B0
    u8 _B1[0xF];
    s32 mFramesOpen;     // 0x00C0
    u32 _C4[0x60 / 4];   // 0x00C4
    JUTRect mRects[11];  // 0x0124
    u32 _1D4[0x5A0 / 4];
    TOptionControl *mOptionControl;  // 0x0774
};

extern TCardLoad *gpCardLoad;