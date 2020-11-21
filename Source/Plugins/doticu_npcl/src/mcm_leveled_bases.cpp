/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_leveled_bases.h"
#include "mcm_leveled_bases_list.h"
#include "mcm_leveled_bases_filter.h"
#include "mcm_leveled_bases_options.h"
#include "mcm_leveled_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using CString_t = skylib::CString_t;

    Leveled_Bases_t*        Leveled_Bases_t::Self()                     { return static_cast<Leveled_Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t                Leveled_Bases_t::Class_Name()               { DEFINE_CLASS_NAME("doticu_npcl_mcm_leveled_bases"); }
    V::Class_t*             Leveled_Bases_t::Class()                    { DEFINE_CLASS(); }
    V::Object_t*            Leveled_Bases_t::Object()                   { DEFINE_OBJECT(); }

    V::String_Variable_t*   Leveled_Bases_t::Current_View_Variable()    { DEFINE_STRING_VARIABLE("p_current_view"); }

    Leveled_Bases_t::View_e Leveled_Bases_t::Current_View()
    {
        String_t current_view = Current_View_Variable()->Value();
        if (CString_t::Is_Same(current_view, LIST_VIEW, true)) {
            return View_e::LIST;
        } else if (CString_t::Is_Same(current_view, FILTER_VIEW, true)) {
            return View_e::FILTER;
        } else if (CString_t::Is_Same(current_view, OPTIONS_VIEW, true)) {
            return View_e::OPTIONS;
        } else if (CString_t::Is_Same(current_view, ITEM_VIEW, true)) {
            return View_e::ITEM;
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
            return View_e::LIST;
        }
    }

    void Leveled_Bases_t::Current_View(Leveled_Bases_t::View_e value)
    {
        if (value == View_e::LIST) {
            Current_View_Variable()->Value(LIST_VIEW);
        } else if (value == View_e::FILTER) {
            Current_View_Variable()->Value(FILTER_VIEW);
        } else if (value == View_e::OPTIONS) {
            Current_View_Variable()->Value(OPTIONS_VIEW);
        } else if (value == View_e::ITEM) {
            Current_View_Variable()->Value(ITEM_VIEW);
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
        }
    }

    Leveled_Bases_List_t* Leveled_Bases_t::List()
    {
        return static_cast<Leveled_Bases_List_t*>(this);
    }

    Leveled_Bases_Filter_t* Leveled_Bases_t::Filter()
    {
        return static_cast<Leveled_Bases_Filter_t*>(this);
    }

    Leveled_Bases_Options_t* Leveled_Bases_t::Options()
    {
        return static_cast<Leveled_Bases_Options_t*>(this);
    }

    Leveled_Bases_Item_t* Leveled_Bases_t::Item()
    {
        return static_cast<Leveled_Bases_Item_t*>(this);
    }

    void Leveled_Bases_t::On_Config_Open()
    {
        List()->do_update_items = true;
    }

    void Leveled_Bases_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Page_Open(is_refresh, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Select(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Input_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Default(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Highlight(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::Register_Me(V::Machine_t* machine)
    {
    }

}}
