/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "intrinsic.h"

namespace doticu_skylib {

    class Global_t;
    class Quest_t;

}

namespace doticu_npcl {

    class Consts_t {
    public:
        static constexpr const char* NPCL_ESP_NAME = "doticu_npc_lookup.esp";

        static skylib::Mod_t* NPCL_Mod();

        static skylib::Global_t* NPCL_Is_Installed_Global();

        static skylib::Quest_t* NPCL_MCM_Quest();
    };

}
