#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGeometry/JGMVec.hxx>

#include <SMS/Strategic/LiveActor.hxx>
#include <SMS/Map/BGCheck.hxx>

void addAfterPreNode(int, int, TBGCheckList *list, TBGCheckList *addNode, int kind);
TBGCheckData *addGroundNode(TBGCheckList *list, TBGCheckData *data);
TBGCheckData *addRoofNode(TBGCheckList *list, TBGCheckData *data);
TBGCheckData *addWallNode(TBGCheckList *list, TBGCheckData *data);