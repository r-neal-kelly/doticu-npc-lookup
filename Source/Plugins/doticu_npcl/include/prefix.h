/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_mcmlib {}
namespace mcmlib = doticu_mcmlib;

namespace doticu_npcl {

    using Bool_t    = skylib::Bool_t;
    using Int_t     = skylib::Int_t;
    using Float_t   = skylib::Float_t;
    using String_t  = skylib::String_t;

    template <typename T>
    using Vector_t  = skylib::Vector_t<T>;

}
