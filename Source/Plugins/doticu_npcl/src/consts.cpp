/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/actor_base.h"

#include "consts.h"

namespace doticu_npcl {

    #define DEFINE_MOD(NAME_)                                   \
    M                                                           \
        static skylib::Mod_t* mod = skylib::Game_t::Mod(NAME_); \
        return mod;                                             \
    W

    #define DEFINE_FORM(MOD_PTR_, TYPE_, LOWER_FORM_ID_)        \
    M                                                           \
        SKYLIB_ASSERT(MOD_PTR_);                                \
        static TYPE_* form = static_cast<TYPE_*>                \
            (skylib::Game_t::Form(MOD_PTR_, LOWER_FORM_ID_));   \
        SKYLIB_ASSERT(form);                                    \
        return form;                                            \
    W

    skylib::Actor_Base_t*   Consts_t::Skyrim_Player_Actor_Base()    { DEFINE_FORM(Skyrim_Mod(), skylib::Actor_Base_t, 0x000007); }

    skylib::Global_t*       Consts_t::NPCL_Is_Installed_Global()    { DEFINE_FORM(NPCL_Mod(), skylib::Global_t, 0x000D63); }

    skylib::Mod_t*          Consts_t::Skyrim_Mod()                  { DEFINE_MOD(SKYRIM_ESM_NAME); }
    skylib::Mod_t*          Consts_t::NPCL_Mod()                    { DEFINE_MOD(NPCL_ESP_NAME); }

    skylib::Quest_t*        Consts_t::NPCL_MCM_Quest()              { DEFINE_FORM(NPCL_Mod(), skylib::Quest_t, 0x000D62); }

    skylib::Word_t          Consts_t::NPCL_Major_Version()          { return 1; }
    skylib::Word_t          Consts_t::NPCL_Minor_Version()          { return 0; }
    skylib::Word_t          Consts_t::NPCL_Patch_Version()          { return 0; }

    #undef DEFINE_MOD
    #undef DEFINE_FORM

}
