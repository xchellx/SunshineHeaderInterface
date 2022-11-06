#pragma once

#include <Dolphin/types.h>
#include <JSystem/JDrama/JDRDirector.hxx>
#include <JSystem/JDrama/JDRDisplay.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <SMS/Player/Mario.hxx>

class TSelectDir : public JDrama::TDirector {
public:
    TSelectDir();
    virtual ~TSelectDir();

    s32 direct() override;

    void changeOrder();
    void rsetup();
    s32 setup(JDrama::TDisplay *, TMarioGamePad *, u8 areaID);
    void setupThreadFunc(void *);

    u32 _18;
    u32 _1C;
    u32 _20;
    u32 _24;
    u32 _28;
    u32 _2C;
    u32 _30;
    u32 _34;
    u8 _38;
    u32 _3C;
    u8 _40;
    u32 _44;
    u32 _48;
    u8 _4C;
};