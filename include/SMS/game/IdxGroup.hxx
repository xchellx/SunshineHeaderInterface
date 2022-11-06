#pragma once

#include <JSystem/J3D/J3DAnimation.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JGadget/List.hxx>
#include <SMS/actor/HitActor.hxx>
#include <JSystem/JDrama/JDRViewObjPtrListT.hxx>

class IdxGroup : public JDrama::TViewObjPtrListT<THitActor> {
public:
    IdxGroup(const char *name) : TViewObjPtrListT(name){};
    virtual ~IdxGroup();

    virtual void loadSuper(JSUMemoryInputStream &stream) override;

    JGadget::TList_pointer<THitActor *> mHitActorList;
};