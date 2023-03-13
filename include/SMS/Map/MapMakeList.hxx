#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGeometry/JGMVec.hxx>

#include <SMS/Strategic/LiveActor.hxx>
#include <SMS/Map/BGCheck.hxx>

void addAfterPreNode(int, int, TBGCheckList *list, TBGCheckList *addNode, int kind);
TBGCheckList *addGroundNode(TBGCheckList *list, TBGCheckData *data);
TBGCheckList *addRoofNode(TBGCheckList *list, TBGCheckData *data);
TBGCheckList *addWallNode(TBGCheckList *list, TBGCheckData *data);