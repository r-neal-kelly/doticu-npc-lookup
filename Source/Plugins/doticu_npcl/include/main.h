/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace Virtual {

    class Machine_t;

}}

namespace doticu_npcl {

    class Main_t
    {
    public:
        static const SKSEInterface*             SKSE;
        static const SKSEPapyrusInterface*      SKSE_PAPYRUS;
        static const SKSEMessagingInterface*    SKSE_MESSAGING;
        static PluginHandle                     SKSE_PLUGIN_HANDLE;
        static IDebugLog                        SKSE_LOG;

        static Bool_t   SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static Bool_t   SKSE_Load_Plugin(const SKSEInterface* skse);
        static Bool_t   SKSE_Register_Functions(skylib::Virtual::Machine_t* machine);

    public:
        static Bool_t   Is_Active();
        static Bool_t   Is_Installed();

        static void     Init();
        static void     After_Load();
        static void     Before_Save();

    public:
        static Bool_t   Try_To_Update();
        static void     Update_1_1_1();
    };

}
