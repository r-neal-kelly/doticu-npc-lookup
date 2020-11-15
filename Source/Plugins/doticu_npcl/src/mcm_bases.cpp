/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    Bases_t*            Bases_t::Self()                             { return static_cast<Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    String_t            Bases_t::Class_Name()                       { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases"); }
    Class_t*            Bases_t::Class()                            { DEFINE_CLASS(); }

    Object_t*           Bases_t::Object()                           { DEFINE_OBJECT(); }

    String_Variable_t*  Bases_t::Current_View_Variable()            { DEFINE_STRING_VARIABLE("p_current_view"); }

    Int_Variable_t*     Bases_t::Filter_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_option"); }
    Int_Variable_t*     Bases_t::Reset_Option_Variable()            { DEFINE_INT_VARIABLE("p_reset_option"); }

    Int_Variable_t*     Bases_t::Name_Option_Variable()             { DEFINE_INT_VARIABLE("p_name_option"); }
    String_Variable_t*  Bases_t::Name_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_name_argument"); }
    Int_Variable_t*     Bases_t::Negate_Name_Option_Variable()      { DEFINE_INT_VARIABLE("p_negate_name_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Name_Variable()          { DEFINE_BOOL_VARIABLE("p_do_negate_name"); }
    Int_Variable_t*     Bases_t::Insert_Race_Option_Variable()      { DEFINE_INT_VARIABLE("p_insert_race_option"); }

    Int_Variable_t*     Bases_t::Race_Option_Variable()             { DEFINE_INT_VARIABLE("p_race_option"); }
    String_Variable_t*  Bases_t::Race_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_race_argument"); }
    Int_Variable_t*     Bases_t::Negate_Race_Option_Variable()      { DEFINE_INT_VARIABLE("p_negate_race_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Race_Variable()          { DEFINE_BOOL_VARIABLE("p_do_negate_race"); }

    Int_Variable_t*     Bases_t::Mod_Option_Variable()              { DEFINE_INT_VARIABLE("p_mod_option"); }
    String_Variable_t*  Bases_t::Mod_Argument_Variable()            { DEFINE_STRING_VARIABLE("p_mod_argument"); }
    String_Variable_t*  Bases_t::Mod_View_Variable()                { DEFINE_STRING_VARIABLE("p_mod_view"); }
    Int_Variable_t*     Bases_t::Negate_Mod_Option_Variable()       { DEFINE_INT_VARIABLE("p_negate_mod_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Mod_Variable()           { DEFINE_BOOL_VARIABLE("p_do_negate_mod"); }

    Int_Variable_t*     Bases_t::Relation_Option_Variable()         { DEFINE_INT_VARIABLE("p_relation_option"); }
    Int_Variable_t*     Bases_t::Relation_Argument_Variable()       { DEFINE_INT_VARIABLE("p_relation_argument"); }
    String_Variable_t*  Bases_t::Relation_View_Variable()           { DEFINE_STRING_VARIABLE("p_relation_view"); }
    Int_Variable_t*     Bases_t::Negate_Relation_Option_Variable()  { DEFINE_INT_VARIABLE("p_negate_relation_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Relation_Variable()      { DEFINE_BOOL_VARIABLE("p_do_negate_relation"); }

    Int_Variable_t*     Bases_t::Is_Male_Option_Variable()          { DEFINE_INT_VARIABLE("p_is_male_option"); }
    Int_Variable_t*     Bases_t::Is_Female_Option_Variable()        { DEFINE_INT_VARIABLE("p_is_female_option"); }
    Int_Variable_t*     Bases_t::Male_Female_Ternary_Variable()     { DEFINE_INT_VARIABLE("p_male_female_ternary"); }

    Int_Variable_t*     Bases_t::Is_Unique_Option_Variable()        { DEFINE_INT_VARIABLE("p_is_unique_option"); }
    Int_Variable_t*     Bases_t::Is_Generic_Option_Variable()       { DEFINE_INT_VARIABLE("p_is_generic_option"); }
    Int_Variable_t*     Bases_t::Unique_Generic_Ternary_Variable()  { DEFINE_INT_VARIABLE("p_unique_generic_ternary"); }

    String_t Bases_t::Current_View()
    {
        return Current_View_Variable()->Value();
    }

    void Bases_t::Current_View(String_t value)
    {
        Current_View_Variable()->Value(value);
    }

    String_t Bases_t::Name_Argument()
    {
        return Name_Argument_Variable()->Value();
    }

    void Bases_t::Name_Argument(String_t value)
    {
        Name_Argument_Variable()->Value(value);
    }

    Bool_t Bases_t::Do_Negate_Name()
    {
        return Do_Negate_Name_Variable()->Value();
    }

    void Bases_t::Do_Negate_Name(Bool_t value)
    {
        Do_Negate_Name_Variable()->Value(value);
    }

    String_t Bases_t::Race_Argument()
    {
        return Race_Argument_Variable()->Value();
    }

    void Bases_t::Race_Argument(String_t value)
    {
        Race_Argument_Variable()->Value(value);
    }

    Bool_t Bases_t::Do_Negate_Race()
    {
        return Do_Negate_Race_Variable()->Value();
    }

    void Bases_t::Do_Negate_Race(Bool_t value)
    {
        Do_Negate_Race_Variable()->Value(value);
    }

    String_t Bases_t::Mod_Argument()
    {
        return Mod_Argument_Variable()->Value();
    }

    void Bases_t::Mod_Argument(String_t value)
    {
        Mod_Argument_Variable()->Value(value);
    }

    String_t Bases_t::Mod_View()
    {
        return Mod_View_Variable()->Value();
    }

    void Bases_t::Mod_View(String_t value)
    {
        Mod_View_Variable()->Value(value);
    }

    Bool_t Bases_t::Do_Negate_Mod()
    {
        return Do_Negate_Mod_Variable()->Value();
    }

    void Bases_t::Do_Negate_Mod(Bool_t value)
    {
        Do_Negate_Mod_Variable()->Value(value);
    }

    Relation_e Bases_t::Relation_Argument()
    {
        return static_cast<Relation_e>(Relation_Argument_Variable()->Value());
    }

    void Bases_t::Relation_Argument(Relation_e value)
    {
        Relation_Argument_Variable()->Value(static_cast<Int_t>(value));
    }

    String_t Bases_t::Relation_View()
    {
        return Relation_View_Variable()->Value();
    }

    void Bases_t::Relation_View(String_t value)
    {
        Relation_View_Variable()->Value(value);
    }

    Bool_t Bases_t::Do_Negate_Relation()
    {
        return Do_Negate_Relation_Variable()->Value();
    }

    void Bases_t::Do_Negate_Relation(Bool_t value)
    {
        Do_Negate_Relation_Variable()->Value(value);
    }

    Int_t Bases_t::Male_Female_Ternary()
    {
        return Male_Female_Ternary_Variable()->Value();
    }

    void Bases_t::Male_Female_Ternary(Int_t value)
    {
        Male_Female_Ternary_Variable()->Value(value);
    }

    Int_t Bases_t::Unique_Generic_Ternary()
    {
        return Unique_Generic_Ternary_Variable()->Value();
    }

    void Bases_t::Unique_Generic_Ternary(Int_t value)
    {
        Unique_Generic_Ternary_Variable()->Value(value);
    }

    void Bases_t::Reset_Filter()
    {
        Name_Argument("");
        Do_Negate_Name(false);

        Race_Argument("");
        Do_Negate_Race(false);

        Mod_Argument("");
        Mod_View(" Any ");
        Do_Negate_Mod(false);

        Relation_Argument(Relation_e::NONE);
        Relation_View(" Any ");
        Do_Negate_Relation(false);

        Male_Female_Ternary(0);
        Unique_Generic_Ternary(0);
    }

    static Bool_t Is_Same(const char* a, const char* b, Bool_t caseless = true)
    {
        return skylib::CString_t::Is_Same(a, b, caseless);
    }

    void Bases_t::On_Build_Page(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Build_Page_Filter(lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Build_Page_List(lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Build_Page_Item(lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Build_Page_Filter(lcallback);
        }
    }

    void Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Option_Select_Filter(option, lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Option_Select_List(option, lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Option_Select_Item(option, lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Option_Select_Filter(option, lcallback);
        }
    }

    void Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Option_Menu_Open_Filter(option, lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Option_Menu_Open_List(option, lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Option_Menu_Open_Item(option, lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Option_Menu_Open_Filter(option, lcallback);
        }
    }

    void Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Option_Menu_Accept_Filter(option, idx, lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Option_Menu_Accept_List(option, idx, lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Option_Menu_Accept_Item(option, idx, lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Option_Menu_Accept_Filter(option, idx, lcallback);
        }
    }

    void Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Option_Input_Accept_Filter(option, value, lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Option_Input_Accept_List(option, value, lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Option_Input_Accept_Item(option, value, lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Option_Input_Accept_Filter(option, value, lcallback);
        }
    }

    void Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        String_t current_view = Current_View();
             if (Is_Same(current_view, FILTER_VIEW))    On_Option_Highlight_Filter(option, lcallback);
        else if (Is_Same(current_view, LIST_VIEW))      On_Option_Highlight_List(option, lcallback);
        else if (Is_Same(current_view, ITEM_VIEW))      On_Option_Highlight_Item(option, lcallback);
        else {
            Current_View(FILTER_VIEW);
            On_Option_Highlight_Filter(option, lcallback);
        }
    }

    void Bases_t::On_Build_Page_Filter(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Filter Bases ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Filter_Option_Variable()->Value(
            mcm->Add_Text_Option(" Run Filter ", "")
        );
        Reset_Option_Variable()->Value(
            mcm->Add_Text_Option(" Reset Filter ", "")
        );

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");

        Name_Option_Variable()->Value(
            mcm->Add_Input_Option(" Name ", Name_Argument())
        );
        Negate_Name_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Name())
        );

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");

        Race_Option_Variable()->Value(
            mcm->Add_Input_Option(" Race ", Race_Argument())
        );
        Negate_Race_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Race())
        );
        Insert_Race_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Insert ", "")
        );
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");

        Mod_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Mod ", Mod_View())
        );
        Negate_Mod_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Mod())
        );

        Relation_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Relation ", Relation_View())
        );
        Negate_Relation_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Relation())
        );

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");

        Is_Male_Option_Variable()->Int(
            mcm->Add_Toggle_Option(" Is Male ", Male_Female_Ternary() > 0)
        );
        Is_Female_Option_Variable()->Int(
            mcm->Add_Toggle_Option(" Is Female ", Male_Female_Ternary() < 0)
        );

        Is_Unique_Option_Variable()->Int(
            mcm->Add_Toggle_Option(" Is Unique ", Unique_Generic_Ternary() > 0)
        );
        Is_Generic_Option_Variable()->Int(
            mcm->Add_Toggle_Option(" Is Generic ", Unique_Generic_Ternary() < 0)
        );

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select_Filter(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Filter_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Show_Message("Would filter.");
        } else if (option == Reset_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Reset_Filter();
            mcm->Reset_Page();

        } else if (option == Negate_Name_Option_Variable()->Value()) {
            Bool_t value = Do_Negate_Name();
            Do_Negate_Name(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Negate_Mod_Option_Variable()->Value()) {
            Bool_t value = Do_Negate_Mod();
            Do_Negate_Mod(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Negate_Race_Option_Variable()->Value()) {
            Bool_t value = Do_Negate_Race();
            Do_Negate_Race(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Negate_Relation_Option_Variable()->Value()) {
            Bool_t value = Do_Negate_Relation();
            Do_Negate_Relation(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Is_Male_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Male_Female_Ternary_Variable(), option, option + 1, Ternary_e::HIGH);
        } else if (option == Is_Female_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Male_Female_Ternary_Variable(), option - 1, option, Ternary_e::LOW);

        } else if (option == Is_Unique_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Unique_Generic_Ternary_Variable(), option, option + 1, Ternary_e::HIGH);
        } else if (option == Is_Generic_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Unique_Generic_Ternary_Variable(), option - 1, option, Ternary_e::LOW);

        } else {

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    static Int_t Race_Comparator(skylib::Race_t* const* race_a, skylib::Race_t* const* race_b)
    {
        const char* editor_id_a = race_a && *race_a ? (*race_a)->Get_Editor_ID() : "";
        const char* editor_id_b = race_b && *race_b ? (*race_b)->Get_Editor_ID() : "";
        return _stricmp(editor_id_a, editor_id_b);
    }

    void Bases_t::On_Option_Menu_Open_Filter(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Insert_Race_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);

            Vector_t<skylib::Race_t*> races = skylib::Race_t::Races();
            races.Sort(Race_Comparator);

            Vector_t<String_t> values;
            values.reserve(races.size() + 1);

            values.push_back(" Any ");
            for (size_t idx = 0, count = races.size(); idx < count; idx += 1) {
                values.push_back(races[idx]->Get_Editor_ID());
            }

            mcm->Menu_Dialog_Values(values);
            mcm->Menu_Dialog_Default(0);
        } else if (option == Mod_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);

            Vector_t<skylib::Mod_t*> mods = skylib::Mod_t::Active_Mods();
            Vector_t<String_t> values;
            values.reserve(mods.size() + 1);

            values.push_back(" Any ");
            for (size_t idx = 0, count = mods.size(); idx < count; idx += 1) {
                values.push_back(mods[idx]->Name());
            }

            mcm->Menu_Dialog_Values(values);
            mcm->Menu_Dialog_Default(0);
        } else if (option == Relation_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);

            Vector_t<String_t> values;
            values.reserve(10);

            values.push_back(" Any ");
            values.push_back(" Lover ");
            values.push_back(" Ally ");
            values.push_back(" Confidant ");
            values.push_back(" Friend ");
            values.push_back(" Acquaintance ");
            values.push_back(" Rival ");
            values.push_back(" Foe ");
            values.push_back(" Enemy ");
            values.push_back(" Archnemesis ");

            mcm->Menu_Dialog_Values(values);
            mcm->Menu_Dialog_Default(0);
        } else {

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Accept_Filter(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Insert_Race_Option_Variable()->Value()) {
            String_t race_editor_id = "";
            if (idx > 0) {
                Vector_t<skylib::Race_t*> races = skylib::Race_t::Races();
                races.Sort(Race_Comparator);
                if (idx - 1 < races.size()) {
                    race_editor_id = races[idx - 1]->Get_Editor_ID();
                }
            }
            Race_Argument(race_editor_id);
            mcm->Input_Option_Value(Race_Option_Variable()->Value(), race_editor_id, true);
        } else if (option == Mod_Option_Variable()->Value()) {
            if (idx < 1) {
                Mod_Argument("");
                Mod_View(" Any ");
            } else {
                Vector_t<skylib::Mod_t*> mods = skylib::Mod_t::Active_Mods();
                if (idx - 1 < mods.size()) {
                    String_t mod_name = mods[idx - 1]->Name();
                    Mod_Argument(mod_name);
                    Mod_View(mod_name);
                } else {
                    Mod_Argument("");
                    Mod_View(" Any ");
                }
            }
            mcm->Menu_Option_Value(option, Mod_View(), true);
        } else if (option == Relation_Option_Variable()->Value()) {
            if (idx == 0) {
                Relation_Argument(Relation_e::NONE);
                Relation_View(" Any ");
            } else if (idx == 1) {
                Relation_Argument(Relation_e::LOVER);
                Relation_View(" Lover ");
            } else if (idx == 2) {
                Relation_Argument(Relation_e::ALLY);
                Relation_View(" Ally ");
            } else if (idx == 3) {
                Relation_Argument(Relation_e::CONFIDANT);
                Relation_View(" Confidant ");
            } else if (idx == 4) {
                Relation_Argument(Relation_e::FRIEND);
                Relation_View(" Friend ");
            } else if (idx == 5) {
                Relation_Argument(Relation_e::ACQUAINTANCE);
                Relation_View(" Acquaintance ");
            } else if (idx == 6) {
                Relation_Argument(Relation_e::RIVAL);
                Relation_View(" Rival ");
            } else if (idx == 7) {
                Relation_Argument(Relation_e::FOE);
                Relation_View(" Foe ");
            } else if (idx == 8) {
                Relation_Argument(Relation_e::ENEMY);
                Relation_View(" Enemy ");
            } else if (idx == 9) {
                Relation_Argument(Relation_e::ARCHNEMESIS);
                Relation_View(" Archnemesis ");
            }
            mcm->Menu_Option_Value(option, Relation_View(), true);
        } else {

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Input_Accept_Filter(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Name_Option_Variable()->Value()) {
            Name_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Race_Option_Variable()->Value()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else {

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Highlight_Filter(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Build_Page_List(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Title_Text("Bases: List");
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select_List(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Open_List(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Accept_List(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Input_Accept_List(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Highlight_List(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Build_Page_Item(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Title_Text("Bases: View");
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Open_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Menu_Accept_Item(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Input_Accept_Item(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Highlight_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::Register_Me(Machine_t* machine)
    {
    }

}}
