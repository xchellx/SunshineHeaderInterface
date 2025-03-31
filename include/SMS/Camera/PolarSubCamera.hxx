#pragma once

#include <Dolphin/types.h>
#include <JSystem/JDrama/JDRCamera.hxx>
#include <JSystem/JDrama/JDRGraphics.hxx>
#include <SMS/Camera/CameraInbetween.hxx>
#include <SMS/Camera/CameraKindParam.hxx>
#include <SMS/Camera/CameraMapTool.hxx>
#include <SMS/NPC/NpcBase.hxx>

class CPolarSubCamera : public JDrama::TLookAtCamera {
public:
    enum EnumNoticeOnOffMode { UNK_MODE_0, UNK_MODE_1, UNK_MODE_2 };

    CPolarSubCamera(const char *);
    virtual ~CPolarSubCamera();

    virtual void loadAfter() override;
    virtual void perform(u32, JDrama::TGraphics *) override;

    void addMoveCameraAndMario(const Vec &pos);
    void addMultiPlayer(const TVec3f *, f32, f32);
    s32 calcAngleXFromXRotRatio_() const;
    s32 calcDistFromXRotRatio_() const;
    void calcFinalPosAndAt_();
    void calcInHouseNo_(bool);
    void calcNoticeTargetYrot_(const Vec &);
    void calcNowTargetFromPosAndAt_(const Vec &, const Vec &);
    void calcPosAndAt_();
    void calcSecureViewTarget_(s16, f32 *, f32 *);
    void calcSlopeAngleX_(s16 *);
    void calcTowerCenterPos_(Vec *);
    void changeCamModeSpecifyCamMapTool_(const TCameraMapTool *);
    void changeCamModeSpecifyCamMapToolAndFrame_(const TCameraMapTool *, int);
    void changeCamModeSpecifyFrame_(int, int);
    void changeCamModeSub_(int, int, bool);
    void controlByCameraCode_(int *);
    void createMultiplayer(u8);
    void ctrlGameCamera_();
    void ctrlJetCoasterCamera_();
    void ctrlLButtonCamera_();
    void ctrlMultiPlayerCamera_();
    void ctrlNormalDeadDemo_();
    void ctrlNormalOrTowerCamera_();
    void ctrlOptionCamera_();
    void ctrlTalkCamera_();
    void doLButtonCameraOff_(bool);
    void endDemoCamera();
    void execCameraModeChangeProc_(int);
    void execDeadDemoProc_();
    void execFrontRotate_();
    void execGroundCheck_(Vec);
    void execHeightPan_();
    void exeInvalidAutoChase_();
    void execNoticeOnOffProc_(EnumNoticeOnOffMode);
    void execRoofCheck_(Vec);
    void execSecureView_(s16, Vec *);
    void execWallCheck_(Vec *);
    s16 getCameraInbetweenFrame_(int);
    s16 getFinalAngleZ() const;
    void *getNoticeActor_();
    TVec3f *getNozzleTopPos_(TVec3f *) const;
    s16 getOffsetAngleX() const;
    s16 getOffsetAngleY() const;
    s32 getRestDemoFrames() const;
    Mtx *getToroccoMtx_() const;
    TVec3f getUsualLookat() const;
    bool isChangeToBossGesoCamera_() const;
    bool isChangeToCancanCamera_() const;
    bool isChangeToParallelCameraByMoveBG_() const;
    bool isChangeToParallelCameraCByMoveBG_() const;
    bool isDefiniteCameraSpecifyMode(int) const;
    bool isFixCameraSpecifyMode(int) const;
    bool isFollowCameraSpecifyMode(int) const;
    bool isHellDeadDemo() const;
    bool isJetCoaster1stCamera() const;
    bool isLButtonCameraInbetween();
    bool isLButtonCameraSpecifyMode(int);
    bool isMarioAimWithGun_() const;
    bool isMarioCrabWalk_() const;
    bool isMomentDefinite_() const;
    bool isNeedGroundCheck_();
    bool isNeedRoofCheck_() const;
    bool isNeedWallCheck_() const;
    bool isNormalCameraCompletely() const;
    bool isNormalCameraSpecifyMode(int) const;
    bool isNormalDeadDemo() const;
    bool isNotHeightPanCamMode_() const;
    bool isNowInbetween() const;
    bool isOverHipAttackSpecifyMode(int) const;
    bool isRailCameraSpecifyMode(int) const;
    bool isSimpleDemoCamera() const;
    bool isSlopeCameraMode() const;
    bool isTalkCameraInbetween() const;
    bool isTalkCameraSpecifyMode(int) const;
    bool isTowerCameraSpecifyMode(int) const;
    void killHeightPan_();
    void killHeightPanWhenChangeCamMode_();
    void makeMtxForPrevTalk();
    void makeMtxForTalk(const TBaseNPC *);
    void offMoveApproach_();
    void onMoveApproach_();
    void removeMultiPlayer(const TVec3f *);
    void rotateX_ByStickY_(f32);
    void rotateY_ByStickX_(f32);
    void setNoticeInfo();
    void setUpFromLButtonCamera_();
    void setUpToLButtonCamera_(int);
    void startDemoCamera(const char *, const TVec3f *, s32, f32, bool);
    void startGateDemoCamera(const JDrama::TActor *);
    void updateDemoCamera_(bool);
    void updateGateDemoCamera_();
    void warpPosAndAt(f32, s16);
    void warpPosAndAt(const Vec &, const Vec &);

    u32 _00[0x14 / 4];  // 0x0050
    struct {
        u8 _00                : 4;
        bool mCenterUp        : 1;
        bool mDisableMovement : 1;
        u32 _01               : 10;
    } mStateFlags;  // 0x0064
    TCameraKindParam *mCamParams;
    TCameraInbetween *mInbetween;  // 0x006C
    u32 _01[0x34 / 4];             // 0x0070
    u16 _02;                       // 0x00A4
    s16 mHorizontalAngle;          // 0x00A6
    f32 mInterpolateDistance;      // 0x00A8
    u32 _AC[0x78 / 4];
    TVec3f mWorldTranslation;  // 0x0124
    u32 _130[0x3C / 4];
    Mtx mProjectionMatrix;  // 0x016C
    u32 _19C[0x50 / 4];
    Mtx mTRSMatrix;  // 0x01EC
    u32 _21C[0x38 / 4];
    u16 _254;
    s16 mAnglePitch;  // 0x0256   matan(sqrtf((cam.x - mar.x) * (cam.x - mar.x) + (cam.z - mar.z) *
                      //                (cam.z - mar.z)), cam.y - mar.y);
    s16 mAngleYaw;    // 0x0258   matan(cam.z - mar.z, cam.x - mar.x);
    u32 _25C[0xF4 / 4];

    static char *mCamKindNameSaveFile[73];
};

struct TCamParamData {
    f32 mProjectionFovy;
    f32 mNearClipDist;
    f32 mNearCamDist;
    f32 mFarCamDist;
    f32 mNearCurveBezierPointOut;
    f32 mFarCurveBezierPointOut;
    s16 mNearAxisFocalRotationY;
    s16 mFarAxisFocalRotationY;
    f32 mCameraZoomSpeed;
    s16 mCameraRotateSpeed;
    s16 _22;
    f32 mNearCamFocalHeight;
    f32 mFarCamFocalHeight;
    f32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 mNearCamAtSideForwardDist;
    f32 _40;
    f32 mFarCamAtSideForwardDist;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    s16 mCamAxisFocalRotationX2;
    s16 mCamAxisFocalRotationY2;
    f32 mCamXOffset;
    f32 _60[0x9C / 4];
};

extern CPolarSubCamera *gpCamera;