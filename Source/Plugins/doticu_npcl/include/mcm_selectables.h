/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "cached_leveled.h"
#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    /* Data */

    template <typename Base_t, typename Item_t>
    class Selectable_Data_t
    {
    public:
        using Filter_t      = std::remove_pointer_t<decltype(Base_t::Self()->Filter()())>;

        using String_f      = V::Variable_tt<String_t>&(Filter_t::*)();
        using Relation_f    = V::Variable_tt<Relation_e>&(Filter_t::*)();
        using Vitality_f    = V::Variable_tt<Vitality_e>& (Filter_t::*)();
        using Binary_f      = V::Variable_tt<Binary_e>&(Filter_t::*)();

        using Select_f          = void(*)(Item_t, Vector_t<String_t>&);
        using Select_Relation_f = void(*)(Item_t, Actor_Base_t*, Vector_t<String_t>&);

    public:
        Vector_t<Item_t>    items;
        Vector_t<String_t>  buffer;
        Vector_t<String_t>  results;

        Selectable_Data_t(String_f string_f, Select_f select_f)
        {
            Init<String_f, String_t>(string_f, "");
            Select(select_f);
            Sort();
        }

        Selectable_Data_t(Relation_f relation_f, Select_Relation_f select_f, Actor_Base_t* base_to_compare)
        {
            Init<Relation_f, Relation_e>(relation_f, Relation_e::_NONE_);
            Select(select_f, base_to_compare);
            Sort();
        }

        Selectable_Data_t(Vitality_f vitality_f, Select_f select_f)
        {
            Init<Vitality_f, Vitality_e>(vitality_f, Vitality_e::_NONE_);
            Select(select_f);
            Sort();
        }

        Selectable_Data_t(Binary_f binary_f, Select_f select_f)
        {
            Init<Binary_f, Binary_e>(binary_f, Binary_e::NONE);
            Select(select_f);
            Sort();
        }

        template <typename Smart_f, typename Value_t>
        inline void Init(Smart_f smart_f, Value_t temp_value)
        {
            auto self = Base_t::Self();
            auto list = self->List();
            auto filter = self->Filter();
            auto options = self->Options();

            if (options->Do_Smart_Select()) {
                Value_t current = (filter()->*smart_f)();
                (filter()->*smart_f)() = temp_value;
                list->do_update_items = true;
                items = list->Items();
                (filter()->*smart_f)() = current;
            } else {
                items = list->Default_Items();
            }

            Reserve();
        }

        inline void Reserve()
        {
            size_t item_count = items.size();
            if (item_count > 2048) {
                results.reserve(2048);
            } else {
                results.reserve(item_count);
            }
            buffer.reserve(128);
        }

        inline void Select(Select_f select_f)
        {
            results.push_back(Main_t::ANY);
            for (size_t idx = 0, end = items.size(); idx < end; idx += 1) {
                Item_t item = items.at(idx);
                if (item) {
                    select_f(item, buffer);
                    for (size_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                        String_t string = buffer[idx];
                        if (string && !results.Has(string)) {
                            results.push_back(string);
                        }
                    }
                    buffer.clear();
                }
            }
        }

        inline void Select(Select_Relation_f select_f, Actor_Base_t* base_to_compare)
        {
            results.push_back(Main_t::ANY);
            for (size_t idx = 0, end = items.size(); idx < end; idx += 1) {
                Item_t item = items.at(idx);
                if (item) {
                    select_f(item, base_to_compare, buffer);
                    for (size_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                        String_t string = buffer[idx];
                        if (string && !results.Has(string)) {
                            results.push_back(string);
                        }
                    }
                    buffer.clear();
                }
            }
        }

        inline void Sort()
        {
            static auto comparator = [](String_t* str_a, String_t* str_b)->Int_t
            {
                return Main_t::String_Comparator(
                    str_a ? *str_a : "",
                    str_b ? *str_b : ""
                );
            };
            results.Sort(comparator, 1);
        }

        inline Vector_t<String_t> Results()
        {
            return results;
        }
    };

    /* Mods */

    template <typename Base_t, typename Item_t>
    class Selectable_Mods_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Mods_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Mod_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Mods_t : public Selectable_Mods_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Mods_t<Base_t, Form_t*> : public Selectable_Mods_i<Base_t, Form_t*>
    {
    public:
        using Item_t = Form_t*;

    public:
        Selectable_Mods_t() :
            Selectable_Mods_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                item->Mod_Names(output);
            }
        }
    };

    template <typename Base_t>
    class Selectable_Mods_t<Base_t, Actor_Base_t*> : public Selectable_Mods_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Mods_t() :
            Selectable_Mods_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            Selectable_Mods_t<Base_t, Form_t*>::Select(item, output);
        }
    };

    template <typename Base_t>
    class Selectable_Mods_t<Base_t, Cached_Leveled_t*> : public Selectable_Mods_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Mods_t() :
            Selectable_Mods_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            Selectable_Mods_t<Base_t, Form_t*>::Select(item->leveled(), output);
        }
    };

    template <typename Base_t>
    class Selectable_Mods_t<Base_t, Actor_t*> : public Selectable_Mods_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Mods_t() :
            Selectable_Mods_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Mods_t<Base_t, Form_t*>::Select(item, output);
            }
        }
    };

    /* Races */

    template <typename Base_t, typename Item_t>
    class Selectable_Races_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Races_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Race_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Races_t : public Selectable_Races_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Races_t<Base_t, Actor_Base_t*> : public Selectable_Races_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Races_t() :
            Selectable_Races_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            Race_t* race = item->Race();
            if (race) {
                output.push_back(race->Get_Editor_ID());
            } else {
                output.push_back("");
            }
        }
    };

    template <typename Base_t>
    class Selectable_Races_t<Base_t, Cached_Leveled_t*> : public Selectable_Races_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Races_t() :
            Selectable_Races_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            item->Race_Names(output);
        }
    };

    template <typename Base_t>
    class Selectable_Races_t<Base_t, Actor_t*> : public Selectable_Races_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Races_t() :
            Selectable_Races_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Races_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), output);
            }
        }
    };

    /* Bases */

    template <typename Base_t, typename Item_t>
    class Selectable_Bases_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Bases_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Base_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Bases_t : public Selectable_Bases_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Bases_t<Base_t, Actor_Base_t*> : public Selectable_Bases_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Bases_t() :
            Selectable_Bases_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            output.push_back(item->Any_Name());
        }
    };

    template <typename Base_t>
    class Selectable_Bases_t<Base_t, Cached_Leveled_t*> : public Selectable_Bases_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Bases_t() :
            Selectable_Bases_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            item->Actor_Base_Names(output);
        }
    };

    template <typename Base_t>
    class Selectable_Bases_t<Base_t, Actor_t*> : public Selectable_Bases_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Bases_t() :
            Selectable_Bases_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Bases_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), output);
            }
        }
    };

    /* Templates */

    template <typename Base_t, typename Item_t>
    class Selectable_Templates_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Templates_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Template_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Templates_t : public Selectable_Templates_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Templates_t<Base_t, Actor_Base_t*> : public Selectable_Templates_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Templates_t() :
            Selectable_Templates_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                for (maybe<Actor_Base_t*> it = item->face_template; it && it->Is_Valid(); it = it->face_template) {
                    String_t name = it->Any_Name();
                    if (name && !output.Has(name)) {
                        output.push_back(name);
                    }
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Templates_t<Base_t, Cached_Leveled_t*> : public Selectable_Templates_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Templates_t() :
            Selectable_Templates_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& bases = item->bases;
                for (size_t idx = 0, end = bases.size(); idx < end; idx += 1) {
                    Selectable_Templates_t<Base_t, Actor_Base_t*>::Select(bases[idx](), output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Templates_t<Base_t, Actor_t*> : public Selectable_Templates_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Templates_t() :
            Selectable_Templates_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Templates_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), output);
            }
        }
    };

    /* Factions */

    template <typename Base_t, typename Item_t>
    class Selectable_Factions_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Factions_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Faction_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Factions_t : public Selectable_Factions_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Factions_t<Base_t, Faction_t*> : public Selectable_Factions_i<Base_t, Faction_t*>
    {
    public:
        using Item_t = Faction_t*;

    public:
        Selectable_Factions_t() :
            Selectable_Factions_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                String_t name = item->Editor_Or_Form_ID();
                if (!output.Has(name)) {
                    output.push_back(name);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Factions_t<Base_t, Actor_Base_t*> : public Selectable_Factions_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Factions_t() :
            Selectable_Factions_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Faction_And_Rank_t> factions_and_ranks = item->Factions_And_Ranks();
                for (size_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
                    Selectable_Factions_t<Base_t, Faction_t*>::Select(factions_and_ranks[idx].faction(), output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Factions_t<Base_t, Cached_Leveled_t*> : public Selectable_Factions_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Factions_t() :
            Selectable_Factions_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& bases = item->bases;
                for (size_t idx = 0, end = bases.size(); idx < end; idx += 1) {
                    Selectable_Factions_t<Base_t, Actor_Base_t*>::Select(bases[idx](), output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Factions_t<Base_t, Actor_t*> : public Selectable_Factions_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Factions_t() :
            Selectable_Factions_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Faction_And_Rank_t> factions_and_ranks = item->Factions_And_Ranks();
                for (size_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
                    Selectable_Factions_t<Base_t, Faction_t*>::Select(factions_and_ranks[idx].faction(), output);
                }
            }
        }
    };

    /* Keywords */

    template <typename Base_t, typename Item_t>
    class Selectable_Keywords_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Keywords_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Keyword_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Keywords_t : public Selectable_Keywords_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Keywords_t<Base_t, Actor_Base_t*> : public Selectable_Keywords_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Keywords_t() :
            Selectable_Keywords_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vector_t<Keyword_t*> keywords = item->Keywords();
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    Keyword_t* keyword = keywords[idx];
                    if (keyword && keyword->Is_Valid()) {
                        String_t name = keyword->Any_Name();
                        if (!output.Has(name)) {
                            output.push_back(name);
                        }
                    }
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Keywords_t<Base_t, Cached_Leveled_t*> : public Selectable_Keywords_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Keywords_t() :
            Selectable_Keywords_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& bases = item->bases;
                for (size_t idx = 0, end = bases.size(); idx < end; idx += 1) {
                    Selectable_Keywords_t<Base_t, Actor_Base_t*>::Select(bases[idx](), output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Keywords_t<Base_t, Actor_t*> : public Selectable_Keywords_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Keywords_t() :
            Selectable_Keywords_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Keywords_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), output);
            }
        }
    };

    /* References */

    template <typename Base_t, typename Item_t>
    class Selectable_References_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_References_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Reference_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_References_t : public Selectable_References_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_References_t<Base_t, Actor_t*> : public Selectable_References_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_References_t() :
            Selectable_References_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                output.push_back(item->Any_Name());
            }
        }
    };

    /* Worldspaces */

    template <typename Base_t, typename Item_t>
    class Selectable_Worldspaces_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Worldspaces_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Worldspace_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Worldspaces_t : public Selectable_Worldspaces_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Worldspaces_t<Base_t, Worldspace_t*> : public Selectable_Worldspaces_i<Base_t, Worldspace_t*>
    {
    public:
        using Item_t = Worldspace_t*;

    public:
        Selectable_Worldspaces_t() :
            Selectable_Worldspaces_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                output.push_back(item->Any_Name());
            }
        }
    };

    template <typename Base_t>
    class Selectable_Worldspaces_t<Base_t, Actor_t*> : public Selectable_Worldspaces_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Worldspaces_t() :
            Selectable_Worldspaces_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vector_t<some<Worldspace_t*>> worldspaces = item->Worldspaces();
                for (size_t idx = 0, end = worldspaces.size(); idx < end; idx += 1) {
                    Selectable_Worldspaces_t<Base_t, Worldspace_t*>::Select(worldspaces[idx](), output);
                }
            }
        }
    };

    /* Locations */

    template <typename Base_t, typename Item_t>
    class Selectable_Locations_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Locations_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Location_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Locations_t : public Selectable_Locations_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Locations_t<Base_t, Cell_t*> : public Selectable_Locations_i<Base_t, Cell_t*>
    {
    public:
        using Item_t = Cell_t*;

    public:
        Selectable_Locations_t() :
            Selectable_Locations_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                item->Location_Names(output);
            }
        }
    };

    template <typename Base_t>
    class Selectable_Locations_t<Base_t, Actor_t*> : public Selectable_Locations_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Locations_t() :
            Selectable_Locations_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Locations_t<Base_t, Cell_t*>::Select(item->Cell(), output);
            }
        }
    };

    /* Cells */

    template <typename Base_t, typename Item_t>
    class Selectable_Cells_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Cells_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Cell_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Cells_t : public Selectable_Cells_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Cells_t<Base_t, Cell_t*> : public Selectable_Cells_i<Base_t, Cell_t*>
    {
    public:
        using Item_t = Cell_t*;

    public:
        Selectable_Cells_t() :
            Selectable_Cells_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                output.push_back(item->Any_Name());
            }
        }
    };

    template <typename Base_t>
    class Selectable_Cells_t<Base_t, Actor_t*> : public Selectable_Cells_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Cells_t() :
            Selectable_Cells_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Cells_t<Base_t, Cell_t*>::Select(item->Cell(), output);
            }
        }
    };

    /* Quests */

    template <typename Base_t, typename Item_t>
    class Selectable_Quests_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Quests_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Quest_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Quests_t : public Selectable_Quests_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Quests_t<Base_t, Quest_t*> : public Selectable_Quests_i<Base_t, Quest_t*>
    {
    public:
        using Item_t = Quest_t*;

    public:
        Selectable_Quests_t() :
            Selectable_Quests_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                String_t name = item->Any_Name();
                if (!output.Has(name)) {
                    output.push_back(name);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Quests_t<Base_t, Actor_t*> : public Selectable_Quests_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Quests_t() :
            Selectable_Quests_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vector_t<some<Quest_t*>> quests = item->Quests();
                for (size_t idx = 0, end = quests.size(); idx < end; idx += 1) {
                    Selectable_Quests_t<Base_t, Quest_t*>::Select(quests[idx](), output);
                }
            }
        }
    };

    /* Relations */

    template <typename Base_t, typename Item_t>
    class Selectable_Relations_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Relations_i(Select_Relation_f select_f, Actor_Base_t* base_to_compare) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Relation_Argument, select_f, base_to_compare)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Relations_t : public Selectable_Relations_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Relations_t<Base_t, Actor_Base_t*> : public Selectable_Relations_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Relations_t(Actor_Base_t* base_to_compare) :
            Selectable_Relations_i<Base_t, Item_t>(&Select, base_to_compare)
        {
        }

        static void Select(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            if (item && base_to_compare) {
                some<Relation_e> relation = Relation_e::Between(item, base_to_compare);
                output.push_back(Main_t::To_Relation_Key(relation())());
            }
        }
    };

    template <typename Base_t>
    class Selectable_Relations_t<Base_t, Cached_Leveled_t*> : public Selectable_Relations_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Relations_t(Actor_Base_t* base_to_compare) :
            Selectable_Relations_i<Base_t, Item_t>(&Select, base_to_compare)
        {
        }

        static void Select(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            if (item && item->leveled && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Selectable_Relations_t<Base_t, Actor_Base_t*>::Select(actor_bases[idx](), base_to_compare, output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Relations_t<Base_t, Actor_t*> : public Selectable_Relations_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Relations_t(Actor_Base_t* base_to_compare) :
            Selectable_Relations_i<Base_t, Item_t>(&Select, base_to_compare)
        {
        }

        static void Select(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Relations_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), base_to_compare, output);
            }
        }
    };

    /* Vitalities */

    template <typename Base_t, typename Item_t>
    class Selectable_Vitalities_i : public Selectable_Data_t<Base_t, Item_t>
    {
    public:
        Selectable_Vitalities_i(Select_f select_f) :
            Selectable_Data_t<Base_t, Item_t>(&Filter_t::Vitality_Argument, select_f)
        {
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectable_Vitalities_t : public Selectable_Vitalities_i<Base_t, Item_t>
    {
    };

    template <typename Base_t>
    class Selectable_Vitalities_t<Base_t, Actor_Base_t*> : public Selectable_Vitalities_i<Base_t, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;

    public:
        Selectable_Vitalities_t() :
            Selectable_Vitalities_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Vitality_e vitality = item->Vitality();
                if (vitality != Vitality_e::_NONE_) {
                    output.push_back(Main_t::To_Vitality_Key(vitality)());
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Vitalities_t<Base_t, Cached_Leveled_t*> : public Selectable_Vitalities_i<Base_t, Cached_Leveled_t*>
    {
    public:
        using Item_t = Cached_Leveled_t*;

    public:
        Selectable_Vitalities_t() :
            Selectable_Vitalities_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->leveled && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>>& actor_bases = item->bases;
                for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                    Selectable_Vitalities_t<Base_t, Actor_Base_t*>::Select(actor_bases[idx](), output);
                }
            }
        }
    };

    template <typename Base_t>
    class Selectable_Vitalities_t<Base_t, Actor_t*> : public Selectable_Vitalities_i<Base_t, Actor_t*>
    {
    public:
        using Item_t = Actor_t*;

    public:
        Selectable_Vitalities_t() :
            Selectable_Vitalities_i<Base_t, Item_t>(&Select)
        {
        }

        static void Select(Item_t item, Vector_t<String_t>& output)
        {
            if (item && item->Is_Valid()) {
                Selectable_Vitalities_t<Base_t, Actor_Base_t*>::Select(item->Actor_Base()(), output);
            }
        }
    };

}}
