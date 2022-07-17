#pragma once

#include <Dolphin/types.h>
#include <Dolphin/GX.h>

#include <JSystem/JParticle/JPADataBlock.hxx>
#include <JSystem/JKernel/JKRHeap.hxx>
#include <JSystem/JUtility/JUTTexture.hxx>

class JPATexture : public JPADataBlock {
public:
    JPATexture(u8 *data, JKRHeap *heap);
    virtual ~JPATexture();

    JUTTexture mTexture;
};