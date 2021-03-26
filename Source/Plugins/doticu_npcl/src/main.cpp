/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/interface.inl"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/main.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/ui.h"

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
                if (SKSE_PAPYRUS->Register(reinterpret_cast<SKSEPapyrusInterface::RegisterFunctions>(SKSE_Register_Functions))) {
                    auto Callback = [](SKSEMessagingInterface::Message* message)->void
                    {
                        if (message) {
                            if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                                if (Has_Requirements() && Is_Active()) {
                                    if (Is_Installed()) {
                                        Before_Save();
                                    } else {
                                        Init();
                                    }
                                }
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                if (Has_Requirements() && Is_Active()) {
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
            SKYLIB_LOG("Added " #TYPE_ " functions.");  \
        SKYLIB_W

        REGISTER(MCM::Main_t);

        #undef REGISTER

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    Bool_t Main_t::Has_Requirements()
    {
        const Version_t<skylib::u8>& running_skyrim_version = Game_t::Version();
        const Version_t<skylib::u8>& required_skyrim_version = Consts_t::Skyrim_Required_Version();

        if (running_skyrim_version < required_skyrim_version) {
            skylib::UI_t::Create_Message_Box("NPC Lookup will not work with your installed version of Skyrim: (" +
                                             std::to_string(running_skyrim_version.major) + "." +
                                             std::to_string(running_skyrim_version.minor) + "." +
                                             std::to_string(running_skyrim_version.patch) + "." +
                                             std::to_string(running_skyrim_version.build) + ")\n" +
                                             "This version of NPC Lookup was written for: (" +
                                             std::to_string(required_skyrim_version.major) + "." +
                                             std::to_string(required_skyrim_version.minor) + "." +
                                             std::to_string(required_skyrim_version.patch) + "." +
                                             std::to_string(required_skyrim_version.build) + ")\n" +
                                             "You need to update your version of Skyrim.",
                                             none<V::Callback_i*>());
            return false;
        } else if (running_skyrim_version > required_skyrim_version) {
            skylib::UI_t::Create_Message_Box("NPC Lookup will not work with your installed version of Skyrim: (" +
                                             std::to_string(running_skyrim_version.major) + "." +
                                             std::to_string(running_skyrim_version.minor) + "." +
                                             std::to_string(running_skyrim_version.patch) + "." +
                                             std::to_string(running_skyrim_version.build) + ")\n" +
                                             "This version of NPC Lookup was written for: (" +
                                             std::to_string(required_skyrim_version.major) + "." +
                                             std::to_string(required_skyrim_version.minor) + "." +
                                             std::to_string(required_skyrim_version.patch) + "." +
                                             std::to_string(required_skyrim_version.build) + ")\n" +
                                             "You should check for an update to NPC Lookup.",
                                             none<V::Callback_i*>());
            return false;
        } else {
            return true;
        }
    }

    Bool_t Main_t::Is_Active()
    {
        return Consts_t::NPCL_Mod() != none<Mod_t*>();
    }

    Bool_t Main_t::Is_Installed()
    {
        return Consts_t::NPCL_Is_Installed_Global()->Bool();
    }

    Bool_t Main_t::Are_Quests_Running()
    {
        const Vector_t<some<Quest_t*>>& quests = Quests();
        for (Index_t idx = 0, end = quests.size(); idx < end; idx += 1) {
            some<Quest_t*> quest = quests[idx];
            if (!quest->Is_Enabled()) {
                return false;
            }
        }
        return true;
    }

    const Vector_t<some<Quest_t*>>& Main_t::Quests()
    {
        static Vector_t<some<Quest_t*>> quests;
        if (quests.size() < 1) {
            quests.push_back(Consts_t::NPCL_MCM_Quest());
        }
        return quests;
    }

    void Main_t::Init()
    {
        SKYLIB_ASSERT(!Is_Installed());

        class Start_Quests_Callback_t : public Callback_i<Bool_t>
        {
            void operator()(Bool_t did_start_all)
            {
                if (did_start_all) {
                    Consts_t::NPCL_Is_Installed_Global()->Bool(true);

                    const Version_t<u8>& npcl_version = Consts_t::NPCL_Version();
                    Consts_t::NPCL_Major_Version_Global()->Int(npcl_version.major);
                    Consts_t::NPCL_Minor_Version_Global()->Int(npcl_version.minor);
                    Consts_t::NPCL_Patch_Version_Global()->Int(npcl_version.patch);

                    MCM::Main_t::Self()->On_Init();
                } else {
                    skylib::UI_t::Create_Message_Box(FAILED_TO_INIT_QUESTS, none<V::Callback_i*>());
                }
            }
        };
        Quest_t::Start(Quests(), new Start_Quests_Callback_t());
    }

    void Main_t::Reinit()
    {
        SKYLIB_ASSERT(Is_Installed());

        class Start_Quests_Callback_t : public Callback_i<Bool_t>
        {
            void operator()(Bool_t did_start_all)
            {
                if (did_start_all) {
                    MCM::Main_t::Self()->On_Load();
                    Try_To_Update();
                } else {
                    skylib::UI_t::Create_Message_Box(FAILED_TO_REINIT_QUESTS, none<V::Callback_i*>());
                }
            }
        };
        Quest_t::Start(Quests(), new Start_Quests_Callback_t());
    }

    void Main_t::After_Load()
    {
        SKYLIB_ASSERT(Is_Installed());

        //skylib::Main_t::After_Load();

        if (Are_Quests_Running()) {
            MCM::Main_t::Self()->On_Load();
            Try_To_Update();
        } else {
            skylib::UI_t::Create_Message_Box(FAILED_TO_LOAD_QUESTS, none<V::Callback_i*>());
            Reinit();
        }
    }

    void Main_t::Before_Save()
    {
        SKYLIB_ASSERT(Is_Installed());

        MCM::Main_t::Self()->On_Save();
    }

    Bool_t Main_t::Try_To_Update()
    {
        const Version_t<u8>& current = Consts_t::NPCL_Version();
        const Version_t<u8> saved(Consts_t::NPCL_Major_Version_Global()->Int(),
                                  Consts_t::NPCL_Minor_Version_Global()->Int(),
                                  Consts_t::NPCL_Patch_Version_Global()->Int());

        if (saved < current) {
            if (saved < Version_t<u8>(1, 1, 1)) {
                Update_1_1_1();
            }

            Consts_t::NPCL_Major_Version_Global()->Int(current.major);
            Consts_t::NPCL_Minor_Version_Global()->Int(current.minor);
            Consts_t::NPCL_Patch_Version_Global()->Int(current.patch);

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

    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Query(const SKSEInterface*, PluginInfo*);
    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Load(const SKSEInterface*);

    skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_npcl::Main_t::SKSE_Query_Plugin(skse, info);
    }

    skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_npcl::Main_t::SKSE_Load_Plugin(skse);
    }

}
