/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/vitality.h"
#include "doticu_skylib/worldspace.h"

#include "intrinsic.h"
#include "cached_leveled.h"

namespace doticu_npcl {

    using Binary_e              = skylib::Binary_e;
    using Relation_e            = skylib::Relation_e;
    using Vitality_e            = skylib::Vitality_e;

    using CString_t             = skylib::CString_t;

    using Actor_t               = skylib::Actor_t;
    using Actor_Base_t          = skylib::Actor_Base_t;
    using Cell_t                = skylib::Cell_t;
    using Faction_t             = skylib::Faction_t;
    using Faction_And_Rank_t    = skylib::Faction_And_Rank_t;
    using Form_t                = skylib::Form_t;
    using Keyword_t             = skylib::Keyword_t;
    using Leveled_Actor_Base_t  = skylib::Leveled_Actor_Base_t;
    using Location_t            = skylib::Location_t;
    using Mod_t                 = skylib::Mod_t;
    using Quest_t               = skylib::Quest_t;
    using Race_t                = skylib::Race_t;
    using Worldspace_t          = skylib::Worldspace_t;

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
    class Vitality_Filter_i : public Filter_i<Item_t>
    {
    public:
        Vitality_Filter_i(Filter_State_t<Item_t>& state,
                          Vitality_e vitality,
                          Bool_t do_negate,
                          Filter_e(*Compare)(Item_t, Vitality_e)) :
            Filter_i<Item_t>(state)
        {
            if (vitality != Vitality_e::NONE) {
                if (do_negate) {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Compare(item, vitality) == Filter_e::ISNT_MATCH) {
                            state.write->push_back(item);
                        }
                    }
                } else {
                    for (Index_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                        Item_t item = state.read->at(idx);
                        if (Compare(item, vitality) == Filter_e::IS_MATCH) {
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

    /* Mod */

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
            if (item && item->form_mods) {
                for (Index_t idx = 0, end = item->form_mods->count; idx < end; idx += 1) {
                    Mod_t* mod = item->form_mods->entries[idx];
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
            if (item && item->Is_Valid()) {
                Item_t highest_static = item->Highest_Static();
                if (highest_static) {
                    return Mod_Filter_t<Form_t*>::Compare(highest_static, string);
                } else {
                    return Mod_Filter_t<Form_t*>::Compare(item, string);
                }
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Mod_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                return Mod_Filter_t<Form_t*>::Compare(item->leveled, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Mod_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Mod_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Mod_Filter_t<Form_t*>::Compare(item, string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Race */

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
    class Race_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Race_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], string) == Filter_e::IS_MATCH) {
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
    class Race_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Race_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Race_Filter_t<Race_t*>::Compare(item->Race(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Base */

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
    class Base_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Base_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Base_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], string) == Filter_e::IS_MATCH) {
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
    class Base_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Base_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Base_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Template */

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
    class Template_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Template_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
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
    class Template_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Template_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Template_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Faction */

    template <typename Item_t>
    class Faction_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Faction_Filter_t<Faction_t*> : public String_Filter_i<Faction_t*>
    {
    public:
        using Item_t = Faction_t*;

    public:
        Faction_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Name(), string, true) ||
                        CString_t::Contains(item->Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Name(), string, true) ||
                        CString_t::Starts_With(item->Editor_ID(), string, true) ||
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
    class Faction_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Faction_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Faction_And_Rank_t> factions_and_ranks = item->Factions_And_Ranks();
                for (Index_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
                    Faction_And_Rank_t& faction_and_rank = factions_and_ranks[idx];
                    if (Faction_Filter_t<Faction_t*>::Compare(faction_and_rank.faction, string) == Filter_e::IS_MATCH) {
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
    class Faction_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Faction_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Faction_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], string) == Filter_e::IS_MATCH) {
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
    class Faction_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Faction_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Faction_And_Rank_t> factions_and_ranks = item->Factions_And_Ranks();
                for (Index_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
                    Faction_And_Rank_t& faction_and_rank = factions_and_ranks[idx];
                    if (Faction_Filter_t<Faction_t*>::Compare(faction_and_rank.faction, string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Keyword */

    template <typename Item_t>
    class Keyword_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Keyword_Filter_t<Keyword_t*> : public String_Filter_i<Keyword_t*>
    {
    public:
        using Item_t = Keyword_t*;

    public:
        Keyword_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                if (CString_t::Is_Length_Greater_Than(string, 1)) {
                    if (CString_t::Contains(item->Get_Editor_ID(), string, true) ||
                        CString_t::Contains(item->Form_ID_String(), string, true)) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else {
                    if (CString_t::Starts_With(item->Get_Editor_ID(), string, true) ||
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
    class Keyword_Filter_t<Actor_Base_t*> : public String_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Keyword_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Keyword_t*> keywords = item->Keywords();
                for (Index_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (Keyword_Filter_t<Keyword_t*>::Compare(keywords[idx], string) == Filter_e::IS_MATCH) {
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
    class Keyword_Filter_t<Cached_Leveled_t*> : public String_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Keyword_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Keyword_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], string) == Filter_e::IS_MATCH) {
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
    class Keyword_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Keyword_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Keyword_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Reference */

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

    /* Worldspace */

    template <typename Item_t>
    class Worldspace_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Worldspace_Filter_t<Worldspace_t*> : public String_Filter_i<Worldspace_t*>
    {
    public:
        using Item_t = Worldspace_t*;

    public:
        Worldspace_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
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
    class Worldspace_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Worldspace_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<some<Worldspace_t*>> worldspaces = item->Worldspaces();
                for (Index_t idx = 0, end = worldspaces.size(); idx < end; idx += 1) {
                    if (Worldspace_Filter_t<Worldspace_t*>::Compare(worldspaces[idx], string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Location */

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
    class Location_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Location_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Location_Filter_t<Cell_t*>::Compare(item->Cell(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Cell */

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
    class Cell_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Cell_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                return Cell_Filter_t<Cell_t*>::Compare(item->Cell(), string);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Quest */

    template <typename Item_t>
    class Quest_Filter_t : public String_Filter_i<Item_t>
    {
    };

    template <>
    class Quest_Filter_t<Quest_t*> : public String_Filter_i<Quest_t*>
    {
    public:
        using Item_t = Quest_t*;

    public:
        Quest_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
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
    class Quest_Filter_t<Actor_t*> : public String_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Quest_Filter_t(Filter_State_t<Item_t>& state, String_t string, Bool_t do_negate) :
            String_Filter_i<Item_t>(state, string, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, String_t string)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Quest_t*> quests = item->Quests();
                for (Index_t idx = 0, end = quests.size(); idx < end; idx += 1) {
                    if (Quest_Filter_t<Quest_t*>::Compare(quests[idx], string) == Filter_e::IS_MATCH) {
                        return Filter_e::IS_MATCH;
                    }
                }
                return Filter_e::ISNT_MATCH;
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Relation */

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
    class Relation_Filter_t<Cached_Leveled_t*> : public Relation_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Relation_Filter_t(Filter_State_t<Item_t>& state, Actor_Base_t* base_to_compare, Relation_e relation, Bool_t do_negate) :
            Relation_Filter_i<Item_t>(state, base_to_compare, relation, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Actor_Base_t* base_to_compare, Relation_e relation)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Relation_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], base_to_compare, relation) == Filter_e::IS_MATCH) {
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
    class Relation_Filter_t<Actor_t*> : public Relation_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Relation_Filter_t(Filter_State_t<Item_t>& state, Actor_Base_t* base_to_compare, Relation_e relation, Bool_t do_negate) :
            Relation_Filter_i<Item_t>(state, base_to_compare, relation, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Actor_Base_t* base_to_compare, Relation_e relation)
        {
            if (item && item->Is_Valid()) {
                return Relation_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), base_to_compare, relation);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Vitality */

    template <typename Item_t>
    class Vitality_Filter_t : public Vitality_Filter_i<Item_t>
    {
    };

    template <>
    class Vitality_Filter_t<Vitality_e> : public Vitality_Filter_i<Vitality_e>
    {
    public:
        using Item_t = Vitality_e;

    public:
        Vitality_Filter_t(Filter_State_t<Item_t>& state, Vitality_e vitality, Bool_t do_negate) :
            Vitality_Filter_i<Item_t>(state, vitality, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Vitality_e vitality)
        {
            if (item != Vitality_e::NONE) {
                if (item == vitality) {
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
    class Vitality_Filter_t<Actor_Base_t*> : public Vitality_Filter_i<Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Vitality_Filter_t(Filter_State_t<Item_t>& state, Vitality_e vitality, Bool_t do_negate) :
            Vitality_Filter_i<Item_t>(state, vitality, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Vitality_e vitality)
        {
            if (item && item->Is_Valid()) {
                return Vitality_Filter_t<Vitality_e>::Compare(item->Vitality(), vitality);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    template <>
    class Vitality_Filter_t<Cached_Leveled_t*> : public Vitality_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Vitality_Filter_t(Filter_State_t<Item_t>& state, Vitality_e vitality, Bool_t do_negate) :
            Vitality_Filter_i<Item_t>(state, vitality, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Vitality_e vitality)
        {
            if (item && item->leveled && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Vitality_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], vitality) == Filter_e::IS_MATCH) {
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
    class Vitality_Filter_t<Actor_t*> : public Vitality_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Vitality_Filter_t(Filter_State_t<Item_t>& state, Vitality_e vitality, Bool_t do_negate) :
            Vitality_Filter_i<Item_t>(state, vitality, do_negate, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Vitality_e vitality)
        {
            if (item && item->Is_Valid()) {
                return Vitality_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), vitality);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Male_Female */

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
    class Male_Female_Filter_t<Cached_Leveled_t*> : public Binary_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Male_Female_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Male_Female_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], binary) == Filter_e::IS_MATCH) {
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
    class Male_Female_Filter_t<Actor_t*> : public Binary_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Male_Female_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                return Male_Female_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Unique_Generic */

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
    class Unique_Generic_Filter_t<Cached_Leveled_t*> : public Binary_Filter_i<Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Unique_Generic_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    if (Unique_Generic_Filter_t<Actor_Base_t*>::Compare(actor_bases[idx], binary) == Filter_e::IS_MATCH) {
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
    class Unique_Generic_Filter_t<Actor_t*> : public Binary_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Unique_Generic_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                return Unique_Generic_Filter_t<Actor_Base_t*>::Compare(item->Actor_Base(), binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Interior_Exterior */

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
    class Interior_Exterior_Filter_t<Actor_t*> : public Binary_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Interior_Exterior_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                return Interior_Exterior_Filter_t<Cell_t*>::Compare(item->Cell(), binary);
            } else {
                return Filter_e::INVALID;
            }
        }
    };

    /* Alive_Dead */

    template <typename Item_t>
    class Alive_Dead_Filter_t : public Binary_Filter_i<Item_t>
    {
    };

    template <>
    class Alive_Dead_Filter_t<Actor_t*> : public Binary_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Alive_Dead_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                if (binary == Binary_e::BOTH) {
                    if (item->Is_Alive() || item->Is_Dead()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::A) {
                    if (item->Is_Alive()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::B) {
                    if (item->Is_Dead()) {
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

    /* Is_Teammate */

    template <typename Item_t>
    class Is_Teammate_Filter_t : public Binary_Filter_i<Item_t>
    {
    };

    template <>
    class Is_Teammate_Filter_t<Actor_t*> : public Binary_Filter_i<Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Is_Teammate_Filter_t(Filter_State_t<Item_t>& state, Binary_e binary) :
            Binary_Filter_i<Item_t>(state, binary, &Compare)
        {
        }

        static Filter_e Compare(Item_t item, Binary_e binary)
        {
            if (item && item->Is_Valid()) {
                if (binary == Binary_e::BOTH) {
                    if (item->Is_Player_Teammate() || item->Isnt_Player_Teammate()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::A) {
                    if (item->Is_Player_Teammate()) {
                        return Filter_e::IS_MATCH;
                    } else {
                        return Filter_e::ISNT_MATCH;
                    }
                } else if (binary == Binary_e::B) {
                    if (item->Isnt_Player_Teammate()) {
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

}
