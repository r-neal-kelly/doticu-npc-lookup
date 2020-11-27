/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_main.h"
#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_bases_static.h"
#include "mcm_bases_dynamic.h"
#include "mcm_bases_leveled.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_loaded.h"
#include "mcm_references_spawned.h"

namespace doticu_npcl { namespace MCM {

    Main_t*             Main_t::Self()                  { return static_cast<Main_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t            Main_t::Class_Name()            { DEFINE_CLASS_NAME("doticu_npcl_mcm_main"); }
    V::Class_t*         Main_t::Class()                 { DEFINE_CLASS(); }

    Int_t Main_t::String_Comparator(const char* str_a, const char* str_b)
    {
        if (!str_a || !str_a[0]) {
            return Comparator_e::IS_UNORDERED;
        } else if (!str_b || !str_b[0]) {
            return Comparator_e::IS_ORDERED;
        } else if (str_a[0] == '0' && str_a[1] == 'x' && str_b[0] != '0' && str_b[1] != 'x') {
            return Comparator_e::IS_UNORDERED;
        } else if (str_a[0] != '0' && str_a[1] != 'x' && str_b[0] == '0' && str_b[1] == 'x') {
            return Comparator_e::IS_ORDERED;
        } else {
            return _stricmp(str_a, str_b);
        }
    }

    V::Object_t* Main_t::Object() { DEFINE_OBJECT(); }

    V::String_Variable_t* Main_t::Current_Page_Variable() { DEFINE_STRING_VARIABLE("p_current_page"); }

    String_t Main_t::Current_Page()
    {
        String_t current_page = Current_Page_Variable()->Value();
        if (!current_page) {
            current_page = DEFAULT_PAGE;
            Current_Page(current_page);
        }
        return current_page;
    }

    void Main_t::Current_Page(String_t current_page)
    {
        Current_Page_Variable()->Value(current_page);
    }

    Latent_Callback_i* Main_t::Create_Latent_Callback(V::Machine_t* machine, V::Stack_ID_t stack_id)
    {
        struct Callback : public Latent_Callback_i
        {
            V::Machine_t* machine;
            V::Stack_ID_t stack_id;
            Callback(V::Machine_t* machine, V::Stack_ID_t stack_id) :
                machine(machine), stack_id(stack_id)
            {
            }
            void operator()()
            {
                V::Variable_t none;
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

    void Main_t::Toggle_Either(V::Int_Variable_t* variable, Int_t option_a, Int_t option_b, Binary_e toggle)
    {
        Binary_e value = variable->Value();

        if (toggle == Binary_e::A) {
            if (value == Binary_e::A) {
                value = Binary_e::NONE;
            } else {
                value = Binary_e::A;
            }
        } else if (toggle == Binary_e::B) {
            if (value == Binary_e::B) {
                value = Binary_e::NONE;
            } else {
                value = Binary_e::B;
            }
        }

        variable->Value(value);
        Toggle_Option_Value(option_a, value == Binary_e::A, false);
        Toggle_Option_Value(option_b, value == Binary_e::B, true);
    }

    void Main_t::Toggle_Any(V::Int_Variable_t* variable, Int_t option_a, Int_t option_b, Binary_e toggle)
    {
        Binary_e value = variable->Value();

        if (toggle == Binary_e::A) {
            if (value == Binary_e::NONE) {
                value = Binary_e::A;
            } else if (value == Binary_e::BOTH) {
                value = Binary_e::B;
            } else if (value == Binary_e::A) {
                value = Binary_e::NONE;
            } else if (value == Binary_e::B) {
                value = Binary_e::BOTH;
            }
        } else if (toggle == Binary_e::B) {
            if (value == Binary_e::NONE) {
                value = Binary_e::B;
            } else if (value == Binary_e::BOTH) {
                value = Binary_e::A;
            } else if (value == Binary_e::A) {
                value = Binary_e::BOTH;
            } else if (value == Binary_e::B) {
                value = Binary_e::NONE;
            }
        }

        variable->Value(value);
        Toggle_Option_Value(option_a, value == Binary_e::A || value == Binary_e::BOTH, false);
        Toggle_Option_Value(option_b, value == Binary_e::B || value == Binary_e::BOTH, true);
    }

    static Bool_t Is_Same(const char* page_a, const char* page_b)
    {
        return skylib::CString_t::Is_Same(page_a, page_b, true);
    }

    void Main_t::On_Load()
    {
        Static_Bases_t::Self()->On_Load();
        Dynamic_Bases_t::Self()->On_Load();
        Leveled_Bases_t::Self()->On_Load();
        Loaded_References_t::Self()->On_Load();
        Spawned_References_t::Self()->On_Load();
    }

    void Main_t::On_Save()
    {
        Static_Bases_t::Self()->On_Save();
        Dynamic_Bases_t::Self()->On_Save();
        Leveled_Bases_t::Self()->On_Save();
        Loaded_References_t::Self()->On_Save();
        Spawned_References_t::Self()->On_Save();
    }

    Bool_t Main_t::On_Config_Open(V::Machine_t* machine, V::Stack_ID_t stack_id)
    {
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

        Mod_Name(MOD_NAME);

        Vector_t<String_t> pages;
        pages.reserve(5);
        pages.push_back(STATIC_BASES_PAGE);
        pages.push_back(DYNAMIC_BASES_PAGE);
        pages.push_back(LEVELED_BASES_PAGE);
        pages.push_back(LOADED_REFERENCES_PAGE);
        pages.push_back(SPAWNED_REFERENCES_PAGE);
        Pages(pages);

        Static_Bases_t::Self()->On_Config_Open();
        Dynamic_Bases_t::Self()->On_Config_Open();
        Leveled_Bases_t::Self()->On_Config_Open();
        Loaded_References_t::Self()->On_Config_Open();
        Spawned_References_t::Self()->On_Config_Open();

        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Config_Close(V::Machine_t* machine, V::Stack_ID_t stack_id)
    {
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

        Static_Bases_t::Self()->On_Config_Close();
        Dynamic_Bases_t::Self()->On_Config_Close();
        Leveled_Bases_t::Self()->On_Config_Close();
        Loaded_References_t::Self()->On_Config_Close();
        Spawned_References_t::Self()->On_Config_Close();

        Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Page_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, String_t current_page)
    {
        Bool_t is_refresh = true;
        if (!current_page) {
            current_page = Current_Page();
        } else {
            if (current_page != Current_Page()) {
                is_refresh = false;
                Current_Page(current_page);
            }
        }

        String_t page = current_page;
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Page_Open(is_refresh, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Page_Open(is_refresh, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Select(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Select(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Select(option, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Menu_Open(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Menu_Open(option, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Menu_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Int_t idx)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Open(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Slider_Open(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Slider_Open(option, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Slider_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Float_t value)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Slider_Accept(option, value, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Input_Accept(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, String_t value)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Input_Accept(option, value, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Keymap_Change(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Default(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Default(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Default(option, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    Bool_t Main_t::On_Option_Highlight(V::Machine_t* machine, V::Stack_ID_t stack_id, Int_t option)
    {
        String_t page = Current_Page();
        Latent_Callback_i* lcallback = Create_Latent_Callback(machine, stack_id);

             if (Is_Same(page, STATIC_BASES_PAGE))          Static_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, DYNAMIC_BASES_PAGE))         Dynamic_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, LEVELED_BASES_PAGE))         Leveled_Bases_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, LOADED_REFERENCES_PAGE))     Loaded_References_t::Self()->On_Option_Highlight(option, lcallback);
        else if (Is_Same(page, SPAWNED_REFERENCES_PAGE))    Spawned_References_t::Self()->On_Option_Highlight(option, lcallback);
        else                                                Destroy_Latent_Callback(lcallback);

        return true;
    }

    void Main_t::Register_Me(V::Machine_t* machine)
    {
        Config_Base_t::Register_Me(machine);

        #define LMETHOD(FUNC_NAME_, ARG_COUNT_, RETURN_TYPE_, METHOD_, ...) \
        M                                                                   \
            BIND_LATENT_METHOD(machine, Class_Name(), Main_t,               \
                               FUNC_NAME_, ARG_COUNT_,                      \
                               RETURN_TYPE_, METHOD_, __VA_ARGS__);         \
        W

        LMETHOD("OnConfigOpen", 0, void, On_Config_Open);
        LMETHOD("OnConfigClose", 0, void, On_Config_Close);
        LMETHOD("OnPageReset", 1, void, On_Page_Open, String_t);
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
