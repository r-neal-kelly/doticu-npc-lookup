/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/actor_base.h"

#include "consts.h"

namespace doticu_npcl {

    #define DEFINE_MOD(NAME_)                                           \
    SKYLIB_M                                                            \
        static skylib::Mod_t* mod = skylib::Mod_t::Active_Mod(NAME_);   \
        return mod;                                                     \
    SKYLIB_W

    #define DEFINE_FORM(MOD_PTR_, TYPE_, LOWER_FORM_ID_)        \
    SKYLIB_M                                                    \
        SKYLIB_ASSERT(MOD_PTR_);                                \
        static maybe<TYPE_*> form = static_cast<maybe<TYPE_*>>  \
            (skylib::Game_t::Form(MOD_PTR_, LOWER_FORM_ID_));   \
        SKYLIB_ASSERT(form);                                    \
        return form;                                            \
    SKYLIB_W

    #define DEFINE_VERSION(...)                             \
    SKYLIB_M                                                \
        static const Version_t<u8> version(__VA_ARGS__);    \
        return version;                                     \
    SKYLIB_W

    skylib::Actor_t*        Consts_t::Skyrim_Player_Actor()         { DEFINE_FORM(Skyrim_Mod(), skylib::Actor_t,        0x000014); }

    skylib::Actor_Base_t*   Consts_t::Skyrim_Player_Actor_Base()    { DEFINE_FORM(Skyrim_Mod(), skylib::Actor_Base_t,   0x000007); }

    skylib::Global_t*       Consts_t::NPCL_Is_Installed_Global()    { DEFINE_FORM(NPCL_Mod(),   skylib::Global_t,       0x000D63); }
    skylib::Global_t*       Consts_t::NPCL_Major_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   skylib::Global_t,       0x000D64); }
    skylib::Global_t*       Consts_t::NPCL_Minor_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   skylib::Global_t,       0x000D65); }
    skylib::Global_t*       Consts_t::NPCL_Patch_Version_Global()   { DEFINE_FORM(NPCL_Mod(),   skylib::Global_t,       0x000D66); }

    skylib::Mod_t*          Consts_t::Skyrim_Mod()                  { DEFINE_MOD(SKYRIM_ESM_NAME); }
    skylib::Mod_t*          Consts_t::NPCL_Mod()                    { DEFINE_MOD(NPCL_ESP_NAME); }

    skylib::Quest_t*        Consts_t::NPCL_MCM_Quest()              { DEFINE_FORM(NPCL_Mod(),   skylib::Quest_t,        0x000D62); }

    const Version_t<u8>     Consts_t::Skyrim_Required_Version()     { DEFINE_VERSION(1, 5, 97, 0); }
    const Version_t<u8>     Consts_t::NPCL_Version()                { DEFINE_VERSION(2, 0, 0); }

    #undef DEFINE_MOD
    #undef DEFINE_FORM
    #undef DEFINE_VERSION

}
