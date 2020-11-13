/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "skse64/PluginAPI.h"

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual.h"

#include "consts.h"
#include "main.h"
#include "mcm_main.h"

#include "doticu_skylib/cell.h"
#include "doticu_skylib/actor.h"
#include "doticu_skylib/worldspace.h"

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

    Bool_t Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
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

    Bool_t Main_t::SKSE_Load_Plugin(const SKSEInterface* skse)
    {
        static Bool_t is_new_game = false;

        LOG().OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcl.log");

        if (skse) {
            SKSE() = skse;
            PLUGIN_HANDLE() = skse->GetPluginHandle();
            PAPYRUS() = static_cast<SKSEPapyrusInterface*>
                (skse->QueryInterface(kInterface_Papyrus));
            MESSAGING() = static_cast<SKSEMessagingInterface*>
                (skse->QueryInterface(kInterface_Messaging));
            if (PAPYRUS() && MESSAGING()) {
                if (PAPYRUS()->Register(SKSE_Register_Functions)) {
                    auto Callback = [](SKSEMessagingInterface::Message* message)->void
                    {
                        if (message) {
                            if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
                                is_new_game = true;
                            } else if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                                if (is_new_game) {
                                    is_new_game = false;
                                    Init();
                                }
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                // we need to check if this is a new install, so init instead
                                Load();
                            }
                        }
                    };
                    MESSAGING()->RegisterListener(PLUGIN_HANDLE(), "SKSE", Callback);
                    return true;
                } else {
                    _FATALERROR("Unable to register functions.");
                    return false;
                }
            } else {
                _FATALERROR("Unable to get papyrus or messaging interface.");
                return false;
            }
        } else {
            _FATALERROR("Unable to get skse interface.");
            return false;
        }
    }

    Bool_t Main_t::SKSE_Register_Functions(skylib::Virtual::Registry_t* registry)
    {
        #define REGISTER(TYPE_)                                                             \
        M                                                                                   \
            TYPE_::Register_Me(reinterpret_cast<skylib::Virtual::Machine_t*>(registry));    \
            _MESSAGE("Added " #TYPE_ " functions.");                                        \
        W

        REGISTER(MCM::Main_t);

        #undef REGISTER

        _MESSAGE("Added all functions.\n");

        return true;
    }

    Bool_t Main_t::Is_Installed()
    {
        return Consts_t::NPCL_Mod() != nullptr;
    }

    void Main_t::Init()
    {
        if (Is_Installed()) { // I want a check with global variable too, to make sure we haven't init'd already. rare possibility
            _MESSAGE("Starting game.");

            Vector_t<skylib::Quest_t*> quests;
            quests.push_back(Consts_t::NPCL_MCM_Quest());

            class UCallback_t : public skylib::Callback_i<> {
                void operator()()
                {
                    _MESSAGE("Started quests.");
                }
            };
            skylib::Quest_t::Start(quests, new UCallback_t());
        }
    }

    void Main_t::Load()
    {
        if (Is_Installed()) {
            _MESSAGE("Loading game.");
            skylib::Actor_Base_t::Log_Actor_Bases();
            skylib::Actor_t::Log_Loaded_Actors();
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
