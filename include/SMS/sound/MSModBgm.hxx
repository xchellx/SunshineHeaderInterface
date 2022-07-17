#pragma once

#include <Dolphin/types.h>
#include <SMS/sound/JAISound.hxx>

class MSModBgm {
public:
    void changeTempo(u8, u8);
    void loop();
    JAISound *modBgm(u8, u8);
};