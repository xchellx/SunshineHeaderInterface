#pragma once

#include <JSystem/JDrama/JDRGraphics.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>
#include <SMS/Strategic/ObjHitCheck.hxx>

class TStrategy : public JDrama::TViewObj {
public:
    TStrategy(const char *name);
    virtual ~TStrategy();

    virtual void load(JSUMemoryInputStream &) override;
    virtual void perform(u32, JDrama::TGraphics *) override;
    virtual void loadAfter() override;
    virtual TNameRef *searchF(u16, const char *) override;

    u32 _10;
    u32 _14;
    u32 _18;
    TIdxGroupObj *_1C;
    TIdxGroupObj *_20;
    TIdxGroupObj *_24;
    TIdxGroupObj *mPlayerGroup;
    TIdxGroupObj *_2C;
    TIdxGroupObj *_30;
    TIdxGroupObj *_34;
    TIdxGroupObj *_38;
    TIdxGroupObj *_3C;
    u32 _40;
    u32 _44;
    u32 _48;
    u32 _4C;
    u16 mHitObjFlags;
};

extern TStrategy *gpStrategy;