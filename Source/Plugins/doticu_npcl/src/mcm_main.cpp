/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusArgs.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_macros.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    String_t Main_t::Class_Name() { DEFINE_CLASS_NAME("doticu_npcl_mcm"); }
    Class_t* Main_t::Class() { DEFINE_CLASS(); }
    Object_t* Main_t::Object() { DEFINE_OBJECT(); }

    void Main_t::Return_Latent(Latent_Callback_i* lcallback)
    {
        if (lcallback) {
            lcallback->operator()();
            delete lcallback;
        }
    }

    Bool_t Main_t::On_Build_Page(Machine_t* machine, Stack_ID_t stack_id, String_t current_page)
    {
        struct Callback : public Latent_Callback_i {
            Machine_t* machine;
            Stack_ID_t stack_id;
            Callback(Machine_t* machine, Stack_ID_t stack_id) :
                machine(machine), stack_id(stack_id)
            {
            }
            void operator()()
            {
                Variable_t none;
                machine->Return_Latent_Function(stack_id, &none);
            }
        };
        Latent_Callback_i* lcallback = new Callback(machine, stack_id);

        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return skylib::CString_t::Is_Same(current_page, page, true);
        };

        if (Is_Page(BASES_PAGE)) {
            Title_Text("This is the Bases Page.");
            Return_Latent(lcallback);
        } else if (Is_Page(REFERENCES_PAGE)) {
            Title_Text("This is the References Page.");
            Return_Latent(lcallback);
        } else {
            Return_Latent(lcallback);
        }

        return true;
    }

    Bool_t Main_t::On_Option_Select(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Menu_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Menu_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t idx)
    {

    }

    Bool_t Main_t::On_Option_Slider_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Slider_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Float_t value)
    {

    }

    Bool_t Main_t::On_Option_Input_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, String_t value)
    {

    }

    Bool_t Main_t::On_Option_Keymap_Change(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod)
    {

    }

    Bool_t Main_t::On_Option_Default(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Highlight(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {

    }

    void Main_t::Register_Me(Machine_t* machine)
    {
        #define LMETHOD(FUNC_NAME_, ARG_COUNT_, RETURN_TYPE_, METHOD_, ...) \
        M                                                                   \
            BIND_LATENT_METHOD(machine, Class_Name(), Main_t,               \
                               FUNC_NAME_, ARG_COUNT_,                      \
                               RETURN_TYPE_, METHOD_, __VA_ARGS__);         \
        W

        LMETHOD("OnPageReset", 1, void, On_Build_Page, String_t);

        #undef LMETHOD

    }

}}
