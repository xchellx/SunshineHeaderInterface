#pragma once

#include <JSystem/JKernel/JKRArchivePri.hxx>
#include <JSystem/J2D/J2DScreen.hxx>
#include <Dolphin/types.h>

class J2DSetScreen : public J2DScreen {
public:
  J2DSetScreen(const char *, JKRArchive *);
  virtual ~J2DSetScreen();
};