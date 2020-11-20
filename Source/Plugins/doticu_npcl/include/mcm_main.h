/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

namespace doticu_npcl { namespace MCM {

    using Ternary_e     = skylib::Ternary_e;
    using Comparator_e  = skylib::Comparator_e;

    namespace V {

        using Class_t           = skylib::Virtual::Class_t;
        using Machine_t         = skylib::Virtual::Machine_t;
        using Object_t          = skylib::Virtual::Object_t;
        using Stack_ID_t        = skylib::Virtual::Stack_ID_t;
        using Variable_t        = skylib::Virtual::Variable_t;
        using Bool_Variable_t   = skylib::Virtual::Bool_Variable_t;
        using Int_Variable_t    = skylib::Virtual::Int_Variable_t;
        using String_Variable_t = skylib::Virtual::String_Variable_t;

    }

    using Flag_e        = mcmlib::Flag_e;
    using Cursor_e      = mcmlib::Cursor_e;

    using Latent_Callback_i = Callback_i<>;

    class Main_t : public mcmlib::Config_Base_t {
    public:
        static constexpr const char*    MOD_NAME            = " NPC Lookup ";
        static constexpr const char*    BASES_PAGE          = " Bases ";
        static constexpr const char*    LEVELED_BASES_PAGE  = " Leveled Bases ";
        static constexpr const char*    REFERENCES_PAGE     = " References ";
        static constexpr const char*    DEFAULT_PAGE        = BASES_PAGE;

        static constexpr const char*    FILTER_LABEL        = "                               Filter";
        static constexpr const char*    OPTIONS_LABEL       = "                             Options";
        static constexpr const char*    PREVIOUS_PAGE_LABEL = "                     Go to Previous Page";
        static constexpr const char*    NEXT_PAGE_LABEL     = "                       Go to Next Page";
        static constexpr const char*    PREVIOUS_ITEM_LABEL = "                     Go to Previous Item";
        static constexpr const char*    NEXT_ITEM_LABEL     = "                       Go to Next Item";
        static constexpr const char*    BACK_LABEL          = "                               Back";
        static constexpr const char*    CLEAR_LABEL         = "                              Clear";
        static constexpr const char*    RESET_LABEL         = "                              Reset";

        static Int_t        String_Comparator(const char* str_a, const char* str_b);

        static Main_t*      Self();
        static String_t     Class_Name();
        static V::Class_t*  Class();

    public:
        V::Object_t*            Object();

        V::String_Variable_t*   Current_Page_Variable();

    public:
        String_t            Current_Page();
        void                Current_Page(String_t current_page);

        Latent_Callback_i*  Create_Latent_Callback(V::Machine_t* machine, V::Stack_ID_t stack_id);
        void                Destroy_Latent_Callback(Latent_Callback_i* lcallback);

        void                Toggle_Ternary(V::Int_Variable_t* ternary,
                                           Int_t high_option,
                                           Int_t low_option,
                                           Ternary_e toggle);

    public:
        Bool_t On_Config_Open(V::Machine_t* machine, V::Stack_ID_t stack_id);
        Bool_t On_Page_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, String_t current_page);
        Bool_t On_Option_Select(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Int_t idx);
        Bool_t On_Option_Slider_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Slider_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Float_t value);
        Bool_t On_Option_Input_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Highlight(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option);

    public:
        static void Register_Me(V::Machine_t* machine);
    };

}}
