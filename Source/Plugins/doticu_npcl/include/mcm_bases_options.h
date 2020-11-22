/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class Bases_Options_t : public Bases_t
    {
    public:
        V::Int_Variable_t*  Back_Option_Variable();
        V::Int_Variable_t*  Reset_Option_Variable();

        V::Int_Variable_t*  Smart_Select_Option_Variable();
        V::Bool_Variable_t* Do_Smart_Select_Variable();

        V::Int_Variable_t*  Uncombative_Spawns_Option_Variable();
        V::Bool_Variable_t* Do_Uncombative_Spawns_Variable();

    public:
        Bool_t  Do_Smart_Select();
        void    Do_Smart_Select(Bool_t value);

        Bool_t  Do_Uncombative_Spawns();
        void    Do_Uncombative_Spawns(Bool_t value);

    public:
        void    Reset();

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
