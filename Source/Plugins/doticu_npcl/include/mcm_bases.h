/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/relation.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    using Sex_e         = skylib::Sex_e;
    using Relation_e    = skylib::Relation_e;
    using Actor_Base_t  = skylib::Actor_Base_t;

    class Bases_List_t;
    class Bases_Filter_t;
    class Bases_Options_t;
    class Bases_Item_t;

    class Bases_t : public skylib::Quest_t {
    public:
        static constexpr const char*    LIST_VIEW       = "list";
        static constexpr const char*    FILTER_VIEW     = "filter";
        static constexpr const char*    OPTIONS_VIEW    = "options";
        static constexpr const char*    ITEM_VIEW       = "item";

        class View_e : public skylib::Enum_t<skylib::Word_t>
        {
        public:
            enum
            {
                LIST,
                FILTER,
                OPTIONS,
                ITEM,
            };
            using Enum_t::Enum_t;
        };

        static Bases_t*     Self();
        static String_t     Class_Name();
        static V::Class_t*  Class();

    public:
        V::Object_t*            Object();

        V::String_Variable_t*   Current_View_Variable();

    public:
        View_e  Current_View();
        void    Current_View(View_e value);

    public:
        Bases_List_t*       List();
        Bases_Filter_t*     Filter();
        Bases_Options_t*    Options();
        Bases_Item_t*       Item();

    public:
        void On_Config_Open();
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

    public:
        static void Register_Me(V::Machine_t* machine);
    };

}}
