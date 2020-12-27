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
        static String_t                     Class_Name();
        static V::Class_t*                  Class();
        V::Object_t*                        Object();

        static some<Spawned_References_t*>  Self();
        some<Spawned_References_List_t*>    List();
        some<Spawned_References_Filter_t*>  Filter();
        some<Spawned_References_Options_t*> Options();
        some<Spawned_References_Item_t*>    Item();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_t : public References_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_List_t : public References_List_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        V::Variable_tt<Vector_t<Form_ID_t>>&    Actor_IDs();
        V::Variable_tt<Vector_t<String_t>>&     Actor_Mod_Names();
        V::Variable_tt<Vector_t<Form_ID_t>>&    Actor_Base_IDs();
        V::Variable_tt<Vector_t<String_t>>&     Actor_Base_Mod_Names();

    public:
        Vector_t<Item_t>&   Items();
        Vector_t<Item_t>    Default_Items();
        Item_t              Null_Item();

    public:
        void    On_Load();
        void    On_Save();
        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_Filter_t : public References_Filter_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        Toggle_Type_e Toggle_Type();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_Options_t : public References_Options_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        static Int_t    do_verify_unspawns_option;

        void            Reset_Option_Ints();

    public:
        V::Variable_tt<Bool_t>& Do_Verify_Unspawns();

    public:
        void    Reset();

    public:
        Bool_t  Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Spawned_References_Item_t : public References_Item_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>
    {
    public:
        V::Variable_tt<Form_ID_t>& Actor_Form_ID();

    public:
        Item_t  Current_Item();
        Bool_t  Current_Item(Item_t item);
        Item_t  Previous_Item();
        Item_t  Next_Item();

        void Back_To_List(some<Main_t*> mcm, some<Latent_Callback_i*> lcallback);
        void Select_Unspawn(some<Main_t*> mcm, Int_t option, some<Latent_Callback_i*> lcallback);

    public:
        void    On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}
