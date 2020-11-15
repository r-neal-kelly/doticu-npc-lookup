/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/virtual_machine.h"

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    using Sex_e         = skylib::Sex_e;
    using Relation_e    = skylib::Relation_e;

    class Bases_t : public skylib::Quest_t {
    public:
        static constexpr const char* FILTER_VIEW    = "filter";
        static constexpr const char* LIST_VIEW      = "list";
        static constexpr const char* ITEM_VIEW      = "item";

        static Bases_t* Self();
        static String_t Class_Name();
        static Class_t* Class();

    public:
        Object_t*           Object();

        String_Variable_t*  Current_View_Variable();

        Int_Variable_t*     Filter_Option_Variable();
        Int_Variable_t*     Reset_Option_Variable();

        Int_Variable_t*     Name_Option_Variable();
        String_Variable_t*  Name_Argument_Variable();
        Int_Variable_t*     Negate_Name_Option_Variable();
        Bool_Variable_t*    Do_Negate_Name_Variable();

        Int_Variable_t*     Race_Option_Variable();
        String_Variable_t*  Race_Argument_Variable();
        Int_Variable_t*     Negate_Race_Option_Variable();
        Bool_Variable_t*    Do_Negate_Race_Variable();
        Int_Variable_t*     Insert_Race_Option_Variable();

        Int_Variable_t*     Mod_Option_Variable();
        String_Variable_t*  Mod_Argument_Variable();
        String_Variable_t*  Mod_View_Variable();
        Int_Variable_t*     Negate_Mod_Option_Variable();
        Bool_Variable_t*    Do_Negate_Mod_Variable();

        Int_Variable_t*     Relation_Option_Variable();
        Int_Variable_t*     Relation_Argument_Variable();
        String_Variable_t*  Relation_View_Variable();
        Int_Variable_t*     Negate_Relation_Option_Variable();
        Bool_Variable_t*    Do_Negate_Relation_Variable();

        Int_Variable_t*     Is_Male_Option_Variable();
        Int_Variable_t*     Is_Female_Option_Variable();
        Int_Variable_t*     Male_Female_Ternary_Variable();

        Int_Variable_t*     Is_Unique_Option_Variable();
        Int_Variable_t*     Is_Generic_Option_Variable();
        Int_Variable_t*     Unique_Generic_Ternary_Variable();

    public:
        String_t    Current_View();
        void        Current_View(String_t value);

        String_t    Name_Argument();
        void        Name_Argument(String_t value);
        Bool_t      Do_Negate_Name();
        void        Do_Negate_Name(Bool_t value);

        String_t    Race_Argument();
        void        Race_Argument(String_t value);
        Bool_t      Do_Negate_Race();
        void        Do_Negate_Race(Bool_t value);

        String_t    Mod_Argument();
        void        Mod_Argument(String_t value);
        String_t    Mod_View();
        void        Mod_View(String_t value);
        Bool_t      Do_Negate_Mod();
        void        Do_Negate_Mod(Bool_t value);

        Relation_e  Relation_Argument();
        void        Relation_Argument(Relation_e value);
        String_t    Relation_View();
        void        Relation_View(String_t value);
        Bool_t      Do_Negate_Relation();
        void        Do_Negate_Relation(Bool_t value);

        Int_t       Male_Female_Ternary();
        void        Male_Female_Ternary(Int_t value);

        Int_t       Unique_Generic_Ternary();
        void        Unique_Generic_Ternary(Int_t value);

        void        Reset_Filter();

    public:
        void On_Build_Page(Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

    private:
        void On_Build_Page_Filter(Latent_Callback_i* lcallback);
        void On_Option_Select_Filter(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_Filter(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_Filter(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_Filter(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Filter(Int_t option, Latent_Callback_i* lcallback);

        void On_Build_Page_List(Latent_Callback_i* lcallback);
        void On_Option_Select_List(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_List(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_List(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_List(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_List(Int_t option, Latent_Callback_i* lcallback);

        void On_Build_Page_Item(Latent_Callback_i* lcallback);
        void On_Option_Select_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_Item(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_Item(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Item(Int_t option, Latent_Callback_i* lcallback);

    public:
        static void Register_Me(Machine_t* machine);
    };

}}
