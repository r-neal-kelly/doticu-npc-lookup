/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/virtual_macros.h"

#include "doticu_mcmlib/config_base_macros.h"

#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_references.h"

#define DEFINE_BOOL     DEFINE_BOOL_VARIABLE
#define DEFINE_INT      DEFINE_INT_VARIABLE
#define DEFINE_STRING   DEFINE_STRING_VARIABLE

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Reference_Search_Option()    { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Reference_Select_Option()    { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Reference_Negate_Option()    { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Worldspace_Search_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Worldspace_Select_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Worldspace_Negate_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Location_Search_Option()     { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Location_Select_Option()     { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Location_Negate_Option()     { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Cell_Search_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Cell_Select_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Cell_Negate_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Interior_Option()            { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Exterior_Option()            { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline V::String_Variable_t*    References_Filter_t<B, I>::Reference_Argument_Variable()            { DEFINE_STRING("p_filter_reference_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      References_Filter_t<B, I>::Reference_Do_Negate_Variable()           { DEFINE_BOOL("p_filter_reference_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    References_Filter_t<B, I>::Worldspace_Argument_Variable()           { DEFINE_STRING("p_filter_worldspace_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      References_Filter_t<B, I>::Worldspace_Do_Negate_Variable()          { DEFINE_BOOL("p_filter_worldspace_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    References_Filter_t<B, I>::Location_Argument_Variable()             { DEFINE_STRING("p_filter_location_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      References_Filter_t<B, I>::Location_Do_Negate_Variable()            { DEFINE_BOOL("p_filter_location_do_negate"); }
    template <typename B, typename I>
    inline V::String_Variable_t*    References_Filter_t<B, I>::Cell_Argument_Variable()                 { DEFINE_STRING("p_filter_cell_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      References_Filter_t<B, I>::Cell_Do_Negate_Variable()                { DEFINE_BOOL("p_filter_cell_do_negate"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       References_Filter_t<B, I>::Interior_Exterior_Argument_Variable()    { DEFINE_INT("p_filter_interior_exterior_argument"); }

    template <typename B, typename I>
    inline String_t References_Filter_t<B, I>::Reference_Argument()                         { return Reference_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Reference_Argument(String_t value)           { Reference_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   References_Filter_t<B, I>::Reference_Do_Negate()                        { return Reference_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Reference_Do_Negate(Bool_t value)            { Reference_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t References_Filter_t<B, I>::Worldspace_Argument()                        { return Worldspace_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Worldspace_Argument(String_t value)          { Worldspace_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   References_Filter_t<B, I>::Worldspace_Do_Negate()                       { return Worldspace_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Worldspace_Do_Negate(Bool_t value)           { Worldspace_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t References_Filter_t<B, I>::Location_Argument()                          { return Location_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Location_Argument(String_t value)            { Location_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   References_Filter_t<B, I>::Location_Do_Negate()                         { return Location_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Location_Do_Negate(Bool_t value)             { Location_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline String_t References_Filter_t<B, I>::Cell_Argument()                              { return Cell_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Cell_Argument(String_t value)                { Cell_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   References_Filter_t<B, I>::Cell_Do_Negate()                             { return Cell_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Cell_Do_Negate(Bool_t value)                 { Cell_Do_Negate_Variable()->Value(value); }
    template <typename B, typename I>
    inline Binary_e References_Filter_t<B, I>::Interior_Exterior_Argument()                 { return Interior_Exterior_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Interior_Exterior_Argument(Binary_e value)   { Interior_Exterior_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::Clear()
    {
        Bases_Filter_t<B, I>::Clear();

        Reference_Argument("");
        Reference_Do_Negate(false);

        Worldspace_Argument("");
        Worldspace_Do_Negate(false);

        Location_Argument("");
        Location_Do_Negate(false);

        Cell_Argument("");
        Cell_Do_Negate(false);

        Interior_Exterior_Argument(Binary_e::NONE);
    }

    template <typename Base_t, typename Item_t>
    inline Filter_State_t<Item_t> References_Filter_t<Base_t, Item_t>::Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write)
    {
        Filter_State_t<Item_t> filter_state = Bases_Filter_t<Base_t, Item_t>::Execute(read, write);

        Reference_Filter_t<Item_t>(filter_state, Reference_Argument(), Reference_Do_Negate());
        //Worldspace_Filter_t<Item_t>(filter_state, Worldspace_Argument(), Worldspace_Do_Negate());
        Location_Filter_t<Item_t>(filter_state, Location_Argument(), Location_Do_Negate());
        Cell_Filter_t<Item_t>(filter_state, Cell_Argument(), Cell_Do_Negate());
        Interior_Exterior_Filter_t<Item_t>(filter_state, Interior_Exterior_Argument());

        return std::move(filter_state);
    }

    template <typename B, typename I>
    inline Vector_t<String_t> References_Filter_t<B, I>::Selectable_References()
    {
        return Selectable_References_t<B, I>().Results();
    }
    template <typename B, typename I>
    inline Vector_t<String_t> References_Filter_t<B, I>::Selectable_Worldspaces()
    {
        return Vector_t<String_t>();
    }
    template <typename B, typename I>
    inline Vector_t<String_t> References_Filter_t<B, I>::Selectable_Locations()
    {
        return Selectable_Locations_t<B, I>().Results();
    }
    template <typename B, typename I>
    inline Vector_t<String_t> References_Filter_t<B, I>::Selectable_Cells()
    {
        return Selectable_Cells_t<B, I>().Results();
    }

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Select_In_Console_Option()   { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Mark_On_Map_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Move_To_Player_Option()      { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Go_To_Reference_Option()     { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Enable_Disable_Option()      { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Bases(Vector_t<Actor_Base_t*> actor_bases)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = actor_bases.size();
        if (count > 0 && mcm->Can_Add_Options(2 + count)) {
            mcm->Add_Header_Option(Main_t::BASES);
            mcm->Add_Header_Option(Main_t::_NONE_);
            for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                Actor_Base_t* actor_base = actor_bases[idx];
                const char* name = actor_base->Name();
                const char* form_id = actor_base->Form_ID_String().data;
                mcm->Add_Text_Option(
                    std::string(Main_t::_SPACE_) + mcm->Pretty_ID(name, Main_t::_NONE_, form_id),
                    Main_t::_NONE_
                );
            }
            if (skylib::Is_Odd(mcm->Cursor_Position())) {
                mcm->Add_Empty_Option();
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Cell(Cell_t* cell)
    {
        Main_t* mcm = Main_t::Self();

        if (cell && cell->Is_Valid()) {
            mcm->Add_Header_Option(Main_t::CELL);
            mcm->Add_Header_Option(Main_t::_NONE_);
            Cell_Name_Option() = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + cell->Any_Name().data, Main_t::_NONE_);
            if (cell->Is_Interior()) {
                mcm->Add_Text_Option(Main_t::IS_INTERIOR, Main_t::_NONE_);
            } else {
                mcm->Add_Text_Option(Main_t::IS_EXTERIOR, Main_t::_NONE_);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Locations(Cell_t* cell)
    {
        Main_t* mcm = Main_t::Self();

        if (cell && cell->Is_Valid()) {
            Vector_t<String_t> location_names = cell->Location_Names();
            size_t count = location_names.size();
            if (count > 0 && mcm->Can_Add_Options(2 + count)) {
                mcm->Add_Header_Option(Main_t::LOCATIONS);
                mcm->Add_Header_Option(Main_t::_NONE_);
                for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + location_names[idx].data, Main_t::_NONE_);
                }
                if (skylib::Is_Odd(mcm->Cursor_Position())) {
                    mcm->Add_Empty_Option();
                }
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Reference(Actor_t* actor, const char* type_name)
    {
        Main_t* mcm = Main_t::Self();

        if (actor && actor->Is_Valid()) {
            mcm->Add_Header_Option(type_name);
            mcm->Add_Header_Option(Main_t::_NONE_);
            {
                mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + actor->Name(), Main_t::_NONE_);
                mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + actor->Form_ID_String().data, Main_t::_NONE_);

                Actor_Base_t* actor_base = actor->Actor_Base();
                if (actor_base && actor_base->Is_Valid()) {
                    if (actor_base->Is_Male()) {
                        mcm->Add_Text_Option(Main_t::IS_MALE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_FEMALE, Main_t::_NONE_);
                    }
                    if (actor_base->Is_Unique()) {
                        mcm->Add_Text_Option(Main_t::IS_UNIQUE, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_GENERIC, Main_t::_NONE_);
                    }
                }
            }

            mcm->Add_Header_Option(Main_t::COMMANDS);
            mcm->Add_Header_Option(Main_t::_NONE_);
            {
                Markers_t* markers = Markers_t::Self();
                if (markers->Has_Marked(actor)) {
                    Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::REMOVE_MARKER_FROM_MAP, Main_t::_NONE_);
                } else {
                    if (markers->Has_Space()) {
                        Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::ADD_MARKER_TO_MAP, Main_t::_NONE_);
                    } else {
                        Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::ADD_MARKER_TO_MAP, Main_t::_NONE_, Flag_e::DISABLE);
                    }
                }

                mcm->Add_Empty_Option();

                Move_To_Player_Option() = mcm->Add_Text_Option(Main_t::MOVE_TO_PLAYER, Main_t::_NONE_);

                Go_To_Reference_Option() = mcm->Add_Text_Option(Main_t::GO_TO_REFERENCE, Main_t::_NONE_);

                if (actor->Is_Disabled()) {
                    Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::ENABLE_REFERENCE, Main_t::_NONE_);
                } else {
                    Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::DISABLE_REFERENCE, Main_t::_NONE_);
                }

                Select_In_Console_Option() = mcm->Add_Text_Option(Main_t::SELECT_IN_CONSOLE, Main_t::_NONE_);
            }
        }
    }

}}

#undef DEFINE_BOOL
#undef DEFINE_INT
#undef DEFINE_STRING
