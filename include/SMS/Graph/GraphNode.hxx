#pragma once

#include <Dolphin/MTX.h>
#include <Dolphin/types.h>
#include <SMS/Graph/RailNode.hxx>

#include <JSystem/JGeometry.hxx>

class TGraphNode {

public:
    TGraphNode();
    void getPoint(Vec *out) const;

    TRailNode *mRailNode;
    u32 _04;
    f32 _08;
    u32 _0C;
};