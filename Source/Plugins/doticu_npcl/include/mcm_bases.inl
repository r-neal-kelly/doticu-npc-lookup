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

#define DEFINE_BOOL     DEFINE_BOOL_VARIABLE
#define DEFINE_INT      DEFINE_INT_VARIABLE
#define DEFINE_STRING   DEFINE_STRING_VARIABLE

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline V::String_Variable_t* Bases_t<B, I>::Current_View_Variable() { DEFINE_STRING("p_current_view"); }

    template <typename B, typename I>
    inline Bases_View_e Bases_t<B, I>::Current_View()
    {
        String_t current_view = Current_View_Variable()->Value();
        if (CString_t::Is_Same(current_view, LIST_VIEW, true)) {
            return Bases_View_e::LIST;
        } else if (CString_t::Is_Same(current_view, FILTER_VIEW, true)) {
            return Bases_View_e::FILTER;
        } else if (CString_t::Is_Same(current_view, OPTIONS_VIEW, true)) {
            return Bases_View_e::OPTIONS;
        } else if (CString_t::Is_Same(current_view, ITEM_VIEW, true)) {
            return Bases_View_e::ITEM;
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
            return Bases_View_e::LIST;
        }
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::Current_View(Bases_View_e value)
    {
        if (value == Bases_View_e::LIST) {
            Current_View_Variable()->Value(LIST_VIEW);
        } else if (value == Bases_View_e::FILTER) {
            Current_View_Variable()->Value(FILTER_VIEW);
        } else if (value == Bases_View_e::OPTIONS) {
            Current_View_Variable()->Value(OPTIONS_VIEW);
        } else if (value == Bases_View_e::ITEM) {
            Current_View_Variable()->Value(ITEM_VIEW);
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
        }
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Init()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Load()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Save()
    {

    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Config_Open()
    {
        List()->do_update_items = true;
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Config_Close()
    {
        List()->Clear();
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
    inline V::Int_Variable_t*   Bases_List_t<B, I>::Page_Index_Variable()   { DEFINE_INT("p_list_page_index"); }

    template <typename B, typename I>
    inline Int_t    Bases_List_t<B, I>::Page_Index()            { return Page_Index_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_List_t<B, I>::Page_Index(Int_t value) { Page_Index_Variable()->Value(value); }

    template <typename B, typename I>
    inline void Bases_List_t<B, I>::Clear()
    {
        do_update_items = true;
        read.clear();
        write.clear();
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
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Mod_Argument_Variable()               { DEFINE_STRING("p_filter_mod_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Mod_Do_Negate_Variable()              { DEFINE_BOOL("p_filter_mod_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Race_Argument_Variable()              { DEFINE_STRING("p_filter_race_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Race_Do_Negate_Variable()             { DEFINE_BOOL("p_filter_race_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Base_Argument_Variable()              { DEFINE_STRING("p_filter_base_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Base_Do_Negate_Variable()             { DEFINE_BOOL("p_filter_base_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Template_Argument_Variable()          { DEFINE_STRING("p_filter_template_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Template_Do_Negate_Variable()         { DEFINE_BOOL("p_filter_template_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Faction_Argument_Variable()           { DEFINE_STRING("p_filter_faction_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Faction_Do_Negate_Variable()          { DEFINE_BOOL("p_filter_faction_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Keyword_Argument_Variable()           { DEFINE_STRING("p_filter_keyword_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Keyword_Do_Negate_Variable()          { DEFINE_BOOL("p_filter_keyword_do_negate"); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Relation_Argument_Variable()          { DEFINE_STRING("p_filter_relation_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Relation_Do_Negate_Variable()         { DEFINE_BOOL("p_filter_relation_do_negate"); }

    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Vitality_Argument_Variable()          { DEFINE_INT("p_filter_vitality_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Vitality_Do_Negate_Variable()         { DEFINE_BOOL("p_filter_vitality_do_negate"); }

    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Male_Female_Argument_Variable()       { DEFINE_INT("p_filter_male_female_argument"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Unique_Generic_Argument_Variable()    { DEFINE_INT("p_filter_unique_generic_argument"); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Mod_Argument()                            { return Mod_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Mod_Argument(String_t value)              { Mod_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Mod_Do_Negate()                           { return Mod_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Mod_Do_Negate(Bool_t value)               { Mod_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Race_Argument()                           { return Race_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Race_Argument(String_t value)             { Race_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Race_Do_Negate()                          { return Race_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Race_Do_Negate(Bool_t value)              { Race_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Base_Argument()                           { return Base_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Base_Argument(String_t value)             { Base_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Base_Do_Negate()                          { return Base_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Base_Do_Negate(Bool_t value)              { Base_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Template_Argument()                       { return Template_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Template_Argument(String_t value)         { Template_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Template_Do_Negate()                      { return Template_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Template_Do_Negate(Bool_t value)          { Template_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Faction_Argument()                        { return Faction_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Faction_Argument(String_t value)          { Faction_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Faction_Do_Negate()                       { return Faction_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Faction_Do_Negate(Bool_t value)           { Faction_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Keyword_Argument()                        { return Keyword_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Keyword_Argument(String_t value)          { Keyword_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Keyword_Do_Negate()                       { return Keyword_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Keyword_Do_Negate(Bool_t value)           { Keyword_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t     Bases_Filter_t<B, I>::Relation_Argument()                       { return Relation_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Relation_Argument(String_t value)         { Relation_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Relation_Do_Negate()                      { return Relation_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Relation_Do_Negate(Bool_t value)          { Relation_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline Vitality_e   Bases_Filter_t<B, I>::Vitality_Argument()                       { return Vitality_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Vitality_Argument(Vitality_e value)       { Vitality_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t       Bases_Filter_t<B, I>::Vitality_Do_Negate()                      { return Vitality_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Vitality_Do_Negate(Bool_t value)          { Vitality_Do_Negate_Variable()->Value(value); }

    template <typename B, typename I>
    inline Binary_e     Bases_Filter_t<B, I>::Male_Female_Argument()                    { return Male_Female_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Male_Female_Argument(Binary_e value)      { Male_Female_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline Binary_e     Bases_Filter_t<B, I>::Unique_Generic_Argument()                 { return Unique_Generic_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Filter_t<B, I>::Unique_Generic_Argument(Binary_e value)   { Unique_Generic_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::Clear()
    {
        Mod_Argument("");
        Mod_Do_Negate(false);

        Race_Argument("");
        Race_Do_Negate(false);

        Base_Argument("");
        Base_Do_Negate(false);

        Template_Argument("");
        Template_Do_Negate(false);

        Faction_Argument("");
        Faction_Do_Negate(false);

        Keyword_Argument("");
        Keyword_Do_Negate(false);

        Relation_Argument("");
        Relation_Do_Negate(false);

        Vitality_Argument(Vitality_e::NONE);
        Vitality_Do_Negate(false);

        Male_Female_Argument(Binary_e::NONE);
        Unique_Generic_Argument(Binary_e::NONE);
    }

    template <typename B, typename I>
    template <typename Type_t>
    inline Filter_State_t<Type_t> Bases_Filter_t<B, I>::Execute(Vector_t<Type_t>* read, Vector_t<Type_t>* write)
    {
        Actor_Base_t* relatable_base = Consts_t::Skyrim_Player_Actor_Base();
        Relation_e relation_argument = Relation_e::From_String(Relation_Argument());

        Filter_State_t<Type_t> filter_state(read, write);

        Mod_Filter_t<Type_t>(filter_state, Mod_Argument(), Mod_Do_Negate());
        Race_Filter_t<Type_t>(filter_state, Race_Argument(), Race_Do_Negate());
        Base_Filter_t<Type_t>(filter_state, Base_Argument(), Base_Do_Negate());
        Template_Filter_t<Type_t>(filter_state, Template_Argument(), Template_Do_Negate());
        Faction_Filter_t<Type_t>(filter_state, Faction_Argument(), Faction_Do_Negate());
        Keyword_Filter_t<Type_t>(filter_state, Keyword_Argument(), Keyword_Do_Negate());
        Relation_Filter_t<Type_t>(filter_state, relatable_base, relation_argument, Relation_Do_Negate());
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
        return Selectable_Relations_t<B, I>(Consts_t::Skyrim_Player_Actor_Base()).Results();
    }

    template <typename B, typename I>
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Vitalities()
    {
        return Selectable_Vitalities_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::Build_Filters(const char* type_name)
    {
        Main_t* mcm = Main_t::Self();

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
        Relation_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Relation_Argument());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::VITALITY);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Vitality_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, mcm->To_Vitality_Key(Vitality_Argument())());
        Vitality_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::OTHER);
        mcm->Add_Header_Option(Main_t::_NONE_);
        if (Toggle_Type() == Toggle_Type_e::EITHER) {

            Male_Option() = mcm->Add_Toggle_Option(Main_t::IS_MALE, Male_Female_Argument() == Binary_e::A);
            Female_Option() = mcm->Add_Toggle_Option(Main_t::IS_FEMALE, Male_Female_Argument() == Binary_e::B);

            Unique_Option() = mcm->Add_Toggle_Option(Main_t::IS_UNIQUE, Unique_Generic_Argument() == Binary_e::A);
            Generic_Option() = mcm->Add_Toggle_Option(Main_t::IS_GENERIC, Unique_Generic_Argument() == Binary_e::B);

        } else if (Toggle_Type() == Toggle_Type_e::ANY) {

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
    inline void Bases_Filter_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

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
            Mod_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Race_Negate_Option()) {
            Bool_t value = Race_Do_Negate();
            Race_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Base_Negate_Option()) {
            Bool_t value = Base_Do_Negate();
            Base_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Template_Negate_Option()) {
            Bool_t value = Template_Do_Negate();
            Template_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Faction_Negate_Option()) {
            Bool_t value = Faction_Do_Negate();
            Faction_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Keyword_Negate_Option()) {
            Bool_t value = Keyword_Do_Negate();
            Keyword_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Relation_Negate_Option()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Vitality_Negate_Option()) {
            Bool_t value = Vitality_Do_Negate();
            Vitality_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else {
            if (Toggle_Type() == Toggle_Type_e::EITHER) {
                if (option == Male_Option()) {
                    mcm->Toggle_Either(Male_Female_Argument_Variable(), option, option + 1, Binary_e::A);
                } else if (option == Female_Option()) {
                    mcm->Toggle_Either(Male_Female_Argument_Variable(), option - 1, option, Binary_e::B);

                } else if (option == Unique_Option()) {
                    mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option, option + 1, Binary_e::A);
                } else if (option == Generic_Option()) {
                    mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option - 1, option, Binary_e::B);

                }
            } else if (Toggle_Type() == Toggle_Type_e::ANY) {
                if (option == Male_Option()) {
                    mcm->Toggle_Any(Male_Female_Argument_Variable(), option, option + 1, Binary_e::A);
                } else if (option == Female_Option()) {
                    mcm->Toggle_Any(Male_Female_Argument_Variable(), option - 1, option, Binary_e::B);

                } else if (option == Unique_Option()) {
                    mcm->Toggle_Any(Unique_Generic_Argument_Variable(), option, option + 1, Binary_e::A);
                } else if (option == Generic_Option()) {
                    mcm->Toggle_Any(Unique_Generic_Argument_Variable(), option - 1, option, Binary_e::B);

                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

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
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Mods();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Mod_Argument(value);
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
                Race_Argument(value);
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
                Base_Argument(value);
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
                Template_Argument(value);
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
                Faction_Argument(value);
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
                Keyword_Argument(value);
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
                Relation_Argument(value);
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
                Vitality_Argument(mcm->From_Vitality_Key(value.data));
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
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Search_Option()) {
            Mod_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Race_Search_Option()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Base_Search_Option()) {
            Base_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Template_Search_Option()) {
            Template_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Faction_Search_Option()) {
            Faction_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Keyword_Search_Option()) {
            Keyword_Argument(value);
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
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Back_Option()                { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Reset_Option()               { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Smart_Select_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Uncombative_Spawns_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Persistent_Spawns_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Static_Spawns_Option()       { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Reset_Option_Ints()
    {
        Back_Option()               = -1;
        Reset_Option()              = -1;

        Smart_Select_Option()       = -1;
        Uncombative_Spawns_Option() = -1;
        Persistent_Spawns_Option()  = -1;
        Static_Spawns_Option()      = -1;
    }

    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Smart_Select_Variable()       { DEFINE_BOOL("p_options_do_smart_select"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Uncombative_Spawns_Variable() { DEFINE_BOOL("p_options_do_uncombative_spawns"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Persistent_Spawns_Variable()  { DEFINE_BOOL("p_options_do_persistent_spawns"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Static_Spawns_Variable()      { DEFINE_BOOL("p_options_do_static_spawns"); }

    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Smart_Select()                    { return Do_Smart_Select_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Smart_Select(Bool_t value)        { Do_Smart_Select_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Uncombative_Spawns()              { return Do_Uncombative_Spawns_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Uncombative_Spawns(Bool_t value)  { Do_Uncombative_Spawns_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Persistent_Spawns()               { return Do_Persistent_Spawns_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Persistent_Spawns(Bool_t value)   { Do_Persistent_Spawns_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Static_Spawns()                   { return Do_Static_Spawns_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Static_Spawns(Bool_t value)       { Do_Static_Spawns_Variable()->Value(value); }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::Reset()
    {
        Do_Smart_Select(true);
        Do_Uncombative_Spawns(true);
        Do_Persistent_Spawns(true);
        Do_Static_Spawns(true);
    }

    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Options_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
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
        Main_t* mcm = Main_t::Self();

        if (option == Reset_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_RESET_OPTIONS);

        } else if (option == Smart_Select_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_SMART_SELECT);
        } else if (option == Uncombative_Spawns_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_UNCOMBATIVE_SPAWNS);
        } else if (option == Persistent_Spawns_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_PERSISTENT_SPAWNS);
        } else if (option == Static_Spawns_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_STATIC_SPAWNS);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Back_Option()                   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Primary_Option()                { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Previous_Option()               { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Next_Option()                   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::View_Item_Option()              { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::View_Bases_Option()             { DEFINE_OPTION(); }

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
    inline Int_t&   Bases_Item_t<B, I>::Race_Name_Option()              { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Cell_Name_Option()              { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Reset_Option_Ints()
    {
        Back_Option()                   = -1;
        Primary_Option()                = -1;
        Previous_Option()               = -1;
        Next_Option()                   = -1;
        View_Item_Option()              = -1;
        View_Bases_Option()             = -1;

        show_bases_option               = -1;
        show_commands_option            = -1;
        show_factions_option            = -1;
        show_keywords_option            = -1;
        show_mods_option                = -1;
        show_races_option               = -1;
        show_templates_option           = -1;

        Race_Name_Option()              = -1;
        Cell_Name_Option()              = -1;
    }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Item_t<B, I>::Nested_View_Variable()          { DEFINE_STRING("p_item_nested_view"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Item_t<B, I>::Nested_Index_Variable()         { DEFINE_INT("p_item_nested_index"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Item_t<B, I>::Nested_Form_Variable()          { DEFINE_INT("p_item_nested_form"); }

    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Bases_Variable()        { DEFINE_BOOL("p_item_do_show_bases"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Commands_Variable()     { DEFINE_BOOL("p_item_do_show_commands"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Factions_Variable()     { DEFINE_BOOL("p_item_do_show_factions"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Keywords_Variable()     { DEFINE_BOOL("p_item_do_show_keywords"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Mods_Variable()         { DEFINE_BOOL("p_item_do_show_mods"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Races_Variable()        { DEFINE_BOOL("p_item_do_show_races"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Item_t<B, I>::Do_Show_Templates_Variable()    { DEFINE_BOOL("p_item_do_show_templates"); }

    template <typename B, typename I>
    inline Bases_Item_View_e Bases_Item_t<B, I>::Nested_View()
    {
        String_t nested_view = Nested_View_Variable()->Value();
        if (CString_t::Is_Same(nested_view, ITEM_VIEW, true)) {
            return Bases_Item_View_e::ITEM;
        } else if (CString_t::Is_Same(nested_view, BASES_VIEW, true)) {
            return Bases_Item_View_e::BASES;
        } else if (CString_t::Is_Same(nested_view, BASES_ITEM_VIEW, true)) {
            return Bases_Item_View_e::BASES_ITEM;
        } else {
            Nested_View_Variable()->Value(ITEM_VIEW);
            return Bases_Item_View_e::ITEM;
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Nested_View(Bases_Item_View_e value)
    {
        if (value == Bases_Item_View_e::ITEM) {
            Nested_View_Variable()->Value(ITEM_VIEW);
        } else if (value == Bases_Item_View_e::BASES) {
            Nested_View_Variable()->Value(BASES_VIEW);
        } else if (value == Bases_Item_View_e::BASES_ITEM) {
            Nested_View_Variable()->Value(BASES_ITEM_VIEW);
        } else {
            Nested_View_Variable()->Value(ITEM_VIEW);
        }
    }

    template <typename B, typename I>
    inline Int_t        Bases_Item_t<B, I>::Nested_Index()                  { return Nested_Index_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Nested_Index(Int_t value)       { Nested_Index_Variable()->Value(value); }
    template <typename B, typename I>
    inline Form_ID_t    Bases_Item_t<B, I>::Nested_Form()                   { return Nested_Form_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Nested_Form(Form_ID_t value)    { Nested_Form_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Bases()                 { return Do_Show_Bases_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Bases(Bool_t value)     { Do_Show_Bases_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Commands()              { return Do_Show_Commands_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Commands(Bool_t value)  { Do_Show_Commands_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Factions()              { return Do_Show_Factions_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Factions(Bool_t value)  { Do_Show_Factions_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Keywords()              { return Do_Show_Keywords_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Keywords(Bool_t value)  { Do_Show_Keywords_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Mods()                  { return Do_Show_Mods_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Mods(Bool_t value)      { Do_Show_Mods_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Races()                 { return Do_Show_Races_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Races(Bool_t value)     { Do_Show_Races_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t       Bases_Item_t<B, I>::Do_Show_Templates()             { return Do_Show_Templates_Variable()->Value(); }
    template <typename B, typename I>
    inline void         Bases_Item_t<B, I>::Do_Show_Templates(Bool_t value) { Do_Show_Templates_Variable()->Value(value); }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Spawn(Actor_Base_t* base)
    {
        auto* options = Options();
        Spawned_Actors_t::Self().Add(
            base,
            options->Do_Persistent_Spawns(),
            options->Do_Uncombative_Spawns(),
            options->Do_Static_Spawns()
        );
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Spawn(Leveled_Actor_Base_t* leveled_base)
    {
        auto* options = Options();
        Spawned_Actors_t::Self().Add(
            leveled_base,
            options->Do_Persistent_Spawns(),
            options->Do_Uncombative_Spawns(),
            options->Do_Static_Spawns()
        );
    }
    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Spawn(Cached_Leveled_t* cached_leveled)
    {
        if (cached_leveled) {
            Spawn(cached_leveled->leveled);
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Base(Actor_Base_t* base, const char* type_name)
    {
        Main_t* mcm = Main_t::Self();

        if (base && base->Is_Valid()) {
            if (Do_Show_Bases()) {
                if (mcm->Can_Add_Options(2 + 4)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, type_name);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + base->Name(), Main_t::_NONE_);
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + base->Form_ID_String().data, Main_t::_NONE_);

                    if (base->Is_Male()) {
                        mcm->Add_Text_Option(Main_t::IS_MALE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_FEMALE, Main_t::_NONE_);
                    }
                    if (base->Is_Unique()) {
                        mcm->Add_Text_Option(Main_t::IS_UNIQUE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_GENERIC, Main_t::_NONE_);
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
                show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Bases(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Factions_And_Ranks(Vector_t<Faction_And_Rank_t> factions_and_ranks)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = factions_and_ranks.size();
        if (count > 0) {
            if (Do_Show_Factions()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::FACTIONS);
                    show_factions_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    factions_and_ranks.Sort(Faction_And_Rank_t::Compare_Editor_Or_Form_IDs);
                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Faction_And_Rank_t& faction_and_rank = factions_and_ranks[idx];
                        Faction_t* faction = faction_and_rank.faction;
                        skylib::Faction_Rank_t rank = faction_and_rank.rank;
                        if (faction && faction->Is_Valid()) {
                            std::string label =
                                std::string(Main_t::_SPACE_) +
                                faction->Editor_Or_Form_ID().data +
                                Main_t::_COLON_SPACE_ +
                                std::to_string(rank);
                            mcm->Add_Text_Option(label, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
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
                show_factions_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Factions(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Header(const char* primary_option_name, size_t listed_item_count)
    {
        Main_t* mcm = Main_t::Self();

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Primary_Option() = mcm->Add_Text_Option(primary_option_name, Main_t::_NONE_);
        if (listed_item_count > 1) {
            Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_);
            Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_);
        } else {
            Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
            Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
        }
        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Keywords(Vector_t<Keyword_t*> keywords)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = keywords.size();
        if (count > 0) {
            if (Do_Show_Keywords()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::KEYWORDS);
                    show_keywords_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    keywords.Sort(Keyword_t::Compare_Any_Names);
                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Keyword_t* keyword = keywords[idx];
                        if (keyword && keyword->Is_Valid()) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + keyword->Any_Name().data, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
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
                show_keywords_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Keywords(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Leveled_Base(Leveled_Actor_Base_t* leveled_base)
    {
        Main_t* mcm = Main_t::Self();

        if (leveled_base && leveled_base->Is_Valid()) {
            if (Do_Show_Bases()) {
                if (mcm->Can_Add_Options(2 + 4)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::LEVELED_BASE);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + leveled_base->Leveled_Name().data, Main_t::_NONE_);
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + leveled_base->Form_ID_String().data, Main_t::_NONE_);

                    View_Bases_Option() = mcm->Add_Text_Option(Main_t::VIEW_INTERNAL_BASES, Main_t::_DOTS_);
                    mcm->Add_Empty_Option();
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
                show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Bases(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Mod_Names(Vector_t<String_t> mod_names)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = mod_names.size();
        if (count > 0) {
            if (Do_Show_Mods()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::MODS);
                    show_mods_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + mod_names[idx].data, Main_t::_NONE_);
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
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
                show_mods_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Mods(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Race(Race_t* race)
    {
        Main_t* mcm = Main_t::Self();

        if (race && race->Is_Valid()) {
            if (Do_Show_Races()) {
                if (mcm->Can_Add_Options(2 + 2)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::RACE);
                    show_races_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    Race_Name_Option() = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Get_Editor_ID(), Main_t::_NONE_);
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Form_ID_String().data, Main_t::_NONE_);
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
                show_races_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Races(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Build_Templates(Vector_t<Actor_Base_t*> templates)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = templates.size();
        if (count > 0) {
            if (Do_Show_Templates()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::TEMPLATES);
                    show_templates_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Actor_Base_t* base_template = templates[idx];
                        const char* name = base_template->Name();
                        const char* form_id = base_template->Form_ID_String().data;
                        mcm->Add_Text_Option(
                            std::string(Main_t::_SPACE_) + mcm->Pretty_ID(name, Main_t::_NONE_, form_id),
                            Main_t::_NONE_
                        );
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
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
                show_templates_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Templates(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline Bool_t Bases_Item_t<B, I>::Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            if (!Item()->Current_Item(Item()->Previous_Item())) {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            if (!Item()->Current_Item(Item()->Next_Item())) {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);
            return true;

        } else if (option == show_bases_option || option == show_bases_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Bases_Variable(), option, lcallback);
            return true;

        } else if (option == show_commands_option || option == show_commands_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Commands_Variable(), option, lcallback);
            return true;

        } else if (option == show_factions_option || option == show_factions_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Factions_Variable(), option, lcallback);
            return true;

        } else if (option == show_keywords_option || option == show_keywords_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Keywords_Variable(), option, lcallback);
            return true;

        } else if (option == show_mods_option || option == show_mods_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Mods_Variable(), option, lcallback);
            return true;

        } else if (option == show_races_option || option == show_races_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Races_Variable(), option, lcallback);
            return true;

        } else if (option == show_templates_option || option == show_templates_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Templates_Variable(), option, lcallback);
            return true;

        } else {
            return false;
        }
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
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

#undef DEFINE_BOOL
#undef DEFINE_INT
#undef DEFINE_STRING
