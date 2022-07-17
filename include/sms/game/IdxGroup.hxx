#pragma once

#include <JSystem/J3D/J3DAnimation.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JGadget/List.hxx>
#include <SMS/actor/HitActor.hxx>
#include <SMS/game/ViewObjPtrList.hxx>

class IdxGroup : public TViewObjPtrListT<THitActor, JDrama::TViewObj> {
public:
    IdxGroup(const char *name) : TViewObjPtrListT<THitActor, JDrama::TViewObj>(name){};
    virtual ~IdxGroup();

    virtual void loadSuper(JSUMemoryInputStream &stream) override;

    JGadget::TList_pointer<THitActor *> mHitActorList;
};