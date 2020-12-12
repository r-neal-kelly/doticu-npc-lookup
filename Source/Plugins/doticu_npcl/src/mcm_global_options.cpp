/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/translations.h"

#include "doticu_skylib/virtual_macros.h"

#include "doticu_mcmlib/config_base_macros.h"
#include "doticu_mcmlib/config_manager.h"

#include "consts.h"
#include "mcm_global_options.h"

namespace doticu_npcl { namespace MCM {

    String_t            Global_Options_t::Class_Name()                          { DEFINE_CLASS_NAME("doticu_npcl_mcm_global_options"); }
    V::Class_t*         Global_Options_t::Class()                               { DEFINE_CLASS(); }
    V::Object_t*        Global_Options_t::Object()                              { DEFINE_OBJECT(); }
    Global_Options_t*   Global_Options_t::Self()                                { return static_cast<Global_Options_t*>(Consts_t::NPCL_MCM_Quest()); }

    Int_t&              Global_Options_t::Reset_Option()                        { DEFINE_OPTION(); }
    Int_t&              Global_Options_t::Prioritize_MCM_Menu_Option()          { DEFINE_OPTION(); }
    Int_t&              Global_Options_t::Translate_Page_Titles_Option()        { DEFINE_OPTION(); }

    V::Bool_Variable_t* Global_Options_t::Prioritize_MCM_Menu_Variable()        { DEFINE_BOOL_VARIABLE("p_prioritize_mcm_menu"); }
    V::Bool_Variable_t* Global_Options_t::Translate_Page_Titles_Variable()      { DEFINE_BOOL_VARIABLE("p_translate_page_titles"); }

    Bool_t              Global_Options_t::Prioritize_MCM_Menu()                 { return Prioritize_MCM_Menu_Variable()->Value(); }
    void                Global_Options_t::Prioritize_MCM_Menu(Bool_t value)     { Prioritize_MCM_Menu_Variable()->Value(value); Update_MCM_Menu_Name(); }
    Bool_t              Global_Options_t::Translate_Page_Titles()               { return Translate_Page_Titles_Variable()->Value(); }
    void                Global_Options_t::Translate_Page_Titles(Bool_t value)   { Translate_Page_Titles_Variable()->Value(value); }

    void Global_Options_t::Reset()
    {
        Prioritize_MCM_Menu(false);
        Translate_Page_Titles(false);
    }

    void Global_Options_t::Update_MCM_Menu_Name()
    {
        if (Prioritize_MCM_Menu()) {
            mcmlib::Config_Manager_t::Self()->Change_Config_Base_Name(Main_t::Self(), Main_t::PRIORITIZED_MOD_NAME);
        } else {
            mcmlib::Config_Manager_t::Self()->Change_Config_Base_Name(Main_t::Self(), Main_t::UNPRIORITIZED_MOD_NAME);
        }
    }

    void Global_Options_t::On_Init()
    {
        Main_t::Self()->Mod_Name(Main_t::UNPRIORITIZED_MOD_NAME);

        if (skylib::Translations_t::Are_English()) {
            Translate_Page_Titles(false);
        }
    }

    void Global_Options_t::On_Load()
    {
        Update_MCM_Menu_Name();

        if (skylib::Translations_t::Are_English()) {
            Translate_Page_Titles(false);
        }
    }

    void Global_Options_t::On_Save()
    {
    }

    void Global_Options_t::On_Config_Open()
    {
    }

    void Global_Options_t::On_Config_Close()
    {
    }

    void Global_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        mcm->Title_Text(Main_t::GLOBAL_OPTIONS);

        mcm->Add_Empty_Option();
        Reset_Option() = mcm->Add_Text_Option(Main_t::CENTER_RESET, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::_NONE_);
        mcm->Add_Header_Option(Main_t::_NONE_);

        Prioritize_MCM_Menu_Option() = mcm->Add_Toggle_Option(Main_t::PRIORITIZE_MCM_MENU, Prioritize_MCM_Menu(), Flag_e::NONE);
        Translate_Page_Titles_Option() = mcm->Add_Toggle_Option(Main_t::TRANSLATE_PAGE_TITLES, Translate_Page_Titles(), Flag_e::NONE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Reset_Option()) {
            mcm->Disable_Option(option);
            Reset();
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Prioritize_MCM_Menu_Option()) {
            Bool_t value = Prioritize_MCM_Menu();
            Prioritize_MCM_Menu(!value);
            mcm->Toggle_Option_Value(option, !value);
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Translate_Page_Titles_Option()) {
            if (skylib::Translations_t::Are_English()) {
                class Callback_t : public Callback_i<Bool_t>
                {
                public:
                    Main_t* mcm;
                    Latent_Callback_i* lcallback;
                    Callback_t(Main_t* mcm, Latent_Callback_i* lcallback) :
                        mcm(mcm), lcallback(lcallback)
                    {
                    }
                    void operator()(Bool_t)
                    {
                        mcm->Destroy_Latent_Callback(lcallback);
                    }
                };
                mcm->Flicker_Option(option);
                mcm->Show_Message(
                    "This option is available for non-English translations only.",
                    false,
                    Main_t::YES,
                    Main_t::NO,
                    new Callback_t(mcm, lcallback)
                );
            } else {
                Bool_t value = Translate_Page_Titles();
                Translate_Page_Titles(!value);
                mcm->Toggle_Option_Value(option, !value);
                mcm->Destroy_Latent_Callback(lcallback);
            }

        } else {
            mcm->Destroy_Latent_Callback(lcallback);
        }
    }

    void Global_Options_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Global_Options_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Reset_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_RESET_OPTIONS);

        } else if (option == Prioritize_MCM_Menu_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_PRIORITIZE_MCM_MENU);
        } else if (option == Translate_Page_Titles_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_TRANSLATE_PAGE_TITLES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}
