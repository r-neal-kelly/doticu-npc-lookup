/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusArgs.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_main.h"
#include "mcm_bases.h"
#include "mcm_leveled_bases.h"
#include "mcm_references.h"

namespace doticu_npcl { namespace MCM {

    Main_t*             Main_t::Self()                  { return static_cast<Main_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t            Main_t::Class_Name()            { DEFINE_CLASS_NAME("doticu_npcl_mcm"); }
    Class_t*            Main_t::Class()                 { DEFINE_CLASS(); }
    Object_t*           Main_t::Object()                { DEFINE_OBJECT(); }

    String_Variable_t*  Main_t::Current_Page_Variable() { DEFINE_STRING_VARIABLE("p_current_page"); }

    String_t Main_t::Current_Page()
    {
        String_t current_page = Current_Page_Variable()->Value();
        if (!current_page || !current_page.data || !current_page.data[0]) {
            current_page = DEFAULT_PAGE;
            Current_Page_Variable()->Value(current_page);
        }
        return current_page;
    }

    void Main_t::Current_Page(String_t current_page)
    {
        Current_Page_Variable()->Value(current_page);
    }

    Latent_Callback_i* Main_t::Create_Latent_Callback(Machine_t* machine, Stack_ID_t stack_id)
    {
        struct Callback : public Latent_Callback_i
        {
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
        return new Callback(machine, stack_id);
    }

    void Main_t::Destroy_Latent_Callback(Latent_Callback_i* lcallback)
    {
        if (lcallback) {
            lcallback->operator()();
            delete lcallback;
        }
    }

    static Bool_t Is_Same(const char* page_a, const char* page_b)
    {
        return skylib::CString_t::Is_Same(page_a, page_b, true);
    }

    Bool_t Main_t::On_Build_Page(Machine_t* machine, Stack_ID_t stack_id, String_t current_page)
    {
        String_t page = current_page;
        if (!page || !page.data || !page.data[0]) {
            page = Current_Page();
        } else {
            Current_Page(page);
        }

        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Build_Page(lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Build_Page(lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Build_Page(lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Select(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Select(option, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Menu_Open(option, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t idx)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Open(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Slider_Open(option, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Float_t value)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Input_Accept(Machine_t* machine, Stack_ID_t stack_id, Int_t option, String_t value)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Keymap_Change(Machine_t* machine, Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Default(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Default(option, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Highlight(Machine_t* machine, Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, BASES_PAGE))         Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE)) Leveled_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, REFERENCES_PAGE))    References_t::Self()->On_Option_Highlight(option, lcallback);
        else                                        Destroy_Latent_Callback(lcallback);

        return true;
    }

    void Main_t::Register_Me(Machine_t* machine)
    {
        Config_Base_t::Register_Me(machine);

        #define LMETHOD(FUNC_NAME_, ARG_COUNT_, RETURN_TYPE_, METHOD_, ...) \
        M                                                                   \
            BIND_LATENT_METHOD(machine, Class_Name(), Main_t,               \
                               FUNC_NAME_, ARG_COUNT_,                      \
                               RETURN_TYPE_, METHOD_, __VA_ARGS__);         \
        W

        LMETHOD("OnPageReset", 1, void, On_Build_Page, String_t);
        LMETHOD("OnOptionSelect", 1, void, On_Option_Select, Int_t);
        LMETHOD("OnOptionMenuOpen", 1, void, On_Option_Menu_Open, Int_t);
        LMETHOD("OnOptionMenuAccept", 2, void, On_Option_Menu_Accept, Int_t, Int_t);
        LMETHOD("OnOptionSliderOpen", 1, void, On_Option_Slider_Open, Int_t);
        LMETHOD("OnOptionSliderAccept", 2, void, On_Option_Slider_Accept, Int_t, Float_t);
        LMETHOD("OnOptionInputAccept", 2, void, On_Option_Input_Accept, Int_t, String_t);
        LMETHOD("OnOptionKeymapChange", 4, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        LMETHOD("OnOptionDefault", 1, void, On_Option_Default, Int_t);
        LMETHOD("OnOptionHighlight", 1, void, On_Option_Highlight, Int_t);

        #undef LMETHOD
    }

}}
