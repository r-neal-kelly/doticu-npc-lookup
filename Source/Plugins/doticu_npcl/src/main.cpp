/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/actor.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/mod.h"

#include "consts.h"
#include "main.h"
#include "mcm_main.h"
#include "mcm_bases.h"
#include "mcm_leveled_bases.h"
#include "mcm_references.h"

namespace doticu_npcl {

    const SKSEInterface* Main_t::SKSE = nullptr;
    const SKSEPapyrusInterface* Main_t::SKSE_PAPYRUS = nullptr;
    const SKSEMessagingInterface* Main_t::SKSE_MESSAGING = nullptr;
    PluginHandle Main_t::SKSE_PLUGIN_HANDLE = 0;

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
        SKSE_LOG.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcl.log");
        if (skse) {
            SKSE = skse;
            SKSE_PAPYRUS = static_cast<const SKSEPapyrusInterface*>(SKSE->QueryInterface(kInterface_Papyrus));
            SKSE_MESSAGING = static_cast<const SKSEMessagingInterface*>(SKSE->QueryInterface(kInterface_Messaging));
            SKSE_PLUGIN_HANDLE = SKSE->GetPluginHandle();
            if (SKSE_PAPYRUS && SKSE_MESSAGING) {
                if (SKSE_PAPYRUS->Register(reinterpret_cast<Bool_t(*)(skylib::Virtual::Registry_t*)>(SKSE_Register_Functions))) {
                    auto Callback = [](SKSEMessagingInterface::Message* message)->void
                    {
                        if (message) {
                            if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                                if (Is_Active()) {
                                    if (!Is_Installed()) {
                                        Init();
                                    }
                                }
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                if (Is_Active()) {
                                    if (Is_Installed()) {
                                        Load();
                                    } else {
                                        Init();
                                    }
                                }
                            }
                        }
                    };
                    SKSE_MESSAGING->RegisterListener(SKSE_PLUGIN_HANDLE, "SKSE", Callback);
                    return true;
                } else {
                    _FATALERROR("Unable to register functions.");
                    return false;
                }
            } else {
                _FATALERROR("Unable to get papyrus and/or messaging interface.");
                return false;
            }
        } else {
            _FATALERROR("Unable to get skse interface.");
            return false;
        }
    }

    Bool_t Main_t::SKSE_Register_Functions(skylib::Virtual::Machine_t* machine)
    {
        #define REGISTER(TYPE_)                         \
        M                                               \
            TYPE_::Register_Me(machine);                \
            _MESSAGE("Added " #TYPE_ " functions.");    \
        W

        REGISTER(MCM::Main_t);
        REGISTER(MCM::Bases_t);
        REGISTER(MCM::Leveled_Bases_t);
        REGISTER(MCM::References_t);

        #undef REGISTER

        _MESSAGE("Added all functions.\n");

        return true;
    }

    Bool_t Main_t::Is_Active()
    {
        return Consts_t::NPCL_Mod() != nullptr;
    }

    Bool_t Main_t::Is_Installed()
    {
        return Consts_t::NPCL_Is_Installed_Global()->Bool();
    }

    void Main_t::Init()
    {
        SKYLIB_ASSERT(!Is_Installed());

        _MESSAGE("Starting game.");

        Consts_t::NPCL_Is_Installed_Global()->Bool(true);

        Vector_t<skylib::Quest_t*> quests;
        quests.push_back(Consts_t::NPCL_MCM_Quest());

        class UCallback_t : public skylib::Callback_i<>
        {
            void operator()()
            {
                _MESSAGE("Started quests.");
            }
        };
        skylib::Quest_t::Start(quests, new UCallback_t());
    }

    void Main_t::Load()
    {
        SKYLIB_ASSERT(Is_Installed());

        _MESSAGE("Loading game.");
        skylib::Mod_t::Log_Mods();
        skylib::Mod_t::Log_Active_Mods();
        skylib::Mod_t::Log_Active_Heavy_Mods();
        skylib::Mod_t::Log_Active_Light_Mods();
        skylib::Race_t::Log_Races();
        skylib::Actor_Base_t::Log_Actor_Bases();
        skylib::Leveled_Actor_Base_t::Log_Leveled_Actor_Bases();
        skylib::Actor_t::Log_Loaded_Actors();
    }

}

extern "C" {

    skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_npcl::Main_t::SKSE_Query_Plugin(skse, info);
    }

    skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_npcl::Main_t::SKSE_Load_Plugin(skse);
    }

}
