/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "intrinsic.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Global_t;
    class Mod_t;
    class Quest_t;

}

namespace doticu_npcl {

    class Consts_t {
    public:
        static constexpr const char* SKYRIM_ESM_NAME    = "Skyrim.esm";
        static constexpr const char* NPCL_ESP_NAME      = "doticu_npc_lookup.esp";

        static skylib::Actor_Base_t*    Skyrim_Player_Actor_Base();

        static skylib::Global_t*        NPCL_Is_Installed_Global();

        static skylib::Mod_t*           Skyrim_Mod();
        static skylib::Mod_t*           NPCL_Mod();

        static skylib::Quest_t*         NPCL_MCM_Quest();

        static skylib::Word_t           NPCL_Major_Version();
        static skylib::Word_t           NPCL_Minor_Version();
        static skylib::Word_t           NPCL_Patch_Version();
    };

}
