/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_references.h"

namespace doticu_npcl { namespace MCM {

    class Spawned_References_t;
    class Spawned_References_List_t;
    class Spawned_References_Filter_t;
    class Spawned_References_Options_t;
    class Spawned_References_Item_t;

    class Spawned_References_Base_t : public Quest_t
    {
    public:
        using Item_t = Actor_t*;

    public:
        static String_t                 Class_Name();
        static V::Class_t*              Class();
        V::Object_t*                    Object();

        static Spawned_References_t*    Self();
        Spawned_References_List_t*      List();
        Spawned_References_Filter_t*    Filter();
        Spawned_References_Options_t*   Options();
        Spawned_References_Item_t*      Item();

        static const char*              Item_Type_Singular();
        static const char*              Item_Type_Plural();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_t : public References_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        void On_Load();
        void On_Save();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_List_t : public References_List_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        V::Array_Variable_t<Int_t>*     Actor_IDs_Variable();
        V::Array_Variable_t<String_t>*  Actor_Mod_Names_Variable();
        V::Array_Variable_t<Int_t>*     Actor_Base_IDs_Variable();
        V::Array_Variable_t<String_t>*  Actor_Base_Mod_Names_Variable();

    public:
        Vector_t<Form_ID_t> Actor_IDs();
        void                Actor_IDs(Vector_t<Form_ID_t> values);
        V::Array_t*         Actor_IDs_Array();

        Vector_t<String_t>  Actor_Mod_Names();
        void                Actor_Mod_Names(Vector_t<String_t> values);
        V::Array_t*         Actor_Mod_Names_Array();

        Vector_t<Form_ID_t> Actor_Base_IDs();
        void                Actor_Base_IDs(Vector_t<Form_ID_t> values);
        V::Array_t*         Actor_Base_IDs_Array();

        Vector_t<String_t>  Actor_Base_Mod_Names();
        void                Actor_Base_Mod_Names(Vector_t<String_t> values);
        V::Array_t*         Actor_Base_Mod_Names_Array();

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

    class Spawned_References_Filter_t : public References_Filter_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
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

    class Spawned_References_Options_t : public References_Options_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_Item_t : public References_Item_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        V::Int_Variable_t*  Actor_Form_ID_Variable();

    public:
        Form_ID_t   Actor_Form_ID();
        void        Actor_Form_ID(Form_ID_t value);

    public:
        Item_t  Current_Item();
        Item_t  Previous_Item();
        Item_t  Next_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}
