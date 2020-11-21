/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    using Sex_e             = skylib::Sex_e;
    using Relation_e        = skylib::Relation_e;

    using CString_t         = skylib::CString_t;

    using Mod_t             = skylib::Mod_t;
    using Worldspace_t      = skylib::Worldspace_t;
    using Location_t        = skylib::Location_t;
    using Cell_t            = skylib::Cell_t;
    using Race_t            = skylib::Race_t;
    using Actor_Base_t      = skylib::Actor_Base_t;
    using Actor_t           = skylib::Actor_t;
    using Loaded_Actor_t    = skylib::Loaded_Actor_t;
    using Form_ID_t         = skylib::Form_ID_t;

    class References_List_t;
    class References_Filter_t;
    class References_Options_t;
    class References_Item_t;

    class References_t : public skylib::Quest_t {
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

        static References_t*    Self();
        static String_t         Class_Name();
        static V::Class_t*      Class();

    public:
        V::Object_t*            Object();

        V::String_Variable_t*   Current_View_Variable();

    public:
        View_e      Current_View();
        void        Current_View(View_e value);

    public:
        References_List_t*      List();
        References_Filter_t*    Filter();
        References_Options_t*   Options();
        References_Item_t*      Item();

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
