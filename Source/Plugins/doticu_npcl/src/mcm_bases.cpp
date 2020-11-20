/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_bases.h"
#include "mcm_bases_list.h"
#include "mcm_bases_filter.h"
#include "mcm_bases_options.h"
#include "mcm_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using CString_t = skylib::CString_t;

    Bases_t*                Bases_t::Self()                     { return static_cast<Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t                Bases_t::Class_Name()               { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases"); }
    V::Class_t*             Bases_t::Class()                    { DEFINE_CLASS(); }
    V::Object_t*            Bases_t::Object()                   { DEFINE_OBJECT(); }

    V::String_Variable_t*   Bases_t::Current_View_Variable()    { DEFINE_STRING_VARIABLE("p_current_view"); }

    Bases_t::View_e Bases_t::Current_View()
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

    void Bases_t::Current_View(Bases_t::View_e value)
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

    Bases_List_t* Bases_t::List()
    {
        return static_cast<Bases_List_t*>(this);
    }

    Bases_Filter_t* Bases_t::Filter()
    {
        return static_cast<Bases_Filter_t*>(this);
    }

    Bases_Options_t* Bases_t::Options()
    {
        return static_cast<Bases_Options_t*>(this);
    }

    Bases_Item_t* Bases_t::Item()
    {
        return static_cast<Bases_Item_t*>(this);
    }

    void Bases_t::On_Config_Open()
    {
        List()->do_update_actor_bases = true;
    }

    void Bases_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Page_Open(is_refresh, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Select(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Input_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Default(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Highlight(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Bases_t::Register_Me(V::Machine_t* machine)
    {
    }

}}
