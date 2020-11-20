/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class Bases_List_t : public Bases_t
    {
    public:
        static constexpr Int_t  HEADERS_PER_PAGE    = 6;
        static constexpr Int_t  ITEMS_PER_PAGE      = 18;

        static Bool_t do_update_actor_bases;

    public:
        V::Int_Variable_t*  Filter_Option_Variable();
        V::Int_Variable_t*  Options_Option_Variable();
        V::Int_Variable_t*  Previous_Page_Option_Variable();
        V::Int_Variable_t*  Next_Page_Option_Variable();
        V::Int_Variable_t*  Page_Index_Variable();

    public:
        Int_t   Page_Index();
        void    Page_Index(Int_t value);

    public:
        String_t                    Format_Title(Int_t item_count, Int_t page_index, Int_t page_count);
        Vector_t<Actor_Base_t*>&    Actor_Bases();
        Actor_Base_t*               Option_To_Actor_Base(Int_t option);

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
