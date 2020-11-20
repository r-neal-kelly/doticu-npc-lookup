/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "mcm_bases_list.h"
#include "mcm_bases_filter.h"
#include "mcm_bases_options.h"
#include "mcm_bases_item.h"

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  Bases_Options_t::Back_Option_Variable()         { DEFINE_INT_VARIABLE("p_options_back_option"); }
    V::Int_Variable_t*  Bases_Options_t::Reset_Option_Variable()        { DEFINE_INT_VARIABLE("p_options_reset_option"); }
    
    V::Int_Variable_t*  Bases_Options_t::Smart_Select_Option_Variable() { DEFINE_INT_VARIABLE("p_options_smart_select_option"); }
    V::Bool_Variable_t* Bases_Options_t::Do_Smart_Select_Variable()     { DEFINE_BOOL_VARIABLE("p_options_do_smart_select"); }

    Bool_t Bases_Options_t::Do_Smart_Select()
    {
        return Do_Smart_Select_Variable()->Value();
    }

    void Bases_Options_t::Do_Smart_Select(Bool_t value)
    {
        Do_Smart_Select_Variable()->Value(value);
    }

    void Bases_Options_t::Reset()
    {
        Do_Smart_Select(true);
    }

    void Bases_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Bases: Options ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::BACK_LABEL, ""));
        Reset_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::RESET_LABEL, ""));

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");
        Smart_Select_Option_Variable()->Value(mcm->Add_Toggle_Option(" Smart Select ", Do_Smart_Select()));

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_actor_bases = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Reset_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Reset();
            mcm->Reset_Page();

        } else if (option == Smart_Select_Option_Variable()->Value()) {
            Bool_t value = Do_Smart_Select();
            Do_Smart_Select(!value);
            mcm->Toggle_Option_Value(option, !value);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Options_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
