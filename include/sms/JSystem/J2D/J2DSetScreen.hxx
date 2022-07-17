#pragma once

#include "JKR/JKRArchivePri.hxx"
#include "J2DScreen.hxx"
#include <dolphin/types.h>

class J2DSetScreen : public J2DScreen {
public:
  J2DSetScreen(const char *, JKRArchive *);
  virtual ~J2DSetScreen();
};