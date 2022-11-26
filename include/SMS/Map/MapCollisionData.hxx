#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGeometry.hxx>
#include <JSystem/JSupport/JSUMemoryStream.hxx>

#include <SMS/Strategic/LiveActor.hxx>
#include <SMS/Map/BGCheck.hxx>
#include <SMS/Map/MapCheck.hxx>
#include <SMS/Map/MapCollisionBase.hxx>

class TMapCollisionData {
public:
    TMapCollisionData();

    void addCheckDataToGrid(TBGCheckData *, int);
    void *allocCheckData(u32);
    void *allocCheckList(int, int);
    // Flags are 0x1 = ignore water, 0x4 = ignore death planes
    f32 checkGround(f32 x, f32 y, f32 z, u8 ignoreFlags, const TBGCheckData **) const;
    f32 checkRoof(f32 x, f32 y, f32 z, u8, const TBGCheckData **) const;
    size_t checkWalls(TBGWallCheckRecord *) const;
    u16 getEntryID();
    bool getGridArea(const TBGCheckData *, int, int *, int *, int *, int *);
    void init(JSUMemoryInputStream &);
    void initMoveCollision();
    u32 intersectLine(const TVec3f &, const TVec3f &, bool, TVec3f *) const;
    bool polygonIsInGrid(f32, f32, f32, f32, TBGCheckData *);
    void removeCheckListData(u16, s32);
    void updateCheckListNode(s32, s32, s32);

    static f32 checkGroundList(f32 x, f32 y, f32 z, u8 ignoreFlags, const TBGCheckList *,
                               const TBGCheckData **);
    static f32 checkRoofList(f32 x, f32 y, f32 z, u8 ignoreFlags, const TBGCheckList *,
                             const TBGCheckData **);
    static size_t checkWallList(const TBGCheckList *, const TBGWallCheckRecord *);

    f32 mAreaSizeX;                          // 0x0000
    f32 mAreaSizeZ;                          // 0x0004
    size_t mBlockXCount;                     // 0x0008
    size_t mBlockZCount;                     // 0x000C
    size_t mBlockTotalCount;                 // 0x0010
    TBGCheckListRoot *mStaticCollisionRoot;  // 0x0014
    TBGCheckListRoot *mMoveCollisionRoot;    // 0x0014
    size_t mCheckDataCount;                  // 0x001C
    size_t mCheckListCount;                  // 0x0020
    size_t mCheckListWarpCount;              // 0x0024
    TBGCheckData *mCollisionTris;            // 0x0028
    TBGCheckList *mCollisionLists;           // 0x002C
    TBGCheckListWarp *mCollisionListWarps;   // 0x0030
    u32 _34;                                 // 0x0034
    size_t mCheckDataLength;                 // 0x0038
    size_t mCheckDataLength2;                // 0x003C
    u16 _40;                                 // 0x0040
    u16 mEntries[256];                       // 0x0042
    u16 mEntryID;
    u32 _244;

    static TBGCheckData mIllegalCheckData;
};

extern TMapCollisionData *gpMapCollisionData;