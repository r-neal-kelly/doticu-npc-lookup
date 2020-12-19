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
    inline Int_t&   References_Filter_t<B, I>::Quest_Search_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Quest_Select_Option()        { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Quest_Negate_Option()        { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Interior_Option()            { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Exterior_Option()            { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Alive_Option()               { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Dead_Option()                { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Is_Teammate_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t&   References_Filter_t<B, I>::Isnt_Teammate_Option()       { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::Reset_Option_Ints()
    {
        Bases_Filter_t<B, I>::Reset_Option_Ints();

        Reference_Search_Option()   = -1;
        Reference_Select_Option()   = -1;
        Reference_Negate_Option()   = -1;

        Worldspace_Search_Option()  = -1;
        Worldspace_Select_Option()  = -1;
        Worldspace_Negate_Option()  = -1;

        Location_Search_Option()    = -1;
        Location_Select_Option()    = -1;
        Location_Negate_Option()    = -1;

        Cell_Search_Option()        = -1;
        Cell_Select_Option()        = -1;
        Cell_Negate_Option()        = -1;

        Quest_Search_Option()       = -1;
        Quest_Select_Option()       = -1;
        Quest_Negate_Option()       = -1;

        Interior_Option()           = -1;
        Exterior_Option()           = -1;

        Alive_Option()              = -1;
        Dead_Option()               = -1;

        Is_Teammate_Option()        = -1;
        Isnt_Teammate_Option()      = -1;
    }

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
    
    inline V::String_Variable_t*    References_Filter_t<B, I>::Quest_Argument_Variable()                { DEFINE_STRING("p_filter_quest_argument"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*      References_Filter_t<B, I>::Quest_Do_Negate_Variable()               { DEFINE_BOOL("p_filter_quest_do_negate"); }
    
    template <typename B, typename I>
    inline V::Int_Variable_t*       References_Filter_t<B, I>::Interior_Exterior_Argument_Variable()    { DEFINE_INT("p_filter_interior_exterior_argument"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       References_Filter_t<B, I>::Alive_Dead_Argument_Variable()           { DEFINE_INT("p_filter_alive_dead_argument"); }
    template <typename B, typename I>
    inline V::Int_Variable_t*       References_Filter_t<B, I>::Is_Teammate_Argument_Variable()          { DEFINE_INT("p_filter_is_teammate_argument"); }

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
    inline String_t References_Filter_t<B, I>::Quest_Argument()                             { return Quest_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Quest_Argument(String_t value)               { Quest_Argument_Variable()->Value(value); }
    template <typename B, typename I>
    inline Bool_t   References_Filter_t<B, I>::Quest_Do_Negate()                            { return Quest_Do_Negate_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Quest_Do_Negate(Bool_t value)                { Quest_Do_Negate_Variable()->Value(value); }
    
    template <typename B, typename I>
    inline Binary_e References_Filter_t<B, I>::Interior_Exterior_Argument()                 { return Interior_Exterior_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Interior_Exterior_Argument(Binary_e value)   { Interior_Exterior_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline Binary_e References_Filter_t<B, I>::Alive_Dead_Argument()                        { return Alive_Dead_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Alive_Dead_Argument(Binary_e value)          { Alive_Dead_Argument_Variable()->Value(value); }

    template <typename B, typename I>
    inline Binary_e References_Filter_t<B, I>::Is_Teammate_Argument()                       { return Is_Teammate_Argument_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Filter_t<B, I>::Is_Teammate_Argument(Binary_e value)         { Is_Teammate_Argument_Variable()->Value(value); }

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

        Quest_Argument("");
        Quest_Do_Negate(false);

        Interior_Exterior_Argument(Binary_e::NONE);
        Alive_Dead_Argument(Binary_e::NONE);
        Is_Teammate_Argument(Binary_e::NONE);
    }

    template <typename Base_t, typename Item_t>
    inline Filter_State_t<Item_t> References_Filter_t<Base_t, Item_t>::Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write)
    {
        Filter_State_t<Item_t> filter_state = Bases_Filter_t<Base_t, Item_t>::Execute(read, write);

        Reference_Filter_t<Item_t>(filter_state, Reference_Argument(), Reference_Do_Negate());
        Worldspace_Filter_t<Item_t>(filter_state, Worldspace_Argument(), Worldspace_Do_Negate());
        Location_Filter_t<Item_t>(filter_state, Location_Argument(), Location_Do_Negate());
        Cell_Filter_t<Item_t>(filter_state, Cell_Argument(), Cell_Do_Negate());
        Quest_Filter_t<Item_t>(filter_state, Quest_Argument(), Quest_Do_Negate());
        Interior_Exterior_Filter_t<Item_t>(filter_state, Interior_Exterior_Argument());
        Alive_Dead_Filter_t<Item_t>(filter_state, Alive_Dead_Argument());
        Is_Teammate_Filter_t<Item_t>(filter_state, Is_Teammate_Argument());

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
        return Selectable_Worldspaces_t<B, I>().Results();
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

    template <typename B, typename I>
    inline Vector_t<String_t> References_Filter_t<B, I>::Selectable_Quests()
    {
        return Selectable_Quests_t<B, I>().Results();
    }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::Build_Filters(const char* type_name)
    {
        Main_t* mcm = Main_t::Self();

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Clear_Option() = mcm->Add_Text_Option(Main_t::CENTER_CLEAR, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::MOD);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Mod_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Mod_Argument());
        Mod_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Mod_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Mod_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RACE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Race_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Race_Argument());
        Race_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Race_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Race_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::BASE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Base_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Base_Argument());
        Base_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Base_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Base_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(type_name);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Reference_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Reference_Argument());
        Reference_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Reference_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Reference_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::TEMPLATE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Template_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Template_Argument());
        Template_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Template_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Template_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::FACTION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Faction_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Faction_Argument());
        Faction_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Faction_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Faction_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::KEYWORD);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Keyword_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Keyword_Argument());
        Keyword_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Keyword_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Keyword_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::WORLDSPACE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Worldspace_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Worldspace_Argument());
        Worldspace_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Worldspace_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Worldspace_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::LOCATION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Location_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Location_Argument());
        Location_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Location_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Location_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::CELL);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Cell_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Cell_Argument());
        Cell_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Cell_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Cell_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::QUEST);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Quest_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Quest_Argument());
        Quest_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Quest_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Quest_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RELATION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Relation_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Relation_Argument());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::VITALITY);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Vitality_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, mcm->To_Vitality_Key(Vitality_Argument())());
        Vitality_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::OTHER);
        mcm->Add_Header_Option(Main_t::_NONE_);

        Male_Option() = mcm->Add_Toggle_Option(Main_t::IS_MALE, Male_Female_Argument() == Binary_e::A);
        Female_Option() = mcm->Add_Toggle_Option(Main_t::IS_FEMALE, Male_Female_Argument() == Binary_e::B);

        Unique_Option() = mcm->Add_Toggle_Option(Main_t::IS_UNIQUE, Unique_Generic_Argument() == Binary_e::A);
        Generic_Option() = mcm->Add_Toggle_Option(Main_t::IS_GENERIC, Unique_Generic_Argument() == Binary_e::B);

        Interior_Option() = mcm->Add_Toggle_Option(Main_t::IN_INTERIOR, Interior_Exterior_Argument() == Binary_e::A);
        Exterior_Option() = mcm->Add_Toggle_Option(Main_t::IN_EXTERIOR, Interior_Exterior_Argument() == Binary_e::B);

        Alive_Option() = mcm->Add_Toggle_Option(Main_t::IS_ALIVE, Alive_Dead_Argument() == Binary_e::A);
        Dead_Option() = mcm->Add_Toggle_Option(Main_t::IS_DEAD, Alive_Dead_Argument() == Binary_e::B);

        Is_Teammate_Option() = mcm->Add_Toggle_Option(Main_t::IS_TEAMMATE, Is_Teammate_Argument() == Binary_e::A);
        Isnt_Teammate_Option() = mcm->Add_Toggle_Option(Main_t::ISNT_TEAMMATE, Is_Teammate_Argument() == Binary_e::B);
    }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();

        } else if (option == Clear_Option()) {
            mcm->Disable_Option(option);
            Clear();
            mcm->Reset_Page();

        } else if (option == Mod_Negate_Option()) {
            Bool_t value = Mod_Do_Negate();
            Mod_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Race_Negate_Option()) {
            Bool_t value = Race_Do_Negate();
            Race_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Base_Negate_Option()) {
            Bool_t value = Base_Do_Negate();
            Base_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Template_Negate_Option()) {
            Bool_t value = Template_Do_Negate();
            Template_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Faction_Negate_Option()) {
            Bool_t value = Faction_Do_Negate();
            Faction_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Keyword_Negate_Option()) {
            Bool_t value = Keyword_Do_Negate();
            Keyword_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Relation_Negate_Option()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Vitality_Negate_Option()) {
            Bool_t value = Vitality_Do_Negate();
            Vitality_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Reference_Negate_Option()) {
            Bool_t value = Reference_Do_Negate();
            Reference_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Worldspace_Negate_Option()) {
            Bool_t value = Worldspace_Do_Negate();
            Worldspace_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Location_Negate_Option()) {
            Bool_t value = Location_Do_Negate();
            Location_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Cell_Negate_Option()) {
            Bool_t value = Cell_Do_Negate();
            Cell_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Quest_Negate_Option()) {
            Bool_t value = Quest_Do_Negate();
            Quest_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Male_Option()) {
            mcm->Toggle_Either(Male_Female_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Female_Option()) {
            mcm->Toggle_Either(Male_Female_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Unique_Option()) {
            mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Generic_Option()) {
            mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Interior_Option()) {
            mcm->Toggle_Either(Interior_Exterior_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Exterior_Option()) {
            mcm->Toggle_Either(Interior_Exterior_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Alive_Option()) {
            mcm->Toggle_Either(Alive_Dead_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Dead_Option()) {
            mcm->Toggle_Either(Alive_Dead_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Is_Teammate_Option()) {
            mcm->Toggle_Either(Is_Teammate_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Isnt_Teammate_Option()) {
            mcm->Toggle_Either(Is_Teammate_Argument_Variable(), option - 1, option, Binary_e::B);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Mods());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Race_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Races());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Base_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Bases());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Template_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Templates());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Faction_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Factions());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Keyword_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Keywords());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Relation_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Vitality_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Vitalities());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Reference_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_References());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Worldspace_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Worldspaces());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Location_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Locations());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Cell_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Cells());
            mcm->Menu_Dialog_Default(0);

        } else if (option == Quest_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Quests());
            mcm->Menu_Dialog_Default(0);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Mods();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Mod_Argument(value);
                mcm->Input_Option_Value(Mod_Search_Option(), value, true);
            }

        } else if (option == Race_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Races();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Race_Argument(value);
                mcm->Input_Option_Value(Race_Search_Option(), value, true);
            }

        } else if (option == Base_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Bases();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Base_Argument(value);
                mcm->Input_Option_Value(Base_Search_Option(), value, true);
            }

        } else if (option == Template_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Templates();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Template_Argument(value);
                mcm->Input_Option_Value(Template_Search_Option(), value, true);
            }

        } else if (option == Faction_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Factions();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Faction_Argument(value);
                mcm->Input_Option_Value(Faction_Search_Option(), value, true);
            }

        } else if (option == Keyword_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Keywords();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Keyword_Argument(value);
                mcm->Input_Option_Value(Keyword_Search_Option(), value, true);
            }

        } else if (option == Relation_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::ANY;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Relations();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Relation_Argument(value);
                mcm->Menu_Option_Value(option, value, true);
            }

        } else if (option == Vitality_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::ANY;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Vitalities();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Vitality_Argument(mcm->From_Vitality_Key(value.data));
                mcm->Menu_Option_Value(option, value, true);
            }

        } else if (option == Reference_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_References();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Reference_Argument(value);
                mcm->Input_Option_Value(Reference_Search_Option(), value, true);
            }

        } else if (option == Worldspace_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Worldspaces();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Worldspace_Argument(value);
                mcm->Input_Option_Value(Worldspace_Search_Option(), value, true);
            }

        } else if (option == Location_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Locations();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Location_Argument(value);
                mcm->Input_Option_Value(Location_Search_Option(), value, true);
            }

        } else if (option == Cell_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Cells();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Cell_Argument(value);
                mcm->Input_Option_Value(Cell_Search_Option(), value, true);
            }

        } else if (option == Quest_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> selectables = Selectable_Quests();
                    if (idx < selectables.size()) {
                        value = selectables[idx];
                    }
                }
                Quest_Argument(value);
                mcm->Input_Option_Value(Quest_Search_Option(), value, true);
            }

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    template <typename B, typename I>
    inline void References_Filter_t<B, I>::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Search_Option()) {
            Mod_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Race_Search_Option()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Base_Search_Option()) {
            Base_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Template_Search_Option()) {
            Template_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Faction_Search_Option()) {
            Faction_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Keyword_Search_Option()) {
            Keyword_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Reference_Search_Option()) {
            Reference_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Worldspace_Search_Option()) {
            Worldspace_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Location_Search_Option()) {
            Location_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Cell_Search_Option()) {
            Cell_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        } else if (option == Quest_Search_Option()) {
            Quest_Argument(value);
            mcm->Input_Option_Value(option, value, true);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    template <typename B, typename I>
    Int_t References_Item_t<B, I>::show_cells_option        = -1;
    template <typename B, typename I>
    Int_t References_Item_t<B, I>::show_locations_option    = -1;
    template <typename B, typename I>
    Int_t References_Item_t<B, I>::show_quests_option       = -1;
    template <typename B, typename I>
    Int_t References_Item_t<B, I>::show_references_option   = -1;
    template <typename B, typename I>
    Int_t References_Item_t<B, I>::show_worldspaces_option  = -1;

    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Select_In_Console_Option()       { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Mark_On_Map_Option()             { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Move_To_Player_Option()          { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Go_To_Reference_Option()         { DEFINE_OPTION(); }
    template <typename B, typename I>
    inline Int_t& References_Item_t<B, I>::Enable_Disable_Option()          { DEFINE_OPTION(); }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Reset_Option_Ints()
    {
        Bases_Item_t<B, I>::Reset_Option_Ints();

        show_cells_option               = -1;
        show_locations_option           = -1;
        show_quests_option              = -1;
        show_references_option          = -1;
        show_worldspaces_option         = -1;

        Select_In_Console_Option()      = -1;
        Mark_On_Map_Option()            = -1;
        Move_To_Player_Option()         = -1;
        Go_To_Reference_Option()        = -1;
        Enable_Disable_Option()         = -1;
    }

    template <typename B, typename I>
    inline V::Bool_Variable_t*  References_Item_t<B, I>::Do_Show_Cells_Variable()       { DEFINE_BOOL("p_item_do_show_cells"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  References_Item_t<B, I>::Do_Show_Locations_Variable()   { DEFINE_BOOL("p_item_do_show_locations"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  References_Item_t<B, I>::Do_Show_Quests_Variable()      { DEFINE_BOOL("p_item_do_show_quests"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  References_Item_t<B, I>::Do_Show_References_Variable()  { DEFINE_BOOL("p_item_do_show_references"); }
    template <typename B, typename I>
    inline V::Bool_Variable_t*  References_Item_t<B, I>::Do_Show_Worldspaces_Variable() { DEFINE_BOOL("p_item_do_show_worldspaces"); }

    template <typename B, typename I>
    inline Bool_t   References_Item_t<B, I>::Do_Show_Cells()                    { return Do_Show_Cells_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Item_t<B, I>::Do_Show_Cells(Bool_t value)        { Do_Show_Cells_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   References_Item_t<B, I>::Do_Show_Locations()                { return Do_Show_Locations_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Item_t<B, I>::Do_Show_Locations(Bool_t value)    { Do_Show_Locations_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   References_Item_t<B, I>::Do_Show_Quests()                   { return Do_Show_Quests_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Item_t<B, I>::Do_Show_Quests(Bool_t value)       { Do_Show_Quests_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   References_Item_t<B, I>::Do_Show_References()               { return Do_Show_References_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Item_t<B, I>::Do_Show_References(Bool_t value)   { Do_Show_References_Variable()->Value(value); }

    template <typename B, typename I>
    inline Bool_t   References_Item_t<B, I>::Do_Show_Worldspaces()              { return Do_Show_Worldspaces_Variable()->Value(); }
    template <typename B, typename I>
    inline void     References_Item_t<B, I>::Do_Show_Worldspaces(Bool_t value)  { Do_Show_Worldspaces_Variable()->Value(value); }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Bases(Vector_t<Actor_Base_t*> actor_bases)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = actor_bases.size();
        if (count > 0) {
            if (Do_Show_Bases()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::BASES);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

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
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::BASES);
                    show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::BASES, Flag_e::DISABLE);
                show_bases_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Bases(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Cell(Cell_t* cell)
    {
        Main_t* mcm = Main_t::Self();

        if (cell && cell->Is_Valid()) {
            if (Do_Show_Cells()) {
                if (mcm->Can_Add_Options(2 + 2)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::CELL);
                    show_cells_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    Cell_Name_Option() = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + cell->Any_Name().data, Main_t::_NONE_);
                    if (cell->Is_Interior()) {
                        mcm->Add_Text_Option(Main_t::IS_INTERIOR, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_EXTERIOR, Main_t::_NONE_);
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::CELL);
                    show_cells_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::CELL, Flag_e::DISABLE);
                show_cells_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Cells(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Locations(Vector_t<Location_t*> locations)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = locations.size();
        if (count > 0) {
            if (Do_Show_Locations()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::LOCATIONS);
                    show_locations_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Location_t* location = locations[idx];
                        if (location && location->Is_Valid()) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + location->Any_Name().data, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::LOCATIONS);
                    show_locations_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::LOCATIONS, Flag_e::DISABLE);
                show_locations_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Locations(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Quests(Vector_t<Quest_t*> quests)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = quests.size();
        if (count > 0) {
            if (Do_Show_Quests()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::QUESTS);
                    show_quests_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    quests.Sort(Quest_t::Compare_Any_Names);
                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Quest_t* quest = quests[idx];
                        if (quest && quest->Is_Valid()) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + quest->Any_Name().data, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::QUESTS);
                    show_quests_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::QUESTS, Flag_e::DISABLE);
                show_quests_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Quests(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Reference(Actor_t* actor, const char* type_name)
    {
        Main_t* mcm = Main_t::Self();

        if (actor && actor->Is_Valid()) {
            if (Do_Show_References()) {
                if (mcm->Can_Add_Options(2 + 4)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, type_name);
                    show_references_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

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
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, type_name);
                    show_references_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }

            if (Do_Show_Commands()) {
                if (mcm->Can_Add_Options(2 + 6)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::COMMANDS);
                    show_commands_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

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

                    mcm->Add_Empty_Option(); // Spawn a Clone? would have to add options that are available in bases, just hook them up

                    Move_To_Player_Option() = mcm->Add_Text_Option(Main_t::MOVE_TO_PLAYER, Main_t::_NONE_);

                    Go_To_Reference_Option() = mcm->Add_Text_Option(Main_t::GO_TO_REFERENCE, Main_t::_NONE_);

                    if (actor->Is_Disabled()) {
                        Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::ENABLE_REFERENCE, Main_t::_NONE_);
                    } else {
                        Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::DISABLE_REFERENCE, Main_t::_NONE_);
                    }

                    Select_In_Console_Option() = mcm->Add_Text_Option(Main_t::SELECT_IN_CONSOLE, Main_t::_NONE_);
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::COMMANDS);
                    show_commands_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, type_name, Flag_e::DISABLE);
                show_references_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_References(), Flag_e::DISABLE);
            }

            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::COMMANDS, Flag_e::DISABLE);
                show_commands_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Commands(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline void References_Item_t<B, I>::Build_Worldspaces(Vector_t<some<Worldspace_t*>> worldspaces)
    {
        Main_t* mcm = Main_t::Self();

        size_t count = worldspaces.size();
        if (count > 0) {
            if (Do_Show_Worldspaces()) {
                if (mcm->Can_Add_Options(2 + count)) {
                    mcm->Add_Text_Option(Main_t::_TEXT_DIVIDER_, Main_t::WORLDSPACES);
                    show_worldspaces_option = mcm->Add_Toggle_Option(Main_t::_TOGGLE_DIVIDER_, true);

                    for (Index_t idx = 0, end = count; idx < end; idx += 1) {
                        Worldspace_t* worldspace = worldspaces[idx];
                        if (worldspace->Is_Valid()) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + worldspace->Any_Name().data, Main_t::_NONE_);
                        }
                    }

                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
                        mcm->Add_Empty_Option();
                    }
                }
            } else {
                if (mcm->Can_Add_Options(2)) {
                    mcm->Add_Text_Option(Main_t::_NONE_, Main_t::WORLDSPACES);
                    show_worldspaces_option = mcm->Add_Toggle_Option(Main_t::_NONE_, false);
                }
            }
        } else {
            if (mcm->Can_Add_Options(2)) {
                mcm->Add_Text_Option(Main_t::_NONE_, Main_t::WORLDSPACES, Flag_e::DISABLE);
                show_worldspaces_option = mcm->Add_Toggle_Option(Main_t::_NONE_, Do_Show_Worldspaces(), Flag_e::DISABLE);
            }
        }
    }

    template <typename B, typename I>
    inline Bool_t References_Item_t<B, I>::Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == show_cells_option || option == show_cells_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Cells_Variable(), option, lcallback);
            return true;

        } else if (option == show_locations_option || option == show_locations_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Locations_Variable(), option, lcallback);
            return true;

        } else if (option == show_quests_option || option == show_quests_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Quests_Variable(), option, lcallback);
            return true;

        } else if (option == show_references_option || option == show_references_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_References_Variable(), option, lcallback);
            return true;

        } else if (option == show_worldspaces_option || option == show_worldspaces_option - 1) {
            mcm->Toggle_And_Reset(Do_Show_Worldspaces_Variable(), option, lcallback);
            return true;

        } else if (Bases_Item_t<B, I>::Try_On_Option_Select(option, lcallback)) {
            return true;

        } else {
            return false;

        }
    }

}}

#undef DEFINE_BOOL
#undef DEFINE_INT
#undef DEFINE_STRING
