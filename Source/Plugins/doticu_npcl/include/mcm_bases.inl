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
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Select(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Select(option, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Menu_Open(option, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Slider_Open(option, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Slider_Accept(option, value, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Input_Accept(option, value, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Default(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Default(option, lcallback);
        else                                            SKYLIB_ASSERT(false);
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_View_e current_view = Current_View();
             if (current_view == Bases_View_e::LIST)    List()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::FILTER)  Filter()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::OPTIONS) Options()->On_Option_Highlight(option, lcallback);
        else if (current_view == Bases_View_e::ITEM)    Item()->On_Option_Highlight(option, lcallback);
        else                                            SKYLIB_ASSERT(false);
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
    inline V::Int_Variable_t*   Bases_List_t<B, I>::Page_Index_Variable()   { DEFINE_INT("p_list_page_index"); }

    template <typename B, typename I>
    inline Int_t    Bases_List_t<B, I>::Page_Index()            { return Page_Index_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_List_t<B, I>::Page_Index(Int_t value) { Page_Index_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t Bases_List_t<B, I>::Title(Int_t item_count, Int_t page_index, Int_t page_count)
    {
        std::string items =
            std::string(Item_Type_Plural()) + ": " +
            std::to_string(item_count);

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return items + "               " + pages;
    }

    template <typename Base_t, typename Item_t>
    inline Item_t Bases_List_t<Base_t, Item_t>::Option_To_Item(Int_t option)
    {
        Int_t relative_idx = mcmlib::Option_t(option).position - HEADERS_PER_PAGE;
        if (relative_idx > -1 && relative_idx < ITEMS_PER_PAGE) {
            Vector_t<Item_t>& items = List()->Items();
            Int_t absolute_idx = Page_Index() * ITEMS_PER_PAGE + relative_idx;
            if (absolute_idx > -1 && absolute_idx < items.size()) {
                return items[absolute_idx];
            } else {
                return List()->Null_Item();
            }
        } else {
            return List()->Null_Item();
        }
    }

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
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Select_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Negate_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Male_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Female_Option()           { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Unique_Option()           { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Generic_Option()          { DEFINE_OPTION(); }

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
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Relation_Argument_Variable()          { DEFINE_STRING("p_filter_relation_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Relation_Do_Negate_Variable()         { DEFINE_BOOL("p_filter_relation_do_negate"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Male_Female_Argument_Variable()       { DEFINE_INT("p_filter_male_female_argument"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Unique_Generic_Argument_Variable()    { DEFINE_INT("p_filter_unique_generic_argument"); }

    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Mod_Argument()                            { return Mod_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Mod_Argument(String_t value)              { Mod_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Mod_Do_Negate()                           { return Mod_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Mod_Do_Negate(Bool_t value)               { Mod_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Race_Argument()                           { return Race_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Race_Argument(String_t value)             { Race_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Race_Do_Negate()                          { return Race_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Race_Do_Negate(Bool_t value)              { Race_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Base_Argument()                           { return Base_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Base_Argument(String_t value)             { Base_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Base_Do_Negate()                          { return Base_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Base_Do_Negate(Bool_t value)              { Base_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Template_Argument()                       { return Template_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Template_Argument(String_t value)         { Template_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Template_Do_Negate()                      { return Template_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Template_Do_Negate(Bool_t value)          { Template_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Relation_Argument()                       { return Relation_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Relation_Argument(String_t value)         { Relation_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Relation_Do_Negate()                      { return Relation_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Relation_Do_Negate(Bool_t value)          { Relation_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline Binary_e Bases_Filter_t<B, I>::Male_Female_Argument()                    { return Male_Female_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Male_Female_Argument(Binary_e value)      { Male_Female_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Binary_e Bases_Filter_t<B, I>::Unique_Generic_Argument()                 { return Unique_Generic_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Unique_Generic_Argument(Binary_e value)   { Unique_Generic_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Title()
    {
        return std::string(Item_Type_Plural()) + ": Filter ";
    }

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

        Relation_Argument("");
        Relation_Do_Negate(false);

        Male_Female_Argument(Binary_e::NONE);
        Unique_Generic_Argument(Binary_e::NONE);
    }

    template <typename Base_t, typename Item_t>
    inline Filter_State_t<Item_t> Bases_Filter_t<Base_t, Item_t>::Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write)
    {
        Actor_Base_t* relatable_base = Consts_t::Skyrim_Player_Actor_Base();
        Relation_e relation_argument = Relation_e::From_String(Relation_Argument());

        Filter_State_t<Item_t> filter_state(read, write);

        Mod_Filter_t<Item_t>(filter_state, Mod_Argument(), Mod_Do_Negate());
        Race_Filter_t<Item_t>(filter_state, Race_Argument(), Race_Do_Negate());
        Base_Filter_t<Item_t>(filter_state, Base_Argument(), Base_Do_Negate());
        Template_Filter_t<Item_t>(filter_state, Template_Argument(), Template_Do_Negate());
        Relation_Filter_t<Item_t>(filter_state, relatable_base, relation_argument, Relation_Do_Negate());
        Male_Female_Filter_t<Item_t>(filter_state, Male_Female_Argument());
        Unique_Generic_Filter_t<Item_t>(filter_state, Unique_Generic_Argument());

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
    inline Vector_t<String_t> Bases_Filter_t<B, I>::Selectable_Relations()
    {
        return Selectable_Relations_t<B, I>(Consts_t::Skyrim_Player_Actor_Base()).Results();
    }

    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }
    template <typename B, typename I>
    inline void Bases_Filter_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
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
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
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
    inline Int_t&   Bases_Options_t<B, I>::Static_Spawns_Option() { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Smart_Select_Variable()       { DEFINE_BOOL("p_options_do_smart_select"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Uncombative_Spawns_Variable() { DEFINE_BOOL("p_options_do_uncombative_spawns"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Persistent_Spawns_Variable()  { DEFINE_BOOL("p_options_do_persistent_spawns"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Static_Spawns_Variable() { DEFINE_BOOL("p_options_do_static_spawns"); }

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
    inline String_t Bases_Options_t<B, I>::Title()
    {
        return std::string(Item_Type_Plural()) + ": Options ";
    }

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

        if (option == Smart_Select_Option()) {
            mcm->Info_Text("On: Filter select menus are filtered dynamically, and thus narrow down results accurately." "\n"
                           "Off: Filter select menus may have options that lead to no results.");
        } else if (option == Uncombative_Spawns_Option()) {
            mcm->Info_Text("On: Tries to stop aggressive spawns from attacking the player." "\n"
                           "Off: Makes no attempt to stop a spawn from attacking the player.");
        } else if (option == Persistent_Spawns_Option()) {
            mcm->Info_Text("On: Forces all spawns to be persistent so the engine doesn't try to delete them." "\n"
                           "Off: Allows spawns to be temporary if their base is. Naturally persistent NPCs may still spawn.");
        } else if (option == Static_Spawns_Option()) {
            mcm->Info_Text("On: Finds the root base of dynamic spawns. Prevents the engine from changing their appearance." "\n"
                           "Off: Allows dynamic spawns that the engine may change the appearance of over time.");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Back_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Previous_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Next_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Primary_Option()    { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline String_t Bases_Item_t<B, I>::Title(const char* item_name)
    {
        return std::string(Item_Type_Singular()) + ": " + item_name;
    }

    inline void Spawn_Impl(Form_t* base, Bool_t do_persist, Bool_t do_uncombative)
    {
        if (base && base->Is_Valid()) {
            Actor_t* actor = static_cast<Actor_t*>
                (Reference_t::Create(base, 1, Consts_t::Skyrim_Player_Actor(), do_persist, false));
            if (actor && actor->Is_Valid()) {
                if (do_uncombative) {
                    actor->Set_Actor_Value(Actor_Value_e::AGGRESSION, 0.0f);
                }
                Spawned_Actors_t::Self().Add(actor);
            }
        }
    }

    inline void Spawn_Impl(Actor_Base_t* base, Bool_t do_static, Bool_t do_persist, Bool_t do_uncombative)
    {
        if (do_static) {
            if (base && base->Is_Valid()) {
                Spawn_Impl(static_cast<Form_t*>(base->Root_Base()), do_persist, do_uncombative);
            }
        } else {
            Spawn_Impl(static_cast<Form_t*>(base), do_persist, do_uncombative);
        }
    }

    inline void Spawn_Impl(Leveled_Actor_Base_t* base, Bool_t do_static, Bool_t do_persist, Bool_t do_uncombative)
    {
        if (do_static) {
            if (base && base->Is_Valid()) {
                Actor_t* actor = static_cast<Actor_t*>
                    (Reference_t::Create(base, 1, Consts_t::Skyrim_Player_Actor(), false, true));
                if (actor && actor->Is_Valid()) {
                    Spawn_Impl(static_cast<Actor_Base_t*>(actor->base_form), do_static, do_persist, do_uncombative);
                    actor->Mark_For_Delete();
                }
            }
        } else {
            Spawn_Impl(static_cast<Form_t*>(base), do_persist, do_uncombative);
        }
    }

    template <typename B, typename I>
    inline void Bases_Item_t<B, I>::Spawn()
    {
        auto* options = Options();

        Spawn_Impl(
            Item()->Current_Item(),
            options->Do_Static_Spawns(),
            options->Do_Persistent_Spawns(),
            options->Do_Uncombative_Spawns()
        );
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
