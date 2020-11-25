/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

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
        using Item_t = Leveled_Actor_Base_t*;

    public:
        static String_t             Class_Name();
        static V::Class_t*          Class();
        V::Object_t*                Object();

        static Leveled_Bases_t*     Self();
        Leveled_Bases_List_t*       List();
        Leveled_Bases_Filter_t*     Filter();
        Leveled_Bases_Options_t*    Options();
        Leveled_Bases_Item_t*       Item();
    };

    class Leveled_Bases_t : public Bases_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
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

    class Leveled_Bases_List_t : public Bases_List_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        static Bool_t               do_update_items;
        static Vector_t<Item_t>     read;
        static Vector_t<Item_t>     write;
        static Vector_t<Item_t>*    items;

    public:
        String_t            Title(Int_t item_count, Int_t page_index, Int_t page_count);
        Vector_t<Item_t>&   Items();
        Vector_t<Item_t>    Default_Items();
        Item_t              Option_To_Item(Int_t option);
        void                Clear();

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

    class Leveled_Bases_Filter_t : public Bases_Filter_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        Vector_t<Item_t>*   Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write);
        void                Clear();

        Vector_t<String_t>  Selectable_Mods();
        Vector_t<String_t>  Selectable_Races();
        Vector_t<String_t>  Selectable_Bases();
        Vector_t<String_t>  Selectable_Relations();

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

    class Leveled_Bases_Options_t : public Bases_Options_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        void Reset();

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

    class Leveled_Bases_Item_t : public Bases_Item_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>
    {
    public:
        V::Int_Variable_t* Leveled_Form_ID_Variable();

    public:
        Form_ID_t   Leveled_Form_ID();
        void        Leveled_Form_ID(Form_ID_t value);

    public:
        Item_t  Current_Item();
        Item_t  Previous_Item();
        Item_t  Next_Item();

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
