/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/global.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_utility.h"

#include "consts.h"
#include "main.h"
#include "spawned_actors.h"
#include "mcm_main.h"

namespace doticu_npcl {

    const Vector_t<some<Quest_t*>>& Main_t::Quests()
    {
        static Vector_t<some<Quest_t*>> quests;
        if (quests.size() < 1) {
            quests.push_back(Consts_t::NPCL_MCM_Quest());
        }
        return quests;
    }

    Main_t::Main_t() :
        SKSE_Plugin_t("doticu_npcl",
                      Version_t<u16>(1, 5, 97),
                      Operator_e::EQUAL_TO,
                      Version_t<u16>(2, 0, 16),
                      Operator_e::GREATER_THAN_OR_EQUAL_TO)
    {
        SKYLIB_LOG("doticu_npcl:");
    }

    Main_t::~Main_t()
    {
    }

    Bool_t Main_t::On_Register(some<V::Machine_t*> v_machine)
    {
        #define REGISTER(TYPE_)                             \
        SKYLIB_M                                            \
            TYPE_::Register_Me(v_machine);                  \
            SKYLIB_LOG("- Added " #TYPE_ " functions.");    \
        SKYLIB_W

        REGISTER(MCM::Main_t);

        #undef REGISTER

        SKYLIB_LOG("");

        return true;
    }

    void Main_t::On_After_Load_Data()
    {
    }

    void Main_t::On_After_New_Game()
    {
        if (Is_Active()) {
            if (Are_Quests_Running()) {
                Consts_t::NPCL_Is_Installed_Global()->Bool(true);

                const Version_t<u8>& npcl_version = Consts_t::NPCL_Version();
                Consts_t::NPCL_Major_Version_Global()->Int(npcl_version.major);
                Consts_t::NPCL_Minor_Version_Global()->Int(npcl_version.minor);
                Consts_t::NPCL_Patch_Version_Global()->Int(npcl_version.patch);

                MCM::Main_t::Self()->On_Init();

                class Wait_Callback :
                    public Callback_i<>
                {
                public:
                    virtual void operator ()() override
                    {
                        UI_t::Create_Notification(NPCL_PRINT_HEAD + "Thank you for playing!", none<V::Callback_i*>());
                    }
                };
                some<Wait_Callback*> wait_callback = new Wait_Callback();
                V::Utility_t::Wait_Out_Of_Menu(1.0f, wait_callback());
                (*wait_callback)();
            } else {
                UI_t::Create_Message_Box(FAILED_TO_INIT_QUESTS, none<V::Callback_i*>());
            }
        }
    }

    void Main_t::On_Before_Save_Game()
    {
        if (Is_Active() && Is_Installed()) {
            MCM::Main_t::Self()->On_Save();
        }
    }

    void Main_t::On_After_Save_Game()
    {
    }

    void Main_t::On_Before_Load_Game(some<const char*> file_path, u32 file_path_length)
    {
    }

    void Main_t::On_After_Load_Game(Bool_t did_load_successfully)
    {
        if (did_load_successfully) {
            if (Is_Active()) {
                if (Is_Installed()) {
                    if (Are_Quests_Running()) {
                        MCM::Main_t::Self()->On_Load();
                        Try_To_Update();
                    } else {
                        UI_t::Create_Message_Box(FAILED_TO_LOAD_QUESTS, none<V::Callback_i*>());
                    }
                } else {
                    On_After_New_Game();
                }
            }
        }
    }

    void Main_t::On_Before_Delete_Game(some<const char*> file_path, u32 file_path_length)
    {
    }

    void Main_t::On_Update(u32 time_stamp)
    {
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
        for (size_t idx = 0, end = quests.size(); idx < end; idx += 1) {
            some<Quest_t*> quest = quests[idx];
            if (!quest->Is_Enabled()) {
                return false;
            }
        }
        return true;
    }

    Bool_t Main_t::Try_To_Update()
    {
        const Version_t<u8>& current = Consts_t::NPCL_Version();
        const Version_t<u8> saved(Consts_t::NPCL_Major_Version_Global()->Int(),
                                  Consts_t::NPCL_Minor_Version_Global()->Int(),
                                  Consts_t::NPCL_Patch_Version_Global()->Int());

        if (saved < current) {
            if (saved < Version_t<u8>(1, 1, 1)) {
                MCM::Main_t::Self()->Update_1_1_1();
            }

            Consts_t::NPCL_Major_Version_Global()->Int(current.major);
            Consts_t::NPCL_Minor_Version_Global()->Int(current.minor);
            Consts_t::NPCL_Patch_Version_Global()->Int(current.patch);

            UI_t::Create_Notification(NPCL_PRINT_HEAD + "Updated to version " +
                                      std::to_string(current.major) + "." +
                                      std::to_string(current.minor) + "." +
                                      std::to_string(current.patch),
                                      none<V::Callback_i*>());

            return true;
        } else {
            return false;
        }
    }

    Main_t main;

}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_npcl::main);
