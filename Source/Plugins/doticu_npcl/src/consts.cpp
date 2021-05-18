/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"

#include "consts.h"

namespace doticu_npcl {

    some<Actor_t*>      Consts_t::Skyrim_Player_Actor()         { DEFINE_FORM(Skyrim_Mod(), Actor_t,        0x000014); }

    some<Actor_Base_t*> Consts_t::Skyrim_Player_Actor_Base()    { DEFINE_FORM(Skyrim_Mod(), Actor_Base_t,   0x000007); }

    some<Global_t*>     Consts_t::NPCL_Is_Installed_Global()    { DEFINE_FORM(NPCL_Mod(),   Global_t,       0x000D63); }
    some<Global_t*>     Consts_t::NPCL_Major_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   Global_t,       0x000D64); }
    some<Global_t*>     Consts_t::NPCL_Minor_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   Global_t,       0x000D65); }
    some<Global_t*>     Consts_t::NPCL_Patch_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   Global_t,       0x000D66); }

    maybe<Mod_t*>       Consts_t::Skyrim_Mod()                  { DEFINE_MOD(SKYRIM_ESM_NAME); }
    maybe<Mod_t*>       Consts_t::NPCL_Mod()                    { DEFINE_MOD(NPCL_ESP_NAME); }

    some<Quest_t*>      Consts_t::NPCL_MCM_Quest()              { DEFINE_FORM(NPCL_Mod(),   Quest_t,        0x000D62); }

    const Version_t<u8> Consts_t::Skyrim_Required_Version()     { DEFINE_VERSION(u8, 1, 5, 97, 0); }
    const Version_t<u8> Consts_t::NPCL_Version()                { DEFINE_VERSION(u8, 2, 1, 3); }

}
