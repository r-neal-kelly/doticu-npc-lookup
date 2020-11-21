/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_leveled_bases_list.h"
#include "mcm_leveled_bases_filter.h"
#include "mcm_leveled_bases_options.h"
#include "mcm_leveled_bases_item.h"

namespace doticu_npcl { namespace MCM {

    using Actor_Base_t  = skylib::Actor_Base_t;
    using Mod_t         = skylib::Mod_t;
    using Race_t        = skylib::Race_t;

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Back_Option_Variable()                  { DEFINE_INT_VARIABLE("p_filter_back_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Clear_Option_Variable()                 { DEFINE_INT_VARIABLE("p_filter_clear_option"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Mod_Search_Option_Variable()            { DEFINE_INT_VARIABLE("p_filter_mod_search_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Mod_Select_Option_Variable()            { DEFINE_INT_VARIABLE("p_filter_mod_select_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Mod_Negate_Option_Variable()            { DEFINE_INT_VARIABLE("p_filter_mod_negate_option"); }
    V::String_Variable_t*   Leveled_Bases_Filter_t::Mod_Argument_Variable()                 { DEFINE_STRING_VARIABLE("p_filter_mod_argument"); }
    V::Bool_Variable_t*     Leveled_Bases_Filter_t::Mod_Do_Negate_Variable()                { DEFINE_BOOL_VARIABLE("p_filter_mod_do_negate"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Race_Search_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_race_search_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Race_Select_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_race_select_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Race_Negate_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_race_negate_option"); }
    V::String_Variable_t*   Leveled_Bases_Filter_t::Race_Argument_Variable()                { DEFINE_STRING_VARIABLE("p_filter_race_argument"); }
    V::Bool_Variable_t*     Leveled_Bases_Filter_t::Race_Do_Negate_Variable()               { DEFINE_BOOL_VARIABLE("p_filter_race_do_negate"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Base_Search_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_base_search_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Base_Select_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_base_select_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Base_Negate_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_base_negate_option"); }
    V::String_Variable_t*   Leveled_Bases_Filter_t::Base_Argument_Variable()                { DEFINE_STRING_VARIABLE("p_filter_base_argument"); }
    V::Bool_Variable_t*     Leveled_Bases_Filter_t::Base_Do_Negate_Variable()               { DEFINE_BOOL_VARIABLE("p_filter_base_do_negate"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Relation_Select_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_relation_select_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Relation_Negate_Option_Variable()       { DEFINE_INT_VARIABLE("p_filter_relation_negate_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Relation_Argument_Variable()            { DEFINE_INT_VARIABLE("p_filter_relation_argument"); }
    V::Bool_Variable_t*     Leveled_Bases_Filter_t::Relation_Do_Negate_Variable()           { DEFINE_BOOL_VARIABLE("p_filter_relation_do_negate"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Has_Male_Option_Variable()              { DEFINE_INT_VARIABLE("p_filter_has_male_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Has_Female_Option_Variable()            { DEFINE_INT_VARIABLE("p_filter_has_female_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Male_Female_Quaternary_Variable()       { DEFINE_INT_VARIABLE("p_filter_male_female_quaternary"); }

    V::Int_Variable_t*      Leveled_Bases_Filter_t::Has_Unique_Option_Variable()            { DEFINE_INT_VARIABLE("p_filter_has_unique_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Has_Generic_Option_Variable()           { DEFINE_INT_VARIABLE("p_filter_has_generic_option"); }
    V::Int_Variable_t*      Leveled_Bases_Filter_t::Unique_Generic_Quaternary_Variable()    { DEFINE_INT_VARIABLE("p_filter_unique_generic_quaternary"); }

    String_t Leveled_Bases_Filter_t::Mod_Argument()
    {
        return Mod_Argument_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Mod_Argument(String_t value)
    {
        Mod_Argument_Variable()->Value(value);
    }

    Bool_t Leveled_Bases_Filter_t::Mod_Do_Negate()
    {
        return Mod_Do_Negate_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Mod_Do_Negate(Bool_t value)
    {
        Mod_Do_Negate_Variable()->Value(value);
    }

    String_t Leveled_Bases_Filter_t::Race_Argument()
    {
        return Race_Argument_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Race_Argument(String_t value)
    {
        Race_Argument_Variable()->Value(value);
    }

    Bool_t Leveled_Bases_Filter_t::Race_Do_Negate()
    {
        return Race_Do_Negate_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Race_Do_Negate(Bool_t value)
    {
        Race_Do_Negate_Variable()->Value(value);
    }

    String_t Leveled_Bases_Filter_t::Base_Argument()
    {
        return Base_Argument_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Base_Argument(String_t value)
    {
        Base_Argument_Variable()->Value(value);
    }

    Bool_t Leveled_Bases_Filter_t::Base_Do_Negate()
    {
        return Base_Do_Negate_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Base_Do_Negate(Bool_t value)
    {
        Base_Do_Negate_Variable()->Value(value);
    }

    Relation_e Leveled_Bases_Filter_t::Relation_Argument()
    {
        return Relation_Argument_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Relation_Argument(Relation_e value)
    {
        Relation_Argument_Variable()->Value(value);
    }

    String_t Leveled_Bases_Filter_t::Relation_Argument_String()
    {
        Relation_e relation = Relation_Argument();
        if (relation == Relation_e::NONE) {
            return " Any ";
        } else {
            return std::string(" ") + Relation_e::To_String(relation) + " ";
        }
    }

    void Leveled_Bases_Filter_t::Relation_Argument_String(String_t value)
    {
        Relation_Argument(Relation_e::From_String(value));
    }

    Bool_t Leveled_Bases_Filter_t::Relation_Do_Negate()
    {
        return Relation_Do_Negate_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Relation_Do_Negate(Bool_t value)
    {
        Relation_Do_Negate_Variable()->Value(value);
    }

    Quaternary_e Leveled_Bases_Filter_t::Male_Female_Quaternary()
    {
        return Male_Female_Quaternary_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Male_Female_Quaternary(Quaternary_e value)
    {
        Male_Female_Quaternary_Variable()->Value(value);
    }

    Quaternary_e Leveled_Bases_Filter_t::Unique_Generic_Quaternary()
    {
        return Unique_Generic_Quaternary_Variable()->Value();
    }

    void Leveled_Bases_Filter_t::Unique_Generic_Quaternary(Quaternary_e value)
    {
        Unique_Generic_Quaternary_Variable()->Value(value);
    }

    class Filter_Ternary_e : public Ternary_e
    {
    public:
        enum : skylib::s8
        {
            INVALID     = Ternary_e::NONE,
            IS_MATCH    = Ternary_e::A,
            ISNT_MATCH  = Ternary_e::B,
        };
        using Ternary_e::Ternary_e;
    };

    template <typename Item_t>
    class Filter_State_t
    {
    public:
        Vector_t<Item_t>* read;
        Vector_t<Item_t>* write;
        Vector_t<Item_t>* temp;

        Filter_State_t(Vector_t<Item_t>* read, Vector_t<Item_t>* write) :
            read(read), write(write), temp(nullptr)
        {
        }

        void Swap()
        {
            temp = read;
            read = write;
            write = temp;
            write->clear();
        }
    };

    template <typename Item_t, typename ...Args>
    class Filter_i
    {
    public:
        Filter_State_t<Item_t>& state;

        Filter_i(Filter_State_t<Item_t>& state) :
            state(state)
        {
        }

        virtual         ~Filter_i()         = default;
        virtual void    Execute(Args...)    = 0;
    };

    template <typename Item_t>
    class String_Filter_i : public Filter_i<Item_t, String_t, Bool_t>
    {
    public:
        using Filter_i<Item_t, String_t, Bool_t>::Filter_i;

        virtual void Execute(String_t string, Bool_t do_negate) override
        {
            if (string.data && string.data[0]) {
                if (do_negate) {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Is_Match(item, string) == Filter_Ternary_e::ISNT_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Is_Match(item, string) == Filter_Ternary_e::IS_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                }
                state.Swap();
            }
        }

        virtual Filter_Ternary_e Is_Match(Item_t, String_t) = 0;
    };

    template <typename Item_t>
    class Relation_Filter_i : public Filter_i<Item_t, Relation_e, Bool_t>
    {
    public:
        using Filter_i<Item_t, Relation_e, Bool_t>::Filter_i;

        virtual void Execute(Relation_e relation, Bool_t do_negate) override
        {
            if (relation != Relation_e::NONE) {
                if (do_negate) {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Is_Match(item, relation) == Filter_Ternary_e::ISNT_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Is_Match(item, relation) == Filter_Ternary_e::IS_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                }
                state.Swap();
            }
        }

        virtual Filter_Ternary_e Is_Match(Item_t, Relation_e) = 0;
    };

    template <typename Item_t>
    class Ternary_Filter_i : public Filter_i<Item_t, Ternary_e>
    {
    public:
        using Filter_i<Item_t, Ternary_e>::Filter_i;

        virtual void Execute(Ternary_e ternary) override
        {
            if (ternary != Ternary_e::NONE) {
                for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Item_t item = state.read->at(idx);
                    if (Is_Match(item, ternary) == Filter_Ternary_e::IS_MATCH) {
                        state.write->push_back(item);
                    }
                }
                state.Swap();
            }
        }

        virtual Filter_Ternary_e Is_Match(Item_t, Ternary_e) = 0;
    };

    template <typename Item_t>
    class Quaternary_Filter_i : public Filter_i<Item_t, Quaternary_e>
    {
    public:
        using Filter_i<Item_t, Quaternary_e>::Filter_i;

        virtual void Execute(Quaternary_e quaternary) override
        {
            if (quaternary != Quaternary_e::NONE) {
                for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Item_t item = state.read->at(idx);
                    if (Is_Match(item, quaternary) == Filter_Ternary_e::IS_MATCH) {
                        state.write->push_back(item);
                    }
                }
                state.Swap();
            }
        }

        virtual Filter_Ternary_e Is_Match(Item_t, Quaternary_e) = 0;
    };

    Vector_t<Leveled_Actor_Base_t*>* Leveled_Bases_Filter_t::Execute(Vector_t<Leveled_Actor_Base_t*>* read, Vector_t<Leveled_Actor_Base_t*>* write)
    {
        Filter_State_t<Leveled_Actor_Base_t*> filter_state(read, write);

        class Mod_Filter_t : public String_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            using String_Filter_i::String_Filter_i;

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, String_t string) override
            {
                if (item && item->form_files) {
                    for (Index_t idx = 0, end = item->form_files->count; idx < end; idx += 1) {
                        Mod_t* mod = item->form_files->entries[idx];
                        if (mod) {
                            if (strlen(string) > 1) {
                                if (skylib::CString_t::Contains(mod->Name(), string, true)) {
                                    return Filter_Ternary_e::IS_MATCH;
                                }
                            } else {
                                if (skylib::CString_t::Starts_With(mod->Name(), string, true)) {
                                    return Filter_Ternary_e::IS_MATCH;
                                }
                            }
                        }
                    }
                    return Filter_Ternary_e::ISNT_MATCH;
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Mod_Filter_t(filter_state).Execute(Mod_Argument(), Mod_Do_Negate());

        class Race_Filter_t : public String_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            using String_Filter_i::String_Filter_i;

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, String_t string) override
            {
                if (item) {
                    Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                    for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = actor_bases[idx];
                        if (actor_base) {
                            Race_t* race = actor_base->Race();
                            if (race) {
                                if (strlen(string) > 1) {
                                    if (skylib::CString_t::Contains(race->Name(), string, true) ||
                                        skylib::CString_t::Contains(race->Get_Editor_ID(), string, true) ||
                                        skylib::CString_t::Contains(race->Form_ID_String(), string, true)) {
                                        return Filter_Ternary_e::IS_MATCH;
                                    }
                                } else {
                                    if (skylib::CString_t::Starts_With(race->Name(), string, true) ||
                                        skylib::CString_t::Starts_With(race->Get_Editor_ID(), string, true) ||
                                        skylib::CString_t::Starts_With(race->Form_ID_String(), string, true)) {
                                        return Filter_Ternary_e::IS_MATCH;
                                    }
                                }
                            }
                        }
                    }
                    return Filter_Ternary_e::ISNT_MATCH;
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Race_Filter_t(filter_state).Execute(Race_Argument(), Race_Do_Negate());

        class Base_Filter_t : public String_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            using String_Filter_i::String_Filter_i;

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, String_t string) override
            {
                if (item) {
                    Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                    for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = actor_bases[idx];
                        if (actor_base) {
                            if (strlen(string) > 1) {
                                if (skylib::CString_t::Contains(actor_base->Name(), string, true) ||
                                    skylib::CString_t::Contains(actor_base->Get_Editor_ID(), string, true) ||
                                    skylib::CString_t::Contains(actor_base->Form_ID_String(), string, true)) {
                                    return Filter_Ternary_e::IS_MATCH;
                                }
                            } else {
                                if (skylib::CString_t::Starts_With(actor_base->Name(), string, true) ||
                                    skylib::CString_t::Starts_With(actor_base->Get_Editor_ID(), string, true) ||
                                    skylib::CString_t::Starts_With(actor_base->Form_ID_String(), string, true)) {
                                    return Filter_Ternary_e::IS_MATCH;
                                }
                            }
                        }
                    }
                    return Filter_Ternary_e::ISNT_MATCH;
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Base_Filter_t(filter_state).Execute(Base_Argument(), Base_Do_Negate());

        class Relation_Filter_t : public Relation_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            Actor_Base_t* player_actor_base;

            Relation_Filter_t(Filter_State_t<Leveled_Actor_Base_t*>& state, Actor_Base_t* player_actor_base) :
                Relation_Filter_i(state), player_actor_base(player_actor_base)
            {
            }

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, Relation_e relation) override
            {
                if (item) {
                    Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                    for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                        Actor_Base_t* actor_base = actor_bases[idx];
                        if (actor_base && Relation_e::Between(player_actor_base, actor_base) == relation) {
                            return Filter_Ternary_e::IS_MATCH;
                        }
                    }
                    return Filter_Ternary_e::ISNT_MATCH;
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Relation_Filter_t(filter_state, Consts_t::Skyrim_Player_Actor_Base()).Execute(Relation_Argument(), Relation_Do_Negate());

        class Male_Female_Filter_t : public Quaternary_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            using Quaternary_Filter_i::Quaternary_Filter_i;

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, Quaternary_e quaternary) override
            {
                if (item) {
                    if (quaternary == Quaternary_e::ALL) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Male() || actor_base->Is_Female()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else if (quaternary == Quaternary_e::A) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Male()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else if (quaternary == Quaternary_e::B) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Female()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else {
                        return Filter_Ternary_e::INVALID;
                    }
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Male_Female_Filter_t(filter_state).Execute(Male_Female_Quaternary());

        class Unique_Generic_Filter_t : public Quaternary_Filter_i<Leveled_Actor_Base_t*>
        {
        public:
            using Quaternary_Filter_i::Quaternary_Filter_i;

            virtual Filter_Ternary_e Is_Match(Leveled_Actor_Base_t* item, Quaternary_e quaternary) override
            {
                if (item) {
                    if (quaternary == Quaternary_e::ALL) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Unique() || actor_base->Is_Generic()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else if (quaternary == Quaternary_e::A) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Unique()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else if (quaternary == Quaternary_e::B) {
                        Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            if (actor_base && actor_base->Is_Generic()) {
                                return Filter_Ternary_e::IS_MATCH;
                            }
                        }
                        return Filter_Ternary_e::ISNT_MATCH;
                    } else {
                        return Filter_Ternary_e::INVALID;
                    }
                } else {
                    return Filter_Ternary_e::INVALID;
                }
            }
        };
        Unique_Generic_Filter_t(filter_state).Execute(Unique_Generic_Quaternary());

        return filter_state.read;
    }

    void Leveled_Bases_Filter_t::Clear()
    {
        Mod_Argument("");
        Mod_Do_Negate(false);

        Race_Argument("");
        Race_Do_Negate(false);

        Base_Argument("");
        Base_Do_Negate(false);

        Relation_Argument(Relation_e::NONE);
        Relation_Do_Negate(false);

        Male_Female_Quaternary(Quaternary_e::NONE);
        Unique_Generic_Quaternary(Quaternary_e::NONE);
    }

    template <typename Type>
    class Argument_i
    {
    public:
        virtual         ~Argument_i()               = default;
        virtual Type    operator()()                = 0;
        virtual void    operator()(Type argument)   = 0;
    };

    template <typename Item_t>
    class Selectable_String_i
    {
    public:
        virtual             ~Selectable_String_i()      = default;
        virtual String_t    operator()(Item_t& item)    = 0;
    };

    template <typename Item_t>
    class Selectable_Strings_i
    {
    public:
        virtual                     ~Selectable_Strings_i()     = default;
        virtual Vector_t<String_t>  operator()(Item_t& item)    = 0;
    };

    static Vector_t<Leveled_Actor_Base_t*> Selectable_Items(Leveled_Bases_Filter_t* self, Argument_i<String_t>& argument)
    {
        Vector_t<Leveled_Actor_Base_t*> items;
        if (self->Options()->Do_Smart_Select()) {
            String_t current = argument();
            argument("");
            self->List()->do_update_items = true;
            items = self->List()->Items();
            argument(current);
        } else {
            items = Leveled_Actor_Base_t::Leveled_Actor_Bases();
        }

        return items;
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

    static Vector_t<String_t> Selectable_Strings(Leveled_Bases_Filter_t* self,
                                                 Argument_i<String_t>& argument,
                                                 Selectable_String_i<Leveled_Actor_Base_t*>& selector)
    {
        Vector_t<Leveled_Actor_Base_t*> items = Selectable_Items(self, argument);

        Vector_t<String_t> results;
        results.reserve(items.size() + 1);
        results.push_back(" Any ");

        for (Index_t idx = 0, end = items.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* item = items.at(idx);
            if (item) {
                String_t string = selector(item);
                if (string.data && string.data[0] && !results.Has(string)) {
                    results.push_back(string);
                }
            }
        }

        Sort_Selectables(results);

        return results;
    }

    static Vector_t<String_t> Selectable_Strings(Leveled_Bases_Filter_t* self,
                                                 Argument_i<String_t>& argument,
                                                 Selectable_Strings_i<Leveled_Actor_Base_t*>& selector)
    {
        Vector_t<Leveled_Actor_Base_t*> items = Selectable_Items(self, argument);

        Vector_t<String_t> results;
        results.reserve(items.size() + 1);
        results.push_back(" Any ");

        for (Index_t idx = 0, end = items.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* item = items.at(idx);
            if (item) {
                Vector_t<String_t> strings = selector(item);
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

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Mods()
    {
        class String_Argument_t : public Argument_i<String_t>
        {
        public:
            Leveled_Bases_Filter_t* self;
            String_Argument_t(Leveled_Bases_Filter_t* self) :
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

        class Selectable_Strings_t : public Selectable_Strings_i<Leveled_Actor_Base_t*>
        {
        public:
            Leveled_Bases_Filter_t* self;
            Selectable_Strings_t(Leveled_Bases_Filter_t* self) :
                self(self)
            {
            }
            Vector_t<String_t> operator()(Leveled_Actor_Base_t*& item)
            {
                return item->Mod_Names();
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Races()
    {
        class String_Argument_t : public Argument_i<String_t>
        {
        public:
            Leveled_Bases_Filter_t* self;
            String_Argument_t(Leveled_Bases_Filter_t* self) :
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

        class Selectable_String_t : public Selectable_Strings_i<Leveled_Actor_Base_t*>
        {
        public:
            Leveled_Bases_Filter_t* self;
            Selectable_String_t(Leveled_Bases_Filter_t* self) :
                self(self)
            {
            }
            Vector_t<String_t> operator()(Leveled_Actor_Base_t*& item)
            {
                return item->Race_Names();
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Bases()
    {
        class String_Argument_t : public Argument_i<String_t>
        {
        public:
            Leveled_Bases_Filter_t* self;
            String_Argument_t(Leveled_Bases_Filter_t* self) :
                self(self)
            {
            }
            String_t operator()()
            {
                return self->Base_Argument();
            }
            void operator()(String_t argument)
            {
                self->Base_Argument(argument);
            }
        } string_argument(this);

        class Selectable_String_t : public Selectable_Strings_i<Leveled_Actor_Base_t*>
        {
        public:
            Leveled_Bases_Filter_t* self;
            Selectable_String_t(Leveled_Bases_Filter_t* self) :
                self(self)
            {
            }
            Vector_t<String_t> operator()(Leveled_Actor_Base_t*& item)
            {
                return item->Actor_Base_Names();
            }
        } selectable_string(this);

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Relations()
    {
        class String_Argument_t : public Argument_i<String_t>
        {
        public:
            Leveled_Bases_Filter_t* self;
            String_Argument_t(Leveled_Bases_Filter_t* self) :
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

        class Selectable_String_t : public Selectable_Strings_i<Leveled_Actor_Base_t*>
        {
        public:
            Leveled_Bases_Filter_t* self;
            Actor_Base_t* player_actor_base;
            Selectable_String_t(Leveled_Bases_Filter_t* self, Actor_Base_t* player_actor_base) :
                self(self), player_actor_base(player_actor_base)
            {
            }
            Vector_t<String_t> operator()(Leveled_Actor_Base_t*& item)
            {
                Vector_t<String_t> results;
                results.reserve(16);

                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (actor_base) {
                        Relation_e relation = Relation_e::Between(player_actor_base, actor_base);
                        if (relation != Relation_e::NONE) {
                            String_t relation_name = std::string(" ") + Relation_e::To_String(relation) + " ";
                            if (!results.Has(relation_name)) {
                                results.push_back(relation_name);
                            }
                        }
                    }
                }

                return results;
            }
        } selectable_string(this, Consts_t::Skyrim_Player_Actor_Base());

        return Selectable_Strings(this, string_argument, selectable_string);
    }

    void Leveled_Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Leveled Bases: Filter ");

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

        mcm->Add_Header_Option(" Base ");
        mcm->Add_Header_Option("");
        Base_Search_Option_Variable()->Value(mcm->Add_Input_Option(" Search ", Base_Argument()));
        Base_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", "..."));
        Base_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Base_Do_Negate()));
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Relation ");
        mcm->Add_Header_Option("");
        Relation_Select_Option_Variable()->Value(mcm->Add_Menu_Option(" Select ", Relation_Argument_String()));
        Relation_Negate_Option_Variable()->Value(mcm->Add_Toggle_Option(" Negate ", Relation_Do_Negate()));

        mcm->Add_Header_Option(" Other ");
        mcm->Add_Header_Option("");

        Quaternary_e male_female_quaternary = Male_Female_Quaternary();
        Has_Male_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Has Male ",
                                   male_female_quaternary == Quaternary_e::A ||
                                   male_female_quaternary == Quaternary_e::ALL)
        );
        Has_Female_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Has Female ",
                                   male_female_quaternary == Quaternary_e::B ||
                                   male_female_quaternary == Quaternary_e::ALL)
        );

        Quaternary_e unique_generic_quaternary = Unique_Generic_Quaternary();
        Has_Unique_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Has Unique ",
                                   unique_generic_quaternary == Quaternary_e::A ||
                                   unique_generic_quaternary == Quaternary_e::ALL)
        );
        Has_Generic_Option_Variable()->Value(
            mcm->Add_Toggle_Option(" Has Generic ",
                                   unique_generic_quaternary == Quaternary_e::B ||
                                   unique_generic_quaternary == Quaternary_e::ALL)
        );

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
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
        } else if (option == Base_Negate_Option_Variable()->Value()) {
            Bool_t value = Base_Do_Negate();
            Base_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Relation_Negate_Option_Variable()->Value()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Has_Male_Option_Variable()->Value()) {
            mcm->Toggle_Quaternary(Male_Female_Quaternary_Variable(), option, option + 1, Quaternary_e::A);
        } else if (option == Has_Female_Option_Variable()->Value()) {
            mcm->Toggle_Quaternary(Male_Female_Quaternary_Variable(), option - 1, option, Quaternary_e::B);

        } else if (option == Has_Unique_Option_Variable()->Value()) {
            mcm->Toggle_Quaternary(Unique_Generic_Quaternary_Variable(), option, option + 1, Quaternary_e::A);
        } else if (option == Has_Generic_Option_Variable()->Value()) {
            mcm->Toggle_Quaternary(Unique_Generic_Quaternary_Variable(), option - 1, option, Quaternary_e::B);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
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
        } else if (option == Base_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Bases());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Relation_Select_Option_Variable()->Value()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
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
        } else if (option == Base_Select_Option_Variable()->Value()) {
            if (idx > -1) {
                String_t value = "";
                if (idx > 0) {
                    Vector_t<String_t> bases = Selectable_Bases();
                    if (idx < bases.size()) {
                        value = bases[idx];
                    }
                }
                Base_Argument(value);
                mcm->Input_Option_Value(Base_Search_Option_Variable()->Value(), value, true);
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

    void Leveled_Bases_Filter_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Search_Option_Variable()->Value()) {
            Mod_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Race_Search_Option_Variable()->Value()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Base_Search_Option_Variable()->Value()) {
            Base_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
