/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <fstream>
#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/global.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "consts.h"
#include "main.h"
#include "spawned_actors.h"
#include "mcm_main.h"

namespace doticu_npcl {

    const SKSEInterface* Main_t::SKSE                       = nullptr;
    const SKSEPapyrusInterface* Main_t::SKSE_PAPYRUS        = nullptr;
    const SKSEMessagingInterface* Main_t::SKSE_MESSAGING    = nullptr;
    PluginHandle Main_t::SKSE_PLUGIN_HANDLE                 = 0;

    Bool_t Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
        if (skse && info) {
            info->infoVersion = PluginInfo::kInfoVersion;
            info->name = "doticu_npcl";
            info->version = 1;
            return skse->skseVersion >= MAKE_EXE_VERSION(2, 0, 16);
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
                                    if (Is_Installed()) {
                                        Before_Save();
                                    } else {
                                        Init();
                                    }
                                }
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                if (Is_Active()) {
                                    if (Is_Installed()) {
                                        After_Load();
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
        SKYLIB_M                                        \
            TYPE_::Register_Me(machine);                \
            _MESSAGE("Added " #TYPE_ " functions.");    \
        SKYLIB_W

        REGISTER(MCM::Main_t);

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

        Consts_t::NPCL_Is_Installed_Global()->Bool(true);
        Consts_t::NPCL_Major_Version_Global()->Long(Consts_t::NPCL_Major_Version());
        Consts_t::NPCL_Minor_Version_Global()->Long(Consts_t::NPCL_Minor_Version());
        Consts_t::NPCL_Patch_Version_Global()->Long(Consts_t::NPCL_Patch_Version());

        Vector_t<skylib::Quest_t*> quests;
        quests.push_back(Consts_t::NPCL_MCM_Quest());

        class UCallback_t : public skylib::Callback_i<>
        {
            void operator()()
            {
                MCM::Main_t::Self()->On_Init();
            }
        };
        skylib::Quest_t::Start(quests, new UCallback_t());
    }

    void Main_t::After_Load()
    {
        SKYLIB_ASSERT(Is_Installed());

        MCM::Main_t::Self()->On_Load();

        Try_To_Update();
    }

    void Main_t::Before_Save()
    {
        SKYLIB_ASSERT(Is_Installed());

        MCM::Main_t::Self()->On_Save();
    }

    Bool_t Main_t::Try_To_Update()
    {
        Word_t saved_major = Consts_t::NPCL_Major_Version_Global()->Long();
        Word_t saved_minor = Consts_t::NPCL_Minor_Version_Global()->Long();
        Word_t saved_patch = Consts_t::NPCL_Patch_Version_Global()->Long();
        Word_t current_major = Consts_t::NPCL_Major_Version();
        Word_t current_minor = Consts_t::NPCL_Minor_Version();
        Word_t current_patch = Consts_t::NPCL_Patch_Version();

        auto Is_Less_Than = [saved_major, saved_minor, saved_patch](Word_t major, Word_t minor, Word_t patch)->Bool_t
        {
            return skylib::Is_Version_Less_Than(saved_major, saved_minor, saved_patch, major, minor, patch);
        };

        if (Is_Less_Than(current_major, current_minor, current_patch)) {

            if (Is_Less_Than(1, 1, 1)) {
                Update_1_1_1();
            }

            Consts_t::NPCL_Major_Version_Global()->Long(current_major);
            Consts_t::NPCL_Minor_Version_Global()->Long(current_minor);
            Consts_t::NPCL_Patch_Version_Global()->Long(current_patch);

            return true;
        } else {
            return false;
        }
    }

    void Main_t::Update_1_1_1()
    {
        MCM::Main_t::Self()->Update_1_1_1();
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
