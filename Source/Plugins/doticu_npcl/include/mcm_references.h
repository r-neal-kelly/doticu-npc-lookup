/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/virtual_machine.h"

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    using Sex_e             = skylib::Sex_e;
    using Relation_e        = skylib::Relation_e;

    using CString_t         = skylib::CString_t;

    using Mod_t             = skylib::Mod_t;
    using Worldspace_t      = skylib::Worldspace_t;
    using Location_t        = skylib::Location_t;
    using Cell_t            = skylib::Cell_t;
    using Race_t            = skylib::Race_t;
    using Actor_Base_t      = skylib::Actor_Base_t;
    using Actor_t           = skylib::Actor_t;
    using Loaded_Actor_t    = skylib::Loaded_Actor_t;

    class References_t;
    class References_List_t;
    class References_Filter_t;
    class References_Options_t;
    class References_Item_t;

    class References_t : public skylib::Quest_t {
    public:
        static constexpr const char*    LIST_VIEW       = "list";
        static constexpr const char*    FILTER_VIEW     = "filter";
        static constexpr const char*    OPTIONS_VIEW    = "options";
        static constexpr const char*    ITEM_VIEW       = "item";

        class View_e : public skylib::Enum_t<skylib::Word_t>
        {
        public:
            enum
            {
                LIST,
                FILTER,
                OPTIONS,
                ITEM,
            };
            using Enum_t::Enum_t;
        };

        static References_t*    Self();
        static String_t         Class_Name();
        static Class_t*         Class();

    public:
        Object_t*           Object();

        String_Variable_t*  Current_View_Variable();
        Int_Variable_t*     Options_Offset_Variable();

    public:
        View_e      Current_View();
        void        Current_View(View_e value);
        Int_t       Options_Offset();
        void        Options_Offset(Int_t value);

    public:
        References_List_t*      List();
        References_Filter_t*    Filter();
        References_Options_t*   Options();
        References_Item_t*      Item();

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

    public:
        static void Register_Me(Machine_t* machine);
    };



    class References_List_t : public References_t
    {
    public:
        static constexpr Int_t  HEADERS_PER_PAGE = 6;
        static constexpr Int_t  ITEMS_PER_PAGE = 18;

        static Bool_t do_update_loaded_actors;

    public:
        Int_Variable_t* Filter_Option_Variable();
        Int_Variable_t* Options_Option_Variable();
        Int_Variable_t* Previous_Page_Option_Variable();
        Int_Variable_t* Next_Page_Option_Variable();
        Int_Variable_t* Page_Index_Variable();

    public:
        Int_t   Page_Index();
        void    Page_Index(Int_t value);

    public:
        String_t                    Format_Title(Int_t item_count, Int_t page_index, Int_t page_count);
        Vector_t<Loaded_Actor_t>&   Loaded_Actors();
        Loaded_Actor_t              Option_To_Loaded_Actor(Int_t option);

    public:
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
    };



    class References_Filter_t : public References_t
    {
    public:
        Int_Variable_t*     Back_Option_Variable();
        Int_Variable_t*     Clear_Option_Variable();

        Int_Variable_t*     Mod_Search_Option_Variable();
        Int_Variable_t*     Mod_Select_Option_Variable();
        Int_Variable_t*     Mod_Negate_Option_Variable();
        String_Variable_t*  Mod_Argument_Variable();
        Bool_Variable_t*    Mod_Do_Negate_Variable();

        Int_Variable_t*     Race_Search_Option_Variable();
        Int_Variable_t*     Race_Select_Option_Variable();
        Int_Variable_t*     Race_Negate_Option_Variable();
        String_Variable_t*  Race_Argument_Variable();
        Bool_Variable_t*    Race_Do_Negate_Variable();

        Int_Variable_t*     Base_Search_Option_Variable();
        Int_Variable_t*     Base_Select_Option_Variable();
        Int_Variable_t*     Base_Negate_Option_Variable();
        String_Variable_t*  Base_Argument_Variable();
        Bool_Variable_t*    Base_Do_Negate_Variable();

        Int_Variable_t*     Name_Search_Option_Variable();
        Int_Variable_t*     Name_Select_Option_Variable();
        Int_Variable_t*     Name_Negate_Option_Variable();
        String_Variable_t*  Name_Argument_Variable();
        Bool_Variable_t*    Name_Do_Negate_Variable();

        Int_Variable_t*     Location_Search_Option_Variable();
        Int_Variable_t*     Location_Select_Option_Variable();
        Int_Variable_t*     Location_Negate_Option_Variable();
        String_Variable_t*  Location_Argument_Variable();
        Bool_Variable_t*    Location_Do_Negate_Variable();

        Int_Variable_t*     Cell_Search_Option_Variable();
        Int_Variable_t*     Cell_Select_Option_Variable();
        Int_Variable_t*     Cell_Negate_Option_Variable();
        String_Variable_t*  Cell_Argument_Variable();
        Bool_Variable_t*    Cell_Do_Negate_Variable();

        Int_Variable_t*     Relation_Select_Option_Variable();
        Int_Variable_t*     Relation_Negate_Option_Variable();
        Int_Variable_t*     Relation_Argument_Variable();
        Bool_Variable_t*    Relation_Do_Negate_Variable();

        Int_Variable_t*     Is_Male_Option_Variable();
        Int_Variable_t*     Is_Female_Option_Variable();
        Int_Variable_t*     Male_Female_Ternary_Variable();

        Int_Variable_t*     Is_Unique_Option_Variable();
        Int_Variable_t*     Is_Generic_Option_Variable();
        Int_Variable_t*     Unique_Generic_Ternary_Variable();

        Int_Variable_t*     In_Interior_Option_Variable();
        Int_Variable_t*     In_Exterior_Option_Variable();
        Int_Variable_t*     Interior_Exterior_Ternary_Variable();

    public:
        String_t    Mod_Argument();
        void        Mod_Argument(String_t value);
        Bool_t      Mod_Do_Negate();
        void        Mod_Do_Negate(Bool_t value);

        String_t    Race_Argument();
        void        Race_Argument(String_t value);
        Bool_t      Race_Do_Negate();
        void        Race_Do_Negate(Bool_t value);

        String_t    Base_Argument();
        void        Base_Argument(String_t value);
        Bool_t      Base_Do_Negate();
        void        Base_Do_Negate(Bool_t value);

        String_t    Name_Argument();
        void        Name_Argument(String_t value);
        Bool_t      Name_Do_Negate();
        void        Name_Do_Negate(Bool_t value);

        String_t    Location_Argument();
        void        Location_Argument(String_t value);
        Bool_t      Location_Do_Negate();
        void        Location_Do_Negate(Bool_t value);

        String_t    Cell_Argument();
        void        Cell_Argument(String_t value);
        Bool_t      Cell_Do_Negate();
        void        Cell_Do_Negate(Bool_t value);

        Relation_e  Relation_Argument();
        void        Relation_Argument(Relation_e value);
        String_t    Relation_Argument_String();
        void        Relation_Argument_String(String_t value);
        Bool_t      Relation_Do_Negate();
        void        Relation_Do_Negate(Bool_t value);

        Ternary_e   Male_Female_Ternary();
        void        Male_Female_Ternary(Ternary_e value);

        Ternary_e   Unique_Generic_Ternary();
        void        Unique_Generic_Ternary(Ternary_e value);

        Ternary_e   Interior_Exterior_Ternary();
        void        Interior_Exterior_Ternary(Ternary_e value);

    public:
        Vector_t<Loaded_Actor_t>*   Execute(Vector_t<Loaded_Actor_t>* read, Vector_t<Loaded_Actor_t>* write);
        void                        Clear();

        Vector_t<String_t>          Selectable_Mods();
        Vector_t<String_t>          Selectable_Races();
        Vector_t<String_t>          Selectable_Bases();
        Vector_t<String_t>          Selectable_Names();
        Vector_t<String_t>          Selectable_Cells();
        Vector_t<String_t>          Selectable_Relations();

    public:
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
    };



    class References_Options_t : public References_t
    {
    public:
        Int_Variable_t*     Smart_Select_Option_Variable();
        Bool_Variable_t*    Do_Smart_Select_Variable();

    public:
        Bool_t  Do_Smart_Select();
        void    Do_Smart_Select(Bool_t value);

    public:
        void    Reset();

    public:
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
    };



    class References_Item_t : public References_t
    {
    public:
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
    };

}}
