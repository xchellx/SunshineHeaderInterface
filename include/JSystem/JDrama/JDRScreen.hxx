#pragma once

#include <Dolphin/types.h>

#include <JSystem/JGeometry.hxx>
#include <JSystem/JDrama/JDRNameRef.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JDrama/JDRViewport.hxx>
#include <JSystem/JDrama/JDRViewConnector.hxx

#include <SMS/camera/CamConnector.hxx>

namespace JDrama {

class TScreen : public TViewConnector {
public:
  TScreen(const TRect &, const char *);
  virtual ~TScreen();

  void assignCamera(TViewObj *);
  void assignViewObj(TViewObj *);

  TViewport *mViewport;         // 10
  TCamConnector *mCamConnecter; // 14
};

} // namespace JDrama