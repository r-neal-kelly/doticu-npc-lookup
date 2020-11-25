/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_macros.h"

#include "doticu_mcmlib/config_base_macros.h"

#include "mcm_bases.h"

#define DEFINE_BOOL     DEFINE_BOOL_VARIABLE
#define DEFINE_INT      DEFINE_INT_VARIABLE
#define DEFINE_STRING   DEFINE_STRING_VARIABLE

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline V::String_Variable_t* Bases_t<B, I>::Current_View_Variable() { DEFINE_STRING("p_current_view"); }

    template <typename B, typename I>
    inline Bases_View_e Bases_t<B, I>::Current_View()
    {
        String_t current_view = Current_View_Variable()->Value();
        if (CString_t::Is_Same(current_view, LIST_VIEW, true)) {
            return Bases_View_e::LIST;
        } else if (CString_t::Is_Same(current_view, FILTER_VIEW, true)) {
            return Bases_View_e::FILTER;
        } else if (CString_t::Is_Same(current_view, OPTIONS_VIEW, true)) {
            return Bases_View_e::OPTIONS;
        } else if (CString_t::Is_Same(current_view, ITEM_VIEW, true)) {
            return Bases_View_e::ITEM;
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
            return Bases_View_e::LIST;
        }
    }

    template <typename B, typename I>
    inline void Bases_t<B, I>::Current_View(Bases_View_e value)
    {
        if (value == Bases_View_e::LIST) {
            Current_View_Variable()->Value(LIST_VIEW);
        } else if (value == Bases_View_e::FILTER) {
            Current_View_Variable()->Value(FILTER_VIEW);
        } else if (value == Bases_View_e::OPTIONS) {
            Current_View_Variable()->Value(OPTIONS_VIEW);
        } else if (value == Bases_View_e::ITEM) {
            Current_View_Variable()->Value(ITEM_VIEW);
        } else {
            Current_View_Variable()->Value(LIST_VIEW);
        }
    }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Filter_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Options_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Previous_Page_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_List_t<B, I>::Next_Page_Option()      { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline V::Int_Variable_t*   Bases_List_t<B, I>::Page_Index_Variable()   { DEFINE_INT("p_list_page_index"); }

    template <typename B, typename I>
    inline Int_t    Bases_List_t<B, I>::Page_Index()            { return Page_Index_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_List_t<B, I>::Page_Index(Int_t value) { Page_Index_Variable()->Value(value); }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Back_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Clear_Option()            { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Search_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Select_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Mod_Negate_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Search_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Select_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Race_Negate_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Search_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Select_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Base_Negate_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Select_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Relation_Negate_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Male_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Female_Option()           { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Unique_Option()           { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Filter_t<B, I>::Generic_Option()          { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Mod_Argument_Variable()               { DEFINE_STRING("p_filter_mod_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Mod_Do_Negate_Variable()              { DEFINE_BOOL("p_filter_mod_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Race_Argument_Variable()              { DEFINE_STRING("p_filter_race_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Race_Do_Negate_Variable()             { DEFINE_BOOL("p_filter_race_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Base_Argument_Variable()              { DEFINE_STRING("p_filter_base_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Base_Do_Negate_Variable()             { DEFINE_BOOL("p_filter_base_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    Bases_Filter_t<B, I>::Relation_Argument_Variable()          { DEFINE_STRING("p_filter_relation_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      Bases_Filter_t<B, I>::Relation_Do_Negate_Variable()         { DEFINE_BOOL("p_filter_relation_do_negate"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Male_Female_Argument_Variable()       { DEFINE_INT("p_filter_male_female_argument"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       Bases_Filter_t<B, I>::Unique_Generic_Argument_Variable()    { DEFINE_INT("p_filter_unique_generic_argument"); }

    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Mod_Argument()                            { return Mod_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Mod_Argument(String_t value)              { Mod_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Mod_Do_Negate()                           { return Mod_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Mod_Do_Negate(Bool_t value)               { Mod_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Race_Argument()                           { return Race_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Race_Argument(String_t value)             { Race_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Race_Do_Negate()                          { return Race_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Race_Do_Negate(Bool_t value)              { Race_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Base_Argument()                           { return Base_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Base_Argument(String_t value)             { Base_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Base_Do_Negate()                          { return Base_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Base_Do_Negate(Bool_t value)              { Base_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t Bases_Filter_t<B, I>::Relation_Argument()                       { return Relation_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Relation_Argument(String_t value)         { Relation_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Filter_t<B, I>::Relation_Do_Negate()                      { return Relation_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Relation_Do_Negate(Bool_t value)          { Relation_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline Binary_e Bases_Filter_t<B, I>::Male_Female_Argument()                    { return Male_Female_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Male_Female_Argument(Binary_e value)      { Male_Female_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Binary_e Bases_Filter_t<B, I>::Unique_Generic_Argument()                 { return Unique_Generic_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Filter_t<B, I>::Unique_Generic_Argument(Binary_e value)   { Unique_Generic_Argument_Variable()->Value(value); }

    template <typename Item_t>
    using Collect_f             = void(*)(Item_t, Vector_t<String_t>&);
    template <typename Item_t>
    using Collect_Relation_f    = void(*)(Item_t, Actor_Base_t*, Vector_t<String_t>&);

    template <typename Item_t>
    class Selectables_Data_t
    {
    public:
        Vector_t<Item_t>    items;
        Vector_t<String_t>  results;
        Vector_t<String_t>  buffer;

        void Reserve()
        {
            size_t item_count = items.size();
            if (item_count > 2048) {
                results.reserve(2048);
            } else {
                results.reserve(item_count);
            }
            buffer.reserve(128);
        }

        void Select(Collect_f<Item_t> Collect)
        {
            Reserve();

            results.push_back(" Any ");
            for (Index_t idx = 0, end = items.size(); idx < end; idx += 1) {
                Item_t item = items.at(idx);
                if (item) {
                    Collect(item, buffer);
                    for (Index_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                        String_t string = buffer[idx];
                        if (string && !results.Has(string)) {
                            results.push_back(string);
                        }
                    }
                    buffer.clear();
                }
            }

            Sort();
        }

        void Select(Collect_Relation_f<Item_t> Collect, Actor_Base_t* base_to_compare)
        {
            Reserve();

            results.push_back(" Any ");
            for (Index_t idx = 0, end = items.size(); idx < end; idx += 1) {
                Item_t item = items.at(idx);
                if (item) {
                    Collect(item, base_to_compare, buffer);
                    for (Index_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                        String_t string = buffer[idx];
                        if (string && !results.Has(string)) {
                            results.push_back(string);
                        }
                    }
                    buffer.clear();
                }
            }

            Sort();
        }

        void Sort()
        {
            static auto comparator = [](String_t* str_a, String_t* str_b)->Int_t
            {
                return Main_t::String_Comparator(
                    str_a ? str_a->data : "",
                    str_b ? str_b->data : ""
                );
            };
            results.Sort(comparator, 1);
        }

        Vector_t<String_t> Results()
        {
            return results;
        }
    };

    template <typename Base_t, typename Item_t, typename Selectable_t>
    class Selectables_i : public Selectables_Data_t<Item_t>
    {
    public:
        Selectables_i()
        {
            STATIC_ASSERT(false);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Mod_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Mod_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Mod_Argument();
                filter->Mod_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Mod_Argument(current);
            } else {
                items = list->Default_Items();
            }

            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Race_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Race_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Race_Argument();
                filter->Race_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Race_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Actor_Base_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Actor_Base_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Base_Argument();
                filter->Base_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Base_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Actor_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Actor_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Reference_Argument();
                filter->Reference_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Reference_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Worldspace_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Worldspace_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Worldspace_Argument();
                filter->Worldspace_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Worldspace_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Location_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Location_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Location_Argument();
                filter->Location_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Location_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Cell_t*> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Cell_t*;

    public:
        Selectables_i(Collect_f<Item_t> Collect)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Cell_Argument();
                filter->Cell_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Cell_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect);
        }
    };

    template <typename Base_t, typename Item_t>
    class Selectables_i<Base_t, Item_t, Relation_e> : public Selectables_Data_t<Item_t>
    {
    public:
        using Selectable_t = Relation_e;

    public:
        Selectables_i(Collect_Relation_f<Item_t> Collect, Actor_Base_t* base_to_compare)
        {
            auto* self = Base_t::Self();
            auto* list = self->List();
            auto* filter = self->Filter();
            auto* options = self->Options();

            if (options->Do_Smart_Select()) {
                String_t current = filter->Relation_Argument();
                filter->Relation_Argument("");
                list->do_update_items = true;
                items = list->Items();
                filter->Relation_Argument(current);
            } else {
                items = list->Default_Items();
            }
            Selectables_Data_t<Item_t>::Select(Collect, base_to_compare);
        }
    };

    template <typename Base_t, typename Item_t>
    class Mod_Selectables_t : public Selectables_i<Base_t, Item_t, Mod_t*>
    {
    public:
        using Selectable_t = Mod_t*;

    public:
        Mod_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            item->Mod_Names(output);
        }
    };

    template <typename Base_t>
    class Mod_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Mod_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Mod_t*;

    public:
        Mod_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                item.actor->Mod_Names(output);
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Race_Selectables_t : public Selectables_i<Base_t, Item_t, Race_t*>
    {
    };

    template <typename Base_t>
    class Race_Selectables_t<Base_t, Actor_Base_t*> : public Selectables_i<Base_t, Actor_Base_t*, Race_t*>
    {
    public:
        using Item_t = Actor_Base_t*;
        using Selectable_t = Race_t*;

    public:
        Race_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
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
    class Race_Selectables_t<Base_t, Leveled_Actor_Base_t*> : public Selectables_i<Base_t, Leveled_Actor_Base_t*, Race_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;
        using Selectable_t = Race_t*;

    public:
        Race_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            item->Race_Names(output);
        }
    };

    template <typename Base_t>
    class Race_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Race_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Race_t*;

    public:
        Race_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                Race_Selectables_t<Base_t, Actor_Base_t*>::Collect(item.actor->Actor_Base(), output);
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Base_Selectables_t : public Selectables_i<Base_t, Item_t, Actor_Base_t*>
    {
    };

    template <typename Base_t>
    class Base_Selectables_t<Base_t, Actor_Base_t*> : public Selectables_i<Base_t, Actor_Base_t*, Actor_Base_t*>
    {
    public:
        using Item_t = Actor_Base_t*;
        using Selectable_t = Actor_Base_t*;

    public:
        Base_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            output.push_back(item->Any_Name());
        }
    };

    template <typename Base_t>
    class Base_Selectables_t<Base_t, Leveled_Actor_Base_t*> : public Selectables_i<Base_t, Leveled_Actor_Base_t*, Actor_Base_t*>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;
        using Selectable_t = Actor_Base_t*;

    public:
        Base_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            item->Actor_Base_Names(output);
        }
    };

    template <typename Base_t>
    class Base_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Actor_Base_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Actor_Base_t*;

    public:
        Base_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                Base_Selectables_t<Base_t, Actor_Base_t*>::Collect(item.actor->Actor_Base(), output);
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Reference_Selectables_t : public Selectables_i<Base_t, Item_t, Actor_t*>
    {
    };

    template <typename Base_t>
    class Reference_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Actor_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Actor_t*;

    public:
        Reference_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                output.push_back(item.actor->Any_Name());
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Location_Selectables_t : public Selectables_i<Base_t, Item_t, Location_t*>
    {
    };

    template <typename Base_t>
    class Location_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Location_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Location_t*;

    public:
        Location_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                item.cell->Location_Names(output);
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Cell_Selectables_t : public Selectables_i<Base_t, Item_t, Cell_t*>
    {
    };

    template <typename Base_t>
    class Cell_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Cell_t*>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Cell_t*;

    public:
        Cell_Selectables_t() :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect)
        {
        }

        static void Collect(Item_t item, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                output.push_back(item.cell->Any_Name());
            }
        }
    };

    template <typename Base_t, typename Item_t>
    class Relation_Selectables_t : public Selectables_i<Base_t, Item_t, Relation_e>
    {
    };

    template <typename Base_t>
    class Relation_Selectables_t<Base_t, Actor_Base_t*> : public Selectables_i<Base_t, Actor_Base_t*, Relation_e>
    {
    public:
        using Item_t = Actor_Base_t*;
        using Selectable_t = Relation_e;

    public:
        Relation_Selectables_t(Actor_Base_t* base_to_compare) :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect, base_to_compare)
        {
        }

        static void Collect(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            Relation_e relation = Relation_e::Between(item, base_to_compare);
            if (relation != Relation_e::NONE) {
                output.push_back(std::string(" ") + Relation_e::To_String(relation) + " ");
            }
        }
    };

    template <typename Base_t>
    class Relation_Selectables_t<Base_t, Leveled_Actor_Base_t*> : public Selectables_i<Base_t, Leveled_Actor_Base_t*, Relation_e>
    {
    public:
        using Item_t = Leveled_Actor_Base_t*;
        using Selectable_t = Relation_e;

    public:
        Relation_Selectables_t(Actor_Base_t* base_to_compare) :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect, base_to_compare)
        {
        }

        static void Collect(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
            for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
                Actor_Base_t* actor_base = actor_bases[idx];
                if (actor_base) {
                    Relation_e relation = Relation_e::Between(actor_base, base_to_compare);
                    if (relation != Relation_e::NONE) {
                        String_t relation_name = std::string(" ") + Relation_e::To_String(relation) + " ";
                        if (!output.Has(relation_name)) {
                            output.push_back(relation_name);
                        }
                    }
                }
            }
        }
    };

    template <typename Base_t>
    class Relation_Selectables_t<Base_t, Loaded_Actor_t> : public Selectables_i<Base_t, Loaded_Actor_t, Relation_e>
    {
    public:
        using Item_t = Loaded_Actor_t;
        using Selectable_t = Relation_e;

    public:
        Relation_Selectables_t(Actor_Base_t* base_to_compare) :
            Selectables_i<Base_t, Item_t, Selectable_t>(&Collect, base_to_compare)
        {
        }

        static void Collect(Item_t item, Actor_Base_t* base_to_compare, Vector_t<String_t>& output)
        {
            if (item.Is_Valid()) {
                Relation_Selectables_t<Base_t, Actor_Base_t*>::Collect(item.actor->Actor_Base(), base_to_compare, output);
            }
        }
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Back_Option()                { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Reset_Option()               { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Smart_Select_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Uncombative_Spawns_Option()  { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Options_t<B, I>::Persistent_Spawns_Option()   { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Smart_Select_Variable()       { DEFINE_BOOL("p_options_do_smart_select"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Uncombative_Spawns_Variable() { DEFINE_BOOL("p_options_do_uncombative_spawns"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  Bases_Options_t<B, I>::Do_Persistent_Spawns_Variable()  { DEFINE_BOOL("p_options_do_persistent_spawns"); }

    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Smart_Select()                    { return Do_Smart_Select_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Smart_Select(Bool_t value)        { Do_Smart_Select_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Uncombative_Spawns()              { return Do_Uncombative_Spawns_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Uncombative_Spawns(Bool_t value)  { Do_Uncombative_Spawns_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   Bases_Options_t<B, I>::Do_Persistent_Spawns()               { return Do_Persistent_Spawns_Variable()->Value(); }
    template <typename B, typename I>
    inline void     Bases_Options_t<B, I>::Do_Persistent_Spawns(Bool_t value)   { Do_Persistent_Spawns_Variable()->Value(value); }

}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Back_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Previous_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Next_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   Bases_Item_t<B, I>::Spawn_Option()      { DEFINE_OPTION(); }

}}
