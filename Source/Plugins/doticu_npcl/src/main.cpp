/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "skse64/PluginAPI.h"

#include "doticu_skylib/utils.h"

#include "main.h"

namespace doticu_npcl {

    const IDebugLog& Main_t::LOG()
    {
        static const IDebugLog self;
        return self;
    }

    const SKSEInterface*& Main_t::SKSE()
    {
        static const SKSEInterface* self = nullptr;
        return self;
    }

    const SKSEPapyrusInterface*& Main_t::PAPYRUS()
    {
        static const SKSEPapyrusInterface* self = nullptr;
        return self;
    }

    const SKSEMessagingInterface*& Main_t::MESSAGING()
    {
        static const SKSEMessagingInterface* self = nullptr;
        return self;
    }

    PluginHandle& Main_t::PLUGIN_HANDLE()
    {
        static PluginHandle self;
        return self;
    }

    bool Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
        if (skse && info) {
            info->infoVersion = PluginInfo::kInfoVersion;
            info->name = "doticu_npcl";
            info->version = 1;
            return skse->skseVersion >= MAKE_EXE_VERSION(2, 0, 19);
        } else {
            return false;
        }
    }

    bool Main_t::SKSE_Load_Plugin(const SKSEInterface* skse)
    {
        LOG().OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcl.log");

        if (skse) {
            SKSE() = skse;
            PLUGIN_HANDLE() = skse->GetPluginHandle();
            PAPYRUS() = static_cast<SKSEPapyrusInterface*>
                (skse->QueryInterface(kInterface_Papyrus));
            MESSAGING() = static_cast<SKSEMessagingInterface*>
                (skse->QueryInterface(kInterface_Messaging));
            if (PAPYRUS() && MESSAGING()) {
                auto Callback = [](SKSEMessagingInterface::Message* message)->void
                {
                    if (message) {
                        if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
                            Is_New_Game() = true;
                        } else if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                            if (Is_New_Game()) {
                                Is_New_Game() = false;
                                Init();
                            }
                        } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                            Load();
                        }
                    }
                };
                MESSAGING()->RegisterListener(PLUGIN_HANDLE(), "SKSE", Callback);
                return true;
            } else {
                _FATALERROR("Unable to get papyrus or messaging interface.");
                return false;
            }
        } else {
            _FATALERROR("Unable to get skse interface.");
            return false;
        }
    }

    bool& Main_t::Is_New_Game()
    {
        static bool self = false;
        return self;
    }

    bool Main_t::Is_ESP_Installed()
    {
        return true;
    }

    void Main_t::Init()
    {
        if (Is_ESP_Installed()) {
            _MESSAGE("started a game.");
            // need to start quests.
        }
    }

    void Main_t::Load()
    {
        if (Is_ESP_Installed()) {
            _MESSAGE("loaded a game.");
        }
    }

}

extern "C" {

    bool SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_npcl::Main_t::SKSE_Query_Plugin(skse, info);
    }

    bool SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_npcl::Main_t::SKSE_Load_Plugin(skse);
    }

}
