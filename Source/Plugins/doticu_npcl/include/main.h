/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skse_plugin.h"

#include "intrinsic.h"

namespace doticu_npcl {

    class Main_t :
        public SKSE_Plugin_t
    {
    public:
        static constexpr const char*    FAILED_TO_INIT_QUESTS   = "$dnpcl_failed_to_init_quests";
        static constexpr const char*    FAILED_TO_LOAD_QUESTS   = "$dnpcl_failed_to_load_quests";

    public:
        static const Vector_t<some<Quest_t*>>& Quests();

    public:
        Main_t();

    public:
        virtual         ~Main_t();

        virtual Bool_t  On_Register(some<V::Machine_t*> v_machine) override;

        virtual void    On_After_Load_Data() override;
        virtual void    On_After_New_Game() override;
        virtual void    On_Before_Save_Game(some<const char*> file_path, u32 file_path_length) override;
        virtual void    On_After_Save_Game() override;
        virtual void    On_Before_Load_Game(some<const char*> file_path, u32 file_path_length) override;
        virtual void    On_After_Load_Game(Bool_t did_load_successfully) override;
        virtual void    On_Before_Delete_Game(some<const char*> file_path, u32 file_path_length) override;
        virtual void    On_Update(u32 time_stamp) override;

    public:
        Bool_t  Is_Active();
        Bool_t  Is_Installed();
        Bool_t  Are_Quests_Running();

    private:
        Bool_t  Try_To_Update();
    };

    extern Main_t main;

}
