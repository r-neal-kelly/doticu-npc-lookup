/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "mcm_references_list.h"
#include "mcm_references_filter.h"
#include "mcm_references_options.h"
#include "mcm_references_item.h"

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  References_Item_t::Back_Option_Variable()       { DEFINE_INT_VARIABLE("p_item_back_option"); }
    V::Int_Variable_t*  References_Item_t::Previous_Option_Variable()   { DEFINE_INT_VARIABLE("p_item_previous_option"); }
    V::Int_Variable_t*  References_Item_t::Next_Option_Variable()       { DEFINE_INT_VARIABLE("p_item_next_option"); }
    V::Int_Variable_t*  References_Item_t::Actor_Form_ID_Variable()     { DEFINE_INT_VARIABLE("p_item_actor_form_id"); }
    V::Int_Variable_t*  References_Item_t::Cell_Form_ID_Variable()      { DEFINE_INT_VARIABLE("p_item_cell_form_id"); }

    Form_ID_t References_Item_t::Actor_Form_ID()
    {
        return Actor_Form_ID_Variable()->Value();
    }

    void References_Item_t::Actor_Form_ID(Form_ID_t value)
    {
        Actor_Form_ID_Variable()->Value(value);
    }

    Form_ID_t References_Item_t::Cell_Form_ID()
    {
        return Cell_Form_ID_Variable()->Value();
    }

    void References_Item_t::Cell_Form_ID(Form_ID_t value)
    {
        Cell_Form_ID_Variable()->Value(value);
    }

    Loaded_Actor_t References_Item_t::Current_Loaded_Actor()
    {
        Loaded_Actor_t loaded_actor(Actor_Form_ID(), Cell_Form_ID());
        if (loaded_actor.Is_Valid() && List()->Loaded_Actors().Has(loaded_actor)) {
            return std::move(loaded_actor);
        } else {
            return std::move(Loaded_Actor_t());
        }
    }

    Loaded_Actor_t References_Item_t::Previous_Loaded_Actor()
    {
        Loaded_Actor_t loaded_actor(Actor_Form_ID(), Cell_Form_ID());
        if (loaded_actor.Is_Valid()) {
            Vector_t<Loaded_Actor_t>& loaded_actors = List()->Loaded_Actors();
            Index_t idx = loaded_actors.Index_Of(loaded_actor);
            if (idx > -1) {
                if (idx == 0) {
                    idx = loaded_actors.size() - 1;
                } else {
                    idx -= 1;
                }
                return loaded_actors[idx];
            } else {
                return std::move(Loaded_Actor_t());
            }
        } else {
            return std::move(Loaded_Actor_t());
        }
    }

    Loaded_Actor_t References_Item_t::Next_Loaded_Actor()
    {
        Loaded_Actor_t loaded_actor(Actor_Form_ID(), Cell_Form_ID());
        if (loaded_actor.Is_Valid()) {
            Vector_t<Loaded_Actor_t>& loaded_actors = List()->Loaded_Actors();
            Index_t idx = loaded_actors.Index_Of(loaded_actor);
            if (idx > -1) {
                if (idx == loaded_actors.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return loaded_actors[idx];
            } else {
                return std::move(Loaded_Actor_t());
            }
        } else {
            return std::move(Loaded_Actor_t());
        }
    }

    void References_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Loaded_Actor_t loaded_actor = Current_Loaded_Actor();
        if (loaded_actor.Is_Valid()) {
            mcm->Title_Text(std::string(" Reference: ") + loaded_actor.actor->Any_Name().data);

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Back_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::BACK_LABEL, ""));
            mcm->Add_Empty_Option();
            if (List()->Loaded_Actors().size() > 1) {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, ""));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, ""));
            } else {
                Previous_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "", Flag_e::DISABLE));
                Next_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "", Flag_e::DISABLE));
            }

            mcm->Add_Header_Option(" Reference ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + loaded_actor.actor->Name(), "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + loaded_actor.actor->Form_ID_String().data, "");

            mcm->Add_Header_Option(" Cell ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + loaded_actor.cell->Name(), "");
            mcm->Add_Text_Option(std::string(" Editor ID: ") + loaded_actor.cell->Get_Editor_ID(), "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + loaded_actor.cell->Form_ID_String().data, "");
            mcm->Add_Empty_Option();

            Race_t* race = loaded_actor.actor->Race();
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

            Vector_t<String_t> mod_names = loaded_actor.actor->Mod_Names();
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

            Vector_t<String_t> location_names = loaded_actor.cell->Location_Names();
            size_t location_name_count = location_names.size();
            if (location_name_count > 0 && mcm->Can_Add_Options(2 + location_name_count)) {
                mcm->Add_Header_Option(" Locations ");
                mcm->Add_Header_Option("");
                for (Index_t idx = 0, end = location_name_count; idx < end; idx += 1) {
                    String_t location_name = location_names[idx];
                    mcm->Add_Text_Option(location_name, "");
                }
                if (Is_Odd_Option()) {
                    mcm->Add_Empty_Option();
                }
            }
        } else {
            List()->do_update_loaded_actors = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_loaded_actors = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Previous_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Loaded_Actor_t loaded_actor = Previous_Loaded_Actor();
            if (loaded_actor.Is_Valid()) {
                Actor_Form_ID(loaded_actor.actor->form_id);
                Cell_Form_ID(loaded_actor.cell->form_id);
            } else {
                List()->do_update_loaded_actors = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Loaded_Actor_t loaded_actor = Next_Loaded_Actor();
            if (loaded_actor.Is_Valid()) {
                Actor_Form_ID(loaded_actor.actor->form_id);
                Cell_Form_ID(loaded_actor.cell->form_id);
            } else {
                List()->do_update_loaded_actors = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void References_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
