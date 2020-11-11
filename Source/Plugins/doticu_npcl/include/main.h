/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcl {

    class Main_t {
    public:
        static const IDebugLog& LOG();
        static const SKSEInterface*& SKSE();
        static const SKSEPapyrusInterface*& PAPYRUS();
        static const SKSEMessagingInterface*& MESSAGING();
        static PluginHandle& PLUGIN_HANDLE();

        static bool SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static bool SKSE_Load_Plugin(const SKSEInterface* skse);

        static bool Is_Installed();
        static void Init();
        static void Load();
    };

}
