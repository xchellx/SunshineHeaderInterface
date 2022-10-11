#pragma once

#include <Dolphin/MTX.h>
#include <Dolphin/types.h>
#include <JSystem/J2D/J2DPane.hxx>
#include <JSystem/JSupport/JSUInputStream.hxx>
#include <JSystem/JUtility/JUTTexture.hxx>

enum J2DBinding {
    BindingBottom = (1 << 0),
    BindingTop    = (1 << 1),
    BindingRight  = (1 << 2),
    BindingLeft   = (1 << 3),
};

enum J2DWrapMode {
    WrapNone,
    WrapClamp,
    WrapRepeat,
    WrapMirror,
};

class J2DPicture : public J2DPane {
public:
    J2DPicture(u32 id, const JUTRect &rect) : J2DPane() {
        mPalette = nullptr;
        mFillColor = {255, 255, 255, 255};
        _140       = {255, 255, 255, 255};
        _4         = 18;
        mID        = id;
        mRect      = rect;
        setBlendKonstColor();
        setBlendKonstAlpha();
    }
    J2DPicture(J2DPane *, JSURandomInputStream *, bool);
    virtual ~J2DPicture();

    virtual void drawSelf(int, int);
    virtual void drawSelf(int, int, Mtx *);

    void changeTexture(const ResTIMG *timg, u8);
    void drawFullSet(int x, int y, int w, int h, J2DBinding binding, u32, bool, J2DWrapMode wrapH,
                     J2DWrapMode wrapV, Mtx *);
    void draw(int x, int y, int w, int h, bool invertX, bool invertY, bool rotate90);
    void drawTexCoord(int x, int y, int w, int h, f32, f32, f32, f32, f32, f32, f32, f32, Mtx *);
    void insert(JUTTexture *texture, u8 index, f32);
    void remove(u8);
    void setTevMode();
    void swap(f32 &, f32 &);
    void setBlendKonstColor();
    void setBlendKonstAlpha();

    JUTTexture *mTextures[4];
    u8 mTextureCount;
    u32 _100;
    f32 _104;
    f32 _108;
    f32 _10C;
    f32 _110;
    f32 _114;
    f32 _118;
    f32 _11C;
    f32 _120;
    JUTPalette *mPalette;
    u32 _128;
    u32 _12C;
    u8 _130;
    u32 _134;
    u32 _138;
    JUtility::TColor mFillColor;
    JUtility::TColor _140;
    JUtility::TColor _144[4];
    JUtility::TColor _154;
    JUtility::TColor _158;
};