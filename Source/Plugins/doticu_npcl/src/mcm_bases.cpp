/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    Bases_t*            Bases_t::Self()                             { return static_cast<Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t            Bases_t::Class_Name()                       { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases"); }
    Class_t*            Bases_t::Class()                            { DEFINE_CLASS(); }

    Object_t*           Bases_t::Object()                           { DEFINE_OBJECT(); }

    String_Variable_t*  Bases_t::Current_View_Variable()            { DEFINE_STRING_VARIABLE("p_current_view"); }

    Int_Variable_t*     Bases_t::Filter_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_option"); }

    Int_Variable_t*     Bases_t::Name_Option_Variable()             { DEFINE_INT_VARIABLE("p_name_option"); }
    String_Variable_t*  Bases_t::Name_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_name_argument"); }

    Int_Variable_t*     Bases_t::Mod_Option_Variable()              { DEFINE_INT_VARIABLE("p_mod_option"); }
    String_Variable_t*  Bases_t::Mod_Argument_Variable()            { DEFINE_STRING_VARIABLE("p_mod_argument"); }
    String_Variable_t*  Bases_t::Mod_View_Variable()                { DEFINE_STRING_VARIABLE("p_mod_view"); }

    Int_Variable_t*     Bases_t::Sex_Option_Variable()              { DEFINE_INT_VARIABLE("p_sex_option"); }
    Int_Variable_t*     Bases_t::Sex_Argument_Variable()            { DEFINE_INT_VARIABLE("p_sex_argument"); }
    String_Variable_t*  Bases_t::Sex_View_Variable()                { DEFINE_STRING_VARIABLE("p_sex_view"); }

    Int_Variable_t*     Bases_t::Race_Option_Variable()             { DEFINE_INT_VARIABLE("p_race_option"); }
    String_Variable_t*  Bases_t::Race_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_race_argument"); }
    String_Variable_t*  Bases_t::Race_View_Variable()               { DEFINE_STRING_VARIABLE("p_race_view"); }

    Int_Variable_t*     Bases_t::Relationship_Option_Variable()     { DEFINE_INT_VARIABLE("p_relationship_option"); }
    Int_Variable_t*     Bases_t::Relationship_Argument_Variable()   { DEFINE_INT_VARIABLE("p_relationship_argument"); }
    String_Variable_t*  Bases_t::Relationship_View_Variable()       { DEFINE_STRING_VARIABLE("p_relationship_view"); }

    Int_Variable_t*     Bases_t::Is_Unique_Option_Variable()        { DEFINE_INT_VARIABLE("p_is_unique_option"); }
    Int_Variable_t*     Bases_t::Is_Generic_Option_Variable()       { DEFINE_INT_VARIABLE("p_is_generic_option"); }
    Int_Variable_t*     Bases_t::Unique_Generic_Ternary_Variable()  { DEFINE_INT_VARIABLE("p_unique_generic_ternary"); }

    void Bases_t::On_Build_Page(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::Register_Me(Machine_t* machine)
    {
    }

}}
