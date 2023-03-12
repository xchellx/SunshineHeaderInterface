#pragma once

#include <JSystem/J3D/J3DAnimation.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <JSystem/JDrama/JDRViewObjPtrListT.hxx>
#include <JSystem/JGadget/List.hxx>
#include <SMS/Strategic/HitActor.hxx>

class IdxGroupObj : public JDrama::TViewObjPtrListT<THitActor> {
public:
    IdxGroupObj(const char *name) : TViewObjPtrListT(name){};
    virtual ~IdxGroupObj();

    virtual void loadSuper(JSUMemoryInputStream &stream) override;
};