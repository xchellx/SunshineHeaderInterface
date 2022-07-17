#pragma once

#include <JSystem/JStage/JSGSystem.hxx>
#include <JSystem/JUtility/JUTGamePad.hxx>
#include <JSystem/JDrama/JDRNameRef.hxx>
#include <SMS/game/PerformList.hxx>
#include <Dolphin/types.h>

namespace JDrama {

class TDirector : public TNameRef, public JStage::TSystem {
public:
  virtual ~TDirector();

  virtual TDirector *searchF(u16, const char *);
  virtual JStage::TObject *
  JSGFindObject(const char *, JStage::TEObject) const; // JStage::TEObject
  virtual s32 direct();

  u32 *mViewObjPtrList; // TViewObjPtrList *
  u32 _14;
  JUTGamePad **mGamePads;
  TPerformList *mPerformListGX;
  TPerformList *mPerformListSilhouette;
};

} // namespace JDrama