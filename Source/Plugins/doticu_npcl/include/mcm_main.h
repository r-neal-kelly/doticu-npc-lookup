/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_machine.h"

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

namespace doticu_npcl { namespace MCM {

    using Machine_t = skylib::Virtual::Machine_t;
    using Stack_ID_t = skylib::Virtual::Stack_ID_t;
    using Class_t = skylib::Virtual::Class_t;
    using Object_t = skylib::Virtual::Object_t;
    using Variable_t = skylib::Virtual::Variable_t;
    using Bool_Variable_t = skylib::Virtual::Bool_Variable_t;
    using Int_Variable_t = skylib::Virtual::Int_Variable_t;
    using String_Variable_t = skylib::Virtual::String_Variable_t;

    using Cursor_e = mcmlib::Cursor_e;

    using Latent_Callback_i = Callback_i<>;

    enum class Ternary_e : skylib::s64
    {
        LOW = -1,
        NONE = 0,
        HIGH = 1,
    };

    class Main_t : public mcmlib::Config_Base_t {
    public:
        static constexpr const char* MOD_NAME           = " NPC Lookup ";
        static constexpr const char* RACES_PAGE         = " Races ";
        static constexpr const char* BASES_PAGE         = " Bases ";
        static constexpr const char* LEVELED_BASES_PAGE = " Leveled Bases ";
        static constexpr const char* REFERENCES_PAGE    = " References ";
        static constexpr const char* DEFAULT_PAGE       = BASES_PAGE;

        static Main_t*  Self();
        static String_t Class_Name();
        static Class_t* Class();

    public:
        Object_t* Object();

        String_Variable_t* Current_Page_Variable();

        String_t    Current_Page();
        void        Current_Page(String_t current_page);

        Latent_Callback_i*  Create_Latent_Callback(Machine_t* machine, Stack_ID_t stack_id);
        void                Destroy_Latent_Callback(Latent_Callback_i* lcallback);

        void                Toggle_Ternary(Int_Variable_t* ternary,
                                           Int_t high_option,
                                           Int_t low_option,
                                           Ternary_e toggle);

        Bool_t On_Build_Page(Machine_t* machine, Stack_ID_t stack_id, String_t current_page);
        Bool_t On_Option_Select(Machine_t* machine, Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t idx);
        Bool_t On_Option_Slider_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Slider_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Float_t value);
        Bool_t On_Option_Input_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(Machine_t* machine, Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Highlight(Machine_t* machine, Stack_ID_t stack_id, Int_t option);

    public:
        static void Register_Me(Machine_t* machine);
    };

}}
