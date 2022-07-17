#pragma once

#include <Dolphin/types.h>
#include <Dolphin/GX.h>

class JPADefaultTexture {
public:
    void initialize();

    void *mData;
    GXTexObj mTexObj;
};