/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "filter.h"
#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    class Bases_View_e : public skylib::Enum_t<skylib::Word_t>
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

    template <typename Base_t, typename Item_t>
    class Bases_t : public Base_t
    {
    public:
        static constexpr const char*    LIST_VIEW       = "list";
        static constexpr const char*    FILTER_VIEW     = "filter";
        static constexpr const char*    OPTIONS_VIEW    = "options";
        static constexpr const char*    ITEM_VIEW       = "item";

    public:
        V::String_Variable_t* Current_View_Variable();

    public:
        Bases_View_e    Current_View();
        void            Current_View(Bases_View_e value);

    public:
        void On_Load();
        void On_Save();
        void On_Config_Open();
        void On_Config_Close();
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

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class Bases_List_t : public Bases_t<Base_t, Item_t>
    {
    public:
        static constexpr Int_t  HEADERS_PER_PAGE    = 6;
        static constexpr Int_t  ITEMS_PER_PAGE      = 18;

    public:
        static Bool_t               do_update_items;
        static Vector_t<Item_t>     read;
        static Vector_t<Item_t>     write;
        static Vector_t<Item_t>*    items;

    public:
        Int_t&  Filter_Option();
        Int_t&  Options_Option();
        Int_t&  Previous_Page_Option();
        Int_t&  Next_Page_Option();

    public:
        V::Int_Variable_t* Page_Index_Variable();

    public:
        Int_t   Page_Index();
        void    Page_Index(Int_t value);

    public:
        String_t    Title(Int_t item_count, Int_t page_index, Int_t page_count);
        Item_t      Option_To_Item(Int_t option);
        void        Clear();

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

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class Bases_Filter_t : public Bases_t<Base_t, Item_t>
    {
    public:
        Int_t&  Back_Option();
        Int_t&  Clear_Option();

        Int_t&  Mod_Search_Option();
        Int_t&  Mod_Select_Option();
        Int_t&  Mod_Negate_Option();

        Int_t&  Race_Search_Option();
        Int_t&  Race_Select_Option();
        Int_t&  Race_Negate_Option();

        Int_t&  Base_Search_Option();
        Int_t&  Base_Select_Option();
        Int_t&  Base_Negate_Option();

        Int_t&  Template_Search_Option();
        Int_t&  Template_Select_Option();
        Int_t&  Template_Negate_Option();

        Int_t&  Relation_Select_Option();
        Int_t&  Relation_Negate_Option();

        Int_t&  Male_Option();
        Int_t&  Female_Option();

        Int_t&  Unique_Option();
        Int_t&  Generic_Option();

    public:
        V::String_Variable_t*   Mod_Argument_Variable();
        V::Bool_Variable_t*     Mod_Do_Negate_Variable();

        V::String_Variable_t*   Race_Argument_Variable();
        V::Bool_Variable_t*     Race_Do_Negate_Variable();

        V::String_Variable_t*   Base_Argument_Variable();
        V::Bool_Variable_t*     Base_Do_Negate_Variable();

        V::String_Variable_t*   Template_Argument_Variable();
        V::Bool_Variable_t*     Template_Do_Negate_Variable();

        V::String_Variable_t*   Relation_Argument_Variable();
        V::Bool_Variable_t*     Relation_Do_Negate_Variable();

        V::Int_Variable_t*      Male_Female_Argument_Variable();
        V::Int_Variable_t*      Unique_Generic_Argument_Variable();

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

        String_t    Template_Argument();
        void        Template_Argument(String_t value);
        Bool_t      Template_Do_Negate();
        void        Template_Do_Negate(Bool_t value);

        String_t    Relation_Argument();
        void        Relation_Argument(String_t value);
        Bool_t      Relation_Do_Negate();
        void        Relation_Do_Negate(Bool_t value);

        Binary_e    Male_Female_Argument();
        void        Male_Female_Argument(Binary_e value);

        Binary_e    Unique_Generic_Argument();
        void        Unique_Generic_Argument(Binary_e value);

    public:
        String_t                Title();
        void                    Clear();
        Filter_State_t<Item_t>  Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write);

        Vector_t<String_t>      Selectable_Mods();
        Vector_t<String_t>      Selectable_Races();
        Vector_t<String_t>      Selectable_Bases();
        Vector_t<String_t>      Selectable_Templates();
        Vector_t<String_t>      Selectable_Relations();

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

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class Bases_Options_t : public Bases_t<Base_t, Item_t>
    {
    public:
        Int_t&  Back_Option();
        Int_t&  Reset_Option();

        Int_t&  Smart_Select_Option();
        Int_t&  Uncombative_Spawns_Option();
        Int_t&  Persistent_Spawns_Option();

    public:
        V::Bool_Variable_t* Do_Smart_Select_Variable();
        V::Bool_Variable_t* Do_Uncombative_Spawns_Variable();
        V::Bool_Variable_t* Do_Persistent_Spawns_Variable();

    public:
        Bool_t  Do_Smart_Select();
        void    Do_Smart_Select(Bool_t value);

        Bool_t  Do_Uncombative_Spawns();
        void    Do_Uncombative_Spawns(Bool_t value);

        Bool_t  Do_Persistent_Spawns();
        void    Do_Persistent_Spawns(Bool_t value);

    public:
        String_t    Title();
        void        Reset();

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

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class Bases_Item_t : public Bases_t<Base_t, Item_t>
    {
    public:
        Int_t&  Back_Option();
        Int_t&  Previous_Option();
        Int_t&  Next_Option();
        Int_t&  Primary_Option();

    public:
        String_t Title(const char* item_name);

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
