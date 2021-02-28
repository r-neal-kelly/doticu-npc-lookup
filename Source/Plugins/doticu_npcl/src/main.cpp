/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <fstream>
#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/interface.inl"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/ui.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "consts.h"
#include "main.h"
#include "spawned_actors.h"
#include "mcm_main.h"

//temp
#include "doticu_skylib/armor.h"
#include "doticu_skylib/console_log.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/package_dialogue.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_utils.h"
//

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
            skylib::UI_t::Message_Box("NPC Lookup will not work with your installed version of Skyrim: (" +
                                      std::to_string(running_skyrim_version.major) + "." +
                                      std::to_string(running_skyrim_version.minor) + "." +
                                      std::to_string(running_skyrim_version.patch) + "." +
                                      std::to_string(running_skyrim_version.build) + ")\n" +
                                      "This version of NPC Lookup was written for: (" +
                                      std::to_string(required_skyrim_version.major) + "." +
                                      std::to_string(required_skyrim_version.minor) + "." +
                                      std::to_string(required_skyrim_version.patch) + "." +
                                      std::to_string(required_skyrim_version.build) + ")\n" +
                                      "You need to update your version of Skyrim.");
            return false;
        } else if (running_skyrim_version > required_skyrim_version) {
            skylib::UI_t::Message_Box("NPC Lookup will not work with your installed version of Skyrim: (" +
                                      std::to_string(running_skyrim_version.major) + "." +
                                      std::to_string(running_skyrim_version.minor) + "." +
                                      std::to_string(running_skyrim_version.patch) + "." +
                                      std::to_string(running_skyrim_version.build) + ")\n" +
                                      "This version of NPC Lookup was written for: (" +
                                      std::to_string(required_skyrim_version.major) + "." +
                                      std::to_string(required_skyrim_version.minor) + "." +
                                      std::to_string(required_skyrim_version.patch) + "." +
                                      std::to_string(required_skyrim_version.build) + ")\n" +
                                      "You should check for an update to NPC Lookup.");
            return false;
        } else {
            return true;
        }
    }

    Bool_t Main_t::Is_Active()
    {
        return Consts_t::NPCL_Mod() != nullptr;
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
                    skylib::UI_t::Message_Box(FAILED_TO_INIT_QUESTS);
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
                    skylib::UI_t::Message_Box(FAILED_TO_REINIT_QUESTS);
                }
            }
        };
        Quest_t::Start(Quests(), new Start_Quests_Callback_t());
    }

    static void Temp()
    {
        class Waiter_t :
            public skylib::Virtual::Callback_t
        {
        public:
            void operator ()(skylib::Virtual::Variable_t*)
            {
                Vector_t<some<Reference_t*>> references = Reference_t::Loaded_Grid_References();
                for (size_t idx = 0, end = references.size(); idx < end; idx += 1) {
                    some<Reference_t*> reference = references[idx];
                    maybe<Actor_t*> actor = reference->As_Actor();
                    if (actor) {
                        class Callback :
                            public skylib::Callback_i<Bool_t>
                        {
                        public:
                            some<Actor_t*> actor;
                            Callback(some<Actor_t*> actor) :
                                actor(actor)
                            {
                            }
                            virtual void operator () (Bool_t result) override
                            {
                                if (result) {
                                    _MESSAGE("%s", actor->Any_Name());
                                }
                            }
                        };
                        actor->Is_In_Dialogue_With_Player(new Callback(actor()));
                    }
                }
                skylib::Virtual::Utils_t::Wait_Out_Of_Menu(1.0f, new Waiter_t());
            }
        };
        skylib::Virtual::Utils_t::Wait_Out_Of_Menu(5.0f, new Waiter_t());

        some<Actor_t*> player_actor = Consts_t::Skyrim_Player_Actor();
        some<skylib::Faction_t*> player_faction = static_cast<skylib::Faction_t*>(Game_t::Form(0x00000DB1)());
        some<skylib::Faction_t*> current_follower_faction = static_cast<skylib::Faction_t*>(Game_t::Form(0x0005C84E)());

        Vector_t<some<Reference_t*>> references = Reference_t::Loaded_References();
        for (size_t idx = 0, end = references.size(); idx < end; idx += 1) {
            some<Reference_t*> reference = references[idx];
            maybe<Actor_t*> actor = reference->As_Actor();
            if (actor) {
                actor->Base_Relation(Consts_t::Skyrim_Player_Actor_Base(), skylib::Relation_e::ALLY);
                actor->Faction_Rank(current_follower_faction, 0);
                actor->Crime_Faction(player_faction());
                actor->Is_Player_Teammate(true);
                actor->Ignores_Ally_Hits(true);
            }
        }

        /*
        some<skylib::Bound_Object_t*> gold = static_cast<maybe<skylib::Bound_Object_t*>>(Game_t::Form(0xF))();
        some<skylib::Armor_t*> silver_ring = static_cast<maybe<skylib::Armor_t*>>(Game_t::Form(0x0003B97C))();

        for (size_t idx = 0, end = references.size(); idx < end; idx += 1) {
            Reference_t* reference = references[idx];
            if (reference) {
                skylib::Reference_Container_t container(reference);
                if (container.Is_Valid()) {
                    //container.Log();
                    for (size_t idx = 0, end = container.entries.size(); idx < end; idx += 1) {
                        skylib::Reference_Container_Entry_t& entry = container.entries[idx];
                        if (!entry.Is_Leveled_Item()) {
                            entry.Decrement_Count(&container, std::numeric_limits<skylib::s32>::max());
                            Vector_t<some<skylib::Extra_List_t*>> x_lists = entry.Some_Extra_Lists();
                            for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                                some<skylib::Extra_List_t*> x_list = x_lists[idx];
                                entry.Remove_And_Destroy(x_list);
                            }
                        }
                    }
                    maybe<Actor_t*> actor = reference->As_Actor();
                    if (actor) {
                        maybe<Actor_Base_t*> actor_base = actor->Actor_Base();
                        if (actor_base) {
                            maybe<skylib::Outfit_t*> outfit = actor_base->Default_Outfit();
                            if (outfit) {
                                some<skylib::Extra_List_t*> x_list = skylib::Extra_List_t::Create();
                                x_list->Increment_Count(2);
                                x_list->Outfit(outfit);
                                container.Add(silver_ring, x_list);

                                some<skylib::Extra_List_t*> other_x_list = skylib::Extra_List_t::Create();
                                other_x_list->Increment_Count(3);
                                other_x_list->Decrement_Count(1);
                                other_x_list->Outfit(outfit);
                                container.Try_To_Consume(silver_ring, other_x_list);

                                container.Log();
                            }
                        }
                    }
                }
            }
        }*/
    }

    void Main_t::After_Load()
    {
        //temp
        //Temp();
        //

        SKYLIB_ASSERT(Is_Installed());

        if (Are_Quests_Running()) {
            MCM::Main_t::Self()->On_Load();
            Try_To_Update();
        } else {
            skylib::UI_t::Message_Box(FAILED_TO_LOAD_QUESTS);
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
