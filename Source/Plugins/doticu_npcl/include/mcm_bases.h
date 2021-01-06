/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

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

    class Item_Sections_t
    {
    public:
        Item_Sections_t()
        {
        }

        Vector_t<Item_Section_t>        Current();
        void                            Reset(Vector_t<Item_Section_t>&& defaults);

        Bool_t                          Is_Enabled(Item_Section_t section);
        void                            Enable(Item_Section_t section);
        void                            Disable(Item_Section_t section);

        Bool_t                          May_Move_Higher(Item_Section_t section);
        Bool_t                          May_Move_Lower(Item_Section_t section);
        void                            Move_Higher(Item_Section_t section);
        void                            Move_Lower(Item_Section_t section);

        template                        <typename Item_Section_e>
        Bool_t                          Serialize(V::Variable_tt<Vector_t<String_t>>& variable);
        template                        <typename Item_Section_e>
        Bool_t                          Deserialize(V::Variable_tt<Vector_t<String_t>>& variable);

    private:
        Vector_t<Item_Section_t>        item_sections;
        std::mutex                      mutex;
    };

    class Bases_Item_Section_e : public Enum_t<Item_Section_t>
    {
    public:
        enum : value_type
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
        V::Variable_tt<String_t>& Current_View_Variable();

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
        V::Variable_tt<Int_t>& Page_Index();

    public:
        void Clear();

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
        V::Variable_tt<String_t>&   Mod_Argument();
        V::Variable_tt<Bool_t>&     Mod_Do_Negate();

        V::Variable_tt<String_t>&   Race_Argument();
        V::Variable_tt<Bool_t>&     Race_Do_Negate();

        V::Variable_tt<String_t>&   Base_Argument();
        V::Variable_tt<Bool_t>&     Base_Do_Negate();

        V::Variable_tt<String_t>&   Template_Argument();
        V::Variable_tt<Bool_t>&     Template_Do_Negate();

        V::Variable_tt<String_t>&   Faction_Argument();
        V::Variable_tt<Bool_t>&     Faction_Do_Negate();

        V::Variable_tt<String_t>&   Keyword_Argument();
        V::Variable_tt<Bool_t>&     Keyword_Do_Negate();

        V::Variable_tt<Relation_e>& Relation_Argument();
        V::Variable_tt<Bool_t>&     Relation_Do_Negate();

        V::Variable_tt<Vitality_e>& Vitality_Argument();
        V::Variable_tt<Bool_t>&     Vitality_Do_Negate();

        V::Variable_tt<Binary_e>&   Male_Female_Argument();
        V::Variable_tt<Binary_e>&   Unique_Generic_Argument();

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
        void    Build_Filters(const char* type_name);

        void    Highlight_Toggle_Option(Latent_Callback_i* lcallback);

    public:
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

        void    On_Init();
        void    On_Load();
        void    On_Save();
        void    On_Config_Open();
        void    On_Config_Close();
        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void    On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void    On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void    On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class Bases_Options_t : public Bases_t<Base_t, Item_t>
    {
    public:
        static Item_Sections_t item_sections;

    public:
        static Int_t    back_option;
        static Int_t    reset_option;

        static Int_t    do_smart_select_option;
        static Int_t    do_smart_sections_option;
        static Int_t    do_uncombative_spawns_option;
        static Int_t    do_persistent_spawns_option;
        static Int_t    do_static_spawns_option;
        static Int_t    do_verify_spawns_option;

        static Int_t    bases_section_option;
        static Int_t    commands_section_option;
        static Int_t    factions_section_option;
        static Int_t    keywords_section_option;
        static Int_t    mods_section_option;
        static Int_t    races_section_option;
        static Int_t    templates_section_option;

        void            Reset_Option_Ints();

        static Int_t    disable_section_menu_option;
        static Int_t    move_section_higher_menu_option;
        static Int_t    move_section_lower_menu_option;

        void            Reset_Menu_Option_Ints();

    public:
        V::Variable_tt<Bool_t>&             Do_Smart_Select();
        V::Variable_tt<Bool_t>&             Do_Smart_Sections();
        V::Variable_tt<Bool_t>&             Do_Uncombative_Spawns();
        V::Variable_tt<Bool_t>&             Do_Persistent_Spawns();
        V::Variable_tt<Bool_t>&             Do_Static_Spawns();
        V::Variable_tt<Bool_t>&             Do_Verify_Spawns();
        V::Variable_tt<Vector_t<String_t>>& Item_Sections();

    public:
        void    Reset();

    public:
        Vector_t<Item_Section_t> Default_Item_Sections();

    public:
        void    Build_Header_Options();
        void    Build_General_Options();
        void    Build_Section_Options();
        void    Build_Section_Options_Impl();

        void    Select_Section_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback);
        void    Open_Section_Menu_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback);
        void    Accept_Section_Menu_Option(Item_Section_t item_section, Int_t idx, Latent_Callback_i* lcallback);

        void    Highlight_Section_Option(Item_Section_t item_section, Latent_Callback_i* lcallback);

    public:
        Bool_t  Try_On_Init();
        Bool_t  Try_On_Load();
        Bool_t  Try_On_Save();
        Bool_t  Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

        void    On_Init();
        void    On_Load();
        void    On_Save();
        void    On_Config_Open();
        void    On_Config_Close();
        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void    On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void    On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void    On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
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

    template <typename T>
    using enable_if_spawnable = std::enable_if_t<
        std::is_same<T, Actor_Base_t*>::value ||
        std::is_same<T, Leveled_Actor_Base_t*>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_raceable = std::enable_if_t<
        std::is_same<T, Actor_Base_t>::value ||
        std::is_same<T, Actor_t>::value,
        Bool_t
    >;
    template <typename T>
    using enable_if_not_raceable = std::enable_if_t<
        !std::is_same<T, Actor_Base_t>::value &&
        !std::is_same<T, Actor_t>::value,
        Bool_t
    >;

    class Buildable_i;
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
        static Int_t    back_option;
        static Int_t    previous_option;
        static Int_t    next_option;
        static Int_t    view_nested_option;
        static Int_t    spawn_option;

        static Int_t    show_bases_option;
        static Int_t    show_commands_option;
        static Int_t    show_factions_option;
        static Int_t    show_keywords_option;
        static Int_t    show_mods_option;
        static Int_t    show_races_option;
        static Int_t    show_templates_option;

        static Int_t    race_name_option;

        void            Reset_Option_Ints();

    public:
        V::Variable_tt<String_t>&   Nested_View_Variable();
        V::Variable_tt<Int_t>&      Nested_Index();
        V::Variable_tt<Form_ID_t>&  Nested_Form();

        V::Variable_tt<Bool_t>&     Do_Show_Bases();
        V::Variable_tt<Bool_t>&     Do_Show_Commands();
        V::Variable_tt<Bool_t>&     Do_Show_Factions();
        V::Variable_tt<Bool_t>&     Do_Show_Keywords();
        V::Variable_tt<Bool_t>&     Do_Show_Mods();
        V::Variable_tt<Bool_t>&     Do_Show_Races();
        V::Variable_tt<Bool_t>&     Do_Show_Templates();

    public:
        Bases_Item_View_e   Nested_View();
        void                Nested_View(Bases_Item_View_e value);

    public:
        void        Build_Sections(Vector_t<Buildable_i*> buildables);

        void        Build_Base(Actor_Base_t* base, const char* type_name);
        void        Build_Factions(Vector_t<Faction_And_Rank_t> factions);
        void        Build_Header(Int_t& top_right_option, const char* top_right_name, size_t listed_item_count);
        void        Build_Keywords(Vector_t<Keyword_t*> keywords);
        void        Build_Leveled_Base(Leveled_Actor_Base_t* leveled_base);
        void        Build_Mods(Vector_t<Mod_t*> mods);
        void        Build_Race(Race_t* race);
        void        Build_Templates(Vector_t<Actor_Base_t*> templates);

        template    <typename Spawnable_t, enable_if_spawnable<Spawnable_t> = true>
        void        Select_Spawn_Option(Spawnable_t item, Int_t option, Latent_Callback_i* lcallback);
        void        Select_Spawn_Option(Cached_Leveled_t* item, Int_t option, Latent_Callback_i* lcallback);
        void        Select_Spawn_Option(Actor_t* item, Int_t option, Latent_Callback_i* lcallback);

        template    <typename Raceable_t, enable_if_raceable<Raceable_t> = true>
        void        Highlight_Race_Option(Raceable_t* raceable, Latent_Callback_i* lcallback);
        template    <typename Unraceable_t, enable_if_not_raceable<Unraceable_t> = true>
        void        Highlight_Race_Option(Unraceable_t* unraceable, Latent_Callback_i* lcallback);

    public:
        Bool_t  Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

        void    On_Init();
        void    On_Load();
        void    On_Save();
        void    On_Config_Open();
        void    On_Config_Close();
        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void    On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void    On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void    On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

    class Buildable_i
    {
    public:
        using Type_t = Item_Section_t;

    public:
        virtual         ~Buildable_i()  = default;
        virtual Bool_t  Can_Enable()    = 0;
        virtual Bool_t  Can_Show()      = 0;
        virtual void    Build()         = 0;
        virtual Type_t  Type()          = 0;
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Base_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Actor_Base_t*                   actor_base;
        const char*                     type_name;

        Buildable_Base_t(Bases_Item_t<Base_t, Item_t>* builder, Actor_Base_t* actor_base, const char* type_name) :
            builder(builder), actor_base(actor_base), type_name(type_name)
        {
        }
        virtual         ~Buildable_Base_t()             = default;
        virtual Bool_t  Can_Enable()        override    { return actor_base && actor_base->Is_Valid() && type_name; }
        virtual Bool_t  Can_Show()          override    { return builder->Do_Show_Bases(); }
        virtual void    Build()             override    { builder->Build_Base(actor_base, type_name); }
        virtual Type_t  Type()              override    { return Bases_Item_Section_e::BASES; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Factions_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Vector_t<Faction_And_Rank_t>    factions;

        Buildable_Factions_t(Bases_Item_t<Base_t, Item_t>* builder, Vector_t<Faction_And_Rank_t>&& factions) :
            builder(builder), factions(std::move(factions))
        {
        }
        virtual         ~Buildable_Factions_t()             = default;
        virtual Bool_t  Can_Enable()            override    { return factions.size() > 0; }
        virtual Bool_t  Can_Show()              override    { return builder->Do_Show_Factions(); }
        virtual void    Build()                 override    { builder->Build_Factions(factions); }
        virtual Type_t  Type()                  override    { return Bases_Item_Section_e::FACTIONS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Keywords_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Vector_t<Keyword_t*>            keywords;

        Buildable_Keywords_t(Bases_Item_t<Base_t, Item_t>* builder, Vector_t<Keyword_t*>&& keywords) :
            builder(builder), keywords(std::move(keywords))
        {
        }
        virtual         ~Buildable_Keywords_t()             = default;
        virtual Bool_t  Can_Enable()            override    { return keywords.size() > 0; }
        virtual Bool_t  Can_Show()              override    { return builder->Do_Show_Keywords(); }
        virtual void    Build()                 override    { builder->Build_Keywords(keywords); }
        virtual Type_t  Type()                  override    { return Bases_Item_Section_e::KEYWORDS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Leveled_Base_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Leveled_Actor_Base_t*           leveled_base;

        Buildable_Leveled_Base_t(Bases_Item_t<Base_t, Item_t>* builder, Leveled_Actor_Base_t* leveled_base) :
            builder(builder), leveled_base(leveled_base)
        {
        }
        virtual         ~Buildable_Leveled_Base_t()             = default;
        virtual Bool_t  Can_Enable()                override    { return leveled_base && leveled_base->Is_Valid(); }
        virtual Bool_t  Can_Show()                  override    { return builder->Do_Show_Bases(); }
        virtual void    Build()                     override    { builder->Build_Leveled_Base(leveled_base); }
        virtual Type_t  Type()                      override    { return Bases_Item_Section_e::BASES; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Mods_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Vector_t<Mod_t*>                mods;

        Buildable_Mods_t(Bases_Item_t<Base_t, Item_t>* builder, Vector_t<Mod_t*>&& mods) :
            builder(builder), mods(std::move(mods))
        {
        }
        virtual         ~Buildable_Mods_t()             = default;
        virtual Bool_t  Can_Enable()        override    { return mods.size() > 0; }
        virtual Bool_t  Can_Show()          override    { return builder->Do_Show_Mods(); }
        virtual void    Build()             override    { builder->Build_Mods(mods); }
        virtual Type_t  Type()              override    { return Bases_Item_Section_e::MODS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Race_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Race_t*                         race;

        Buildable_Race_t(Bases_Item_t<Base_t, Item_t>* builder, Race_t* race) :
            builder(builder), race(race)
        {
        }
        virtual         ~Buildable_Race_t()             = default;
        virtual Bool_t  Can_Enable()        override    { return race && race->Is_Valid(); }
        virtual Bool_t  Can_Show()          override    { return builder->Do_Show_Races(); }
        virtual void    Build()             override    { builder->Build_Race(race); }
        virtual Type_t  Type()              override    { return Bases_Item_Section_e::RACES; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Templates_t : public Buildable_i
    {
    public:
        Bases_Item_t<Base_t, Item_t>*   builder;
        Vector_t<Actor_Base_t*>         templates;

        Buildable_Templates_t(Bases_Item_t<Base_t, Item_t>* builder, Vector_t<Actor_Base_t*>&& templates) :
            builder(builder), templates(std::move(templates))
        {
        }
        virtual         ~Buildable_Templates_t()                = default;
        virtual Bool_t  Can_Enable()                override    { return templates.size() > 0; }
        virtual Bool_t  Can_Show()                  override    { return builder->Do_Show_Templates(); }
        virtual void    Build()                     override    { builder->Build_Templates(templates); }
        virtual Type_t  Type()                      override    { return Bases_Item_Section_e::TEMPLATES; }
    };

}}
