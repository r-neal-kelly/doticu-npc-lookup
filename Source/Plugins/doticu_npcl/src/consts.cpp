/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/game.h"

#include "consts.h"

namespace doticu_npcl {

    skylib::Mod_t* Consts_t::NPCL_Mod()
    {
        static skylib::Mod_t* self = skylib::Game_t::Mod(NPCL_ESP_NAME);
        return self;
    }

    #define DEFINE_FORM(MOD_PTR, TYPE, LOWER_FORM_ID)       \
    M                                                       \
        static TYPE* form = static_cast<TYPE*>              \
            (skylib::Game_t::Form(MOD_PTR, LOWER_FORM_ID)); \
        SKYLIB_ASSERT(form);                                \
        return form;                                        \
    W

    skylib::Quest_t* Consts_t::NPCL_MCM_Quest() { DEFINE_FORM(NPCL_Mod(), skylib::Quest_t, 0x000D62); }

    #undef DEFINE_FORM

}
