/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class Static_Bases_t;
    class Static_Bases_List_t;
    class Static_Bases_Filter_t;
    class Static_Bases_Options_t;
    class Static_Bases_Item_t;

    class Static_Bases_Base_t : public Quest_t
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        static String_t         Class_Name();
        static V::Class_t*      Class();
        V::Object_t*            Object();

        static Static_Bases_t*  Self();
        Static_Bases_List_t*    List();
        Static_Bases_Filter_t*  Filter();
        Static_Bases_Options_t* Options();
        Static_Bases_Item_t*    Item();

        static const char*      Item_Type_Singular();
        static const char*      Item_Type_Plural();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Static_Bases_t : public Bases_t<Static_Bases_Base_t, Static_Bases_Base_t::Item_t>
    {
    };

}}

namespace doticu_npcl { namespace MCM {

    class Static_Bases_List_t : public Bases_List_t<Static_Bases_Base_t, Static_Bases_Base_t::Item_t>
    {
    public:
        Vector_t<Item_t>&   Items();
        Vector_t<Item_t>    Default_Items();
        Item_t              Null_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Static_Bases_Filter_t : public Bases_Filter_t<Static_Bases_Base_t, Static_Bases_Base_t::Item_t>
    {
    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Static_Bases_Options_t : public Bases_Options_t<Static_Bases_Base_t, Static_Bases_Base_t::Item_t>
    {
    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Static_Bases_Item_t : public Bases_Item_t<Static_Bases_Base_t, Static_Bases_Base_t::Item_t>
    {
    public:
        V::Int_Variable_t* Static_Form_ID_Variable();

    public:
        Form_ID_t   Static_Form_ID();
        void        Static_Form_ID(Form_ID_t value);

    public:
        Item_t  Current_Item();
        Item_t  Previous_Item();
        Item_t  Next_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}
