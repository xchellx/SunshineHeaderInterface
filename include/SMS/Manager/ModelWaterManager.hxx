#pragma once

#include <Dolphin/types.h>

#include <JSystem/JDrama/JDRGraphics.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JGeometry/JGMVec.hxx>
#include <JSystem/JSupport/JSUMemoryStream.hxx>
#include <JSystem/JUtility/JUTColor.hxx>
#include <SMS/Player/Watergun.hxx>
#include <SMS/Strategic/HitActor.hxx>

class TModelWaterManager : public JDrama::TViewObj {
public:
    virtual ~TModelWaterManager();

    virtual void perform(u32, JDrama::TGraphics *) override;
    virtual void load(JSUMemoryInputStream &) override;
    virtual void loadAfter() override;

    void askDoWaterHitCheck();
    void askHitWaterParticleOnGround(const TVec3f &);
    void calcDrawVtx(Mtx44);
    void calcVMAll(Mtx44);
    void calcVMMtxGround(Mtx44, f32, const TVec3f &, const TVec3f &, Mtx44);
    void calcVMMtxWall(Mtx44, f32, const TVec3f &, const TVec3f &, Mtx44);
    void calcWorldMinMax();
    void drawMirror(Mtx44);
    void drawRefracAndSpec() const;
    void drawShineShadowVolume(Mtx44);
    void drawSilhouette(Mtx44);
    void drawTouching();
    void drawWaterVolume(Mtx44);
    u8 emitRequest(const TWaterEmitInfo &info);
    void garbageCollect();
    void makeEmit(const TWaterEmitInfo &info);
    void move();
    void wind(const TVec3f &);

    s16 mMaxEmit;         // 0x0010
    s16 mEmitCount;       // 0x0012
    u32 _03[0x5D48 / 4];  // 0x0014
    u16 _04;              // 0x5D5C
    u8 _05;               // 0x5D5E
    s8 mWaterCardType;    // 0x5D5F

    struct {
        u8 _00            : 6;
        bool mMaskObjects : 1;
        bool mShowShadow  : 1;
        u8 _01            : 8;
    } LightType;  // 0x5D60

    u16 _06;                  // 0x5D62
    u32 _07[0xA8 / 4];        // 0x5D64
    f32 mSize;                // 0x5E0C
    f32 _08[0x30 / 4];        // 0x5E10
    f32 mSphereStep;          // 0x5E40
    u8 mLayerCount;           // 0x5E44
    u8 mDarkLevel;            // 0x5E45
    u8 _09;                   // 0x5E46
    JUtility::TColor mColor;  // 0x5E47

    static THitActor mStaticHitActor;
};

extern TModelWaterManager *gpModelWaterManager;
extern JUtility::TColor waterColor[4];
extern TVec3f gShineShadowPos;