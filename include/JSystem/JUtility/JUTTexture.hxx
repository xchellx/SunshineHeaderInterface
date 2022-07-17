#pragma once

#include <Dolphin/types.h>
#include <Dolphin/GX.h>

#include <JSystem/JUtility/JUTPalette.hxx>

class ResTIMG {};

class JUTTexture {
public:
  JUTTexture(int sX, int sY, GXTexFmt format);
  ~JUTTexture();

  void attachPalette(JUTPalette *palette);
  void initTexObj(GXTlut tlut);
  void initTexObj();
  void load(GXTexMapID id);
  void storeTIMG(ResTIMG *timg);

  u32 _00[0x54 / 4];
};