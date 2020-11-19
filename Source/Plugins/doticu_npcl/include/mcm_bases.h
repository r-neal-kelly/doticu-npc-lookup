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
    using Actor_Base_t  = skylib::Actor_Base_t;

    class Bases_t : public skylib::Quest_t {
    public:
        static constexpr const char*    FILTER_VIEW         = "filter";
        static constexpr const char*    OPTIONS_VIEW        = "options";
        static constexpr const char*    LIST_VIEW           = "list";
        static constexpr const char*    ITEM_VIEW           = "item";

        static constexpr Int_t          HEADERS_PER_PAGE    = 6;
        static constexpr Int_t          ITEMS_PER_PAGE      = 18;

        static Bases_t* Self();
        static String_t Class_Name();
        static Class_t* Class();

    public:
        Object_t*           Object();

        String_Variable_t*  Current_View_Variable();
        Int_Variable_t*     Options_Offset_Variable();

        Int_Variable_t*     Filter_Option_Variable();
        Int_Variable_t*     Options_Option_Variable();
        Int_Variable_t*     Previous_Page_Option_Variable();
        Int_Variable_t*     Next_Page_Option_Variable();
        Int_Variable_t*     Page_Index_Variable();

        Int_Variable_t*     Back_Option_Variable();
        Int_Variable_t*     Reset_Option_Variable();

        Int_Variable_t*     Name_Option_Variable();
        String_Variable_t*  Name_Argument_Variable();
        Int_Variable_t*     Negate_Name_Option_Variable();
        Bool_Variable_t*    Do_Negate_Name_Variable();

        Int_Variable_t*     Race_Option_Variable();
        String_Variable_t*  Race_Argument_Variable();
        Int_Variable_t*     Negate_Race_Option_Variable();
        Bool_Variable_t*    Do_Negate_Race_Variable();
        Int_Variable_t*     Select_Race_Option_Variable();

        Int_Variable_t*     Mod_Option_Variable();
        String_Variable_t*  Mod_Argument_Variable();
        Int_Variable_t*     Negate_Mod_Option_Variable();
        Bool_Variable_t*    Do_Negate_Mod_Variable();
        Int_Variable_t*     Select_Mod_Option_Variable();

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

        Int_t       Page_Index();
        void        Page_Index(Int_t value);

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
        Bool_t      Do_Negate_Mod();
        void        Do_Negate_Mod(Bool_t value);

        Relation_e  Relation_Argument();
        void        Relation_Argument(Relation_e value);
        String_t    Relation_View();
        void        Relation_View(String_t value);
        Bool_t      Do_Negate_Relation();
        void        Do_Negate_Relation(Bool_t value);

        Ternary_e   Male_Female_Ternary();
        void        Male_Female_Ternary(Ternary_e value);

        Ternary_e   Unique_Generic_Ternary();
        void        Unique_Generic_Ternary(Ternary_e value);

    private:
        String_t                    Format_List_Title(Int_t base_count, Int_t page_index, Int_t page_count);
        Vector_t<Actor_Base_t*>&    Actor_Bases();
        Actor_Base_t*               Option_To_Actor_Base(Int_t option);

        void                        Reset_Filter();
        Vector_t<Actor_Base_t*>&    Filter_Actor_Bases(Vector_t<Actor_Base_t*>* read, Vector_t<Actor_Base_t*>* write);

    public:
        void On_Config_Open();
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
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
        void On_Page_Open_Filter(Latent_Callback_i* lcallback);
        void On_Option_Select_Filter(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_Filter(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_Filter(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_Filter(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Filter(Int_t option, Latent_Callback_i* lcallback);

        void On_Page_Open_List(Latent_Callback_i* lcallback);
        void On_Option_Select_List(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_List(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_List(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_List(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_List(Int_t option, Latent_Callback_i* lcallback);

        void On_Page_Open_Item(Latent_Callback_i* lcallback);
        void On_Option_Select_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept_Item(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept_Item(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Item(Int_t option, Latent_Callback_i* lcallback);

    public:
        static void Register_Me(Machine_t* machine);
    };

}}
