/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_machine.h"

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    class Bases_t : public skylib::Quest_t {
    public:
        static Bases_t* Self();
        static String_t Class_Name();
        static Class_t* Class();

    public:
        Object_t* Object();

        String_Variable_t*  Current_View_Variable();

        Int_Variable_t*     Filter_Option_Variable();

        Int_Variable_t*     Name_Option_Variable();
        String_Variable_t*  Name_Argument_Variable();

        Int_Variable_t*     Mod_Option_Variable();
        String_Variable_t*  Mod_Argument_Variable();
        String_Variable_t*  Mod_View_Variable();

        Int_Variable_t*     Sex_Option_Variable();
        Int_Variable_t*     Sex_Argument_Variable();
        String_Variable_t*  Sex_View_Variable();

        Int_Variable_t*     Race_Option_Variable();
        String_Variable_t*  Race_Argument_Variable();
        String_Variable_t*  Race_View_Variable();

        Int_Variable_t*     Relationship_Option_Variable();
        Int_Variable_t*     Relationship_Argument_Variable();
        String_Variable_t*  Relationship_View_Variable();

        Int_Variable_t*     Is_Unique_Option_Variable();
        Int_Variable_t*     Is_Generic_Option_Variable();
        Int_Variable_t*     Unique_Generic_Ternary_Variable();

    public:
        void On_Build_Page(Latent_Callback_i* lcallback);
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
        static void Register_Me(Machine_t* machine);
    };

}}
