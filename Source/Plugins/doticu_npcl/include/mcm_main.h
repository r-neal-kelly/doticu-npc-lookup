/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_machine.h"

#include "doticu_mcmlib/config_base.h"

namespace doticu_npcl { namespace MCM {

    using Machine_t = skylib::Virtual::Machine_t;
    using Stack_ID_t = skylib::Virtual::Stack_ID_t;

    class Main_t : mcmlib::Config_Base_t {
    public:
        static constexpr const char* MOD_NAME           = " NPC Lookup ";
        static constexpr const char* BASES_PAGE         = " Bases ";
        static constexpr const char* REFERENCES_PAGE    = " References ";

    public:
        Bool_t On_Build_Page(Machine_t* vm, Stack_ID_t stack_id, String_t current_page);
        Bool_t On_Option_Select(Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Menu_Open(Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Menu_Accept(Machine_t* vm, Stack_ID_t stack_id, Int_t option, Int_t idx);
        void On_Option_Slider_Open(Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Slider_Accept(Machine_t* vm, Stack_ID_t stack_id, Int_t option, Float_t value);
        void On_Option_Input_Accept(Machine_t* vm, Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(Machine_t* vm, Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Highlight(Machine_t* vm, Stack_ID_t stack_id, Int_t option);

    public:
        static void Register_Me(Machine_t* vm);
    };

}}
