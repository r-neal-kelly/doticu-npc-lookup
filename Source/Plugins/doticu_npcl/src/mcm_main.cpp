/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/interface.inl"
#include "doticu_skylib/translations.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_main.h"
#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_bases_static.h"
#include "mcm_bases_dynamic.h"
#include "mcm_bases_leveled.h"
#include "mcm_global_options.h"
#include "mcm_markers.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_loaded.h"
#include "mcm_references_spawned.h"

namespace doticu_npcl { namespace MCM {

    const String_t Main_t::_TEXT_DIVIDER_   = Main_t::Add_Font("_______________________",   "", "#80",  "27");
    const String_t Main_t::_TOGGLE_DIVIDER_ = Main_t::Add_Font("_____________________",     "", "#80",  "27");

    some<const char*> Main_t::To_Relation_Key(Relation_e relation)
    {
        if (relation == Relation_e::LOVER) {
            return LOVER;
        } else if (relation == Relation_e::ALLY) {
            return ALLY;
        } else if (relation == Relation_e::CONFIDANT) {
            return CONFIDANT;
        } else if (relation == Relation_e::FRIEND) {
            return FRIEND;
        } else if (relation == Relation_e::ACQUAINTANCE) {
            return ACQUAINTANCE;
        } else if (relation == Relation_e::RIVAL) {
            return RIVAL;
        } else if (relation == Relation_e::FOE) {
            return FOE;
        } else if (relation == Relation_e::ENEMY) {
            return ENEMY;
        } else if (relation == Relation_e::ARCHNEMESIS) {
            return ARCHNEMESIS;
        } else {
            return ANY;
        }
    }

    some<const char*> Main_t::To_Is_Relation_Key(Relation_e relation)
    {
        if (relation == Relation_e::LOVER) {
            return IS_LOVER;
        } else if (relation == Relation_e::ALLY) {
            return IS_ALLY;
        } else if (relation == Relation_e::CONFIDANT) {
            return IS_CONFIDANT;
        } else if (relation == Relation_e::FRIEND) {
            return IS_FRIEND;
        } else if (relation == Relation_e::ACQUAINTANCE) {
            return IS_ACQUAINTANCE;
        } else if (relation == Relation_e::RIVAL) {
            return IS_RIVAL;
        } else if (relation == Relation_e::FOE) {
            return IS_FOE;
        } else if (relation == Relation_e::ENEMY) {
            return IS_ENEMY;
        } else if (relation == Relation_e::ARCHNEMESIS) {
            return IS_ARCHNEMESIS;
        } else {
            return _NONE_;
        }
    }

    Relation_e Main_t::From_Relation_Key(some<const char*> relation_key)
    {
        SKYLIB_ASSERT_SOME(relation_key);

        if (CString_t::Is_Same(LOVER, relation_key(), false)) {
            return Relation_e::LOVER;
        } else if (CString_t::Is_Same(ALLY, relation_key(), false)) {
            return Relation_e::ALLY;
        } else if (CString_t::Is_Same(CONFIDANT, relation_key(), false)) {
            return Relation_e::CONFIDANT;
        } else if (CString_t::Is_Same(FRIEND, relation_key(), false)) {
            return Relation_e::FRIEND;
        } else if (CString_t::Is_Same(ACQUAINTANCE, relation_key(), false)) {
            return Relation_e::ACQUAINTANCE;
        } else if (CString_t::Is_Same(RIVAL, relation_key(), false)) {
            return Relation_e::RIVAL;
        } else if (CString_t::Is_Same(FOE, relation_key(), false)) {
            return Relation_e::FOE;
        } else if (CString_t::Is_Same(ENEMY, relation_key(), false)) {
            return Relation_e::ENEMY;
        } else if (CString_t::Is_Same(ARCHNEMESIS, relation_key(), false)) {
            return Relation_e::ARCHNEMESIS;
        } else {
            return Relation_e::ACQUAINTANCE;
        }
    }

    some<const char*> Main_t::To_Vitality_Key(Vitality_e vitality)
    {
        if (vitality == Vitality_e::MORTAL) {
            return MORTAL;
        } else if (vitality == Vitality_e::PROTECTED) {
            return PROTECTED;
        } else if (vitality == Vitality_e::ESSENTIAL) {
            return ESSENTIAL;
        } else if (vitality == Vitality_e::INVULNERABLE) {
            return INVULNERABLE;
        } else {
            return ANY;
        }
    }

    some<const char*> Main_t::To_Is_Vitality_Key(Vitality_e vitality)
    {
        if (vitality == Vitality_e::MORTAL) {
            return IS_MORTAL;
        } else if (vitality == Vitality_e::PROTECTED) {
            return IS_PROTECTED;
        } else if (vitality == Vitality_e::ESSENTIAL) {
            return IS_ESSENTIAL;
        } else if (vitality == Vitality_e::INVULNERABLE) {
            return IS_INVULNERABLE;
        } else {
            return _NONE_;
        }
    }

    Vitality_e Main_t::From_Vitality_Key(some<const char*> vitality_key)
    {
        SKYLIB_ASSERT_SOME(vitality_key);

        if (CString_t::Is_Same(MORTAL, vitality_key(), false)) {
            return Vitality_e::MORTAL;
        } else if (CString_t::Is_Same(PROTECTED, vitality_key(), false)) {
            return Vitality_e::PROTECTED;
        } else if (CString_t::Is_Same(ESSENTIAL, vitality_key(), false)) {
            return Vitality_e::ESSENTIAL;
        } else if (CString_t::Is_Same(INVULNERABLE, vitality_key(), false)) {
            return Vitality_e::INVULNERABLE;
        } else {
            return Vitality_e::_NONE_;
        }
    }

    using Default_Page_t = Static_Bases_t;

    std::mutex      Main_t::mutex;

    some<Main_t*>   Main_t::Self()                  { return static_cast<some<Main_t*>>(Consts_t::NPCL_MCM_Quest()); }
    String_t        Main_t::Class_Name()            { DEFINE_CLASS_NAME("doticu_npcl_mcm_main"); }
    V::Class_t*     Main_t::Class()                 { DEFINE_CLASS(); }

    Int_t Main_t::String_Comparator(const char* str_a, const char* str_b)
    {
        if (!str_a || !str_a[0]) {
            return Comparator_e::IS_UNORDERED;
        } else if (!str_b || !str_b[0]) {
            return Comparator_e::IS_ORDERED;
        } else if (str_a[0] == '0' && str_a[1] == 'x' && str_b[0] != '0' && str_b[1] != 'x') {
            return Comparator_e::IS_UNORDERED;
        } else if (str_a[0] != '0' && str_a[1] != 'x' && str_b[0] == '0' && str_b[1] == 'x') {
            return Comparator_e::IS_ORDERED;
        } else {
            return _stricmp(str_a, str_b);
        }
    }

    V::Object_t* Main_t::Object() { DEFINE_OBJECT_METHOD(); }

    V::Variable_tt<String_t>& Main_t::Current_Page_Variable() { DEFINE_VARIABLE_REFERENCE(String_t, "p_current_page"); }

    String_t Main_t::Current_Page()
    {
        String_t current_page = Current_Page_Variable();
        if (!current_page) {
            current_page = DEFAULT_PAGE;
            Current_Page(current_page);
        }
        return current_page;
    }

    void Main_t::Current_Page(String_t current_page)
    {
        Current_Page_Variable() = current_page;
    }

    Latent_Callback_i* Main_t::Create_Latent_Callback(V::Stack_ID_t stack_id)
    {
        struct Callback : public Latent_Callback_i
        {
            V::Stack_ID_t stack_id;
            Callback(V::Stack_ID_t stack_id) :
                stack_id(stack_id)
            {
            }
            void operator()()
            {
                V::Machine_t::Self()->Return_Latent_Function(stack_id, V::Variable_t());
            }
        };
        return new Callback(stack_id);
    }

    void Main_t::Destroy_Latent_Callback(Latent_Callback_i* lcallback)
    {
        if (lcallback) {
            lcallback->operator()();
            delete lcallback;
        }
    }

    void Main_t::Toggle_Either(V::Variable_tt<Binary_e>& variable, Int_t option_a, Int_t option_b, Binary_e toggle)
    {
        if (toggle == Binary_e::A) {
            if (variable == Binary_e::A) {
                variable = Binary_e::NONE;
            } else {
                variable = Binary_e::A;
            }
        } else if (toggle == Binary_e::B) {
            if (variable == Binary_e::B) {
                variable = Binary_e::NONE;
            } else {
                variable = Binary_e::B;
            }
        }

        Toggle_Option_Value(option_a, variable == Binary_e::A, false);
        Toggle_Option_Value(option_b, variable == Binary_e::B, true);
    }

    void Main_t::Toggle_Any(V::Variable_tt<Binary_e>& variable, Int_t option_a, Int_t option_b, Binary_e toggle)
    {
        if (toggle == Binary_e::A) {
            if (variable == Binary_e::NONE) {
                variable = Binary_e::A;
            } else if (variable == Binary_e::BOTH) {
                variable = Binary_e::B;
            } else if (variable == Binary_e::A) {
                variable = Binary_e::NONE;
            } else if (variable == Binary_e::B) {
                variable = Binary_e::BOTH;
            }
        } else if (toggle == Binary_e::B) {
            if (variable == Binary_e::NONE) {
                variable = Binary_e::B;
            } else if (variable == Binary_e::BOTH) {
                variable = Binary_e::A;
            } else if (variable == Binary_e::A) {
                variable = Binary_e::BOTH;
            } else if (variable == Binary_e::B) {
                variable = Binary_e::NONE;
            }
        }

        Toggle_Option_Value(option_a, variable == Binary_e::A || variable == Binary_e::BOTH, false);
        Toggle_Option_Value(option_b, variable == Binary_e::B || variable == Binary_e::BOTH, true);
    }

    void Main_t::Toggle_And_Reset(V::Variable_tt<Bool_t>& variable, Int_t option, Latent_Callback_i* lcallback)
    {
        Disable_Option(option);
        variable = !variable;
        Reset_Page();
        Destroy_Latent_Callback(lcallback);
    }

    void Main_t::Toggle_And_Update(V::Variable_tt<Bool_t>& variable, Int_t option, Latent_Callback_i* lcallback)
    {
        Bool_t value = variable;
        variable = !value;
        Toggle_Option_Value(option, !value);
        Destroy_Latent_Callback(lcallback);
    }

    void Main_t::Highlight(String_t info_text, Latent_Callback_i* lcallback)
    {
        SKYLIB_ASSERT_SOME(info_text);

        Current_Info_Text() = info_text;
        Destroy_Latent_Callback(lcallback);
    }

    Bool_t Main_t::Should_Translate_Page_Titles()
    {
        return Global_Options_t::Self()->Translate_Page_Titles(); // maybe add a non english check here.
    }

    std::wstring Main_t::Translation(const wchar_t* key)
    {
        std::wstring translation = Translations_t::Translation(key);
        return translation[0] == L'_' ? translation.data() + 1 : translation.data();
    }

    void Main_t::Translation(const wchar_t* key, std::wstring&& value_to_copy)
    {
        Translations_t::Translation(key, value_to_copy.c_str());
    }

    std::wstring Main_t::Singular_Title(const wchar_t* singular_name_key, const char* sub_title)
    {
        return std::wstring(Translation(singular_name_key)) + L": " + CString_t::To<std::wstring>(sub_title);
    }

    std::wstring Main_t::Singular_Title(const wchar_t* singular_name_key, const char* item_name, Int_t item_index, Int_t item_count)
    {
        std::wstring name =
            std::wstring(Translation(singular_name_key)) + L": " +
            CString_t::To<std::wstring>(item_name);

        std::wstring items =
            std::wstring(Translation(COMPONENT_ITEM)) + L": " +
            std::to_wstring(item_index + 1) + L"/" +
            std::to_wstring(item_count);

        return name + L"               " + items;
    }

    std::wstring Main_t::Plural_Title(const wchar_t* plural_name_key, const wchar_t* sub_title_key)
    {
        return std::wstring(Translation(plural_name_key)) + L": " + Translation(sub_title_key);
    }

    std::wstring Main_t::Plural_Title(const wchar_t* plural_name_key, Int_t item_count)
    {
        std::wstring items =
            std::wstring(Translation(plural_name_key)) + L": " +
            std::to_wstring(item_count);

        return items;
    }

    std::wstring Main_t::Plural_Title(const wchar_t* plural_name_key, Int_t item_count, Int_t item_max)
    {
        std::wstring items =
            std::wstring(Translation(plural_name_key)) + L": " +
            std::to_wstring(item_count) + L"/" +
            std::to_wstring(item_max);

        return items;
    }

    std::wstring Main_t::Plural_Title(const wchar_t* plural_name_key, Int_t item_count, Int_t page_index, Int_t page_count)
    {
        std::wstring items =
            std::wstring(Translation(plural_name_key)) + L": " +
            std::to_wstring(item_count);

        std::wstring pages =
            std::wstring(Translation(COMPONENT_PAGE)) + L": " +
            std::to_wstring(page_index + 1) + L"/" +
            std::to_wstring(page_count);

        return items + L"               " + pages;
    }

    void Main_t::Translated_Title_Text(std::wstring&& translation)
    {
        Translation(PLACEHOLDER_TITLE_W, std::move(translation));
        Title_Text(PLACEHOLDER_TITLE);
    }

    std::string Main_t::Singular_Title(const char* singular_name, const char* sub_title)
    {
        return std::string(singular_name) + _COLON_SPACE_ + sub_title;
    }

    std::string Main_t::Singular_Title(const char* singular_name, const char* item_name, Int_t item_index, Int_t item_count)
    {
        std::string name =
            std::string(singular_name) + _COLON_SPACE_ +
            item_name;

        std::string items =
            std::string(SAFE_COMPONENT_ITEM) + _COLON_SPACE_ +
            std::to_string(item_index + 1) + "/" +
            std::to_string(item_count);

        return name + "               " + items;
    }

    std::string Main_t::Plural_Title(const char* plural_name, const char* sub_title)
    {
        return std::string(plural_name) + _COLON_SPACE_ + sub_title;
    }

    std::string Main_t::Plural_Title(const char* plural_name, Int_t item_count)
    {
        std::string items =
            std::string(plural_name) + _COLON_SPACE_ +
            std::to_string(item_count);

        return items;
    }

    std::string Main_t::Plural_Title(const char* plural_name, Int_t item_count, Int_t item_max)
    {
        std::string items =
            std::string(plural_name) + _COLON_SPACE_ +
            std::to_string(item_count) + "/" +
            std::to_string(item_max);

        return items;
    }

    std::string Main_t::Plural_Title(const char* plural_name, Int_t item_count, Int_t page_index, Int_t page_count)
    {
        std::string items =
            std::string(plural_name) + _COLON_SPACE_ +
            std::to_string(item_count);

        std::string pages =
            std::string(SAFE_COMPONENT_PAGE) + _COLON_SPACE_ +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return items + "               " + pages;
    }

    std::string Main_t::Pretty_ID(some<const char*> name, some<const char*> editor_id, some<const char*> form_id)
    {
        SKYLIB_ASSERT(name);
        SKYLIB_ASSERT(editor_id);
        SKYLIB_ASSERT(form_id);

        if (name[0] && editor_id[0]) {
            return
                std::string(name()) + _SPACED_DASH_ +
                editor_id() + _SPACED_DASH_ +
                form_id();
        } else if (name[0]) {
            return
                std::string(name()) + _SPACED_DASH_ +
                form_id();
        } else if (editor_id[0]) {
            return
                std::string(editor_id()) + _SPACED_DASH_ +
                form_id();
        } else {
            return
                std::string(form_id());
        }
    }

    maybe<size_t> Main_t::Option_To_Item_Index(Int_t option,
                                               Int_t item_count,
                                               Int_t page_index,
                                               Int_t headers_per_page,
                                               Int_t items_per_page)
    {
        Int_t relative_idx = mcmlib::Option_t(option).position - headers_per_page;
        if (relative_idx > -1 && relative_idx < items_per_page) {
            Int_t absolute_idx = page_index * items_per_page + relative_idx;
            if (absolute_idx > -1 && absolute_idx < item_count) {
                return absolute_idx;
            } else {
                return none<size_t>();
            }
        } else {
            return none<size_t>();
        }
    }

    static Bool_t Is_Same(const char* page_a, const char* page_b)
    {
        return skylib::CString_t::Is_Same(page_a, page_b, true);
    }

    void Main_t::On_Init()
    {
        std::lock_guard<std::mutex> guard(mutex);

        Static_Bases_t::Self()->On_Init();
        Dynamic_Bases_t::Self()->On_Init();
        Leveled_Bases_t::Self()->On_Init();
        Loaded_References_t::Self()->On_Init();
        Spawned_References_t::Self()->On_Init();
        Markers_t::Self()->On_Init();
        Global_Options_t::Self()->On_Init();
    }

    void Main_t::On_Load()
    {
        std::lock_guard<std::mutex> guard(mutex);

        Static_Bases_t::Self()->On_Load();
        Dynamic_Bases_t::Self()->On_Load();
        Leveled_Bases_t::Self()->On_Load();
        Loaded_References_t::Self()->On_Load();
        Spawned_References_t::Self()->On_Load();
        Markers_t::Self()->On_Load();
        Global_Options_t::Self()->On_Load();
    }

    void Main_t::On_Save()
    {
        std::lock_guard<std::mutex> guard(mutex);

        Static_Bases_t::Self()->On_Save();
        Dynamic_Bases_t::Self()->On_Save();
        Leveled_Bases_t::Self()->On_Save();
        Loaded_References_t::Self()->On_Save();
        Spawned_References_t::Self()->On_Save();
        Markers_t::Self()->On_Save();
        Global_Options_t::Self()->On_Save();
    }

    Bool_t Main_t::On_Config_Open(V::Stack_ID_t stack_id)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

        Vector_t<String_t> pages;
        pages.reserve(7);
        pages.push_back(STATIC_BASES);
        pages.push_back(DYNAMIC_BASES);
        pages.push_back(LEVELED_BASES);
        pages.push_back(LOADED_REFERENCES);
        pages.push_back(SPAWNED_REFERENCES);
        pages.push_back(MARKED_REFERENCES);
        pages.push_back(GLOBAL_OPTIONS);
        Pages() = pages;

        Static_Bases_t::Self()->On_Config_Open();
        Dynamic_Bases_t::Self()->On_Config_Open();
        Leveled_Bases_t::Self()->On_Config_Open();
        Loaded_References_t::Self()->On_Config_Open();
        Spawned_References_t::Self()->On_Config_Open();
        Markers_t::Self()->On_Config_Open();
        Global_Options_t::Self()->On_Config_Open();

        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Config_Close(V::Stack_ID_t stack_id)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

        Static_Bases_t::Self()->On_Config_Close();
        Dynamic_Bases_t::Self()->On_Config_Close();
        Leveled_Bases_t::Self()->On_Config_Close();
        Loaded_References_t::Self()->On_Config_Close();
        Spawned_References_t::Self()->On_Config_Close();
        Markers_t::Self()->On_Config_Close();
        Global_Options_t::Self()->On_Config_Close();

        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Page_Open(V::Stack_ID_t stack_id, String_t current_page)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Bool_t is_refresh = true;
        if (!current_page) {
            current_page = Current_Page();
        } else {
            if (!CString_t::Is_Same(current_page, Current_Page(), true)) {
                is_refresh = false;
                Current_Page(current_page);
            }
        }

        String_t page = current_page;
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Page_Open(is_refresh, lcallback);
        else                                        Default_Page_t::Self()->On_Page_Open(is_refresh, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Select(V::Stack_ID_t stack_id, Int_t option)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Select(option, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Select(option, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Open(V::Stack_ID_t stack_id, Int_t option)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Menu_Open(option, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Menu_Open(option, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Accept(V::Stack_ID_t stack_id, Int_t option, Int_t idx)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Open(V::Stack_ID_t stack_id, Int_t option)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Slider_Open(option, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Slider_Open(option, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Accept(V::Stack_ID_t stack_id, Int_t option, Float_t value)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Slider_Accept(option, value, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Input_Accept(V::Stack_ID_t stack_id, Int_t option, String_t value)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Input_Accept(option, value, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Keymap_Change(V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Default(V::Stack_ID_t stack_id, Int_t option)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Default(option, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Default(option, lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Highlight(V::Stack_ID_t stack_id, Int_t option)
    {
        std::lock_guard<std::mutex> guard(mutex);

        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(stack_id);

             if (Is_Same(page, STATIC_BASES))       Static_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES))      Dynamic_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES))      Leveled_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES))  Loaded_References_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES)) Spawned_References_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, MARKED_REFERENCES))  Markers_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, GLOBAL_OPTIONS))     Global_Options_t::Self()->On_Option_Highlight(option, lcallback);
        else                                        Default_Page_t::Self()->On_Option_Highlight(option, lcallback);

        return true;
    }

    void Main_t::Update_1_1_1()
    {
        Global_Options_t::Self()->Prioritize_MCM_Menu() = true;
    }

    void Main_t::Register_Me(some<V::Machine_t*> v_machine)
    {
        Config_Base_t::Register_Me(v_machine);

        String_t class_name = Class_Name();

        #define METHOD(NAME_, WAITS_FOR_FRAME_, RETURN_, METHOD_, ...)              \
        SKYLIB_M                                                                    \
            BIND_METHOD(v_machine, class_name, Main_t,                              \
                        NAME_, WAITS_FOR_FRAME_, RETURN_, METHOD_, __VA_ARGS__);    \
        SKYLIB_W

        METHOD("OnConfigOpen", true, void, On_Config_Open);
        METHOD("OnConfigClose", true, void, On_Config_Close);
        METHOD("OnPageReset", true, void, On_Page_Open, String_t);
        METHOD("OnOptionSelect", true, void, On_Option_Select, Int_t);
        METHOD("OnOptionMenuOpen", true, void, On_Option_Menu_Open, Int_t);
        METHOD("OnOptionMenuAccept", true, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("OnOptionSliderOpen", true, void, On_Option_Slider_Open, Int_t);
        METHOD("OnOptionSliderAccept", true, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("OnOptionInputAccept", true, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("OnOptionKeymapChange", true, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("OnOptionDefault", true, void, On_Option_Default, Int_t);
        METHOD("OnOptionHighlight", true, void, On_Option_Highlight, Int_t);

        #undef METHOD
    }

}}
