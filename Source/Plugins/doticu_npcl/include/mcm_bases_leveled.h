/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "cached_leveled.h"
#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_t;
    class Leveled_Bases_List_t;
    class Leveled_Bases_Filter_t;
    class Leveled_Bases_Options_t;
    class Leveled_Bases_Item_t;

    class Leveled_Bases_Base_t : public Quest_t
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        static String_t                 Class_Name();
        static V::Class_t*              Class();
        V::Object_t*                    Object();

        static some<Leveled_Bases_t*>   Self();
        some<Leveled_Bases_List_t*>     List();
        some<Leveled_Bases_Filter_t*>   Filter();
        some<Leveled_Bases_Options_t*>  Options();
        some<Leveled_Bases_Item_t*>     Item();
    };

}}

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_t : public Bases_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_List_t : public Bases_List_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        static Vector_t<Cached_Leveled_t>   cached_leveleds;
        static std::mutex                   cached_leveleds_mutex;

    public:
        void                Refresh_Cache();

        Vector_t<Item_t>&   Items();
        Vector_t<Item_t>    Default_Items();
        Item_t              Null_Item();

    public:
        void On_Config_Open();
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_Filter_t : public Bases_Filter_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        Toggle_Type_e Toggle_Type();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_Options_t : public Bases_Options_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    class Leveled_Bases_Item_t : public Bases_Item_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        V::Variable_tt<Form_ID_t>& Leveled_Form_ID();

    public:
        Item_t                          Current_Item();
        Bool_t                          Current_Item(Item_t item);
        Item_t                          Previous_Item();
        Item_t                          Next_Item();

        Vector_t<some<Actor_Base_t*>>   Nested_Items();

        maybe<Actor_Base_t*>            Current_Nested_Item();
        maybe<Actor_Base_t*>            Previous_Nested_Item();
        maybe<Actor_Base_t*>            Next_Nested_Item();

    public:
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Page_Open_Item(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Page_Open_Bases(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Page_Open_Bases_Item(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Select_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Select_Bases(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Select_Bases_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Item(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Bases(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight_Bases_Item(Int_t option, Latent_Callback_i* lcallback);
    };

}}
