/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "filter.h"
#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    class Toggle_Type_e : public Enum_t<Word_t>
    {
    public:
        enum : Word_t
        {
            EITHER,
            ANY,
        };
        using Enum_t::Enum_t;
    };

    using Item_Section_t = s64;

    class Bases_Item_Section_e : public Enum_t<Item_Section_t>
    {
    public:
        enum : _TYPE_
        {
            NONE = -1,

            BASES,
            COMMANDS,
            FACTIONS,
            KEYWORDS,
            MODS,
            RACES,
            TEMPLATES,

            _END_,
        };
        using Enum_t::Enum_t;

        static some<const char*>    To_String(Bases_Item_Section_e section_e);
        static Bases_Item_Section_e From_String(some<const char*> section_str);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Bases_View_e : public Enum_t<Word_t>
    {
    public:
        enum : Word_t
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
        void On_Init();
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

        void    Reset_Option_Ints();

    public:
        V::Int_Variable_t* Page_Index_Variable();

    public:
        Int_t   Page_Index();
        void    Page_Index(Int_t value);

    public:
        void    Clear();

    public:
        void On_Init();
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

        Int_t&  Faction_Search_Option();
        Int_t&  Faction_Select_Option();
        Int_t&  Faction_Negate_Option();

        Int_t&  Keyword_Search_Option();
        Int_t&  Keyword_Select_Option();
        Int_t&  Keyword_Negate_Option();

        Int_t&  Relation_Select_Option();
        Int_t&  Relation_Negate_Option();

        Int_t&  Vitality_Select_Option();
        Int_t&  Vitality_Negate_Option();

        Int_t&  Male_Option();
        Int_t&  Female_Option();

        Int_t&  Unique_Option();
        Int_t&  Generic_Option();

        void    Reset_Option_Ints();

    public:
        V::String_Variable_t*   Mod_Argument_Variable();
        V::Bool_Variable_t*     Mod_Do_Negate_Variable();

        V::String_Variable_t*   Race_Argument_Variable();
        V::Bool_Variable_t*     Race_Do_Negate_Variable();

        V::String_Variable_t*   Base_Argument_Variable();
        V::Bool_Variable_t*     Base_Do_Negate_Variable();

        V::String_Variable_t*   Template_Argument_Variable();
        V::Bool_Variable_t*     Template_Do_Negate_Variable();

        V::String_Variable_t*   Faction_Argument_Variable();
        V::Bool_Variable_t*     Faction_Do_Negate_Variable();

        V::String_Variable_t*   Keyword_Argument_Variable();
        V::Bool_Variable_t*     Keyword_Do_Negate_Variable();

        V::String_Variable_t*   Relation_Argument_Variable();
        V::Bool_Variable_t*     Relation_Do_Negate_Variable();

        V::Int_Variable_t*      Vitality_Argument_Variable();
        V::Bool_Variable_t*     Vitality_Do_Negate_Variable();

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

        String_t    Faction_Argument();
        void        Faction_Argument(String_t value);
        Bool_t      Faction_Do_Negate();
        void        Faction_Do_Negate(Bool_t value);

        String_t    Keyword_Argument();
        void        Keyword_Argument(String_t value);
        Bool_t      Keyword_Do_Negate();
        void        Keyword_Do_Negate(Bool_t value);

        String_t    Relation_Argument();
        void        Relation_Argument(String_t value);
        Bool_t      Relation_Do_Negate();
        void        Relation_Do_Negate(Bool_t value);

        Vitality_e  Vitality_Argument();
        void        Vitality_Argument(Vitality_e value);
        Bool_t      Vitality_Do_Negate();
        void        Vitality_Do_Negate(Bool_t value);

        Binary_e    Male_Female_Argument();
        void        Male_Female_Argument(Binary_e value);

        Binary_e    Unique_Generic_Argument();
        void        Unique_Generic_Argument(Binary_e value);

    public:
        void                    Clear();

        template <typename Type_t>
        Filter_State_t<Type_t>  Execute(Vector_t<Type_t>* read, Vector_t<Type_t>* write);

        Vector_t<String_t>      Selectable_Mods();
        Vector_t<String_t>      Selectable_Races();
        Vector_t<String_t>      Selectable_Bases();
        Vector_t<String_t>      Selectable_Templates();
        Vector_t<String_t>      Selectable_Factions();
        Vector_t<String_t>      Selectable_Keywords();
        Vector_t<String_t>      Selectable_Relations();
        Vector_t<String_t>      Selectable_Vitalities();

    public:
        void Build_Filters(const char* type_name);

    public:
        void On_Init();
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
    class Bases_Options_t : public Bases_t<Base_t, Item_t>
    {
    public:
        static Vector_t<Item_Section_t> item_sections;

    public:
        Int_t&  Back_Option();
        Int_t&  Reset_Option();

        Int_t&  Smart_Select_Option();
        Int_t&  Uncombative_Spawns_Option();
        Int_t&  Persistent_Spawns_Option();
        Int_t&  Static_Spawns_Option();

        static Int_t bases_section_option;
        static Int_t commands_section_option;
        static Int_t factions_section_option;
        static Int_t keywords_section_option;
        static Int_t mods_section_option;
        static Int_t races_section_option;
        static Int_t templates_section_option;

        void    Reset_Option_Ints();

        static Int_t disable_section_menu_option;
        static Int_t move_section_higher_menu_option;
        static Int_t move_section_lower_menu_option;

        void    Reset_Menu_Option_Ints();

    public:
        V::Bool_Variable_t*             Do_Smart_Select_Variable();
        V::Bool_Variable_t*             Do_Uncombative_Spawns_Variable();
        V::Bool_Variable_t*             Do_Persistent_Spawns_Variable();
        V::Bool_Variable_t*             Do_Static_Spawns_Variable();

        V::Array_Variable_t<String_t>*  Item_Sections_Variable();

    public:
        Bool_t  Do_Smart_Select();
        void    Do_Smart_Select(Bool_t value);

        Bool_t  Do_Uncombative_Spawns();
        void    Do_Uncombative_Spawns(Bool_t value);

        Bool_t  Do_Persistent_Spawns();
        void    Do_Persistent_Spawns(Bool_t value);

        Bool_t  Do_Static_Spawns();
        void    Do_Static_Spawns(Bool_t value);

    public:
        void    Reset();

    public:
        void                        Reset_Item_Sections();
        void                        Serialize_Item_Sections();
        void                        Deserialize_Item_Sections();

        Vector_t<Item_Section_t>    Item_Sections();
        Bool_t                      Is_Item_Section_Enabled(Item_Section_t section);
        void                        Enable_Item_Section(Item_Section_t section);
        void                        Disable_Item_Section(Item_Section_t section);
        Bool_t                      May_Move_Item_Section_Higher(Item_Section_t section);
        Bool_t                      May_Move_Item_Section_Lower(Item_Section_t section);
        void                        Move_Item_Section_Higher(Item_Section_t section);
        void                        Move_Item_Section_Lower(Item_Section_t section);

        void                        Build_Section_Options(Vector_t<Item_Section_t>& allowed_sections);
        void                        Build_Section_Options_Impl(Vector_t<Item_Section_t>& allowed_sections);

        void                        Select_Section_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback);
        void                        Open_Section_Menu_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback);
        void                        Accept_Section_Menu_Option(Item_Section_t item_section, Int_t idx, Latent_Callback_i* lcallback);

        Bool_t                      Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t                      Try_On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        Bool_t                      Try_On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);

    public:
        void On_Init();
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

    class Bases_Item_View_e : public Enum_t<Word_t>
    {
    public:
        enum : Word_t
        {
            ITEM,
            BASES,
            BASES_ITEM,
        };
        using Enum_t::Enum_t;
    };

    template <typename Base_t, typename Item_t>
    class Bases_Item_t : public Bases_t<Base_t, Item_t>
    {
    public:
        static constexpr const char*    ITEM_VIEW           = "item";
        static constexpr const char*    BASES_VIEW          = "bases";
        static constexpr const char*    BASES_ITEM_VIEW     = "bases_item";
        static constexpr Int_t          HEADERS_PER_PAGE    = 6;
        static constexpr Int_t          ITEMS_PER_PAGE      = 18;

    public:
        Int_t&  Back_Option();
        Int_t&  Primary_Option();
        Int_t&  Previous_Option();
        Int_t&  Next_Option();
        Int_t&  View_Item_Option();
        Int_t&  View_Bases_Option();

        static Int_t show_bases_option;
        static Int_t show_commands_option;
        static Int_t show_factions_option;
        static Int_t show_keywords_option;
        static Int_t show_mods_option;
        static Int_t show_races_option;
        static Int_t show_templates_option;

        Int_t&  Race_Name_Option();
        Int_t&  Cell_Name_Option();

        void    Reset_Option_Ints();

    public:
        V::String_Variable_t*   Nested_View_Variable();
        V::Int_Variable_t*      Nested_Index_Variable();
        V::Int_Variable_t*      Nested_Form_Variable();

        V::Bool_Variable_t*     Do_Show_Bases_Variable();
        V::Bool_Variable_t*     Do_Show_Commands_Variable();
        V::Bool_Variable_t*     Do_Show_Factions_Variable();
        V::Bool_Variable_t*     Do_Show_Keywords_Variable();
        V::Bool_Variable_t*     Do_Show_Mods_Variable();
        V::Bool_Variable_t*     Do_Show_Races_Variable();
        V::Bool_Variable_t*     Do_Show_Templates_Variable();

    public:
        Bases_Item_View_e   Nested_View();
        void                Nested_View(Bases_Item_View_e value);
        Int_t               Nested_Index();
        void                Nested_Index(Int_t value);
        Form_ID_t           Nested_Form();
        void                Nested_Form(Form_ID_t value);

        Bool_t              Do_Show_Bases();
        void                Do_Show_Bases(Bool_t value);
        Bool_t              Do_Show_Commands();
        void                Do_Show_Commands(Bool_t value);
        Bool_t              Do_Show_Factions();
        void                Do_Show_Factions(Bool_t value);
        Bool_t              Do_Show_Keywords();
        void                Do_Show_Keywords(Bool_t value);
        Bool_t              Do_Show_Mods();
        void                Do_Show_Mods(Bool_t value);
        Bool_t              Do_Show_Races();
        void                Do_Show_Races(Bool_t value);
        Bool_t              Do_Show_Templates();
        void                Do_Show_Templates(Bool_t value);

    public:
        void        Spawn(Actor_Base_t* base);
        void        Spawn(Leveled_Actor_Base_t* leveled_base);
        void        Spawn(Cached_Leveled_t* cached_leveled);

    public:
        void        Build_Base(Actor_Base_t* base, const char* type_name);
        void        Build_Factions_And_Ranks(Vector_t<Faction_And_Rank_t> factions_and_ranks);
        void        Build_Header(const char* primary_option_name, size_t listed_item_count);
        void        Build_Keywords(Vector_t<Keyword_t*> keywords);
        void        Build_Leveled_Base(Leveled_Actor_Base_t* leveled_base);
        void        Build_Mod_Names(Vector_t<String_t> mod_names);
        void        Build_Race(Race_t* race);
        void        Build_Templates(Vector_t<Actor_Base_t*> templates);

        Bool_t      Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);

    public:
        void On_Init();
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
