#pragma once

#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JDrama/JDRGraphics.hxx>
#include <JSystem/J3D/J3DModel.hxx>
#include <SMS/M3DUtil/MActor.hxx>

#include <JSystem/JointObj.hxx>

class TJointModelManager;

class TJointModel : public TJointObj {
public:
  TJointModel();

  virtual void perform(u32, JDrama::TGraphics *);

  virtual void initJointModel();
  virtual u32 getJ3DModelFlag() const;

  TJointModelManager *mManager;
  J3DModelData *mModelData;
  J3DModel *mModel;
  MActor *mActor;
};