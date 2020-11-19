/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_leveled_bases.h"

namespace doticu_npcl { namespace MCM {

    Leveled_Bases_t*    Leveled_Bases_t::Self()         { return static_cast<Leveled_Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t            Leveled_Bases_t::Class_Name()   { DEFINE_CLASS_NAME("doticu_npcl_mcm_leveled_bases"); }
    Class_t*            Leveled_Bases_t::Class()        { DEFINE_CLASS(); }
    Object_t*           Leveled_Bases_t::Object()       { DEFINE_OBJECT(); }

    void Leveled_Bases_t::On_Config_Open()
    {

    }

    void Leveled_Bases_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_t::Register_Me(Machine_t* machine)
    {
    }

}}
