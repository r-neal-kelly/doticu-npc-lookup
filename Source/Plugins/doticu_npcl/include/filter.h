/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/relation.h"

#include "intrinsic.h"

namespace doticu_npcl {

    using Binary_e      = skylib::Binary_e;
    using Relation_e    = skylib::Relation_e;

    using CString_t     = skylib::CString_t;

    using Actor_t               = skylib::Actor_t;
    using Actor_Base_t          = skylib::Actor_Base_t;
    using Cell_t                = skylib::Cell_t;
    using Form_t                = skylib::Form_t;
    using Leveled_Actor_Base_t  = skylib::Leveled_Actor_Base_t;
    using Loaded_Actor_t        = skylib::Loaded_Actor_t;
    using Location_t            = skylib::Location_t;
    using Mod_t                 = skylib::Mod_t;
    using Race_t                = skylib::Race_t;

    class Filter_e : public Binary_e
    {
    public:
        enum : skylib::s8
        {
            INVALID     = Binary_e::NONE,
            IS_MATCH    = Binary_e::A,
            ISNT_MATCH  = Binary_e::B,
        };
        using Binary_e::Binary_e;
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

        Vector_t<Item_t>* Results()
        {
            return read;
        }
    };

    template <typename Item_t>
    class Filter_i
    {
    public:
        Filter_State_t<Item_t>& state;

        Filter_i(Filter_State_t<Item_t>& state) :
            state(state)
        {
        }
    };

    template <typename Item_t>
    class String_Filter_i : public Filter_i<Item_t>
    {
    public:
        String_Filter_i(Filter_State_t<Item_t>& state,
                        String_t string,
                        Bool_t do_negate,
                        Filter_e(*Compare)(Item_t, String_t)) :
            Filter_i<Item_t>(state)
        {
            if (string) {
                if (do_negate) {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Compare(item, string) == Filter_e::ISNT_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Compare(item, string) == Filter_e::IS_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                }
                state.Swap();
            }
        }
    };

    template <typename Item_t>
    class Relation_Filter_i : public Filter_i<Item_t>
    {
    public:
        Relation_Filter_i(Filter_State_t<Item_t>& state,
                          Actor_Base_t* base_to_compare,
                          Relation_e relation,
                          Bool_t do_negate,
                          Filter_e(*Compare)(Item_t, Actor_Base_t*, Relation_e)) :
            Filter_i<Item_t>(state)
        {
            if (relation != Relation_e::NONE) {
                if (do_negate) {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (base_to_compare && Compare(item, base_to_compare, relation) == Filter_e::ISNT_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (base_to_compare && Compare(item, base_to_compare, relation) == Filter_e::IS_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                }
                state.Swap();
            }
        }
    };

    template <typename Item_t>
    class Binary_Filter_i : public Filter_i<Item_t>
    {
    public:
        Binary_Filter_i(Filter_State_t<Item_t>& state,
                        Binary_e binary,
                        Filter_e(*Compare)(Item_t, Binary_e)) :
            Filter_i<Item_t>(state)
        {
            if (binary != Binary_e::NONE) {
                for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Item_t item = state.read->at(idx);
                    if (Compare(item, binary) == Filter_e::IS_MATCH) {
                        state.write->push_back(item);
                    }
                }
                state.Swap();
            }
        }
    };

    template <typename Item_t>
    class Mod_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Mod_Filter_t<Form_t*> : public String_Filter_i<Form_t*>
    {
    public:
        using Item_t = Form_t*;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->form_files) {
                for (Index_t idx = 0, end = item->form_files->count; idx < end; idx += 1) {
                    Mod_t* mod = item->form_files->entries[idx];
                    if (mod) {
                        if (CString_t::Is_Length_Greater_Than(string, 1)) {
                            if (CString_t::Contains(mod->Name(), string, true)) {
                                return Filter_e::IS_MATCH;
                            }
                        } else {
                            if (CString_t::Starts_With(mod->Name(), string, true)) {
                                return Filter_e::IS_MATCH;
                            }
                        }
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Mod_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            return Mod_Filter_t<Form_t*>::Compare(item, string);
        }
    };

    template <>
    class Mod_Filter_t<Leveled_Actor_Base_t*> : public String_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            return Mod_Filter_t<Form_t*>::Compare(item, string);
        }
    };

    template <>
    class Mod_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Mod_Filter_t<Form_t*>::Compare(item.actor, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Race_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Race_Filter_t<Race_t*> : public String_Filter_i<Race_t*>
    {
    public:
        using Item_t = Race_t*;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Name(), string, true) ||
                        CString_t::Contains(item->Get_Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Name(), string, true) ||
                        CString_t::Starts_With(item->Get_Editor_ID(), string, true) ||
                        CString_t::Starts_With(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Race_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item) {
                return Race_Filter_t<Race_t*>::Compare(item->Race(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Race_Filter_t<Leveled_Actor_Base_t*> : public String_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (Race_Filter_t<Actor_Base_t*>::Compare(actor_base, string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Race_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Race_Filter_t<Race_t*>::Compare(item.actor->Race(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Base_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Base_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Base_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Name(), string, true) ||
                        CString_t::Contains(item->Get_Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Name(), string, true) ||
                        CString_t::Starts_With(item->Get_Editor_ID(), string, true) ||
                        CString_t::Starts_With(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Base_Filter_t<Leveled_Actor_Base_t*> : public String_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Base_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (Base_Filter_t<Actor_Base_t*>::Compare(actor_base, string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Base_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Base_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Base_Filter_t<Actor_Base_t*>::Compare(item.actor->Actor_Base(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Template_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Template_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Template_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                for (Actor_Base_t* it = item->template_list; it != nullptr; it = it->template_list) {
                    if (Base_Filter_t<Actor_Base_t*>::Compare(it, string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Template_Filter_t<Leveled_Actor_Base_t*> : public String_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Template_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Template_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Template_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Template_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Template_Filter_t<Actor_Base_t*>::Compare(item.actor->Actor_Base(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Reference_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Reference_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Reference_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Name(), string, true) ||
                        CString_t::Contains(item->Base_Name(), string, true) ||
                        CString_t::Contains(item->Get_Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Name(), string, true) ||
                        CString_t::Starts_With(item->Base_Name(), string, true) ||
                        CString_t::Starts_With(item->Get_Editor_ID(), string, true) ||
                        CString_t::Starts_With(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Reference_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Reference_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Reference_Filter_t<Actor_t*>::Compare(item.actor, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Location_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Location_Filter_t<Cell_t*> : public String_Filter_i<Cell_t*>
    {
    public:
        using Item_t = Cell_t*;

    public:
        Location_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Location_t*> locations = item->Locations();
                for (Index_t idx = 0, end = locations.size(); idx < end; idx += 1) {
                    Location_t* location = locations[idx];
                    if (location) {
                        if (CString_t::Is_Length_Greater_Than(string, 1)) {
                            if (CString_t::Contains(location->Name(), string, true) ||
                                CString_t::Contains(location->Get_Editor_ID(), string, true) ||
                                CString_t::Contains(location->Form_ID_String(), string, true)) {
                                return Filter_e::IS_MATCH;
                            }
                        } else {
                            if (CString_t::Starts_With(location->Name(), string, true) ||
                                CString_t::Starts_With(location->Get_Editor_ID(), string, true) ||
                                CString_t::Starts_With(location->Form_ID_String(), string, true)) {
                                return Filter_e::IS_MATCH;
                            }
                        }
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Location_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Location_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Location_Filter_t<Cell_t*>::Compare(item.cell, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Cell_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Cell_Filter_t<Cell_t*> : public String_Filter_i<Cell_t*>
    {
    public:
        using Item_t = Cell_t*;

    public:
        Cell_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Name(), string, true) ||
                        CString_t::Contains(item->Get_Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Name(), string, true) ||
                        CString_t::Starts_With(item->Get_Editor_ID(), string, true) ||
                        CString_t::Starts_With(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Cell_Filter_t<Loaded_Actor_t> : public String_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Cell_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item.Is_Valid()) {
                return Cell_Filter_t<Cell_t*>::Compare(item.cell, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Relation_Filter_t : public Relation_Filter_i<Item_t>
    {
    };

    template <>
    class Relation_Filter_t<Actor_Base_t*> : public Relation_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Relation_Filter_t(Filter_State_t<Item_t>& state, Actor_Base_t* base_to_compare, Relation_e relation, Bool_t do_negate) :
            Relation_Filter_i<Item_t>(state, base_to_compare, relation, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Actor_Base_t* base_to_compare, Relation_e relation)
        {
            if (item) {
                if (Relation_e::Between(item, base_to_compare) == relation) {
                    return Filter_e::IS_MATCH;
                } else {
                    return Filter_e::ISNT_MATCH;
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Relation_Filter_t<Leveled_Actor_Base_t*> : public Relation_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Relation_Filter_t(Filter_State_t<Item_t>& state, Actor_Base_t* base_to_compare, Relation_e relation, Bool_t do_negate) :
            Relation_Filter_i<Item_t>(state, base_to_compare, relation, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Actor_Base_t* base_to_compare, Relation_e relation)
        {
            if (item) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (Relation_Filter_t<Actor_Base_t*>::Compare(actor_base, base_to_compare, relation) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Relation_Filter_t<Loaded_Actor_t> : public Relation_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Relation_Filter_t(Filter_State_t<Item_t>& state, Actor_Base_t* base_to_compare, Relation_e relation, Bool_t do_negate) :
            Relation_Filter_i<Item_t>(state, base_to_compare, relation, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Actor_Base_t* base_to_compare, Relation_e relation)
        {
            if (item.Is_Valid()) {
                return Relation_Filter_t<Actor_Base_t*>::Compare(item.actor->Actor_Base(), base_to_compare, relation);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Male_Female_Filter_t : public Binary_Filter_i<Item_t>
    {
    };

    template <>
    class Male_Female_Filter_t<Actor_Base_t*> : public Binary_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Male_Female_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item) {
                if (binary == Binary_e::BOTH) {
                    if (item->Is_Male() || item->Is_Female()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::A) {
                    if (item->Is_Male()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::B) {
                    if (item->Is_Female()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    return Filter_e::INVALID;
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Male_Female_Filter_t<Leveled_Actor_Base_t*> : public Binary_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Male_Female_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (Male_Female_Filter_t<Actor_Base_t*>::Compare(actor_base, binary) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Male_Female_Filter_t<Loaded_Actor_t> : public Binary_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Male_Female_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item.Is_Valid()) {
                return Male_Female_Filter_t<Actor_Base_t*>::Compare(item.actor->Actor_Base(), binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Unique_Generic_Filter_t : public Binary_Filter_i<Item_t>
    {
    };

    template <>
    class Unique_Generic_Filter_t<Actor_Base_t*> : public Binary_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Unique_Generic_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item) {
                if (binary == Binary_e::BOTH) {
                    if (item->Is_Unique() || item->Is_Generic()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::A) {
                    if (item->Is_Unique()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::B) {
                    if (item->Is_Generic()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    return Filter_e::INVALID;
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Unique_Generic_Filter_t<Leveled_Actor_Base_t*> : public Binary_Filter_i<Leveled_Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;

    public:
        Unique_Generic_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item) {
                Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Actor_Base_t* actor_base = actor_bases[idx];
                    if (Unique_Generic_Filter_t<Actor_Base_t*>::Compare(actor_base, binary) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Unique_Generic_Filter_t<Loaded_Actor_t> : public Binary_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Unique_Generic_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item.Is_Valid()) {
                return Unique_Generic_Filter_t<Actor_Base_t*>::Compare(item.actor->Actor_Base(), binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <typename Item_t>
    class Interior_Exterior_Filter_t : public Binary_Filter_i<Item_t>
    {
    };

    template <>
    class Interior_Exterior_Filter_t<Cell_t*> : public Binary_Filter_i<Cell_t*>
    {
    public:
        using Item_t = Cell_t*;

    public:
        Interior_Exterior_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                if (binary == Binary_e::BOTH) {
                    if (item->Is_Interior() || item->Is_Exterior()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::A) {
                    if (item->Is_Interior()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::B) {
                    if (item->Is_Exterior()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    return Filter_e::INVALID;
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Interior_Exterior_Filter_t<Loaded_Actor_t> : public Binary_Filter_i<Loaded_Actor_t>
    {
    public:
        using Item_t = Loaded_Actor_t;

    public:
        Interior_Exterior_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item.Is_Valid()) {
                return Interior_Exterior_Filter_t<Cell_t*>::Compare(item.cell, binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

}
