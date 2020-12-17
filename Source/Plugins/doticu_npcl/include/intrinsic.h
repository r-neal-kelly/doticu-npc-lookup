/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_mcmlib {}
namespace mcmlib = doticu_mcmlib;

namespace doticu_npcl {

    using Byte_t        = skylib::Byte_t;
    using Word_t        = skylib::Word_t;
    using Index_t       = skylib::Index_t;

    using Bool_t        = skylib::Bool_t;
    using Int_t         = skylib::Int_t;
    using Float_t       = skylib::Float_t;
    using String_t      = skylib::String_t;

    using u8            = skylib::u8;

    template <typename Type>
    using none          = skylib::none<Type>;
    template <typename Type>
    using some          = skylib::some<Type>;
    template <typename Type>
    using maybe         = skylib::maybe<Type>;

    template <typename Type>
    using Enum_t        = skylib::Enum_t<Type>;

    template <typename Type>
    using Version_t     = skylib::Version_t<Type>;

    template <typename Type>
    using Vector_t      = skylib::Vector_t<Type>;

    template <typename ...Types>
    using Callback_i    = skylib::Callback_i<Types...>;

}
