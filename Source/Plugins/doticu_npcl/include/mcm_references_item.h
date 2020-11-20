/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_references.h"

namespace doticu_npcl { namespace MCM {

    class References_Item_t : public References_t
    {
    public:
        V::Int_Variable_t*  Back_Option_Variable();
        V::Int_Variable_t*  Previous_Option_Variable();
        V::Int_Variable_t*  Next_Option_Variable();
        V::Int_Variable_t*  Actor_Form_ID_Variable();
        V::Int_Variable_t*  Cell_Form_ID_Variable();

    public:
        Form_ID_t   Actor_Form_ID();
        void        Actor_Form_ID(Form_ID_t value);
        Form_ID_t   Cell_Form_ID();
        void        Cell_Form_ID(Form_ID_t value);

    public:
        Loaded_Actor_t  Current_Loaded_Actor();
        Loaded_Actor_t  Previous_Loaded_Actor();
        Loaded_Actor_t  Next_Loaded_Actor();

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
