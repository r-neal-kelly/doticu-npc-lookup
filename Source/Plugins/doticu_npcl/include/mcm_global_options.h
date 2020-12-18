/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    class Global_Options_t : public Quest_t
    {
    public:
        static String_t             Class_Name();
        static V::Class_t*          Class();
        V::Object_t*                Object();
        static Global_Options_t*    Self();

    public:
        Int_t&  Reset_Option();
        Int_t&  Prioritize_MCM_Menu_Option();
        Int_t&  Translate_Page_Titles_Option();

        void    Reset_Option_Ints();

    public:
        V::Bool_Variable_t* Prioritize_MCM_Menu_Variable();
        V::Bool_Variable_t* Translate_Page_Titles_Variable();

    public:
        Bool_t  Prioritize_MCM_Menu();
        void    Prioritize_MCM_Menu(Bool_t value);
        Bool_t  Translate_Page_Titles();
        void    Translate_Page_Titles(Bool_t value);

    public:
        void Reset();
        void Update_MCM_Menu_Name();

    public:
        void On_Init();
        void On_Load();
        void On_Save();
        void On_Config_Open();
        void On_Config_Close();
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
