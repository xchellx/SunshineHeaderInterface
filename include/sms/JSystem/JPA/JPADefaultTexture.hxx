#pragma once

#include <dolphin/types.h>
#include <dolphin/GX.h>

class JPADefaultTexture {
public:
    void initialize();

    void *mData;
    GXTexObj mTexObj;
};