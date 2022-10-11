#pragma once

#include <Dolphin/GX.h>
#include <Dolphin/types.h>

#include <JSystem/JKernel/JKRFileLoader.hxx>
#include <JSystem/JUtility/JUTPalette.hxx>

class ResTIMG {};

class JUTTexture {
public:
    inline JUTTexture() {}
    inline JUTTexture(const char *resource) {
        auto *timg = reinterpret_cast<const ResTIMG *>(JKRFileLoader::getGlbResource(resource));
        mTexObj2.val[2] = 0;
        storeTIMG(timg);
        _50 = false;
    }
    JUTTexture(int sX, int sY, GXTexFmt format);
    ~JUTTexture();

    void attachPalette(JUTPalette *palette);
    void initTexObj(GXTlut tlut);
    void initTexObj();
    void load(GXTexMapID id);
    void storeTIMG(const ResTIMG *timg);

    GXTexObj mTexObj;
    GXTexObj mTexObj2;
    u16 _40;
    bool _42;
    bool _43;
    u32 _44;
    u32 _48;
    GXTexObj *mGXObj;  // 0x4C
    bool _50;

    // 4C = GXTexFmt
};