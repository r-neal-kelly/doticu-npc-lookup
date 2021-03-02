/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"
#include "doticu_skylib/virtual.h"

#include "doticu_mcmlib/mcmlib.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_mcmlib {}
namespace mcmlib = doticu_mcmlib;

namespace doticu_npcl {

    using Byte_t                = skylib::Byte_t;
    using Word_t                = skylib::Word_t;
    using Index_t               = skylib::Index_t;

    using Bool_t                = skylib::Bool_t;
    using Int_t                 = skylib::Int_t;
    using Float_t               = skylib::Float_t;
    using String_t              = skylib::String_t;

    using u8                    = skylib::u8;
    using s64                   = skylib::s64;

    template <typename Type>
    using none                  = skylib::none<Type>;
    template <typename Type>
    using some                  = skylib::some<Type>;
    template <typename Type>
    using maybe                 = skylib::maybe<Type>;

    template <typename Type>
    using Enum_t                = skylib::Enum_t<Type>;

    template <typename Type>
    using Version_t             = skylib::Version_t<Type>;

    template <typename Type>
    using Vector_t              = skylib::Vector_t<Type>;

    template <typename ...Types>
    using Callback_i            = skylib::Callback_i<Types...>;

    using CString_t             = skylib::CString_t;

    using Actor_Value_e         = skylib::Actor_Value_e;
    using Binary_e              = skylib::Binary_e;
    using Comparator_e          = skylib::Comparator_e;
    using Cursor_e              = mcmlib::Cursor_e;
    using Flag_e                = mcmlib::Flag_e;
    using Form_Type_e           = skylib::Form_Type_e;
    using Relation_e            = skylib::Relation_e;
    using Sex_e                 = skylib::Sex_e;
    using Rarity_e              = skylib::Rarity_e;
    using Vitality_e            = skylib::Vitality_e;

    using Actor_t               = skylib::Actor_t;
    using Actor_Base_t          = skylib::Actor_Base_t;
    using Alias_Base_t          = skylib::Alias_Base_t;
    using Alias_Reference_t     = skylib::Alias_Reference_t;
    using Cell_t                = skylib::Cell_t;
    using CString_t             = skylib::CString_t;
    using Faction_t             = skylib::Faction_t;
    using Faction_And_Rank_t    = skylib::Faction_And_Rank_t;
    using Form_t                = skylib::Form_t;
    using Form_ID_t             = skylib::Raw_Form_ID_t; // Form_ID_t
    using Game_t                = skylib::Game_t;
    using Global_t              = skylib::Global_t;
    using Keyword_t             = skylib::Keyword_t;
    using Leveled_Actor_Base_t  = skylib::Leveled_Actor_Base_t;
    using Location_t            = skylib::Location_t;
    using Mod_t                 = skylib::Mod_t;
    using Player_t              = skylib::Player_t;
    using Quest_t               = skylib::Quest_t;
    using Race_t                = skylib::Race_t;
    using Raw_Form_ID_t         = skylib::Raw_Form_ID_t;
    using Reference_t           = skylib::Reference_t;
    using Translations_t        = skylib::Translations_t;
    using Worldspace_t          = skylib::Worldspace_t;

    namespace V {

        using Array_t           = skylib::Virtual::Array_t;
        using Callback_t        = skylib::Virtual::Callback_t;
        using Class_t           = skylib::Virtual::Class_t;
        using Input_t           = skylib::Virtual::Input_t;
        using Machine_t         = skylib::Virtual::Machine_t;
        using Object_t          = skylib::Virtual::Object_t;
        using Stack_ID_t        = skylib::Virtual::Stack_ID_t;
        using Utility_t         = skylib::Virtual::Utility_t;
        using Variable_t        = skylib::Virtual::Variable_t;

        template <typename T>
        using Variable_tt       = skylib::Virtual::Variable_tt<T>;

    }

}
