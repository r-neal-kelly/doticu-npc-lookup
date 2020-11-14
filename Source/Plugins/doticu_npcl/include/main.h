/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcl {

    class Main_t {
    public:
        static const IDebugLog& LOG();
        static const SKSEInterface*& SKSE();
        static const SKSEPapyrusInterface*& PAPYRUS();
        static const SKSEMessagingInterface*& MESSAGING();
        static PluginHandle& PLUGIN_HANDLE();

        static Bool_t SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static Bool_t SKSE_Load_Plugin(const SKSEInterface* skse);
        static Bool_t SKSE_Register_Functions(skylib::Virtual::Registry_t* registry);

        static Bool_t Is_Installed();
        static Bool_t Is_Active();
        static void Init();
        static void Load();
    };

}
