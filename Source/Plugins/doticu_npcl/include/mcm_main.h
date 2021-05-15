/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

namespace doticu_npcl { namespace MCM {

    using Latent_Callback_i = Callback_i<>;

    class Main_t : public mcmlib::Config_Base_t
    {
    public:
        static constexpr const char*    _NONE_                              = "";
        static constexpr const char*    _SPACE_                             = " ";
        static constexpr const char*    _SPACED_DASH_                       = " - ";
        static constexpr const char*    _COLON_SPACE_                       = ": ";

        static const String_t   _TEXT_DIVIDER_;
        static const String_t   _TOGGLE_DIVIDER_;

        static constexpr const char*    STATIC_BASE                         = "$dnpcl_static_base";
        static constexpr const char*    DYNAMIC_BASE                        = "$dnpcl_dynamic_base";
        static constexpr const char*    LEVELED_BASE                        = "$dnpcl_leveled_base";
        static constexpr const char*    INTERNAL_BASE                       = "$dnpcl_internal_base";
        static constexpr const char*    LOADED_REFERENCE                    = "$dnpcl_loaded_reference";
        static constexpr const char*    SPAWNED_REFERENCE                   = "$dnpcl_spawned_reference";
        static constexpr const char*    MARKED_REFERENCE                    = "$dnpcl_marked_reference";

        static constexpr const char*    STATIC_BASES                        = "$dnpcl_static_bases";
        static constexpr const char*    DYNAMIC_BASES                       = "$dnpcl_dynamic_bases";
        static constexpr const char*    LEVELED_BASES                       = "$dnpcl_leveled_bases";
        static constexpr const char*    INTERNAL_BASES                      = "$dnpcl_internal_bases";
        static constexpr const char*    LOADED_REFERENCES                   = "$dnpcl_loaded_references";
        static constexpr const char*    SPAWNED_REFERENCES                  = "$dnpcl_spawned_references";
        static constexpr const char*    MARKED_REFERENCES                   = "$dnpcl_marked_references";

        static constexpr const char*    NO_STATIC_BASES                     = "$dnpcl_no_static_bases";
        static constexpr const char*    NO_DYNAMIC_BASES                    = "$dnpcl_no_dynamic_bases";
        static constexpr const char*    NO_LEVELED_BASES                    = "$dnpcl_no_leveled_bases";
        static constexpr const char*    NO_INTERNAL_BASES                   = "$dnpcl_no_internal_bases";
        static constexpr const char*    NO_LOADED_REFERENCES                = "$dnpcl_no_loaded_references";
        static constexpr const char*    NO_SPAWNED_REFERENCES               = "$dnpcl_no_spawned_references";
        static constexpr const char*    NO_MARKED_REFERENCES                = "$dnpcl_no_marked_references";

        static constexpr const char*    ANY                                 = "$dnpcl_any";
        static constexpr const char*    MOD                                 = "$dnpcl_mod";
        static constexpr const char*    MODS                                = "$dnpcl_mods";
        static constexpr const char*    RACE                                = "$dnpcl_race";
        static constexpr const char*    RACES                               = "$dnpcl_races";
        static constexpr const char*    BASE                                = "$dnpcl_base";
        static constexpr const char*    BASES                               = "$dnpcl_bases";
        static constexpr const char*    TEMPLATE                            = "$dnpcl_template";
        static constexpr const char*    TEMPLATES                           = "$dnpcl_templates";
        static constexpr const char*    FACTION                             = "$dnpcl_faction";
        static constexpr const char*    FACTIONS                            = "$dnpcl_factions";
        static constexpr const char*    KEYWORD                             = "$dnpcl_keyword";
        static constexpr const char*    KEYWORDS                            = "$dnpcl_keywords";
        static constexpr const char*    RELATION                            = "$dnpcl_relation";
        static constexpr const char*    VITALITY                            = "$dnpcl_vitality";
        static constexpr const char*    REFERENCE                           = "$dnpcl_reference";
        static constexpr const char*    REFERENCES                          = "$dnpcl_references";
        static constexpr const char*    WORLDSPACE                          = "$dnpcl_worldspace";
        static constexpr const char*    WORLDSPACES                         = "$dnpcl_worldspaces";
        static constexpr const char*    LOCATION                            = "$dnpcl_location";
        static constexpr const char*    LOCATIONS                           = "$dnpcl_locations";
        static constexpr const char*    CELL                                = "$dnpcl_cell";
        static constexpr const char*    CELLS                               = "$dnpcl_cells";
        static constexpr const char*    QUEST                               = "$dnpcl_quest";
        static constexpr const char*    QUESTS                              = "$dnpcl_quests";
        static constexpr const char*    OTHER                               = "$dnpcl_other";
        static constexpr const char*    IS_MALE                             = "$dnpcl_is_male";
        static constexpr const char*    IS_FEMALE                           = "$dnpcl_is_female";
        static constexpr const char*    IS_UNIQUE                           = "$dnpcl_is_unique";
        static constexpr const char*    IS_GENERIC                          = "$dnpcl_is_generic";
        static constexpr const char*    IS_INTERIOR                         = "$dnpcl_is_interior";
        static constexpr const char*    IS_EXTERIOR                         = "$dnpcl_is_exterior";
        static constexpr const char*    IS_ALIVE                            = "$dnpcl_is_alive";
        static constexpr const char*    IS_DEAD                             = "$dnpcl_is_dead";
        static constexpr const char*    IS_TEAMMATE                         = "$dnpcl_is_teammate";
        static constexpr const char*    ISNT_TEAMMATE                       = "$dnpcl_isnt_teammate";
        static constexpr const char*    HAS_MALE                            = "$dnpcl_has_male";
        static constexpr const char*    HAS_FEMALE                          = "$dnpcl_has_female";
        static constexpr const char*    HAS_UNIQUE                          = "$dnpcl_has_unique";
        static constexpr const char*    HAS_GENERIC                         = "$dnpcl_has_generic";
        static constexpr const char*    IN_INTERIOR                         = "$dnpcl_in_interior";
        static constexpr const char*    IN_EXTERIOR                         = "$dnpcl_in_exterior";

        static constexpr const char*    SEARCH                              = "$dnpcl_search";
        static constexpr const char*    SELECT                              = "$dnpcl_select";
        static constexpr const char*    NEGATE                              = "$dnpcl_negate";
        static constexpr const char*    _DOTS_                              = "$dnpcl_...";

        static constexpr const char*    LOVER                               = "$dnpcl_lover";
        static constexpr const char*    ALLY                                = "$dnpcl_ally";
        static constexpr const char*    CONFIDANT                           = "$dnpcl_confidant";
        static constexpr const char*    FRIEND                              = "$dnpcl_friend";
        static constexpr const char*    ACQUAINTANCE                        = "$dnpcl_acquaintance";
        static constexpr const char*    RIVAL                               = "$dnpcl_rival";
        static constexpr const char*    FOE                                 = "$dnpcl_foe";
        static constexpr const char*    ENEMY                               = "$dnpcl_enemy";
        static constexpr const char*    ARCHNEMESIS                         = "$dnpcl_archnemesis";

        static constexpr const char*    IS_LOVER                            = "$dnpcl_is_lover";
        static constexpr const char*    IS_ALLY                             = "$dnpcl_is_ally";
        static constexpr const char*    IS_CONFIDANT                        = "$dnpcl_is_confidant";
        static constexpr const char*    IS_FRIEND                           = "$dnpcl_is_friend";
        static constexpr const char*    IS_ACQUAINTANCE                     = "$dnpcl_is_acquaintance";
        static constexpr const char*    IS_RIVAL                            = "$dnpcl_is_rival";
        static constexpr const char*    IS_FOE                              = "$dnpcl_is_foe";
        static constexpr const char*    IS_ENEMY                            = "$dnpcl_is_enemy";
        static constexpr const char*    IS_ARCHNEMESIS                      = "$dnpcl_is_archnemesis";

        static constexpr const char*    MORTAL                              = "$dnpcl_mortal";
        static constexpr const char*    PROTECTED                           = "$dnpcl_protected";
        static constexpr const char*    ESSENTIAL                           = "$dnpcl_essential";
        static constexpr const char*    INVULNERABLE                        = "$dnpcl_invulnerable";

        static constexpr const char*    IS_MORTAL                           = "$dnpcl_is_mortal";
        static constexpr const char*    IS_PROTECTED                        = "$dnpcl_is_protected";
        static constexpr const char*    IS_ESSENTIAL                        = "$dnpcl_is_essential";
        static constexpr const char*    IS_INVULNERABLE                     = "$dnpcl_is_invulnerable";

        static constexpr const char*    GENERAL                             = "$dnpcl_general";
        static constexpr const char*    SMART_SELECT                        = "$dnpcl_smart_select";
        static constexpr const char*    SMART_SECTIONS                      = "$dnpcl_smart_sections";
        static constexpr const char*    UNCOMBATIVE_SPAWNS                  = "$dnpcl_uncombative_spawns";
        static constexpr const char*    PERSISTENT_SPAWNS                   = "$dnpcl_persistent_spawns";
        static constexpr const char*    STATIC_SPAWNS                       = "$dnpcl_static_spawns";
        static constexpr const char*    VERIFY_SPAWNS                       = "$dnpcl_verify_spawns";
        static constexpr const char*    VERIFY_UNSPAWNS                     = "$dnpcl_verify_unspawns";

        static constexpr const char*    ITEM_SECTIONS                       = "$dnpcl_item_sections";
        static constexpr const char*    ENABLE_SECTION                      = "$dnpcl_enable_section";
        static constexpr const char*    DISABLE_SECTION                     = "$dnpcl_disable_section";
        static constexpr const char*    MOVE_SECTION_HIGHER                 = "$dnpcl_move_section_higher";
        static constexpr const char*    MOVE_SECTION_LOWER                  = "$dnpcl_move_section_lower";

        static constexpr const char*    COMMANDS                            = "$dnpcl_commands";
        static constexpr const char*    VIEW_INTERNAL_BASES                 = "$dnpcl_view_internal_bases";
        static constexpr const char*    ADD_MARKER_TO_MAP                   = "$dnpcl_add_marker_to_map";
        static constexpr const char*    REMOVE_MARKER_FROM_MAP              = "$dnpcl_remove_marker_from_map";
        static constexpr const char*    SPAWN_A_CLONE                       = "$dnpcl_spawn_a_clone";
        static constexpr const char*    MOVE_TO_PLAYER                      = "$dnpcl_move_to_player";
        static constexpr const char*    GO_TO_REFERENCE                     = "$dnpcl_go_to_reference";
        static constexpr const char*    ENABLE_REFERENCE                    = "$dnpcl_enable_reference";
        static constexpr const char*    DISABLE_REFERENCE                   = "$dnpcl_disable_reference";
        static constexpr const char*    SELECT_IN_CONSOLE                   = "$dnpcl_select_in_console";
        static constexpr const char*    RENAME_REFERENCE                    = "$dnpcl_rename_reference";

        static constexpr const char*    CONFIRM_SPAWN                       = "$dnpcl_confirm_spawn";
        static constexpr const char*    CONFIRM_UNSPAWN                     = "$dnpcl_confirm_unspawn";
        static constexpr const char*    CONFIRM_REMOVE_MARKER               = "$dnpcl_confirm_remove_marker";
        static constexpr const char*    YES                                 = "$dnpcl_yes";
        static constexpr const char*    NO                                  = "$dnpcl_no";

        static constexpr const char*    GLOBAL_OPTIONS                      = "$dnpcl_global_options";
        static constexpr const char*    PRIORITIZE_MCM_MENU                 = "$dnpcl_prioritize_mcm_menu";
        static constexpr const char*    TRANSLATE_PAGE_TITLES               = "$dnpcl_translate_page_titles";

        static constexpr const char*    CENTER_FILTER                       = "$dnpcl_center_filter";
        static constexpr const char*    CENTER_OPTIONS                      = "$dnpcl_center_options";
        static constexpr const char*    CENTER_GO_TO_PREVIOUS_PAGE          = "$dnpcl_center_go_to_previous_page";
        static constexpr const char*    CENTER_GO_TO_NEXT_PAGE              = "$dnpcl_center_go_to_next_page";
        static constexpr const char*    CENTER_GO_TO_PREVIOUS_ITEM          = "$dnpcl_center_go_to_previous_item";
        static constexpr const char*    CENTER_GO_TO_NEXT_ITEM              = "$dnpcl_center_go_to_next_item";
        static constexpr const char*    CENTER_BACK                         = "$dnpcl_center_back";
        static constexpr const char*    CENTER_CLEAR                        = "$dnpcl_center_clear";
        static constexpr const char*    CENTER_RESET                        = "$dnpcl_center_reset";
        static constexpr const char*    CENTER_SPAWN                        = "$dnpcl_center_spawn";
        static constexpr const char*    CENTER_UNSPAWN                      = "$dnpcl_center_unspawn";

        static constexpr const char*    HIGHLIGHT_FILTER_BACK               = "$dnpcl_highlight_filter_back";
        static constexpr const char*    HIGHLIGHT_FILTER_CLEAR              = "$dnpcl_highlight_filter_clear";
        static constexpr const char*    HIGHLIGHT_FILTER_SEARCH             = "$dnpcl_highlight_filter_search";
        static constexpr const char*    HIGHLIGHT_FILTER_SELECT             = "$dnpcl_highlight_filter_select";
        static constexpr const char*    HIGHLIGHT_FILTER_NEGATE             = "$dnpcl_highlight_filter_negate";
        static constexpr const char*    HIGHLIGHT_FILTER_TOGGLE_EITHER      = "$dnpcl_highlight_filter_toggle_either";
        static constexpr const char*    HIGHLIGHT_FILTER_TOGGLE_ANY         = "$dnpcl_highlight_filter_toggle_any";

        static constexpr const char*    HIGHLIGHT_OPTIONS_BACK              = "$dnpcl_highlight_options_back";
        static constexpr const char*    HIGHLIGHT_RESET_OPTIONS             = "$dnpcl_highlight_reset_options";
        static constexpr const char*    HIGHLIGHT_SMART_SELECT              = "$dnpcl_highlight_smart_select";
        static constexpr const char*    HIGHLIGHT_SMART_SECTIONS            = "$dnpcl_highlight_smart_sections";
        static constexpr const char*    HIGHLIGHT_UNCOMBATIVE_SPAWNS        = "$dnpcl_highlight_uncombative_spawns";
        static constexpr const char*    HIGHLIGHT_PERSISTENT_SPAWNS         = "$dnpcl_highlight_persistent_spawns";
        static constexpr const char*    HIGHLIGHT_STATIC_SPAWNS             = "$dnpcl_highlight_static_spawns";
        static constexpr const char*    HIGHLIGHT_VERIFY_SPAWNS             = "$dnpcl_highlight_verify_spawns";
        static constexpr const char*    HIGHLIGHT_VERIFY_UNSPAWNS           = "$dnpcl_highlight_verify_unspawns";
        static constexpr const char*    HIGHLIGHT_OPTIONS_ENABLED_SECTION   = "$dnpcl_highlight_options_enabled_section";
        static constexpr const char*    HIGHLIGHT_OPTIONS_DISABLED_SECTION  = "$dnpcl_highlight_options_disabled_section";

        static constexpr const char*    HIGHLIGHT_ITEM_TOGGLE_SECTION       = "$dnpcl_highlight_item_toggle_section";
        static constexpr const char*    HIGHLIGHT_SPAWN                     = "$dnpcl_highlight_spawn";
        static constexpr const char*    HIGHLIGHT_SPAWN_LEVELED             = "$dnpcl_highlight_spawn_leveled";
        static constexpr const char*    HIGHLIGHT_SPAWN_A_CLONE             = "$dnpcl_highlight_spawn_a_clone";
        static constexpr const char*    HIGHLIGHT_UNSPAWN                   = "$dnpcl_highlight_unspawn";
        static constexpr const char*    HIGHLIGHT_VIEW_INTERNAL_BASES       = "$dnpcl_highlight_view_internal_bases";
        static constexpr const char*    HIGHLIGHT_ADD_REMOVE_MAP_MARKER     = "$dnpcl_highlight_add_remove_map_marker";
        static constexpr const char*    HIGHLIGHT_MOVE_TO_PLAYER            = "$dnpcl_highlight_move_to_player";
        static constexpr const char*    HIGHLIGHT_GO_TO_REFERENCE           = "$dnpcl_highlight_go_to_reference";
        static constexpr const char*    HIGHLIGHT_ENABLE_DISABLE_REFERENCE  = "$dnpcl_highlight_enable_disable_reference";
        static constexpr const char*    HIGHLIGHT_SELECT_IN_CONSOLE         = "$dnpcl_highlight_select_in_console";

        static constexpr const char*    HIGHLIGHT_PRIORITIZE_MCM_MENU       = "$dnpcl_highlight_prioritize_mcm_menu";
        static constexpr const char*    HIGHLIGHT_TRANSLATE_PAGE_TITLES     = "$dnpcl_highlight_translate_page_titles";

        static constexpr const char*    PLACEHOLDER_TITLE                   = "$dnpcl_placeholder_title";
        static constexpr const wchar_t* PLACEHOLDER_TITLE_W                 = L"$dnpcl_placeholder_title";
        static constexpr const char*    PLACEHOLDER_HIGHLIGHT               = "$dnpcl_placeholder_highlight";
        static constexpr const wchar_t* PLACEHOLDER_HIGHLIGHT_W             = L"$dnpcl_placeholder_highlight";

        static constexpr const wchar_t* COMPONENT_STATIC_BASE               = L"$dnpcl_component_static_base";
        static constexpr const wchar_t* COMPONENT_DYNAMIC_BASE              = L"$dnpcl_component_dynamic_base";
        static constexpr const wchar_t* COMPONENT_LEVELED_BASE              = L"$dnpcl_component_leveled_base";
        static constexpr const wchar_t* COMPONENT_INTERNAL_BASE             = L"$dnpcl_component_internal_base";
        static constexpr const wchar_t* COMPONENT_LOADED_REFERENCE          = L"$dnpcl_component_loaded_reference";
        static constexpr const wchar_t* COMPONENT_SPAWNED_REFERENCE         = L"$dnpcl_component_spawned_reference";
        static constexpr const wchar_t* COMPONENT_MARKED_REFERENCE          = L"$dnpcl_component_marked_reference";

        static constexpr const wchar_t* COMPONENT_STATIC_BASES              = L"$dnpcl_component_static_bases";
        static constexpr const wchar_t* COMPONENT_DYNAMIC_BASES             = L"$dnpcl_component_dynamic_bases";
        static constexpr const wchar_t* COMPONENT_LEVELED_BASES             = L"$dnpcl_component_leveled_bases";
        static constexpr const wchar_t* COMPONENT_INTERNAL_BASES            = L"$dnpcl_component_internal_bases";
        static constexpr const wchar_t* COMPONENT_LOADED_REFERENCES         = L"$dnpcl_component_loaded_references";
        static constexpr const wchar_t* COMPONENT_SPAWNED_REFERENCES        = L"$dnpcl_component_spawned_references";
        static constexpr const wchar_t* COMPONENT_MARKED_REFERENCES         = L"$dnpcl_component_marked_references";

        static constexpr const wchar_t* COMPONENT_FILTER                    = L"$dnpcl_component_filter";
        static constexpr const wchar_t* COMPONENT_OPTIONS                   = L"$dnpcl_component_options";
        static constexpr const wchar_t* COMPONENT_PAGE                      = L"$dnpcl_component_page";
        static constexpr const wchar_t* COMPONENT_ITEM                      = L"$dnpcl_component_item";

        static constexpr const char*    SAFE_COMPONENT_STATIC_BASE          = "Static Base";
        static constexpr const char*    SAFE_COMPONENT_DYNAMIC_BASE         = "Dynamic Base";
        static constexpr const char*    SAFE_COMPONENT_LEVELED_BASE         = "Leveled Base";
        static constexpr const char*    SAFE_COMPONENT_INTERNAL_BASE        = "Internal Base";
        static constexpr const char*    SAFE_COMPONENT_LOADED_REFERENCE     = "Loaded Reference";
        static constexpr const char*    SAFE_COMPONENT_SPAWNED_REFERENCE    = "Spawned Reference";
        static constexpr const char*    SAFE_COMPONENT_MARKED_REFERENCE     = "Marked Reference";

        static constexpr const char*    SAFE_COMPONENT_STATIC_BASES         = "Static Bases";
        static constexpr const char*    SAFE_COMPONENT_DYNAMIC_BASES        = "Dynamic Bases";
        static constexpr const char*    SAFE_COMPONENT_LEVELED_BASES        = "Leveled Bases";
        static constexpr const char*    SAFE_COMPONENT_INTERNAL_BASES       = "Internal Bases";
        static constexpr const char*    SAFE_COMPONENT_LOADED_REFERENCES    = "Loaded References";
        static constexpr const char*    SAFE_COMPONENT_SPAWNED_REFERENCES   = "Spawned References";
        static constexpr const char*    SAFE_COMPONENT_MARKED_REFERENCES    = "Marked References";

        static constexpr const char*    SAFE_COMPONENT_FILTER               = "Filter";
        static constexpr const char*    SAFE_COMPONENT_OPTIONS              = "Options";
        static constexpr const char*    SAFE_COMPONENT_PAGE                 = "Page";
        static constexpr const char*    SAFE_COMPONENT_ITEM                 = "Item";

        static constexpr const char*    PRIORITIZED_MOD_NAME                = " NPC Lookup ";
        static constexpr const char*    UNPRIORITIZED_MOD_NAME              = "NPC Lookup ";
        static constexpr const char*    DEFAULT_PAGE                        = STATIC_BASES;

        static some<const char*>    To_Relation_Key(Relation_e relation);
        static some<const char*>    To_Is_Relation_Key(Relation_e relation);
        static Relation_e           From_Relation_Key(some<const char*> relation_key);
        static some<const char*>    To_Vitality_Key(Vitality_e vitality);
        static some<const char*>    To_Is_Vitality_Key(Vitality_e vitality);
        static Vitality_e           From_Vitality_Key(some<const char*> vitality_key);

    public:
        static std::mutex   mutex;

        static some<Main_t*>    Self();
        static String_t         Class_Name();
        static V::Class_t*      Class();
        static Int_t            String_Comparator(const char* str_a, const char* str_b);

    public:
        V::Object_t* Object();

    public:
        V::Variable_tt<String_t>& Current_Page_Variable();

    public:
        String_t            Current_Page();
        void                Current_Page(String_t current_page);

        Latent_Callback_i*  Create_Latent_Callback(V::Stack_ID_t stack_id);
        void                Destroy_Latent_Callback(Latent_Callback_i* lcallback);

        void                Toggle_Either(V::Variable_tt<Binary_e>& variable, Int_t option_a, Int_t option_b, Binary_e toggle);
        void                Toggle_Any(V::Variable_tt<Binary_e>& variable, Int_t option_a, Int_t option_b, Binary_e toggle);

        void                Toggle_And_Reset(V::Variable_tt<Bool_t>& variable, Int_t option, Latent_Callback_i* lcallback);
        void                Toggle_And_Update(V::Variable_tt<Bool_t>& variable, Int_t option, Latent_Callback_i* lcallback);
        void                Highlight(String_t info_text, Latent_Callback_i* lcallback);

        Bool_t              Should_Translate_Page_Titles();
        std::wstring        Translation(const wchar_t* key);
        void                Translation(const wchar_t* key, std::wstring&& translation);
        std::wstring        Singular_Title(const wchar_t* singular_name_key, const char* sub_title);
        std::wstring        Singular_Title(const wchar_t* singular_name_key, const char* item_name, Int_t item_index, Int_t item_count);
        std::wstring        Plural_Title(const wchar_t* plural_name_key, const wchar_t* sub_title_key);
        std::wstring        Plural_Title(const wchar_t* plural_name_key, Int_t item_count);
        std::wstring        Plural_Title(const wchar_t* plural_name_key, Int_t item_count, Int_t item_max);
        std::wstring        Plural_Title(const wchar_t* plural_name_key, Int_t item_count, Int_t page_index, Int_t page_count);
        void                Translated_Title_Text(std::wstring&& translation);

        std::string         Singular_Title(const char* singular_name, const char* sub_title);
        std::string         Singular_Title(const char* singular_name, const char* item_name, Int_t item_index, Int_t item_count);
        std::string         Plural_Title(const char* plural_name, const char* sub_title);
        std::string         Plural_Title(const char* plural_name, Int_t item_count);
        std::string         Plural_Title(const char* plural_name, Int_t item_count, Int_t item_max);
        std::string         Plural_Title(const char* plural_name, Int_t item_count, Int_t page_index, Int_t page_count);

        std::string         Pretty_ID(some<const char*> name, some<const char*> editor_id, some<const char*> form_id);

        maybe<size_t>       Option_To_Item_Index(Int_t option, Int_t item_count, Int_t page_index, Int_t headers_per_page, Int_t items_per_page);

    public:
        void On_Init();
        void On_Load();
        void On_Save();
        Bool_t On_Config_Open(V::Stack_ID_t stack_id);
        Bool_t On_Config_Close(V::Stack_ID_t stack_id);
        Bool_t On_Page_Open(V::Stack_ID_t stack_id, String_t current_page);
        Bool_t On_Option_Select(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Open(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Accept(V::Stack_ID_t stack_id, Int_t option, Int_t idx);
        Bool_t On_Option_Slider_Open(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Slider_Accept(V::Stack_ID_t stack_id, Int_t option, Float_t value);
        Bool_t On_Option_Input_Accept(V::Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Highlight(V::Stack_ID_t stack_id, Int_t option);

    public:
        void Update_1_1_1();

    public:
        static void Register_Me(some<V::Machine_t*> v_machine);
    };

}}
