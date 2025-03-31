#pragma once

#include <Dolphin/types.h>
#include <JSystem/JAudio/JAISound.hxx>

enum MSStageInfo {
    BGM_DOLPIC          = 0x80010001,
    BGM_BIANCO          = 0x80010002,
    BGM_MAMMA           = 0x80010003,
    BGM_PINNAPACO_SEA   = 0x80010004,
    BGM_PINNAPACO       = 0x80010005,
    BGM_MARE_SEA        = 0x80010006,
    BGM_MONTEVILLAGE    = 0x80010007,
    BGM_SHILENA         = 0x80010008,
    BGM_RICCO           = 0x80010009,
    BGM_GET_SHINE       = 0x8001000A,
    BGM_CHUBOSS         = 0x8001000B,
    BGM_MISS            = 0x8001000C,
    BGM_BOSS            = 0x8001000D,
    BGM_MAP_SELECT      = 0x8001000E,
    BGM_BOSSPAKU_DEMO   = 0x8001000F,
    BGM_MAIN_TITLE      = 0x80010010,
    BGM_CHUBOSS2        = 0x80010011,
    BGM_EXTRA           = 0x80010012,
    BGM_DELFINO         = 0x80010013,
    BGM_MAREVILLAGE     = 0x80010014,
    BGM_CORONA          = 0x80010015,
    BGM_KAGEMARIO       = 0x80010016,
    BGM_CAMERA          = 0x80010017,
    BGM_MONTE_ONSEN     = 0x80010018,
    BGM_MECHAKUPPA      = 0x80010019,
    BGM_AIRPORT         = 0x8001001A,
    BGM_UNDERGROUND     = 0x8001001B,
    BGM_TITLEBACK       = 0x8001001C,
    BGM_MONTE_NIGHT     = 0x8001001D,
    BGM_CASINO          = 0x8001001E,
    BGM_EVENT           = 0x8001001F,
    BGM_TIME_IVENT      = 0x80010020,
    BGM_SKY_AND_SEA     = 0x80010021,
    BGM_MONTE_RESCUE    = 0x80010022,
    BGM_MERRY_GO_ROUND  = 0x80010023,
    BGM_SCENARIO_SELECT = 0x80010024,
    BGM_FANFARE_CASINO  = 0x80010025,
    BGM_FANFARE_RACE    = 0x80010026,
    BGM_CAMERA_KAGE     = 0x80010027,
    BGM_GAMEOVER        = 0x80010028,
    BGM_BOSSHANA_2ND3RD = 0x80010029,
    BGM_BOSSGESO_2ND3RD = 0x8001002A,
    BGM_CHUBOSS_MANTA   = 0x8001002B,
    BGM_MONTE_LAST      = 0x8001002C,
    BGM_SHINE_APPEAR    = 0x8001002D,
    BGM_KUPPA           = 0x8001002E,
    BGM_MONTEMAN_RA     = 0x8001002F,
    BGM_SPACEWORLD      = 0x80011030
};

class MSBgm {
public:
    static void setStageBgmYoshiPercussion(bool);
    static void setDolby(u8, f32, u32, u8);
    static void setPan(u8, f32, u32, u8);
    static void setVolume(u32, f32, u32, u8);
    static void setTrackVolume(u8, f32, u32, u8);
    static void stopTrackBGMs(u8, u32);
    static void stopTrackBGM(u8, u32);
    static void stopBGM(u32 id, u32);
    static JAISound *getHandle(u8);
    static JAISound *startBGM(u32 id);
    static u32 getSceneNo(u32 id);
    static void init();

    static void *smBgmInTrack[4];  // JASystem::TTrack
};

extern u32 gDemoBGM;
extern u32 gStageBGM;