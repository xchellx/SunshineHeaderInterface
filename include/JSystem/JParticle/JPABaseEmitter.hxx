#pragma once

#include <JSystem/JParticle/JPABaseParticle.hxx>
#include <JSystem/JSupport/JSUList.hxx>

class JPABaseEmitter : public JSUPtrLink {
public:
    JPABaseEmitter();

    void calc();

    JPABaseParticle *calcCreateParticle();
    void calcCurrentRateTimerStep();
    void calcEmitterGlobalParams();
    void calcKeyFrameAnime();
    bool checkMaxFrame();
    bool checkStartFrame();
    JPABaseParticle *createChildParticle(JPABaseParticle *particle);
    JPABaseParticle *createParticle();
    void deleteAllParticle();
    void doChildParticle();
    void doParticle();
    void drawEmitterCallback();
    f32 getAspect();
    void getEmitterGlobalTranslation(TVec3f &);
    f32 getFovy();
    void loadBaseEmitterBlock(JPABaseParticle * /*JPADataBlock **/);
    void setGlobalRTMatrix(Mtx);
    void setGlobalSRTMatrix(Mtx);

    u32 _0C[0xE8 / 4];
    JSUPtrList mParticleList;  // _F4
    JSUPtrList mChildParticleList;  // _100
    u32 _10C[0x50 / 4];
    TVec3f mSize1;
    u32 _160;
    TVec3f mSize2;
    u32 _170;
    TVec3f mSize3;
    u32 _180[0xB0 / 4];
};