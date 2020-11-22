/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_leveled_bases.h"

namespace doticu_npcl { namespace MCM {

    using Form_ID_t = skylib::Form_ID_t;

    class Leveled_Bases_Item_t : public Leveled_Bases_t
    {
    public:
        V::Int_Variable_t*  Back_Option_Variable();
        V::Int_Variable_t*  Previous_Option_Variable();
        V::Int_Variable_t*  Next_Option_Variable();
        V::Int_Variable_t*  Spawn_Option_Variable();
        V::Int_Variable_t*  Leveled_Actor_Base_Form_ID_Variable();

    public:
        Form_ID_t   Leveled_Actor_Base_Form_ID();
        void        Leveled_Actor_Base_Form_ID(Form_ID_t value);

    public:
        Leveled_Actor_Base_t*   Current_Item();
        Leveled_Actor_Base_t*   Previous_Item();
        Leveled_Actor_Base_t*   Next_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

}}
