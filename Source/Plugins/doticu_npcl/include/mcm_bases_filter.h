/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class Bases_Filter_t : public Bases_t
    {
    public:
        V::Int_Variable_t*      Back_Option_Variable();
        V::Int_Variable_t*      Clear_Option_Variable();

        V::Int_Variable_t*      Mod_Search_Option_Variable();
        V::Int_Variable_t*      Mod_Select_Option_Variable();
        V::Int_Variable_t*      Mod_Negate_Option_Variable();
        V::String_Variable_t*   Mod_Argument_Variable();
        V::Bool_Variable_t*     Mod_Do_Negate_Variable();

        V::Int_Variable_t*      Race_Search_Option_Variable();
        V::Int_Variable_t*      Race_Select_Option_Variable();
        V::Int_Variable_t*      Race_Negate_Option_Variable();
        V::String_Variable_t*   Race_Argument_Variable();
        V::Bool_Variable_t*     Race_Do_Negate_Variable();

        V::Int_Variable_t*      Name_Search_Option_Variable();
        V::Int_Variable_t*      Name_Select_Option_Variable();
        V::Int_Variable_t*      Name_Negate_Option_Variable();
        V::String_Variable_t*   Name_Argument_Variable();
        V::Bool_Variable_t*     Name_Do_Negate_Variable();

        V::Int_Variable_t*      Relation_Select_Option_Variable();
        V::Int_Variable_t*      Relation_Negate_Option_Variable();
        V::Int_Variable_t*      Relation_Argument_Variable();
        V::Bool_Variable_t*     Relation_Do_Negate_Variable();

        V::Int_Variable_t*      Is_Male_Option_Variable();
        V::Int_Variable_t*      Is_Female_Option_Variable();
        V::Int_Variable_t*      Male_Female_Ternary_Variable();

        V::Int_Variable_t*      Is_Unique_Option_Variable();
        V::Int_Variable_t*      Is_Generic_Option_Variable();
        V::Int_Variable_t*      Unique_Generic_Ternary_Variable();

    public:
        String_t    Mod_Argument();
        void        Mod_Argument(String_t value);
        Bool_t      Mod_Do_Negate();
        void        Mod_Do_Negate(Bool_t value);

        String_t    Race_Argument();
        void        Race_Argument(String_t value);
        Bool_t      Race_Do_Negate();
        void        Race_Do_Negate(Bool_t value);

        String_t    Name_Argument();
        void        Name_Argument(String_t value);
        Bool_t      Name_Do_Negate();
        void        Name_Do_Negate(Bool_t value);

        Relation_e  Relation_Argument();
        void        Relation_Argument(Relation_e value);
        String_t    Relation_Argument_String();
        void        Relation_Argument_String(String_t value);
        Bool_t      Relation_Do_Negate();
        void        Relation_Do_Negate(Bool_t value);

        Ternary_e   Male_Female_Ternary();
        void        Male_Female_Ternary(Ternary_e value);

        Ternary_e   Unique_Generic_Ternary();
        void        Unique_Generic_Ternary(Ternary_e value);

    public:
        Vector_t<Actor_Base_t*>*    Execute(Vector_t<Actor_Base_t*>* read, Vector_t<Actor_Base_t*>* write);
        void                        Clear();

        Vector_t<String_t>          Selectable_Mods();
        Vector_t<String_t>          Selectable_Races();
        Vector_t<String_t>          Selectable_Names();
        Vector_t<String_t>          Selectable_Relations();

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
