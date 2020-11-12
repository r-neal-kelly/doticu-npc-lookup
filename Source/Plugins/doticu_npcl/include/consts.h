/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/quest.h"

#include "intrinsic.h"

namespace doticu_npcl {

    class Consts_t {
    public:
        static constexpr const char* NPCL_ESP_NAME = "doticu_npc_lookup.esp";

        static skylib::Mod_t* NPCL_Mod();

        static skylib::Quest_t* NPCL_MCM_Quest();
    };

}
