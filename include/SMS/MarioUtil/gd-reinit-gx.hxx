#pragma once

#include <Dolphin/types.h>
#include <Dolphin/MTX.h>

#include <JSystem/JUtility/JUTColor.hxx>
#include <JSystem/JUtility/JUTTexture.hxx>

extern "C" {
	void ReInitializeGX();

	extern JUtility::TColor ColorWhite;
	extern JUtility::TColor ColorBlack;
}

void ReInitGeometry();
void ReInitTransform();
void ReInitTevStages();

extern u32 NullTexData[4];
extern Mtx IdentityMtx;