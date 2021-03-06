/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_references.h"

namespace doticu_npcl { namespace MCM {

    class Loaded_References_t;
    class Loaded_References_List_t;
    class Loaded_References_Filter_t;
    class Loaded_References_Options_t;
    class Loaded_References_Item_t;

    class Loaded_References_Base_t : public Quest_t
    {
    public:
        using Item_t = Actor_t*;

    public:
        static String_t                     Class_Name();
        static V::Class_t*                  Class();
        V::Object_t*                        Object();

        static some<Loaded_References_t*>   Self();
        some<Loaded_References_List_t*>     List();
        some<Loaded_References_Filter_t*>   Filter();
        some<Loaded_References_Options_t*>  Options();
        some<Loaded_References_Item_t*>     Item();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Loaded_References_t : public References_t<Loaded_References_Base_t, Loaded_References_Base_t::Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    class Loaded_References_List_t : public References_List_t<Loaded_References_Base_t, Loaded_References_Base_t::Item_t>
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

    class Loaded_References_Filter_t : public References_Filter_t<Loaded_References_Base_t, Loaded_References_Base_t::Item_t>
    {
    public:
        Toggle_Type_e Toggle_Type();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Loaded_References_Options_t : public References_Options_t<Loaded_References_Base_t, Loaded_References_Base_t::Item_t>
    {
    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Loaded_References_Item_t : public References_Item_t<Loaded_References_Base_t, Loaded_References_Base_t::Item_t>
    {
    public:
        V::Variable_tt<Form_ID_t>& Actor_Form_ID();

    public:
        Item_t  Current_Item();
        Bool_t  Current_Item(Item_t item);
        Item_t  Previous_Item();
        Item_t  Next_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}
