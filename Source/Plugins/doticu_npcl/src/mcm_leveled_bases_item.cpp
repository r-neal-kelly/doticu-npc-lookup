/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_leveled_bases_list.h"
#include "mcm_leveled_bases_filter.h"
#include "mcm_leveled_bases_options.h"
#include "mcm_leveled_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using Actor_t       = skylib::Actor_t;
    using Actor_Value_e = skylib::Actor_Value_e;
    using Game_t        = skylib::Game_t;

    V::Int_Variable_t*  Leveled_Bases_Item_t::Back_Option_Variable()                { DEFINE_INT_VARIABLE("p_item_back_option"); }
    V::Int_Variable_t*  Leveled_Bases_Item_t::Previous_Option_Variable()            { DEFINE_INT_VARIABLE("p_item_previous_option"); }
    V::Int_Variable_t*  Leveled_Bases_Item_t::Next_Option_Variable()                { DEFINE_INT_VARIABLE("p_item_next_option"); }
    V::Int_Variable_t*  Leveled_Bases_Item_t::Spawn_Option_Variable()               { DEFINE_INT_VARIABLE("p_item_spawn_option"); }
    V::Int_Variable_t*  Leveled_Bases_Item_t::Leveled_Actor_Base_Form_ID_Variable() { DEFINE_INT_VARIABLE("p_item_leveled_actor_base_form_id"); }

    Form_ID_t Leveled_Bases_Item_t::Leveled_Actor_Base_Form_ID()
    {
        return Leveled_Actor_Base_Form_ID_Variable()->Value();
    }

    void Leveled_Bases_Item_t::Leveled_Actor_Base_Form_ID(Form_ID_t value)
    {
        Leveled_Actor_Base_Form_ID_Variable()->Value(value);
    }

    Leveled_Actor_Base_t* Leveled_Bases_Item_t::Current_Item()
    {
        Leveled_Actor_Base_t* item = static_cast<Leveled_Actor_Base_t*>(Game_t::Form(Leveled_Actor_Base_Form_ID()));
        if (item && List()->Items().Has(item)) {
            return item;
        } else {
            return nullptr;
        }
    }

    Leveled_Actor_Base_t* Leveled_Bases_Item_t::Previous_Item()
    {
        Leveled_Actor_Base_t* item = static_cast<Leveled_Actor_Base_t*>(Game_t::Form(Leveled_Actor_Base_Form_ID()));
        if (item) {
            Vector_t<Leveled_Actor_Base_t*>& items = List()->Items();
            Index_t idx = items.Index_Of(item);
            if (idx > -1) {
                if (idx == 0) {
                    idx = items.size() - 1;
                } else {
                    idx -= 1;
                }
                return items[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Leveled_Actor_Base_t* Leveled_Bases_Item_t::Next_Item()
    {
        Leveled_Actor_Base_t* item = static_cast<Leveled_Actor_Base_t*>(Game_t::Form(Leveled_Actor_Base_Form_ID()));
        if (item) {
            Vector_t<Leveled_Actor_Base_t*>& items = List()->Items();
            Index_t idx = items.Index_Of(item);
            if (idx > -1) {
                if (idx == items.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return items[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Leveled_Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Leveled_Actor_Base_t* item = Current_Item();
        if (item) {
            mcm->Title_Text(std::string(" Leveled Base: ") + item->Any_Name().data);

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Back_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::BACK_LABEL, ""));
            Spawn_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::SPAWN_LABEL, ""));
            if (List()->Items().size() > 1) {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, ""));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, ""));
            } else {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "", Flag_e::DISABLE));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "", Flag_e::DISABLE));
            }

            mcm->Add_Header_Option(" Leveled Base ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + item->Leveled_Name().data, "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + item->Form_ID_String().data, "");

            auto Is_Odd_Option = [&mcm]()->Bool_t
            {
                return skylib::Is_Odd(mcm->Cursor_Position());
            };

            Vector_t<String_t> mod_names = item->Mod_Names();
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
            List()->do_update_items = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Spawn_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            Leveled_Actor_Base_t* item = Current_Item();
            if (item && item->Is_Valid()) {
                Actor_t* actor = static_cast<Actor_t*>
                    (skylib::Reference_t::Create(item, 1, Consts_t::Skyrim_Player_Actor(), true, false));
                if (actor) {
                    if (Options()->Do_Uncombative_Spawns()) {
                        actor->Set_Actor_Value(Actor_Value_e::AGGRESSION, 0.0f);
                    }
                }
            }
        } else if (option == Previous_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Leveled_Actor_Base_t* item = Previous_Item();
            if (item) {
                Leveled_Actor_Base_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Leveled_Actor_Base_t* item = Next_Item();
            if (item) {
                Leveled_Actor_Base_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
