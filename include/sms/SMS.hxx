#pragma once

#include <Dolphin/types.h>

#include <JSystem/JGeometry.hxx>
#include <JSystem/JUtility/JUTColor.hxx>
#include <JSystem/JUtility/JUTConsole.hxx>
#include <JSystem/JUtility/JUTResFont.hxx>
#include <JSystem/JParticle/JPAResourceManager.hxx>

#include <SMS/actor/Mario.hxx>
#include <SMS/camera/CameraMarioData.hxx>
#include <SMS/camera/CameraShake.hxx>
#include <SMS/camera/PolarSubCamera.hxx>
#include <SMS/collision/MapCollisionData.hxx>
#include <SMS/game/Application.hxx>
#include <SMS/game/GCConsole2.hxx>
#include <SMS/game/MarDirector.hxx>
#include <SMS/game/Strategy.hxx>
#include <SMS/game/Conductor.hxx>
#include <SMS/manager/EffectObjManager.hxx>
#include <SMS/manager/FlagManager.hxx>
#include <SMS/manager/PollutionManager.hxx>
#include <SMS/manager/RumbleManager.hxx>
#include <SMS/manager/MarioParticleManager.hxx>
#include <SMS/manager/ModelWaterManager.hxx>
#include <SMS/map/Map.hxx>
#include <SMS/option/CardLoad.hxx>
#include <SMS/sound/MSound.hxx>


extern JUtility::TColor gYoshiBodyColor[4];
extern TVec3f gShineShadowPos;
extern TMarioAnimeData gMarioAnimeData[336];
extern JUtility::TColor gModelWaterManagerWaterColor;
extern JUtility::TColor gYoshiJuiceColor[3];
extern TApplication gpApplication;
extern f32 gAudioVolume;
extern CPolarSubCamera *gpCamera;
extern TCameraMarioData *gpCameraMario;
extern TCameraShake *gpCameraShake;
extern TCardLoad *gpCardLoad;
extern TMap *gpMap;
extern TMapCollisionData *gpMapCollisionData;
extern f32 gEffectCoronaScale;
extern TPollutionManager *gpPollution;
extern float *gpNPCPtrSaveNormal;
extern RumbleMgr *gpPad1RumbleMgr;
extern RumbleMgr *gpPad2RumbleMgr;
extern RumbleMgr *gpPad3RumbleMgr;
extern RumbleMgr *gpPad4RumbleMgr;
extern TConductor *gpConductor;
extern TEffectObjManager *gpEffectObjManager;
extern TStrategy *gpStrategy;
extern TMario *gpMarioOriginal;
extern TMario *gpMarioAddress;
extern TVec3f *gpMarioPos;
extern TModelWaterManager *gpModelWaterManager;
extern TMarioParticleManager *gpMarioParticleManager;
extern TMarDirector *gpMarDirector;
extern MSound *gpMSound;
extern TCardManager *gpCardManager;
extern JPAResourceManager *gpResourceManager;
extern JUTResFont *gpSystemFont;
extern JUTResFont *gpRomFont;
extern void *gpArcBufferMario;
extern void *spGameHeapBlock;
extern void *gArbkConsole;
extern void *gArbkGuide;
extern u32 gDemoBGM;
extern u32 gStageBGM;
extern JUTConsole *sReportConsole;
extern JUTConsole *sWarningConsole;
extern f32 gAudioPitch;
extern f32 gAudioSpeed;