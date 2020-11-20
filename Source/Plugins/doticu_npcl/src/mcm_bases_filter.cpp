/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_bases_list.h"
#include "mcm_bases_filter.h"
#include "mcm_bases_options.h"
#include "mcm_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using Mod_t = skylib::Mod_t;
    using Race_t = skylib::Race_t;

    V::Int_Variable_t*      Bases_Filter_t::Back_Option_Variable()              { DEFINE_INT_VARIABLE("p_filter_back_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Clear_Option_Variable()             { DEFINE_INT_VARIABLE("p_filter_clear_option"); }

    V::Int_Variable_t*      Bases_Filter_t::Mod_Search_Option_Variable()        { DEFINE_INT_VARIABLE("p_filter_mod_search_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Mod_Select_Option_Variable()        { DEFINE_INT_VARIABLE("p_filter_mod_select_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Mod_Negate_Option_Variable()        { DEFINE_INT_VARIABLE("p_filter_mod_negate_option"); }
    V::String_Variable_t*   Bases_Filter_t::Mod_Argument_Variable()             { DEFINE_STRING_VARIABLE("p_filter_mod_argument"); }
    V::Bool_Variable_t*     Bases_Filter_t::Mod_Do_Negate_Variable()            { DEFINE_BOOL_VARIABLE("p_filter_mod_do_negate"); }

    V::Int_Variable_t*      Bases_Filter_t::Race_Search_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_race_search_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Race_Select_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_race_select_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Race_Negate_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_race_negate_option"); }
    V::String_Variable_t*   Bases_Filter_t::Race_Argument_Variable()            { DEFINE_STRING_VARIABLE("p_filter_race_argument"); }
    V::Bool_Variable_t*     Bases_Filter_t::Race_Do_Negate_Variable()           { DEFINE_BOOL_VARIABLE("p_filter_race_do_negate"); }

    V::Int_Variable_t*      Bases_Filter_t::Name_Search_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_name_search_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Name_Select_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_name_select_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Name_Negate_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_name_negate_option"); }
    V::String_Variable_t*   Bases_Filter_t::Name_Argument_Variable()            { DEFINE_STRING_VARIABLE("p_filter_name_argument"); }
    V::Bool_Variable_t*     Bases_Filter_t::Name_Do_Negate_Variable()           { DEFINE_BOOL_VARIABLE("p_filter_name_do_negate"); }

    V::Int_Variable_t*      Bases_Filter_t::Relation_Select_Option_Variable()   { DEFINE_INT_VARIABLE("p_filter_relation_select_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Relation_Negate_Option_Variable()   { DEFINE_INT_VARIABLE("p_filter_relation_negate_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Relation_Argument_Variable()        { DEFINE_INT_VARIABLE("p_filter_relation_argument"); }
    V::Bool_Variable_t*     Bases_Filter_t::Relation_Do_Negate_Variable()       { DEFINE_BOOL_VARIABLE("p_filter_relation_do_negate"); }

    V::Int_Variable_t*      Bases_Filter_t::Is_Male_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_is_male_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Is_Female_Option_Variable()         { DEFINE_INT_VARIABLE("p_filter_is_female_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Male_Female_Ternary_Variable()      { DEFINE_INT_VARIABLE("p_filter_male_female_ternary"); }

    V::Int_Variable_t*      Bases_Filter_t::Is_Unique_Option_Variable()         { DEFINE_INT_VARIABLE("p_filter_is_unique_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Is_Generic_Option_Variable()        { DEFINE_INT_VARIABLE("p_filter_is_generic_option"); }
    V::Int_Variable_t*      Bases_Filter_t::Unique_Generic_Ternary_Variable()   { DEFINE_INT_VARIABLE("p_filter_unique_generic_ternary"); }

    String_t Bases_Filter_t::Mod_Argument()
    {
        return Mod_Argument_Variable()->Value();
    }

    void Bases_Filter_t::Mod_Argument(String_t value)
    {
        Mod_Argument_Variable()->Value(value);
    }

    Bool_t Bases_Filter_t::Mod_Do_Negate()
    {
        return Mod_Do_Negate_Variable()->Value();
    }

    void Bases_Filter_t::Mod_Do_Negate(Bool_t value)
    {
        Mod_Do_Negate_Variable()->Value(value);
    }

    String_t Bases_Filter_t::Race_Argument()
    {
        return Race_Argument_Variable()->Value();
    }

    void Bases_Filter_t::Race_Argument(String_t value)
    {
        Race_Argument_Variable()->Value(value);
    }

    Bool_t Bases_Filter_t::Race_Do_Negate()
    {
        return Race_Do_Negate_Variable()->Value();
    }

    void Bases_Filter_t::Race_Do_Negate(Bool_t value)
    {
        Race_Do_Negate_Variable()->Value(value);
    }

    String_t Bases_Filter_t::Name_Argument()
    {
        return Name_Argument_Variable()->Value();
    }

    void Bases_Filter_t::Name_Argument(String_t value)
    {
        Name_Argument_Variable()->Value(value);
    }

    Bool_t Bases_Filter_t::Name_Do_Negate()
    {
        return Name_Do_Negate_Variable()->Value();
    }

    void Bases_Filter_t::Name_Do_Negate(Bool_t value)
    {
        Name_Do_Negate_Variable()->Value(value);
    }

    Relation_e Bases_Filter_t::Relation_Argument()
    {
        return Relation_Argument_Variable()->Value();
    }

    void Bases_Filter_t::Relation_Argument(Relation_e value)
    {
        Relation_Argument_Variable()->Value(value);
    }

    String_t Bases_Filter_t::Relation_Argument_String()
    {
        Relation_e relation = Relation_Argument();
        if (relation == Relation_e::NONE) {
            return " Any ";
        } else {
            return std::string(" ") + Relation_e::To_String(relation) + " ";
        }
    }

    void Bases_Filter_t::Relation_Argument_String(String_t value)
    {
        Relation_Argument(Relation_e::From_String(value));
    }

    Bool_t Bases_Filter_t::Relation_Do_Negate()
    {
        return Relation_Do_Negate_Variable()->Value();
    }

    void Bases_Filter_t::Relation_Do_Negate(Bool_t value)
    {
        Relation_Do_Negate_Variable()->Value(value);
    }

    Ternary_e Bases_Filter_t::Male_Female_Ternary()
    {
        return Male_Female_Ternary_Variable()->Value();
    }

    void Bases_Filter_t::Male_Female_Ternary(Ternary_e value)
    {
        Male_Female_Ternary_Variable()->Value(value);
    }

    Ternary_e Bases_Filter_t::Unique_Generic_Ternary()
    {
        return Unique_Generic_Ternary_Variable()->Value();
    }

    void Bases_Filter_t::Unique_Generic_Ternary(Ternary_e value)
    {
        Unique_Generic_Ternary_Variable()->Value(value);
    }

    Vector_t<Actor_Base_t*>* Bases_Filter_t::Execute(Vector_t<Actor_Base_t*>* read, Vector_t<Actor_Base_t*>* write)
    {
        Vector_t<Actor_Base_t*>* temp = nullptr;
        auto Swap = [&temp, &read, &write]()->void
        {
            temp = read;
            read = write;
            write = temp;
            write->clear();
        };

        auto Filter_Search = [&read, &write, &Swap](String_t search,
                                                    Bool_t do_negate,
                                                    Ternary_e(*is_match)(Actor_Base_t*, String_t))->void
        {
            if (search.data && search.data[0]) {
                if (do_negate) {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base) {
                            if (is_match(actor_base, search) == Ternary_e::LOW) {
                                write->push_back(actor_base);
                            }
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base) {
                            if (is_match(actor_base, search) == Ternary_e::HIGH) {
                                write->push_back(actor_base);
                            }
                        }
                    }
                }
                Swap();
            }
        };

        Filter_Search(
            Mod_Argument(),
            Mod_Do_Negate(),
            [](Actor_Base_t* actor_base, String_t search)->Ternary_e
            {
                if (actor_base->form_files) {
                    for (Index_t idx = 0, end = actor_base->form_files->count; idx < end; idx += 1) {
                        Mod_t* mod = actor_base->form_files->entries[idx];
                        if (mod) {
                            if (strlen(search) > 1) {
                                if (skylib::CString_t::Contains(mod->Name(), search, true)) {
                                    return Ternary_e::HIGH;
                                }
                            } else {
                                if (skylib::CString_t::Starts_With(mod->Name(), search, true)) {
                                    return Ternary_e::HIGH;
                                }
                            }
                        }
                    }
                    return Ternary_e::LOW;
                } else {
                    return Ternary_e::NONE;
                }
            }
        );

        Filter_Search(
            Race_Argument(),
            Race_Do_Negate(),
            [](Actor_Base_t* actor_base, String_t search)->Ternary_e
            {
                Race_t* race = actor_base->Race();
                if (race) {
                    if (strlen(search) > 1) {
                        if (skylib::CString_t::Contains(race->Name(), search, true) ||
                            skylib::CString_t::Contains(race->Get_Editor_ID(), search, true) ||
                            skylib::CString_t::Contains(race->Form_ID_String(), search, true)) {
                            return Ternary_e::HIGH;
                        } else {
                            return Ternary_e::LOW;
                        }
                    } else {
                        if (skylib::CString_t::Starts_With(race->Name(), search, true) ||
                            skylib::CString_t::Starts_With(race->Get_Editor_ID(), search, true) ||
                            skylib::CString_t::Starts_With(race->Form_ID_String(), search, true)) {
                            return Ternary_e::HIGH;
                        } else {
                            return Ternary_e::LOW;
                        }
                    }
                } else {
                    return Ternary_e::NONE;
                }
            }
        );

        Filter_Search(
            Name_Argument(),
            Name_Do_Negate(),
            [](Actor_Base_t* actor_base, String_t search)->Ternary_e
            {
                if (strlen(search) > 1) {
                    if (skylib::CString_t::Contains(actor_base->Name(), search, true) ||
                        skylib::CString_t::Contains(actor_base->Get_Editor_ID(), search, true) ||
                        skylib::CString_t::Contains(actor_base->Form_ID_String(), search, true)) {
                        return Ternary_e::HIGH;
                    } else {
                        return Ternary_e::LOW;
                    }
                } else {
                    if (skylib::CString_t::Starts_With(actor_base->Name(), search, true) ||
                        skylib::CString_t::Starts_With(actor_base->Get_Editor_ID(), search, true) ||
                        skylib::CString_t::Starts_With(actor_base->Form_ID_String(), search, true)) {
                        return Ternary_e::HIGH;
                    } else {
                        return Ternary_e::LOW;
                    }
                }
            }
        );

        {
            Relation_e relation = Relation_Argument();
            if (relation != Relation_e::NONE) {
                Actor_Base_t* player_actor_base = Consts_t::Skyrim_Player_Actor_Base();
                if (Relation_Do_Negate()) {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base) {
                            if (Relation_e::Between(player_actor_base, actor_base) != relation) {
                                write->push_back(actor_base);
                            }
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = read->at(idx);
                        if (actor_base) {
                            if (Relation_e::Between(player_actor_base, actor_base) == relation) {
                                write->push_back(actor_base);
                            }
                        }
                    }
                }
                Swap();
            }
        }

        auto Filter_Ternary = [&read, &write, &Swap](Ternary_e ternary,
                                                     Bool_t(*is_high)(Actor_Base_t*),
                                                     Bool_t(*is_low)(Actor_Base_t*))->void
        {
            if (ternary == Ternary_e::HIGH) {
                for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = read->at(idx);
                    if (actor_base) {
                        if (is_high(actor_base)) {
                            write->push_back(actor_base);
                        }
                    }
                }
                Swap();
            } else if (ternary == Ternary_e::LOW) {
                for (Index_t idx = 0, end = read->size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = read->at(idx);
                    if (actor_base) {
                        if (is_low(actor_base)) {
                            write->push_back(actor_base);
                        }
                    }
                }
                Swap();
            }
        };

        Filter_Ternary(
            Male_Female_Ternary(),
            [](Actor_Base_t* actor_base)->Bool_t
            {
                return actor_base->Is_Male();
            },
            [](Actor_Base_t* actor_base)->Bool_t
            {
                return actor_base->Is_Female();
            }
        );

        Filter_Ternary(
            Unique_Generic_Ternary(),
            [](Actor_Base_t* actor_base)->Bool_t
            {
                return actor_base->Is_Unique();
            },
            [](Actor_Base_t* actor_base)->Bool_t
            {
                return actor_base->Is_Generic();
            }
        );

        return read;
    }

    void Bases_Filter_t::Clear()
    {
        Mod_Argument("");
        Mod_Do_Negate(false);

        Race_Argument("");
        Race_Do_Negate(false);

        Name_Argument("");
        Name_Do_Negate(false);

        Relation_Argument(Relation_e::NONE);
        Relation_Do_Negate(false);

        Male_Female_Ternary(Ternary_e::NONE);
        Unique_Generic_Ternary(Ternary_e::NONE);
    }

    class String_Argument_i
    {
    public:
        virtual             ~String_Argument_i()            = default;
        virtual String_t    operator()()                    = 0;
        virtual void        operator()(String_t argument)   = 0;
    };

    class Selectable_String_i
    {
    public:
        virtual             ~Selectable_String_i()                  = default;
        virtual String_t    operator()(Actor_Base_t* actor_base)    = 0;
    };

    class Selectable_Strings_i
    {
    public:
        virtual                     ~Selectable_Strings_i()                 = default;
        virtual Vector_t<String_t>  operator()(Actor_Base_t* actor_base)    = 0;
    };

    static Vector_t<Actor_Base_t*> Selectable_Actor_Bases(Bases_Filter_t* self, String_Argument_i& argument)
    {
        Vector_t<Actor_Base_t*> actor_bases;
        if (self->Options()->Do_Smart_Select()) {
            String_t current = argument();
            argument("");
            self->List()->do_update_actor_bases = true;
            actor_bases = self->List()->Actor_Bases();
            argument(current);
        } else {
            actor_bases = Actor_Base_t::Actor_Bases();
        }

        return actor_bases;
    }

    static void Sort_Selectables(Vector_t<String_t>& selectables)
    {
        selectables.Sort(
            [](String_t* str_a, String_t* str_b)->Int_t
            {
                return Main_t::String_Comparator(
                    str_a ? str_a->data : "",
                    str_b ? str_b->data : ""
                );
            },
            1
        );
    }

    static Vector_t<String_t> Selectable_Strings(Bases_Filter_t* self,
                                                 String_Argument_i& argument,
                                                 Selectable_String_i& selectable)
    {
        Vector_t<Actor_Base_t*> actor_bases = Selectable_Actor_Bases(self, argument);

        Vector_t<String_t> results;
        results.reserve(actor_bases.size() + 1);
        results.push_back(" Any ");

        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases.at(idx);
            if (actor_base) {
                String_t string = selectable(actor_base);
                if (string.data && string.data[0] && !results.Has(string)) {
                    results.push_back(string);
                }
            }
        }

        Sort_Selectables(results);

        return results;
    }

    static Vector_t<String_t> Selectable_Strings(Bases_Filter_t* self,
                                                 String_Argument_i& argument,
                                                 Selectable_Strings_i& selectable)
    {
        Vector_t<Actor_Base_t*> actor_bases = Selectable_Actor_Bases(self, argument);

        Vector_t<String_t> results;
        results.reserve(actor_bases.size() + 1);
        results.push_back(" Any ");

        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases.at(idx);
            if (actor_base) {
                Vector_t<String_t> strings = selectable(actor_base);
                for (Index_t idx = 0, end = strings.size(); idx < end; idx += 1) {
                    String_t string = strings[idx];
                    if (string.data && string.data[0] && !results.Has(string)) {
                        results.push_back(string);
                    }
                }
            }
        }

        Sort_Selectables(results);

        return results;
    }

    Vector_t<String_t> Bases_Filter_t::Selectable_Mods()
    {
        class String_Argument_t : public String_Argument_i
        {
        public:
            Bases_Filter_t* self;
            String_Argument_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()()
            {
                return self->Mod_Argument();
            }
            void operator()(String_t argument)
            {
                self->Mod_Argument(argument);
            }
        } string_argument(this);

        class Selectable_Strings_t : public Selectable_Strings_i
        {
        public:
            Bases_Filter_t* self;
            Selectable_Strings_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            Vector_t<String_t> operator()(Actor_Base_t* actor_base)
            {
                return actor_base->Mod_Names();
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Bases_Filter_t::Selectable_Races()
    {
        class String_Argument_t : public String_Argument_i
        {
        public:
            Bases_Filter_t* self;
            String_Argument_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()()
            {
                return self->Race_Argument();
            }
            void operator()(String_t argument)
            {
                self->Race_Argument(argument);
            }
        } string_argument(this);

        class Selectable_String_t : public Selectable_String_i
        {
        public:
            Bases_Filter_t* self;
            Selectable_String_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()(Actor_Base_t* actor_base)
            {
                Race_t* race = actor_base->Race();
                if (race) {
                    return race->Get_Editor_ID();
                } else {
                    return "";
                }
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Bases_Filter_t::Selectable_Names()
    {
        class String_Argument_t : public String_Argument_i
        {
        public:
            Bases_Filter_t* self;
            String_Argument_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()()
            {
                return self->Name_Argument();
            }
            void operator()(String_t argument)
            {
                self->Name_Argument(argument);
            }
        } string_argument(this);

        class Selectable_String_t : public Selectable_String_i
        {
        public:
            Bases_Filter_t* self;
            Selectable_String_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()(Actor_Base_t* actor_base)
            {
                return actor_base->Any_Name();
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Bases_Filter_t::Selectable_Relations()
    {
        class String_Argument_t : public String_Argument_i
        {
        public:
            Bases_Filter_t* self;
            String_Argument_t(Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()()
            {
                return self->Relation_Argument_String();
            }
            void operator()(String_t argument)
            {
                self->Relation_Argument_String(argument);
            }
        } string_argument(this);

        class Selectable_String_t : public Selectable_String_i
        {
        public:
            Bases_Filter_t* self;
            Actor_Base_t* player_actor_base;
            Selectable_String_t(Bases_Filter_t* self, Actor_Base_t* player_actor_base) :
                self(self), player_actor_base(player_actor_base)
            {
            }
            String_t operator()(Actor_Base_t* actor_base)
            {
                Relation_e relation = Relation_e::Between(player_actor_base, actor_base);
                if (relation != Relation_e::NONE) {
                    return std::string(" ") + Relation_e::To_String(relation) + " ";
                } else {
                    return "";
                }
            }
        } selectable_string(this, Consts_t::Skyrim_Player_Actor_Base());

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    void Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Bases: Filter ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::BACK_LABEL, ""));
        Clear_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::CLEAR_LABEL, ""));

        mcm->Add_Header_Option(" Mod ");
        mcm->Add_Header_Option("");
        Mod_Search_Option_Variable()->Value(mcm->Add_Input_Option(" Search ", Mod_Argument()));
        Mod_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", "..."));
        Mod_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Mod_Do_Negate()));
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Race ");
        mcm->Add_Header_Option("");
        Race_Search_Option_Variable()->Value(mcm->Add_Input_Option(" Search ", Race_Argument()));
        Race_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", "..."));
        Race_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Race_Do_Negate()));
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Name ");
        mcm->Add_Header_Option("");
        Name_Search_Option_Variable()->Value(mcm->Add_Input_Option(" Search ", Name_Argument()));
        Name_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", "..."));
        Name_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Name_Do_Negate()));
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Relation ");
        mcm->Add_Header_Option("");
        Relation_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", Relation_Argument_String()));
        Relation_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Relation_Do_Negate()));

        mcm->Add_Header_Option(" Other ");
        mcm->Add_Header_Option("");

        Is_Male_Option_Variable()->Value(mcm->Add_Toggle_Option(" Is Male ", Male_Female_Ternary() == Ternary_e::HIGH));
        Is_Female_Option_Variable()->Value(mcm->Add_Toggle_Option(" Is Female ", Male_Female_Ternary() == Ternary_e::LOW));

        Is_Unique_Option_Variable()->Value(mcm->Add_Toggle_Option(" Is Unique ", Unique_Generic_Ternary() == Ternary_e::HIGH));
        Is_Generic_Option_Variable()->Value(mcm->Add_Toggle_Option(" Is Generic ", Unique_Generic_Ternary() == Ternary_e::LOW));

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_actor_bases = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Clear_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Clear();
            mcm->Reset_Page();

        } else if (option == Mod_Negate_Option_Variable()->Value()) {
            Bool_t value = Mod_Do_Negate();
            Mod_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Race_Negate_Option_Variable()->Value()) {
            Bool_t value = Race_Do_Negate();
            Race_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Name_Negate_Option_Variable()->Value()) {
            Bool_t value = Name_Do_Negate();
            Name_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Relation_Negate_Option_Variable()->Value()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Is_Male_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Male_Female_Ternary_Variable(), option, option + 1, Ternary_e::HIGH);
        } else if (option == Is_Female_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Male_Female_Ternary_Variable(), option - 1, option, Ternary_e::LOW);

        } else if (option == Is_Unique_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Unique_Generic_Ternary_Variable(), option, option + 1, Ternary_e::HIGH);
        } else if (option == Is_Generic_Option_Variable()->Value()) {
            mcm->Toggle_Ternary(Unique_Generic_Ternary_Variable(), option - 1, option, Ternary_e::LOW);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Mods());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Race_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Races());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Name_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Names());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Relation_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t value = "";
                if (idx > 0) {
                    Vector_t<String_t> mods = Selectable_Mods();
                    if (idx < mods.size()) {
                        value = mods[idx];
                    }
                }
                Mod_Argument(value);
                mcm->Input_Option_Value(Mod_Search_Option_Variable()->Value(), value, true);
            }
        } else if (option == Race_Select_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t value = "";
                if (idx > 0) {
                    Vector_t<String_t> races = Selectable_Races();
                    if (idx < races.size()) {
                        value = races[idx];
                    }
                }
                Race_Argument(value);
                mcm->Input_Option_Value(Race_Search_Option_Variable()->Value(), value, true);
            }
        } else if (option == Name_Select_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t value = "";
                if (idx > 0) {
                    Vector_t<String_t> names = Selectable_Names();
                    if (idx < names.size()) {
                        value = names[idx];
                    }
                }
                Name_Argument(value);
                mcm->Input_Option_Value(Name_Search_Option_Variable()->Value(), value, true);
            }
        } else if (option == Relation_Select_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t value = " Any ";
                if (idx > 0) {
                    Vector_t<String_t> relations = Selectable_Relations();
                    if (idx < relations.size()) {
                        value = relations[idx];
                    }
                }
                Relation_Argument_String(value);
                mcm->Menu_Option_Value(option, value, true);
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Search_Option_Variable()->Value()) {
            Mod_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Race_Search_Option_Variable()->Value()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Name_Search_Option_Variable()->Value()) {
            Name_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Bases_Filter_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
