/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcl {

    class Consts_t {
    public:
        static constexpr const char* SKYRIM_ESM_NAME    = "Skyrim.esm";
        static constexpr const char* NPCL_ESP_NAME      = "doticu_npc_lookup.esp";

        static some<Actor_t*>       Skyrim_Player_Actor();

        static some<Actor_Base_t*>  Skyrim_Player_Actor_Base();

        static some<Global_t*>      NPCL_Is_Installed_Global();
        static some<Global_t*>      NPCL_Major_Version_Global();
        static some<Global_t*>      NPCL_Minor_Version_Global();
        static some<Global_t*>      NPCL_Patch_Version_Global();

        static maybe<Mod_t*>        Skyrim_Mod();
        static maybe<Mod_t*>        NPCL_Mod();

        static some<Quest_t*>       NPCL_MCM_Quest();

        static const Version_t<u8>  Skyrim_Required_Version();
        static const Version_t<u8>  NPCL_Version();
    };

}
