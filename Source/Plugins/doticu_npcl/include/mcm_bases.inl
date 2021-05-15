/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_macros.h"

#include "doticu_mcmlib/config_base_macros.h"

#include "consts.h"
#include "spawned_actors.h"
#include "mcm_selectables.h"
#include "mcm_bases.h"

#define DEFINE_VAR DEFINE_VARIABLE_REFERENCE

namespace doticu_npcl { namespace MCM {

    template <typename Item_Section_e>
    Bool_t Item_Sections_t::Serialize(V::Variable_tt<Vector_t<String_t>>& variable)
    {
        std::lock_guard<std::mutex> guard(mutex);

        size_t item_section_count = item_sections.size();
        if (item_section_count > 0) {
            Vector_t<String_t> strs;
            strs.reserve(item_section_count);

            for (size_t idx = 0, end = item_section_count; idx < end; idx += 1) {
                some<const char*> str = Item_Section_e::To_String(item_sections[idx]);
                strs.push_back(str());
            }

            variable = strs;

            return true;
        } else {
            return false;
        }
    }

    template <typename Item_Section_e>
    Bool_t Item_Sections_t::Deserialize(V::Variable_tt<Vector_t<String_t>>& variable)
    {
        std::lock_guard<std::mutex> guard(mutex);

        V::Array_t* arr = variable.Array();
        if (arr) {
            item_sections.clear();
            item_sections.reserve(arr->count);

            for (size_t idx = 0, end = arr->count; idx < end; idx += 1) {
                V::Variable_t* var = arr->Point(idx);
                if (var && var->Is_String()) {
                    String_t str = var->String();
                    if (str) {
                        Item_Section_e item_section = Item_Section_e::From_String(str);
                        if (item_section > Item_Section_e::NONE && item_section < Item_Section_e::_END_) {
                            item_sections.push_back(item_section);
                        }
                    }
                }
            }

            return true;
        } else {
            return false;
        }
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline V::Variable_tt<String_t>& Bases_t<B, I>::Current_View_Variable() { DEFINE_VAR(String_t, "p_current_view"); }

    template <typename B, typename I>
    inline Bases_View_e Bases_t<B, I>::Current_View()
    {
        String_t current_view = Current_View_Variable();
        if (CString_t::Is_Same(current_view, LIST_VIEW, true)) {
            return Bases_View_e::LIST;
        } else if (CString_t::Is_Same(current_view, FILTER_VIEW, true)) {
            return Bases_View_e::FILTER;
        } else if (CString_t::Is_Same(current_view, OPTIONS_VIEW, true)) {
            return Bases_View_e::OPTIONS;
        } else if (CString_t::Is_Same(current_view, ITEM_VIEW, true)) {
            return Bases_View_e::ITEM;
        } else {
            Current_View_Variable() = LIST_VIEW;
            return Bases_View_e::LIST;
        }
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::Current_View(Bases_View_e value)
    {
        if (value == Bases_View_e::LIST) {
            Current_View_Variable() = LIST_VIEW;
        } else if (value == Bases_View_e::FILTER) {
            Current_View_Variable() = FILTER_VIEW;
        } else if (value == Bases_View_e::OPTIONS) {
            Current_View_Variable() = OPTIONS_VIEW;
        } else if (value == Bases_View_e::ITEM) {
            Current_View_Variable() = ITEM_VIEW;
        } else {
            Current_View_Variable() = LIST_VIEW;
        }
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Init()
    {
        List()->On_Init();
        Filter()->On_Init();
        Options()->On_Init();
        Item()->On_Init();
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Load()
    {
        List()->On_Load();
        Filter()->On_Load();
        Options()->On_Load();
        Item()->On_Load();
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Save()
    {
        List()->On_Save();
        Filter()->On_Save();
        Options()->On_Save();
        Item()->On_Save();
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Config_Open()
    {
        List()->On_Config_Open();
        Filter()->On_Config_Open();
        Options()->On_Config_Open();
        Item()->On_Config_Open();
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Config_Close()
    {
        List()->On_Config_Close();
        Filter()->On_Config_Close();
        Options()->On_Config_Close();
        Item()->On_Config_Close();
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Page_Open(is_refresh, lcallback);
        else                                            List()->On_Page_Open(is_refresh, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Select(option, lcallback);
        else                                            List()->On_Option_Select(option, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Menu_Open(option, lcallback);
        else                                            List()->On_Option_Menu_Open(option, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                            List()->On_Option_Menu_Accept(option, idx, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Slider_Open(option, lcallback);
        else                                            List()->On_Option_Slider_Open(option, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Slider_Accept(option, value, lcallback);
        else                                            List()->On_Option_Slider_Accept(option, value, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Input_Accept(option, value, lcallback);
        else                                            List()->On_Option_Input_Accept(option, value, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                            List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Default(option, lcallback);
        else                                            List()->On_Option_Default(option, lcallback);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Highlight(option, lcallback);
        else                                            List()->On_Option_Highlight(option, lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    Bool_t          Bases_List_t<B, I>::do_update_items = true;
    template <typename B, typename I>
    Vector_t<I>     Bases_List_t<B, I>::read = Vector_t<I>();
    template <typename B, typename I>
    Vector_t<I>     Bases_List_t<B, I>::write = Vector_t<I>();
    template <typename B, typename I>
    Vector_t<I>*    Bases_List_t<B, I>::items = nullptr;

    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Filter_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Options_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Previous_Page_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Next_Page_Option()      { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::Reset_Option_Ints()
    {
        Filter_Option()         = -1;
        Options_Option()        = -1;
        Previous_Page_Option()  = -1;
        Next_Page_Option()      = -1;
    }

    template <typename B, typename I>
    inline V::Variable_tt<Int_t>& Bases_List_t<B, I>::Page_Index() { DEFINE_VAR(Int_t, "p_list_page_index"); }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::Clear()
    {
        do_update_items = true;
        read.clear();
        write.clear();
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Init()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Load()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Save()
    {
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Config_Open()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Config_Close()
    {
        List()->Clear();
    }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_List_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Back_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Clear_Option()            { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Search_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Select_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Negate_Option()       { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Search_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Select_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Negate_Option()      { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Search_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Select_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Negate_Option()      { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Template_Search_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Template_Select_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Template_Negate_Option()  { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Faction_Search_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Faction_Select_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Faction_Negate_Option()   { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Keyword_Search_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Keyword_Select_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Keyword_Negate_Option()   { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Select_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Negate_Option()  { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Vitality_Select_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Vitality_Negate_Option()  { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Male_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Female_Option()           { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Unique_Option()           { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Generic_Option()          { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::Reset_Option_Ints()
    {
        Back_Option()               = -1;
        Clear_Option()              = -1;

        Mod_Search_Option()         = -1;
        Mod_Select_Option()         = -1;
        Mod_Negate_Option()         = -1;

        Race_Search_Option()        = -1;
        Race_Select_Option()        = -1;
        Race_Negate_Option()        = -1;

        Base_Search_Option()        = -1;
        Base_Select_Option()        = -1;
        Base_Negate_Option()        = -1;

        Template_Search_Option()    = -1;
        Template_Select_Option()    = -1;
        Template_Negate_Option()    = -1;

        Faction_Search_Option()     = -1;
        Faction_Select_Option()     = -1;
        Faction_Negate_Option()     = -1;

        Keyword_Search_Option()     = -1;
        Keyword_Select_Option()     = -1;
        Keyword_Negate_Option()     = -1;

        Relation_Select_Option()    = -1;
        Relation_Negate_Option()    = -1;

        Vitality_Select_Option()    = -1;
        Vitality_Negate_Option()    = -1;

        Male_Option()               = -1;
        Female_Option()             = -1;

        Unique_Option()             = -1;
        Generic_Option()            = -1;
    }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Mod_Argument()            { DEFINE_VAR(String_t, "p_filter_mod_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Mod_Do_Negate()           { DEFINE_VAR(Bool_t, "p_filter_mod_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Race_Argument()           { DEFINE_VAR(String_t, "p_filter_race_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Race_Do_Negate()          { DEFINE_VAR(Bool_t, "p_filter_race_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Base_Argument()           { DEFINE_VAR(String_t, "p_filter_base_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Base_Do_Negate()          { DEFINE_VAR(Bool_t, "p_filter_base_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Template_Argument()       { DEFINE_VAR(String_t, "p_filter_template_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Template_Do_Negate()      { DEFINE_VAR(Bool_t, "p_filter_template_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Faction_Argument()        { DEFINE_VAR(String_t, "p_filter_faction_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Faction_Do_Negate()       { DEFINE_VAR(Bool_t, "p_filter_faction_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Filter_t<B, I>::Keyword_Argument()        { DEFINE_VAR(String_t, "p_filter_keyword_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Keyword_Do_Negate()       { DEFINE_VAR(Bool_t, "p_filter_keyword_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<Relation_e>&  Bases_Filter_t<B, I>::Relation_Argument()       { DEFINE_VAR(Relation_e, "p_filter_relation_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Relation_Do_Negate()      { DEFINE_VAR(Bool_t, "p_filter_relation_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<Vitality_e>&  Bases_Filter_t<B, I>::Vitality_Argument()       { DEFINE_VAR(Vitality_e, "p_filter_vitality_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Filter_t<B, I>::Vitality_Do_Negate()      { DEFINE_VAR(Bool_t, "p_filter_vitality_do_negate"); }

    template <typename B, typename I>
    inline V::Variable_tt<Binary_e>&    Bases_Filter_t<B, I>::Male_Female_Argument()    { DEFINE_VAR(Binary_e, "p_filter_male_female_argument"); }
    template <typename B, typename I>
    inline V::Variable_tt<Binary_e>&    Bases_Filter_t<B, I>::Unique_Generic_Argument() { DEFINE_VAR(Binary_e, "p_filter_unique_generic_argument"); }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::Clear()
    {
        Mod_Argument() = "";
        Mod_Do_Negate() = false;

        Race_Argument() = "";
        Race_Do_Negate() = false;

        Base_Argument() = "";
        Base_Do_Negate() = false;

        Template_Argument() = "";
        Template_Do_Negate() = false;

        Faction_Argument() = "";
        Faction_Do_Negate() = false;

        Keyword_Argument() = "";
        Keyword_Do_Negate() = false;

        Relation_Argument() = Relation_e::_NONE_;
        Relation_Do_Negate() = false;

        Vitality_Argument() = Vitality_e::_NONE_;
        Vitality_Do_Negate() = false;

        Male_Female_Argument() = Binary_e::NONE;
        Unique_Generic_Argument() = Binary_e::NONE;
    }

    template <typename B, typename I>
    template <typename Type_t>
    inline Filter_State_t<Type_t> Bases_Filter_t<B, I>::Execute(Vector_t<Type_t>* read, Vector_t<Type_t>* write)
    {
        Filter_State_t<Type_t> filter_state(read, write);

        Mod_Filter_t<Type_t>(filter_state, Mod_Argument(), Mod_Do_Negate());
        Race_Filter_t<Type_t>(filter_state, Race_Argument(), Race_Do_Negate());
        Base_Filter_t<Type_t>(filter_state, Base_Argument(), Base_Do_Negate());
        Template_Filter_t<Type_t>(filter_state, Template_Argument(), Template_Do_Negate());
        Faction_Filter_t<Type_t>(filter_state, Faction_Argument(), Faction_Do_Negate());
        Keyword_Filter_t<Type_t>(filter_state, Keyword_Argument(), Keyword_Do_Negate());
        Relation_Filter_t<Type_t>(filter_state, Consts_t::Skyrim_Player_Actor_Base(), Relation_Argument(), Relation_Do_Negate());
        Vitality_Filter_t<Type_t>(filter_state, Vitality_Argument(), Vitality_Do_Negate());
        Male_Female_Filter_t<Type_t>(filter_state, Male_Female_Argument());
        Unique_Generic_Filter_t<Type_t>(filter_state, Unique_Generic_Argument());

        return std::move(filter_state);
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Mods()
    {
        return Selectable_Mods_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Races()
    {
        return Selectable_Races_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Bases()
    {
        return Selectable_Bases_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Templates()
    {
        return Selectable_Templates_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Factions()
    {
        return Selectable_Factions_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Keywords()
    {
        return Selectable_Keywords_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Relations()
    {
        return Selectable_Relations_t<B, I>(Consts_t::Skyrim_Player_Actor_Base()()).Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Vitalities()
    {
        return Selectable_Vitalities_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::Build_Filters(const char* type_name)
    {
        some<Main_t*> mcm = Main_t::Self();

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Clear_Option() = mcm->Add_Text_Option(Main_t::CENTER_CLEAR, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::MOD);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Mod_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Mod_Argument());
        Mod_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Mod_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Mod_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RACE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Race_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Race_Argument());
        Race_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Race_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Race_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(type_name);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Base_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Base_Argument());
        Base_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Base_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Base_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::TEMPLATE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Template_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Template_Argument());
        Template_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Template_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Template_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::FACTION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Faction_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Faction_Argument());
        Faction_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Faction_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Faction_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::KEYWORD);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Keyword_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Keyword_Argument());
        Keyword_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Keyword_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Keyword_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RELATION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Relation_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, mcm->To_Relation_Key(Relation_Argument())());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::VITALITY);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Vitality_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, mcm->To_Vitality_Key(Vitality_Argument())());
        Vitality_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Vitality_Do_Negate());

        mcm->Add_Header_Option(Main_t::OTHER);
        mcm->Add_Header_Option(Main_t::_NONE_);
        if (Filter()->Toggle_Type() == Toggle_Type_e::EITHER) {

            Male_Option() = mcm->Add_Toggle_Option(Main_t::IS_MALE, Male_Female_Argument() == Binary_e::A);
            Female_Option() = mcm->Add_Toggle_Option(Main_t::IS_FEMALE, Male_Female_Argument() == Binary_e::B);

            Unique_Option() = mcm->Add_Toggle_Option(Main_t::IS_UNIQUE, Unique_Generic_Argument() == Binary_e::A);
            Generic_Option() = mcm->Add_Toggle_Option(Main_t::IS_GENERIC, Unique_Generic_Argument() == Binary_e::B);

        } else if (Filter()->Toggle_Type() == Toggle_Type_e::ANY) {

            Binary_e male_female_argument = Male_Female_Argument();
            Male_Option() = mcm->Add_Toggle_Option(
                Main_t::HAS_MALE,
                male_female_argument == Binary_e::A ||
                male_female_argument == Binary_e::ALL
            );
            Female_Option() = mcm->Add_Toggle_Option(
                Main_t::HAS_FEMALE,
                male_female_argument == Binary_e::B ||
                male_female_argument == Binary_e::ALL
            );

            Binary_e unique_generic_argument = Unique_Generic_Argument();
            Unique_Option() = mcm->Add_Toggle_Option(
                Main_t::HAS_UNIQUE,
                unique_generic_argument == Binary_e::A ||
                unique_generic_argument == Binary_e::ALL
            );
            Generic_Option() = mcm->Add_Toggle_Option(
                Main_t::HAS_GENERIC,
                unique_generic_argument == Binary_e::B ||
                unique_generic_argument == Binary_e::ALL
            );

        }
    }

    template <typename B, typename I>
    inline void  Bases_Filter_t<B, I>::Highlight_Toggle_Option(Latent_Callback_i* lcallback)
    {
        if (Filter()->Toggle_Type() == Toggle_Type_e::EITHER) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_TOGGLE_EITHER, lcallback);
        } else if (Filter()->Toggle_Type() == Toggle_Type_e::ANY) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_TOGGLE_ANY, lcallback);
        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Filter_t<B, I>::Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == Back_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_BACK, lcallback);
            return true;
        } else if (option == Clear_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_CLEAR, lcallback);
            return true;

        } else if (option == Mod_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Mod_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Mod_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Race_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Race_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Race_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Base_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Base_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Base_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Template_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Template_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Template_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Faction_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Faction_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Faction_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Keyword_Search_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SEARCH, lcallback);
            return true;
        } else if (option == Keyword_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Keyword_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Relation_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Relation_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Vitality_Select_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_SELECT, lcallback);
            return true;
        } else if (option == Vitality_Negate_Option()) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_FILTER_NEGATE, lcallback);
            return true;

        } else if (option == Male_Option()) {
            Highlight_Toggle_Option(lcallback);
            return true;
        } else if (option == Female_Option()) {
            Highlight_Toggle_Option(lcallback);
            return true;

        } else if (option == Unique_Option()) {
            Highlight_Toggle_Option(lcallback);
            return true;
        } else if (option == Generic_Option()) {
            Highlight_Toggle_Option(lcallback);
            return true;

        } else {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
            return true;

        }
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Init()
    {
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Load()
    {
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Save()
    {
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Config_Open()
    {
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Config_Close()
    {
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();

        } else if (option == Clear_Option()) {
            mcm->Disable_Option(option);
            Clear();
            mcm->Reset_Page();

        } else if (option == Mod_Negate_Option()) {
            Bool_t value = Mod_Do_Negate();
            Mod_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Race_Negate_Option()) {
            Bool_t value = Race_Do_Negate();
            Race_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Base_Negate_Option()) {
            Bool_t value = Base_Do_Negate();
            Base_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Template_Negate_Option()) {
            Bool_t value = Template_Do_Negate();
            Template_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Faction_Negate_Option()) {
            Bool_t value = Faction_Do_Negate();
            Faction_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Keyword_Negate_Option()) {
            Bool_t value = Keyword_Do_Negate();
            Keyword_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Relation_Negate_Option()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Vitality_Negate_Option()) {
            Bool_t value = Vitality_Do_Negate();
            Vitality_Do_Negate() = !value;
            mcm->Toggle_Option_Value(option, !value);

        } else {
            if (Filter()->Toggle_Type() == Toggle_Type_e::EITHER) {
                if (option == Male_Option()) {
                    mcm->Toggle_Either(Male_Female_Argument(), option, option + 1, Binary_e::A);
                } else if (option == Female_Option()) {
                    mcm->Toggle_Either(Male_Female_Argument(), option - 1, option, Binary_e::B);

                } else if (option == Unique_Option()) {
                    mcm->Toggle_Either(Unique_Generic_Argument(), option, option + 1, Binary_e::A);
                } else if (option == Generic_Option()) {
                    mcm->Toggle_Either(Unique_Generic_Argument(), option - 1, option, Binary_e::B);

                }
            } else if (Filter()->Toggle_Type() == Toggle_Type_e::ANY) {
                if (option == Male_Option()) {
                    mcm->Toggle_Any(Male_Female_Argument(), option, option + 1, Binary_e::A);
                } else if (option == Female_Option()) {
                    mcm->Toggle_Any(Male_Female_Argument(), option - 1, option, Binary_e::B);

                } else if (option == Unique_Option()) {
                    mcm->Toggle_Any(Unique_Generic_Argument(), option, option + 1, Binary_e::A);
                } else if (option == Generic_Option()) {
                    mcm->Toggle_Any(Unique_Generic_Argument(), option - 1, option, Binary_e::B);

                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Mods());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Race_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Races());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Base_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Bases());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Template_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Templates());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Faction_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Factions());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Keyword_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Keywords());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Relation_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Vitality_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Vitalities());
            mcm->Menu_Dialog_Default(0);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Mods();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Mod_Argument() = value;
                mcm->Input_Option_Value(Mod_Search_Option(), value, true);
            }

        } else if (option == Race_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Races();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Race_Argument() = value;
                mcm->Input_Option_Value(Race_Search_Option(), value, true);
            }

        } else if (option == Base_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Bases();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Base_Argument() = value;
                mcm->Input_Option_Value(Base_Search_Option(), value, true);
            }

        } else if (option == Template_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Templates();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Template_Argument() = value;
                mcm->Input_Option_Value(Template_Search_Option(), value, true);
            }

        } else if (option == Faction_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Factions();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Faction_Argument() = value;
                mcm->Input_Option_Value(Faction_Search_Option(), value, true);
            }

        } else if (option == Keyword_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Keywords();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Keyword_Argument() = value;
                mcm->Input_Option_Value(Keyword_Search_Option(), value, true);
            }

        } else if (option == Relation_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::ANY;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Relations();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Relation_Argument() = mcm->From_Relation_Key(value);
                mcm->Menu_Option_Value(option, value, true);
            }

        } else if (option == Vitality_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::ANY;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Vitalities();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Vitality_Argument() = mcm->From_Vitality_Key(value);
                mcm->Menu_Option_Value(option, value, true);
            }

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == Mod_Search_Option()) {
            Mod_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Race_Search_Option()) {
            Race_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Base_Search_Option()) {
            Base_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Template_Search_Option()) {
            Template_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Faction_Search_Option()) {
            Faction_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Keyword_Search_Option()) {
            Keyword_Argument() = value;
            mcm->Input_Option_Value(option, value, true);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Filter()->Try_On_Option_Highlight(option, lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    Item_Sections_t Bases_Options_t<B, I>::item_sections;

    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::back_option                  = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::reset_option                 = -1;

    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_smart_select_option       = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_smart_sections_option     = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_uncombative_spawns_option = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_persistent_spawns_option  = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_static_spawns_option      = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::do_verify_spawns_option      = -1;

    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::bases_section_option         = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::commands_section_option      = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::factions_section_option      = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::keywords_section_option      = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::mods_section_option          = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::races_section_option         = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::templates_section_option     = -1;

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Reset_Option_Ints()
    {
        back_option                     = -1;
        reset_option                    = -1;

        do_smart_select_option          = -1;
        do_smart_sections_option        = -1;
        do_uncombative_spawns_option    = -1;
        do_persistent_spawns_option     = -1;
        do_static_spawns_option         = -1;
        do_verify_spawns_option         = -1;

        bases_section_option            = -1;
        commands_section_option         = -1;
        factions_section_option         = -1;
        keywords_section_option         = -1;
        mods_section_option             = -1;
        races_section_option            = -1;
        templates_section_option        = -1;
    }

    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::disable_section_menu_option      = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::move_section_higher_menu_option  = -1;
    template <typename B, typename I>
    Int_t   Bases_Options_t<B, I>::move_section_lower_menu_option   = -1;

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Reset_Menu_Option_Ints()
    {
        disable_section_menu_option     = -1;
        move_section_higher_menu_option = -1;
        move_section_lower_menu_option  = -1;
    }

    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Smart_Select()        { DEFINE_VAR(Bool_t, "p_options_do_smart_select"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Smart_Sections()      { DEFINE_VAR(Bool_t, "p_options_do_smart_sections"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Uncombative_Spawns()  { DEFINE_VAR(Bool_t, "p_options_do_uncombative_spawns"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Persistent_Spawns()   { DEFINE_VAR(Bool_t, "p_options_do_persistent_spawns"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Static_Spawns()       { DEFINE_VAR(Bool_t, "p_options_do_static_spawns"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&              Bases_Options_t<B, I>::Do_Verify_Spawns()       { DEFINE_VAR(Bool_t, "p_options_do_verify_spawns"); }
    template <typename B, typename I>
    inline V::Variable_tt<Vector_t<String_t>>&  Bases_Options_t<B, I>::Item_Sections()          { DEFINE_VAR(Vector_t<String_t>, "p_options_item_sections"); }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Reset()
    {
        Do_Smart_Select() = true;
        Do_Smart_Sections() = true;
        Do_Uncombative_Spawns() = true;
        Do_Persistent_Spawns() = true;
        Do_Static_Spawns() = true;
        Do_Verify_Spawns() = true;

        item_sections.Reset(Options()->Default_Item_Sections());
    }

    template <typename B, typename I>
    inline Vector_t<Item_Section_t> Bases_Options_t<B, I>::Default_Item_Sections()
    {
        Vector_t<Item_Section_t> sections;
        sections.reserve(6);

        sections.push_back(Bases_Item_Section_e::BASES);
        sections.push_back(Bases_Item_Section_e::RACES);
        sections.push_back(Bases_Item_Section_e::TEMPLATES);

        sections.push_back(Bases_Item_Section_e::FACTIONS);
        sections.push_back(Bases_Item_Section_e::KEYWORDS);
        sections.push_back(Bases_Item_Section_e::MODS);

        return sections;
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Build_Header_Options()
    {
        some<Main_t*> mcm = Main_t::Self();

        if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
            mcm->Add_Empty_Option();
        }

        back_option = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        reset_option = mcm->Add_Text_Option(Main_t::CENTER_RESET, Main_t::_NONE_);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Build_General_Options()
    {
        some<Main_t*> mcm = Main_t::Self();

        if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
            mcm->Add_Empty_Option();
        }

        mcm->Add_Header_Option(Main_t::GENERAL);
        mcm->Add_Header_Option(Main_t::_NONE_);

        do_smart_select_option = mcm->Add_Toggle_Option(Main_t::SMART_SELECT, Do_Smart_Select());
        do_smart_sections_option = mcm->Add_Toggle_Option(Main_t::SMART_SECTIONS, Do_Smart_Sections());
        do_uncombative_spawns_option = mcm->Add_Toggle_Option(Main_t::UNCOMBATIVE_SPAWNS, Do_Uncombative_Spawns());
        do_persistent_spawns_option = mcm->Add_Toggle_Option(Main_t::PERSISTENT_SPAWNS, Do_Persistent_Spawns());
        do_static_spawns_option = mcm->Add_Toggle_Option(Main_t::STATIC_SPAWNS, Do_Static_Spawns());
        do_verify_spawns_option = mcm->Add_Toggle_Option(Main_t::VERIFY_SPAWNS, Do_Verify_Spawns());
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Build_Section_Options()
    {
        some<Main_t*> mcm = Main_t::Self();

        if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
            mcm->Add_Empty_Option();
        }

        mcm->Add_Header_Option(Main_t::ITEM_SECTIONS);
        mcm->Add_Header_Option("");

        Options()->Build_Section_Options_Impl();

        if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
            mcm->Add_Empty_Option();
        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Build_Section_Options_Impl()
    {
        using Section_e = Bases_Item_Section_e;

        Vector_t<Item_Section_t> allowed_sections = Options()->Default_Item_Sections();
        Vector_t<Item_Section_t> current_sections = item_sections.Current();

        some<Main_t*> mcm = Main_t::Self();

        auto Enabled = [&mcm](const char* label)->Int_t
        {
            return mcm->Add_Menu_Option(label, Main_t::_DOTS_);
        };
        for (size_t idx = 0, end = current_sections.size(); idx < end; idx += 1) {
            Section_e section_e = current_sections[idx];
            if (allowed_sections.Has(section_e)) {
                     if (section_e == Section_e::BASES)     bases_section_option        = Enabled(Main_t::BASES);
                else if (section_e == Section_e::COMMANDS)  commands_section_option     = Enabled(Main_t::COMMANDS);
                else if (section_e == Section_e::FACTIONS)  factions_section_option     = Enabled(Main_t::FACTIONS);
                else if (section_e == Section_e::KEYWORDS)  keywords_section_option     = Enabled(Main_t::KEYWORDS);
                else if (section_e == Section_e::MODS)      mods_section_option         = Enabled(Main_t::MODS);
                else if (section_e == Section_e::RACES)     races_section_option        = Enabled(Main_t::RACES);
                else if (section_e == Section_e::TEMPLATES) templates_section_option    = Enabled(Main_t::TEMPLATES);
            }
        }

        auto Disabled = [&mcm](const char* label)->Int_t
        {
            return mcm->Add_Toggle_Option(mcm->Add_Font(label, "", "#80", ""), false);
        };
        for (size_t idx = 0, end = allowed_sections.size(); idx < end; idx += 1) {
            Section_e section_e = allowed_sections[idx];
            if (!current_sections.Has(section_e)) {
                     if (section_e == Section_e::BASES)     bases_section_option        = Disabled(Main_t::BASES);
                else if (section_e == Section_e::COMMANDS)  commands_section_option     = Disabled(Main_t::COMMANDS);
                else if (section_e == Section_e::FACTIONS)  factions_section_option     = Disabled(Main_t::FACTIONS);
                else if (section_e == Section_e::KEYWORDS)  keywords_section_option     = Disabled(Main_t::KEYWORDS);
                else if (section_e == Section_e::MODS)      mods_section_option         = Disabled(Main_t::MODS);
                else if (section_e == Section_e::RACES)     races_section_option        = Disabled(Main_t::RACES);
                else if (section_e == Section_e::TEMPLATES) templates_section_option    = Disabled(Main_t::TEMPLATES);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Select_Section_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback)
    {
        item_sections.Enable(item_section);

        some<Main_t*> mcm = Main_t::Self();
        mcm->Disable_Option(option);
        mcm->Reset_Page();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Open_Section_Menu_Option(Item_Section_t item_section, Int_t option, Latent_Callback_i* lcallback)
    {
        Vector_t<String_t> options;
        options.reserve(3);

        disable_section_menu_option = options.size();
        options.push_back(Main_t::DISABLE_SECTION);

        if (item_sections.May_Move_Higher(item_section)) {
            move_section_higher_menu_option = options.size();
            options.push_back(Main_t::MOVE_SECTION_HIGHER);
        }

        if (item_sections.May_Move_Lower(item_section)) {
            move_section_lower_menu_option = options.size();
            options.push_back(Main_t::MOVE_SECTION_LOWER);
        }

        some<Main_t*> mcm = Main_t::Self();
        mcm->Flicker_Option(option);
        mcm->Menu_Dialog_Values(options);
        mcm->Menu_Dialog_Default(-1);
        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Accept_Section_Menu_Option(Item_Section_t item_section, Int_t idx, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (idx > -1) {
            if (idx == disable_section_menu_option) {
                item_sections.Disable(item_section);
            } else if (idx == move_section_higher_menu_option) {
                item_sections.Move_Higher(item_section);
            } else if (idx == move_section_lower_menu_option) {
                item_sections.Move_Lower(item_section);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Highlight_Section_Option(Item_Section_t item_section, Latent_Callback_i* lcallback)
    {
        if (item_sections.Is_Enabled(item_section)) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_OPTIONS_ENABLED_SECTION, lcallback);
        } else {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_OPTIONS_DISABLED_SECTION, lcallback);
        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Init()
    {
        item_sections.Reset(Options()->Default_Item_Sections());
        return true;
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Load()
    {
        if (!item_sections.Deserialize<Bases_Item_Section_e>(Item_Sections())) {
            item_sections.Reset(Options()->Default_Item_Sections());
        }
        return true;
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Save()
    {
        item_sections.Serialize<Bases_Item_Section_e>(Item_Sections());
        return true;
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == back_option) {
            some<Main_t*> mcm = Main_t::Self();
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Options()->Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == reset_option) {
            some<Main_t*> mcm = Main_t::Self();
            mcm->Disable_Option(option);
            Options()->Reset();
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == do_smart_select_option) {
            Main_t::Self()->Toggle_And_Update(Do_Smart_Select(), option, lcallback);
            return true;

        } else if (option == do_smart_sections_option) {
            Main_t::Self()->Toggle_And_Update(Do_Smart_Sections(), option, lcallback);
            return true;

        } else if (option == do_uncombative_spawns_option) {
            Main_t::Self()->Toggle_And_Update(Do_Uncombative_Spawns(), option, lcallback);
            return true;

        } else if (option == do_persistent_spawns_option) {
            Main_t::Self()->Toggle_And_Update(Do_Persistent_Spawns(), option, lcallback);
            return true;

        } else if (option == do_static_spawns_option) {
            Main_t::Self()->Toggle_And_Update(Do_Static_Spawns(), option, lcallback);
            return true;

        } else if (option == do_verify_spawns_option) {
            Main_t::Self()->Toggle_And_Update(Do_Verify_Spawns(), option, lcallback);
            return true;

        } else if (option == bases_section_option) {
            Select_Section_Option(Bases_Item_Section_e::BASES, option, lcallback);
            return true;

        } else if (option == commands_section_option) {
            Select_Section_Option(Bases_Item_Section_e::COMMANDS, option, lcallback);
            return true;

        } else if (option == factions_section_option) {
            Select_Section_Option(Bases_Item_Section_e::FACTIONS, option, lcallback);
            return true;

        } else if (option == keywords_section_option) {
            Select_Section_Option(Bases_Item_Section_e::KEYWORDS, option, lcallback);
            return true;

        } else if (option == mods_section_option) {
            Select_Section_Option(Bases_Item_Section_e::MODS, option, lcallback);
            return true;

        } else if (option == races_section_option) {
            Select_Section_Option(Bases_Item_Section_e::RACES, option, lcallback);
            return true;

        } else if (option == templates_section_option) {
            Select_Section_Option(Bases_Item_Section_e::TEMPLATES, option, lcallback);
            return true;

        } else {
            return false;

        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Reset_Menu_Option_Ints();

        if (option == bases_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::BASES, option, lcallback);
            return true;

        } else if (option == commands_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::COMMANDS, option, lcallback);
            return true;

        } else if (option == factions_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::FACTIONS, option, lcallback);
            return true;

        } else if (option == keywords_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::KEYWORDS, option, lcallback);
            return true;

        } else if (option == mods_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::MODS, option, lcallback);
            return true;

        } else if (option == races_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::RACES, option, lcallback);
            return true;

        } else if (option == templates_section_option) {
            Open_Section_Menu_Option(Bases_Item_Section_e::TEMPLATES, option, lcallback);
            return true;

        } else {
            return false;

        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        if (option == bases_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::BASES, idx, lcallback);
            return true;

        } else if (option == commands_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::COMMANDS, idx, lcallback);
            return true;

        } else if (option == factions_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::FACTIONS, idx, lcallback);
            return true;

        } else if (option == keywords_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::KEYWORDS, idx, lcallback);
            return true;

        } else if (option == mods_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::MODS, idx, lcallback);
            return true;

        } else if (option == races_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::RACES, idx, lcallback);
            return true;

        } else if (option == templates_section_option) {
            Accept_Section_Menu_Option(Bases_Item_Section_e::TEMPLATES, idx, lcallback);
            return true;

        } else {
            return false;

        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Options_t<B, I>::Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == back_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_OPTIONS_BACK, lcallback);
            return true;

        } else if (option == reset_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_RESET_OPTIONS, lcallback);
            return true;


        } else if (option == do_smart_select_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_SMART_SELECT, lcallback);
            return true;

        } else if (option == do_smart_sections_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_SMART_SECTIONS, lcallback);
            return true;

        } else if (option == do_uncombative_spawns_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_UNCOMBATIVE_SPAWNS, lcallback);
            return true;

        } else if (option == do_persistent_spawns_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_PERSISTENT_SPAWNS, lcallback);
            return true;

        } else if (option == do_static_spawns_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_STATIC_SPAWNS, lcallback);
            return true;

        } else if (option == do_verify_spawns_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_VERIFY_SPAWNS, lcallback);
            return true;


        } else if (option == bases_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::BASES, lcallback);
            return true;

        } else if (option == commands_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::COMMANDS, lcallback);
            return true;

        } else if (option == factions_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::FACTIONS, lcallback);
            return true;

        } else if (option == keywords_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::KEYWORDS, lcallback);
            return true;

        } else if (option == mods_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::MODS, lcallback);
            return true;

        } else if (option == races_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::RACES, lcallback);
            return true;

        } else if (option == templates_section_option) {
            Highlight_Section_Option(Bases_Item_Section_e::TEMPLATES, lcallback);
            return true;


        } else {
            return false;

        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Init()
    {
        Options()->Try_On_Init();
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Load()
    {
        Options()->Try_On_Load();
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Save()
    {
        Options()->Try_On_Save();
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Config_Open()
    {
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Config_Close()
    {
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        if (!Options()->Try_On_Option_Select(option, lcallback)) {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        if (!Options()->Try_On_Option_Menu_Open(option, lcallback)) {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        if (!Options()->Try_On_Option_Menu_Accept(option, idx, lcallback)) {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
        }
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        if (!Options()->Try_On_Option_Highlight(option, lcallback)) {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
        }
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::back_option           = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::previous_option       = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::next_option           = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::view_nested_option    = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::spawn_option          = -1;

    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_bases_option     = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_commands_option  = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_factions_option  = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_keywords_option  = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_mods_option      = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_races_option     = -1;
    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::show_templates_option = -1;

    template <typename B, typename I>
    Int_t Bases_Item_t<B, I>::race_name_option      = -1;

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Reset_Option_Ints()
    {
        back_option             = -1;
        previous_option         = -1;
        next_option             = -1;
        view_nested_option      = -1;
        spawn_option            = -1;

        show_bases_option       = -1;
        show_commands_option    = -1;
        show_factions_option    = -1;
        show_keywords_option    = -1;
        show_mods_option        = -1;
        show_races_option       = -1;
        show_templates_option   = -1;

        race_name_option        = -1;
    }

    template <typename B, typename I>
    inline V::Variable_tt<String_t>&    Bases_Item_t<B, I>::Nested_View_Variable()  { DEFINE_VAR(String_t, "p_item_nested_view"); }
    template <typename B, typename I>
    inline V::Variable_tt<Int_t>&       Bases_Item_t<B, I>::Nested_Index()          { DEFINE_VAR(Int_t, "p_item_nested_index"); }
    template <typename B, typename I>
    inline V::Variable_tt<Form_ID_t>&   Bases_Item_t<B, I>::Nested_Form()           { DEFINE_VAR(Form_ID_t, "p_item_nested_form"); }

    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Bases()         { DEFINE_VAR(Bool_t, "p_item_do_show_bases"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Commands()      { DEFINE_VAR(Bool_t, "p_item_do_show_commands"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Factions()      { DEFINE_VAR(Bool_t, "p_item_do_show_factions"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Keywords()      { DEFINE_VAR(Bool_t, "p_item_do_show_keywords"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Mods()          { DEFINE_VAR(Bool_t, "p_item_do_show_mods"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Races()         { DEFINE_VAR(Bool_t, "p_item_do_show_races"); }
    template <typename B, typename I>
    inline V::Variable_tt<Bool_t>&      Bases_Item_t<B, I>::Do_Show_Templates()     { DEFINE_VAR(Bool_t, "p_item_do_show_templates"); }

    template <typename B, typename I>
    inline Bases_Item_View_e Bases_Item_t<B, I>::Nested_View()
    {
        String_t nested_view = Nested_View_Variable();
        if (CString_t::Is_Same(nested_view, ITEM_VIEW, true)) {
            return Bases_Item_View_e::ITEM;
        } else if (CString_t::Is_Same(nested_view, BASES_VIEW, true)) {
            return Bases_Item_View_e::BASES;
        } else if (CString_t::Is_Same(nested_view, BASES_ITEM_VIEW, true)) {
            return Bases_Item_View_e::BASES_ITEM;
        } else {
            Nested_View_Variable() = ITEM_VIEW;
            return Bases_Item_View_e::ITEM;
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Nested_View(Bases_Item_View_e value)
    {
        if (value == Bases_Item_View_e::ITEM) {
            Nested_View_Variable() = ITEM_VIEW;
        } else if (value == Bases_Item_View_e::BASES) {
            Nested_View_Variable() = BASES_VIEW;
        } else if (value == Bases_Item_View_e::BASES_ITEM) {
            Nested_View_Variable() = BASES_ITEM_VIEW;
        } else {
            Nested_View_Variable() = ITEM_VIEW;
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Sections(Vector_t<Buildable_i*> buildables)
    {
        auto Buildable = [](Vector_t<Buildable_i*>& buildables, Item_Section_t item_section)->Buildable_i*
        {
            for (size_t idx = 0, end = buildables.size(); idx < end; idx += 1) {
                Buildable_i* buildable = buildables[idx];
                if (buildable && buildable->Type() == item_section) {
                    return buildable;
                }
            }
            return nullptr;
        };

        if (Options()->Do_Smart_Sections()) {
            Vector_t<Buildable_i*> shown;
            Vector_t<Buildable_i*> unshown;
            Vector_t<Buildable_i*> disabled;

            size_t buildable_count = buildables.size();
            shown.reserve(buildable_count);
            unshown.reserve(buildable_count);
            disabled.reserve(buildable_count);

            for (size_t idx = 0, end = buildables.size(); idx < end; idx += 1) {
                Buildable_i* buildable = buildables[idx];
                if (buildable) {
                    if (buildable->Can_Enable()) {
                        if (buildable->Can_Show()) {
                            shown.push_back(buildable);
                        } else {
                            unshown.push_back(buildable);
                        }
                    } else {
                        disabled.push_back(buildable);
                    }
                }
            }

            Vector_t<Item_Section_t> current_sections = Options()->item_sections.Current();
            for (size_t idx = 0, end = current_sections.size(); idx < end; idx += 1) {
                Item_Section_t item_section = current_sections[idx];
                Buildable_i* buildable = Buildable(shown, item_section);
                if (buildable) {
                    buildable->Build();
                }
            }
            for (size_t idx = 0, end = current_sections.size(); idx < end; idx += 1) {
                Item_Section_t item_section = current_sections[idx];
                Buildable_i* buildable = Buildable(unshown, item_section);
                if (buildable) {
                    buildable->Build();
                }
            }
            for (size_t idx = 0, end = current_sections.size(); idx < end; idx += 1) {
                Item_Section_t item_section = current_sections[idx];
                Buildable_i* buildable = Buildable(disabled, item_section);
                if (buildable) {
                    buildable->Build();
                }
            }
        } else {
            Vector_t<Item_Section_t> current_sections = Options()->item_sections.Current();
            for (size_t idx = 0, end = current_sections.size(); idx < end; idx += 1) {
                Item_Section_t item_section = current_sections[idx];
                Buildable_i* buildable = Buildable(buildables, item_section);
                if (buildable) {
                    buildable->Build();
                }
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Base(Actor_Base_t* base, const char* type_name)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (base && base->Is_Valid()) {
            if (Do_Show_Bases()) {
                if (mcm->Can_Add_Options(2 + 6)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, type_name);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + base->Name(), Main_t::_NONE_); // 1
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + base->Form_ID_String(), Main_t::_NONE_); // 2

                    if (base->Is_Male()) { // 3
                        mcm->Add_Text_Option(Main_t::IS_MALE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_FEMALE, Main_t::_NONE_);
                    }
                    if (base->Is_Unique()) { // 4
                        mcm->Add_Text_Option(Main_t::IS_UNIQUE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_GENERIC, Main_t::_NONE_);
                    }
                    some<Vitality_e> vitality = base->Vitality(); // 5
                    mcm->Add_Text_Option(mcm->To_Is_Vitality_Key(vitality())(), Main_t::_NONE_);
                    some<Relation_e> relation = base->Relation(Consts_t::Skyrim_Player_Actor_Base()); // 6
                    mcm->Add_Text_Option(mcm->To_Is_Relation_Key(relation())(), Main_t::_NONE_);

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, type_name);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, type_name, Flag_e::DISABLE);
                show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Bases());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Factions(Vector_t<Faction_And_Rank_t> factions)
    {
        some<Main_t*> mcm = Main_t::Self();

        size_t count = factions.size();
        if (count > 0) {
            if (Do_Show_Factions()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::FACTIONS);
                    show_factions_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    factions.Sort(Faction_And_Rank_t::Compare_Editor_Or_Form_IDs);
                    for (size_t idx = 0, end = count; idx < end; idx += 1) {
                        Faction_And_Rank_t& faction_and_rank = factions[idx];
                        maybe<Faction_t*> faction = faction_and_rank.faction;
                        skylib::Raw_Faction_Rank_t rank = faction_and_rank.rank;
                        if (faction && faction->Is_Valid()) {
                            std::string label =
                                std::string(Main_t::_SPACE_) +
                                faction->Editor_Or_Form_ID() +
                                Main_t::_COLON_SPACE_ +
                                std::to_string(rank);
                            mcm->Add_Text_Option(label, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::FACTIONS);
                    show_factions_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::FACTIONS, Flag_e::DISABLE);
                show_factions_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Factions());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Header(Int_t& top_right_option, const char* top_right_name, size_t listed_item_count)
    {
        some<Main_t*> mcm = Main_t::Self();

        back_option = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        top_right_option = mcm->Add_Text_Option(top_right_name, Main_t::_NONE_);
        if (listed_item_count > 1) {
            previous_option = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_);
            next_option = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_);
        } else {
            previous_option = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
            next_option = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
        }
        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Keywords(Vector_t<Keyword_t*> keywords)
    {
        some<Main_t*> mcm = Main_t::Self();

        size_t count = keywords.size();
        if (count > 0) {
            if (Do_Show_Keywords()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::KEYWORDS);
                    show_keywords_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    keywords.Sort(Keyword_t::Compare_Any_Names);
                    for (size_t idx = 0, end = count; idx < end; idx += 1) {
                        Keyword_t* keyword = keywords[idx];
                        if (keyword && keyword->Is_Valid()) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + keyword->Any_Name(), Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::KEYWORDS);
                    show_keywords_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::KEYWORDS, Flag_e::DISABLE);
                show_keywords_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Keywords());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Leveled_Base(Leveled_Actor_Base_t* leveled_base)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (leveled_base && leveled_base->Is_Valid()) {
            if (Do_Show_Bases()) {
                if (mcm->Can_Add_Options(2 + 4)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::LEVELED_BASE);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + leveled_base->Leveled_Name(), Main_t::_NONE_); // 1
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + leveled_base->Form_ID_String(), Main_t::_NONE_); // 2

                    view_nested_option = mcm->Add_Text_Option(Main_t::VIEW_INTERNAL_BASES, Main_t::_DOTS_); // 3
                    mcm->Add_Empty_Option(); // 4

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::LEVELED_BASE);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::LEVELED_BASE, Flag_e::DISABLE);
                show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Bases());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Mods(Vector_t<Mod_t*> mods)
    {
        some<Main_t*> mcm = Main_t::Self();

        size_t count = mods.size();
        if (count > 0) {
            if (Do_Show_Mods()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::MODS);
                    show_mods_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (size_t idx = 0, end = count; idx < end; idx += 1) {
                        Mod_t* mod = mods[idx];
                        if (mod) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + mod->Name(), Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::MODS);
                    show_mods_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::MODS, Flag_e::DISABLE);
                show_mods_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Mods());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Race(Race_t* race)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (race && race->Is_Valid()) {
            if (Do_Show_Races()) {
                if (mcm->Can_Add_Options(2 + 2)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::RACE);
                    show_races_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    race_name_option = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Get_Editor_ID(), Main_t::_NONE_); // 1
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Form_ID_String(), Main_t::_NONE_); // 2

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::RACE);
                    show_races_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::RACE, Flag_e::DISABLE);
                show_races_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Races());
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Templates(Vector_t<Actor_Base_t*> templates)
    {
        some<Main_t*> mcm = Main_t::Self();

        size_t count = templates.size();
        if (count > 0) {
            if (Do_Show_Templates()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::TEMPLATES);
                    show_templates_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (size_t idx = 0, end = count; idx < end; idx += 1) {
                        Actor_Base_t* base_template = templates[idx];
                        const char* name = base_template->Name();
                        const char* form_id = base_template->Form_ID_String();
                        mcm->Add_Text_Option(
                            std::string(Main_t::_SPACE_) + mcm->Pretty_ID(name, Main_t::_NONE_, form_id),
                            Main_t::_NONE_
                        );
                    }

                    if (skylib::Is_Odd(mcm->Current_Cursor_Position().Int())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::TEMPLATES);
                    show_templates_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::TEMPLATES, Flag_e::DISABLE);
                show_templates_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Templates());
            }
        }
    }

    template <typename B, typename I>
    template <typename Spawnable_t, enable_if_spawnable<Spawnable_t>>
    inline void Bases_Item_t<B, I>::Select_Spawn_Option(Spawnable_t item, Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (Options()->Do_Verify_Spawns()) {
            class Verify_Callback_t : public Callback_i<Bool_t>
            {
            public:
                Bases_Item_t<B, I>* self;
                Spawnable_t item;
                Latent_Callback_i* lcallback;
                Verify_Callback_t(Bases_Item_t<B, I>* self,
                                  Spawnable_t item,
                                  Latent_Callback_i* lcallback) :
                    self(self),
                    item(item),
                    lcallback(lcallback)
                {
                }
                void operator()(Bool_t accept)
                {
                    if (accept) {
                        if (item && item->Is_Valid()) {
                            auto options = self->Options();
                            Spawned_Actors_t::Self().Add(
                                item,
                                options->Do_Persistent_Spawns(),
                                options->Do_Uncombative_Spawns(),
                                options->Do_Static_Spawns()
                            );
                        }
                    }
                    Main_t::Self()->Destroy_Latent_Callback(lcallback);
                }
            };
            mcm->Flicker_Option(option);
            mcm->Show_Message(
                Main_t::CONFIRM_SPAWN,
                true,
                Main_t::YES,
                Main_t::NO,
                new Verify_Callback_t(this, item, lcallback)
            );
        } else {
            mcm->Flicker_Option(option);
            if (item && item->Is_Valid()) {
                auto options = Options();
                Spawned_Actors_t::Self().Add(
                    item,
                    options->Do_Persistent_Spawns(),
                    options->Do_Uncombative_Spawns(),
                    options->Do_Static_Spawns()
                );
            }
            mcm->Destroy_Latent_Callback(lcallback);
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Select_Spawn_Option(Cached_Leveled_t* item, Int_t option, Latent_Callback_i* lcallback)
    {
        if (item) {
            Select_Spawn_Option(item->leveled(), option, lcallback);
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Select_Spawn_Option(Actor_t* item, Int_t option, Latent_Callback_i* lcallback)
    {
        if (item && item->Is_Valid()) {
            Select_Spawn_Option(item->Actor_Base()(), option, lcallback);
        }
    }

    template <typename B, typename I>
    template <typename Raceable_t, enable_if_raceable<Raceable_t>>
    inline void Bases_Item_t<B, I>::Highlight_Race_Option(Raceable_t* raceable, Latent_Callback_i* lcallback)
    {
        if (raceable && raceable->Is_Valid()) {
            maybe<Race_t*> race = raceable->Race();
            if (race && race->Is_Valid()) {
                const char* name = race->Name();
                const char* editor_id = race->Get_Editor_ID();
                const char* form_id = race->Form_ID_String();
                some<Main_t*> mcm = Main_t::Self();
                mcm->Highlight(mcm->Pretty_ID(name, editor_id, form_id), lcallback);
            }
        }
    }

    template <typename B, typename I>
    template <typename Unraceable_t, enable_if_not_raceable<Unraceable_t>>
    inline void Bases_Item_t<B, I>::Highlight_Race_Option(Unraceable_t* unraceable, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline Bool_t Bases_Item_t<B, I>::Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == back_option) {
            mcm->Disable_Option(option);

            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);

            Item_t current_item = Item()->Current_Item();
            if (current_item) {
                maybe<size_t> maybe_idx = List()->Items().Index_Of(current_item);
                if (maybe_idx.Has_Value()) {
                    List()->Page_Index() = maybe_idx.Value() / Bases_List_t<B, I>::ITEMS_PER_PAGE;
                }
            }

            mcm->Reset_Page();

            mcm->Destroy_Latent_Callback(lcallback);

            return true;

        } else if (option == previous_option) {
            mcm->Disable_Option(option);
            if (!Item()->Current_Item(Item()->Previous_Item())) {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == next_option) {
            mcm->Disable_Option(option);
            if (!Item()->Current_Item(Item()->Next_Item())) {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == spawn_option) {
            Select_Spawn_Option(Item()->Current_Item(), option, lcallback);
            return true;

        } else if (option == show_bases_option || option == show_bases_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Bases(), option, lcallback);
            return true;

        } else if (option == show_commands_option || option == show_commands_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Commands(), option, lcallback);
            return true;

        } else if (option == show_factions_option || option == show_factions_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Factions(), option, lcallback);
            return true;

        } else if (option == show_keywords_option || option == show_keywords_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Keywords(), option, lcallback);
            return true;

        } else if (option == show_mods_option || option == show_mods_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Mods(), option, lcallback);
            return true;

        } else if (option == show_races_option || option == show_races_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Races(), option, lcallback);
            return true;

        } else if (option == show_templates_option || option == show_templates_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Templates(), option, lcallback);
            return true;

        } else {
            return false;
        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Item_t<B, I>::Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == show_bases_option || option == show_bases_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_commands_option || option == show_commands_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_factions_option || option == show_factions_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_keywords_option || option == show_keywords_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_mods_option || option == show_mods_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_races_option || option == show_races_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;
        } else if (option == show_templates_option || option == show_templates_option - 1) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_ITEM_TOGGLE_SECTION, lcallback);
            return true;

        } else if (option == spawn_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_SPAWN, lcallback);
            return true;

        } else if (option == race_name_option) {
            Highlight_Race_Option(Item()->Current_Item(), lcallback);
            return true;

        } else {
            Main_t::Self()->Destroy_Latent_Callback(lcallback);
            return true;
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Init()
    {
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Load()
    {
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Save()
    {
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Config_Open()
    {
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Config_Close()
    {
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Item()->Try_On_Option_Highlight(option, lcallback);
    }

}}
