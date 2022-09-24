#pragma once

#include <Dolphin/types.h>
#include <SMS/m3d/M3UModel.hxx>

class M3UModelMario : public M3UModel {
public:
    virtual void updateIn() override;
    virtual void updateOut() override;

    void changeMtxCalcSIAnmBQAnmTransform(int, int, u8);
    void updateInMotion();
};