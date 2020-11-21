/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/virtual_macros.h"

#include "mcm_bases_list.h"
#include "mcm_bases_filter.h"
#include "mcm_bases_options.h"
#include "mcm_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using Game_t = skylib::Game_t;
    using Race_t = skylib::Race_t;

    V::Int_Variable_t*  Bases_Item_t::Back_Option_Variable()        { DEFINE_INT_VARIABLE("p_item_back_option"); }
    V::Int_Variable_t*  Bases_Item_t::Previous_Option_Variable()    { DEFINE_INT_VARIABLE("p_item_previous_option"); }
    V::Int_Variable_t*  Bases_Item_t::Next_Option_Variable()        { DEFINE_INT_VARIABLE("p_item_next_option"); }
    V::Int_Variable_t*  Bases_Item_t::Actor_Base_Form_ID_Variable() { DEFINE_INT_VARIABLE("p_item_actor_base_form_id"); }

    Form_ID_t Bases_Item_t::Actor_Base_Form_ID()
    {
        return Actor_Base_Form_ID_Variable()->Value();
    }

    void Bases_Item_t::Actor_Base_Form_ID(Form_ID_t value)
    {
        Actor_Base_Form_ID_Variable()->Value(value);
    }

    Actor_Base_t* Bases_Item_t::Current_Actor_Base()
    {
        Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(Game_t::Form(Actor_Base_Form_ID()));
        if (actor_base && List()->Actor_Bases().Has(actor_base)) {
            return actor_base;
        } else {
            return nullptr;
        }
    }

    Actor_Base_t* Bases_Item_t::Previous_Actor_Base()
    {
        Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(Game_t::Form(Actor_Base_Form_ID()));
        if (actor_base) {
            Vector_t<Actor_Base_t*>& actor_bases = List()->Actor_Bases();
            Index_t idx = actor_bases.Index_Of(actor_base);
            if (idx > -1) {
                if (idx == 0) {
                    idx = actor_bases.size() - 1;
                } else {
                    idx -= 1;
                }
                return actor_bases[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Actor_Base_t* Bases_Item_t::Next_Actor_Base()
    {
        Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(Game_t::Form(Actor_Base_Form_ID()));
        if (actor_base) {
            Vector_t<Actor_Base_t*>& actor_bases = List()->Actor_Bases();
            Index_t idx = actor_bases.Index_Of(actor_base);
            if (idx > -1) {
                if (idx == actor_bases.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return actor_bases[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Actor_Base_t* actor_base = Current_Actor_Base();
        if (actor_base) {
            mcm->Title_Text(std::string(" Bases: ") + actor_base->Any_Name().data);

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Back_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::BACK_LABEL, ""));
            mcm->Add_Empty_Option();
            if (List()->Actor_Bases().size() > 1) {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, ""));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, ""));
            } else {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "", Flag_e::DISABLE));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "", Flag_e::DISABLE));
            }

            mcm->Add_Header_Option(" Base ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + actor_base->Name(), "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + actor_base->Form_ID_String().data, "");

            Race_t* race = actor_base->Race();
            if (race) {
                mcm->Add_Header_Option(" Race ");
                mcm->Add_Header_Option("");
                mcm->Add_Text_Option(std::string(" Name: ") + race->Name(), "");
                mcm->Add_Text_Option(std::string(" Editor ID: ") + race->Get_Editor_ID(), "");
                mcm->Add_Text_Option(std::string(" Form ID: ") + race->Form_ID_String().data, "");
                mcm->Add_Empty_Option();
            }

            auto Is_Odd_Option = [&mcm]()->Bool_t
            {
                return skylib::Is_Odd(mcm->Cursor_Position());
            };

            Vector_t<String_t> mod_names = actor_base->Mod_Names();
            size_t mod_name_count = mod_names.size();
            if (mod_name_count > 0 && mcm->Can_Add_Options(2 + mod_name_count)) {
                mcm->Add_Header_Option(" Mods ");
                mcm->Add_Header_Option("");
                for (Index_t idx = 0, end = mod_name_count; idx < end; idx += 1) {
                    String_t mod_name = mod_names[idx];
                    mcm->Add_Text_Option(mod_name, "");
                }
                if (Is_Odd_Option()) {
                    mcm->Add_Empty_Option();
                }
            }
        } else {
            List()->do_update_actor_bases = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_actor_bases = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Previous_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Actor_Base_t* actor_base = Previous_Actor_Base();
            if (actor_base) {
                Actor_Base_Form_ID(actor_base->form_id);
            } else {
                List()->do_update_actor_bases = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Actor_Base_t* actor_base = Next_Actor_Base();
            if (actor_base) {
                Actor_Base_Form_ID(actor_base->form_id);
            } else {
                List()->do_update_actor_bases = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
