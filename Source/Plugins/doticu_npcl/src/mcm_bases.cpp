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
    Int_Variable_t*     Bases_t::Options_Offset_Variable()          { DEFINE_INT_VARIABLE("p_options_offset"); }

    Int_Variable_t*     Bases_t::Filter_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_option"); }
    Int_Variable_t*     Bases_t::Options_Option_Variable()          { DEFINE_INT_VARIABLE("p_options_option"); }
    Int_Variable_t*     Bases_t::Previous_Page_Option_Variable()    { DEFINE_INT_VARIABLE("p_previous_page_option"); }
    Int_Variable_t*     Bases_t::Next_Page_Option_Variable()        { DEFINE_INT_VARIABLE("p_next_page_option"); }
    Int_Variable_t*     Bases_t::Page_Index_Variable()              { DEFINE_INT_VARIABLE("p_page_index"); }

    Int_Variable_t*     Bases_t::Back_Option_Variable()             { DEFINE_INT_VARIABLE("p_back_option"); }
    Int_Variable_t*     Bases_t::Reset_Option_Variable()            { DEFINE_INT_VARIABLE("p_reset_option"); }

    Int_Variable_t*     Bases_t::Name_Option_Variable()             { DEFINE_INT_VARIABLE("p_name_option"); }
    String_Variable_t*  Bases_t::Name_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_name_argument"); }
    Int_Variable_t*     Bases_t::Negate_Name_Option_Variable()      { DEFINE_INT_VARIABLE("p_negate_name_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Name_Variable()          { DEFINE_BOOL_VARIABLE("p_do_negate_name"); }

    Int_Variable_t*     Bases_t::Race_Option_Variable()             { DEFINE_INT_VARIABLE("p_race_option"); }
    String_Variable_t*  Bases_t::Race_Argument_Variable()           { DEFINE_STRING_VARIABLE("p_race_argument"); }
    Int_Variable_t*     Bases_t::Negate_Race_Option_Variable()      { DEFINE_INT_VARIABLE("p_negate_race_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Race_Variable()          { DEFINE_BOOL_VARIABLE("p_do_negate_race"); }
    Int_Variable_t*     Bases_t::Select_Race_Option_Variable()      { DEFINE_INT_VARIABLE("p_select_race_option"); }

    Int_Variable_t*     Bases_t::Mod_Option_Variable()              { DEFINE_INT_VARIABLE("p_mod_option"); }
    String_Variable_t*  Bases_t::Mod_Argument_Variable()            { DEFINE_STRING_VARIABLE("p_mod_argument"); }
    Int_Variable_t*     Bases_t::Negate_Mod_Option_Variable()       { DEFINE_INT_VARIABLE("p_negate_mod_option"); }
    Bool_Variable_t*    Bases_t::Do_Negate_Mod_Variable()           { DEFINE_BOOL_VARIABLE("p_do_negate_mod"); }
    Int_Variable_t*     Bases_t::Select_Mod_Option_Variable()       { DEFINE_INT_VARIABLE("p_select_mod_option"); }

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

    Int_t Bases_t::Page_Index()
    {
        return Page_Index_Variable()->Value();
    }

    void Bases_t::Page_Index(Int_t value)
    {
        Page_Index_Variable()->Value(value);
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
        return Relation_Argument_Variable()->Value();
    }

    void Bases_t::Relation_Argument(Relation_e value)
    {
        Relation_Argument_Variable()->Value(value);
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

    Ternary_e Bases_t::Male_Female_Ternary()
    {
        return static_cast<Ternary_e>(Male_Female_Ternary_Variable()->Value());
    }

    void Bases_t::Male_Female_Ternary(Ternary_e value)
    {
        Male_Female_Ternary_Variable()->Value(static_cast<Int_t>(value));
    }

    Ternary_e Bases_t::Unique_Generic_Ternary()
    {
        return static_cast<Ternary_e>(Unique_Generic_Ternary_Variable()->Value());
    }

    void Bases_t::Unique_Generic_Ternary(Ternary_e value)
    {
        Unique_Generic_Ternary_Variable()->Value(static_cast<Int_t>(value));
    }

    String_t Bases_t::Format_List_Title(Int_t base_count, Int_t page_index, Int_t page_count)
    {
        std::string bases =
            std::string("Bases: ") +
            std::to_string(base_count);

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return (bases + "               " + pages).c_str();
    }

    Vector_t<Actor_Base_t*>& Bases_t::Actor_Bases()
    {
        size_t actor_base_count = Actor_Base_t::Count_Actor_Bases();

        static Vector_t<Actor_Base_t*> read;
        read.reserve(actor_base_count);
        read.resize(0);
        Actor_Base_t::Actor_Bases(read);

        static Vector_t<Actor_Base_t*> write;
        write.reserve(actor_base_count);
        write.resize(0);

        Vector_t<Actor_Base_t*>& results = Filter_Actor_Bases(&read, &write);

        results.Sort(
            [](Actor_Base_t** base_a, Actor_Base_t** base_b)->Int_t
            {
                const char* name_a = base_a && *base_a ? (*base_a)->Any_Name() : "";
                const char* name_b = base_b && *base_b ? (*base_b)->Any_Name() : "";
                return Main_t::String_Comparator(name_a, name_b);
            }
        );

        return results;
    }

    Actor_Base_t* Bases_t::Option_To_Actor_Base(Int_t option)
    {
        Int_t relative_idx = option - Options_Offset_Variable()->Value() - HEADERS_PER_PAGE;
        if (relative_idx > -1 && relative_idx < ITEMS_PER_PAGE) {
            Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
            Int_t absolute_idx = Page_Index() * ITEMS_PER_PAGE + relative_idx;
            if (absolute_idx > -1 && absolute_idx < actor_bases.size()) {
                return actor_bases[absolute_idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Bases_t::Reset_Filter()
    {
        Name_Argument("");
        Do_Negate_Name(false);

        Race_Argument("");
        Do_Negate_Race(false);

        Mod_Argument("");
        Do_Negate_Mod(false);

        Relation_Argument(Relation_e::NONE);
        Relation_View(" Any ");
        Do_Negate_Relation(false);

        Male_Female_Ternary(Ternary_e::NONE);
        Unique_Generic_Ternary(Ternary_e::NONE);
    }

    Vector_t<Actor_Base_t*>& Bases_t::Filter_Actor_Bases(Vector_t<Actor_Base_t*>* read, Vector_t<Actor_Base_t*>* write)
    {
        Vector_t<Actor_Base_t*>* temp = nullptr;
        auto Swap = [&temp, &read, &write]()->void
        {
            temp = read;
            read = write;
            write = temp;
            write->resize(0);
        };

        auto Filter_Search = [&read, &write, &Swap](String_t search,
                                                    Bool_t do_negate,
                                                    Bool_t(*is_match)(Actor_Base_t*, String_t))->void
        {
            if (search.data && search.data[0]) {
                if (do_negate) {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base && !is_match(actor_base, search)) {
                            write->push_back(actor_base);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base && is_match(actor_base, search)) {
                            write->push_back(actor_base);
                        }
                    }
                }
                Swap();
            }
        };

        Filter_Search(
            Name_Argument(),
            Do_Negate_Name(),
            [](Actor_Base_t* actor_base, String_t search)->Bool_t
            {
                if (strlen(search) > 1) {
                    return skylib::CString_t::Contains(actor_base->Any_Name(), search, true);
                } else {
                    return skylib::CString_t::Starts_With(actor_base->Any_Name(), search, true);
                }
            }
        );

        Filter_Search(
            Race_Argument(),
            Do_Negate_Race(),
            [](Actor_Base_t* actor_base, String_t search)->Bool_t
            {
                skylib::Race_t* race = actor_base->Race();
                if (race) {
                    if (strlen(search) > 1) {
                        return skylib::CString_t::Contains(race->Get_Editor_ID(), search, true);
                    } else {
                        return skylib::CString_t::Starts_With(race->Get_Editor_ID(), search, true);
                    }
                } else {
                    return false;
                }
            }
        );

        Filter_Search(
            Mod_Argument(),
            Do_Negate_Mod(),
            [](Actor_Base_t* actor_base, String_t search)->Bool_t
            {
                if (actor_base->form_files) {
                    for (Index_t idx = 0, end = actor_base->form_files->count; idx < end; idx += 1) {
                        skylib::Mod_t* mod = actor_base->form_files->entries[idx];
                        if (mod) {
                            if (strlen(search) > 1) {
                                if (skylib::CString_t::Contains(mod->Name(), search, true)) {
                                    return true;
                                }
                            } else {
                                if (skylib::CString_t::Starts_With(mod->Name(), search, true)) {
                                    return true;
                                }
                            }
                        }
                    }
                    return false;
                } else {
                    return false;
                }
            }
        );

        auto Filter_Ternary = [&read, &write, &Swap](Ternary_e ternary,
                                                     Bool_t(*is_high)(Actor_Base_t*),
                                                     Bool_t(*is_low)(Actor_Base_t*))->void
        {
            if (ternary == Ternary_e::HIGH) {
                for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = read->at(idx);
                    if (actor_base && is_high(actor_base)) {
                        write->push_back(actor_base);
                    }
                }
                Swap();
            } else if (ternary == Ternary_e::LOW) {
                for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = read->at(idx);
                    if (actor_base && is_low(actor_base)) {
                        write->push_back(actor_base);
                    }
                }
                Swap();
            }
        };

        Filter_Ternary(
            Male_Female_Ternary(),
            [](Actor_Base_t* actor_base)->Bool_t { return actor_base->Is_Male(); },
            [](Actor_Base_t* actor_base)->Bool_t { return actor_base->Is_Female(); }
        );

        Filter_Ternary(
            Unique_Generic_Ternary(),
            [](Actor_Base_t* actor_base)->Bool_t { return actor_base->Is_Unique(); },
            [](Actor_Base_t* actor_base)->Bool_t { return actor_base->Is_Generic(); }
        );

        {
            Relation_e relation = Relation_Argument();
            if (relation != Relation_e::NONE) {
                Actor_Base_t* player_actor_base = Consts_t::Skyrim_Player_Actor_Base();
                for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = read->at(idx);
                    if (actor_base && Relation_e::Between(player_actor_base, actor_base) == relation) {
                        write->push_back(actor_base);
                    }
                }
                Swap();
            }
        }

        return *read;
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
            Current_View(LIST_VIEW);
            On_Build_Page(lcallback);
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
            Current_View(LIST_VIEW);
            On_Option_Select(option, lcallback);
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
            Current_View(LIST_VIEW);
            On_Option_Menu_Open(option, lcallback);
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
            Current_View(LIST_VIEW);
            On_Option_Menu_Accept(option, idx, lcallback);
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
            Current_View(LIST_VIEW);
            On_Option_Input_Accept(option, value, lcallback);
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
            Current_View(LIST_VIEW);
            On_Option_Highlight(option, lcallback);
        }
    }

    void Bases_t::On_Build_Page_Filter(Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Filter Bases ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option_Variable()->Value(
            mcm->Add_Text_Option("                               Back", "")
        );
        Reset_Option_Variable()->Value(
            mcm->Add_Text_Option("                              Reset ", "")
        );

        mcm->Add_Header_Option(" Name ");
        mcm->Add_Header_Option("");
        Name_Option_Variable()->Value(
            mcm->Add_Input_Option(" Search ", Name_Argument())
        );
        Negate_Name_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Name())
        );

        mcm->Add_Header_Option(" Race ");
        mcm->Add_Header_Option("");
        Race_Option_Variable()->Value(
            mcm->Add_Input_Option(" Search ", Race_Argument())
        );
        Negate_Race_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Race())
        );
        Select_Race_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Select ", "")
        );
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Mod ");
        mcm->Add_Header_Option("");
        Mod_Option_Variable()->Value(
            mcm->Add_Input_Option(" Search ", Mod_Argument())
        );
        Negate_Mod_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Mod())
        );
        Select_Mod_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Select ", "")
        );
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Relation ");
        mcm->Add_Header_Option("");
        Relation_Option_Variable()->Value(
            mcm->Add_Menu_Option(" Select ", Relation_View())
        );
        Negate_Relation_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Negate ", Do_Negate_Relation())
        );

        mcm->Add_Header_Option(" Other ");
        mcm->Add_Header_Option("");

        Is_Male_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Is Male ", Male_Female_Ternary() == Ternary_e::HIGH)
        );
        Is_Female_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Is Female ", Male_Female_Ternary() == Ternary_e::LOW)
        );

        Is_Unique_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Is Unique ", Unique_Generic_Ternary() == Ternary_e::HIGH)
        );
        Is_Generic_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Is Generic ", Unique_Generic_Ternary() == Ternary_e::LOW)
        );

        Options_Offset_Variable()->Value(Back_Option_Variable()->Value());

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select_Filter(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Reset_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Reset_Filter();
            mcm->Reset_Page();
        } else if (option == Back_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            Current_View(LIST_VIEW);
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

    void Bases_t::On_Option_Menu_Open_Filter(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Select_Race_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);

            Vector_t<skylib::Race_t*> races = skylib::Race_t::Races();
            races.Sort(
                [](skylib::Race_t** race_a, skylib::Race_t** race_b)->Int_t
                {
                    const char* name_a = race_a && *race_a ? (*race_a)->Get_Editor_ID() : "";
                    const char* name_b = race_b && *race_b ? (*race_b)->Get_Editor_ID() : "";
                    return Main_t::String_Comparator(name_a, name_b);
                }
            );

            Vector_t<String_t> values;
            values.reserve(races.size() + 1);

            values.push_back(" Any ");
            for (size_t idx = 0, count = races.size(); idx < count; idx += 1) {
                values.push_back(races[idx]->Get_Editor_ID());
            }

            mcm->Menu_Dialog_Values(values);
            mcm->Menu_Dialog_Default(0);
        } else if (option == Select_Mod_Option_Variable()->Value()) {
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

        if (option == Select_Race_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t race_editor_id = "";
                if (idx > 0) {
                    Vector_t<skylib::Race_t*> races = skylib::Race_t::Races();
                    races.Sort(
                        [](skylib::Race_t** race_a, skylib::Race_t** race_b)->Int_t
                        {
                            const char* name_a = race_a && *race_a ? (*race_a)->Get_Editor_ID() : "";
                            const char* name_b = race_b && *race_b ? (*race_b)->Get_Editor_ID() : "";
                            return Main_t::String_Comparator(name_a, name_b);
                        }
                    );
                    if (idx - 1 < races.size()) {
                        race_editor_id = races[idx - 1]->Get_Editor_ID();
                    }
                }
                Race_Argument(race_editor_id);
                mcm->Input_Option_Value(Race_Option_Variable()->Value(), race_editor_id, true);
            }
        } else if (option == Select_Mod_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t mod_name = "";
                if (idx > 0) {
                    Vector_t<skylib::Mod_t*> mods = skylib::Mod_t::Active_Mods();
                    if (idx - 1 < mods.size()) {
                        mod_name = mods[idx - 1]->Name();
                    }
                }
                Mod_Argument(mod_name);
                mcm->Input_Option_Value(Mod_Option_Variable()->Value(), mod_name, true);
            }
        } else if (option == Relation_Option_Variable()->Value()) {
            if (idx > -1) {
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
            }
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
        } else if (option == Mod_Option_Variable()->Value()) {
            Mod_Argument(value);
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

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        size_t actor_base_count = actor_bases.size();
        if (actor_base_count > 0) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index(page_index);
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index(page_index);
            }

            mcm->Title_Text(Format_List_Title(actor_base_count, page_index, page_count));

            Filter_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::FILTER_LABEL, "")
            );
            Options_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, "")
            );
            if (page_count > 1) {
                Previous_Page_Option_Variable()->Value(
                    mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "")
                );
                Next_Page_Option_Variable()->Value(
                    mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "")
                );
            } else {
                Previous_Page_Option_Variable()->Value(
                    mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE)
                );
                Next_Page_Option_Variable()->Value(
                    mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE)
                );
            }

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            Int_t begin = ITEMS_PER_PAGE * page_index;
            Int_t end = begin + ITEMS_PER_PAGE;
            if (end > actor_base_count) {
                end = actor_base_count;
            }
            for (; begin < end; begin += 1) {
                Actor_Base_t* actor_base = actor_bases[begin];
                mcm->Add_Text_Option(actor_base->Any_Name(), "...");
            }

            Options_Offset_Variable()->Value(Filter_Option_Variable()->Value());
        } else {
            mcm->Title_Text(Format_List_Title(0, 0, 1));

            Filter_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::FILTER_LABEL, "")
            );
            Options_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, "")
            );
            Previous_Page_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE)
            );
            Next_Page_Option_Variable()->Value(
                mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE)
            );

            mcm->Add_Header_Option(" No Actor Bases ");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_t::On_Option_Select_List(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Filter_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Current_View(FILTER_VIEW);
            mcm->Reset_Page();
        } else if (option == Options_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Current_View(OPTIONS_VIEW);
            mcm->Reset_Page();
        } else if (option == Previous_Page_Option_Variable()->Value()) {
            mcm->Disable_Option(option);

            Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
            size_t actor_base_count = actor_bases.size();
            if (actor_base_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == 0) {
                    page_index = page_count - 1;
                } else {
                    page_index -= 1;
                }
                Page_Index(page_index);
            }

            mcm->Reset_Page();
        } else if (option == Next_Page_Option_Variable()->Value()) {
            mcm->Disable_Option(option);

            Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
            size_t actor_base_count = actor_bases.size();
            if (actor_base_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == page_count - 1) {
                    page_index = 0;
                } else {
                    page_index += 1;
                }
                Page_Index(page_index);
            }

            mcm->Reset_Page();
        } else {
            Actor_Base_t* actor_base = Option_To_Actor_Base(option);
            if (actor_base) {
                //mcm->Disable_Option(option);

                mcm->Flicker_Option(option);
                mcm->Show_Message((std::string("Would open item menu for ") + actor_base->Any_Name().data + ".").c_str());

                //mcm->Reset_Page();
            }
        }

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
