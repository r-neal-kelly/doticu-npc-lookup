/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_macros.h"

#include "doticu_mcmlib/config_base_macros.h"

#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_references.h"

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

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {



}}
