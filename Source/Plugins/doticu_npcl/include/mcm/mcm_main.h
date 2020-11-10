/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/papyrus/virtual.h"

namespace doticu_npcl { namespace MCM {

    using namespace doticu_skylib;
    using namespace doticu_skylib::Papyrus;

    class Main_t {
    public:
        static constexpr const char* MOD_NAME           = " NPC Lookup ";
        static constexpr const char* BASES_PAGE         = " Bases ";
        static constexpr const char* REFERENCES_PAGE    = " References ";

    public:
        Bool_t On_Build_Page(Virtual_Machine_t* vm, Stack_ID_t stack_id, String_t current_page);
        Bool_t On_Option_Select(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Menu_Open(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Menu_Accept(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option, Int_t idx);
        void On_Option_Slider_Open(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Slider_Accept(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option, Float_t value);
        void On_Option_Input_Accept(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option);
        void On_Option_Highlight(Virtual_Machine_t* vm, Stack_ID_t stack_id, Int_t option);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
