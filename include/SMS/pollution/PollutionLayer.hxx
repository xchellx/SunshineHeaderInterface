#pragma once

#include <Dolphin/types.h>
#include <SMS/pollution/PollutionPos.hxx>

#include <SMS/j3d/Joint.hxx>

class TPollutionLayer : public TJointModel {

public:
    u16 mPollutionEffect;  // 0x0030
};