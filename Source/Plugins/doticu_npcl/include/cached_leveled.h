/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcl {

    using Actor_Base_t          = skylib::Actor_Base_t;
    using Leveled_Actor_Base_t  = skylib::Leveled_Actor_Base_t;
    using Race_t                = skylib::Race_t;
    using Relation_e            = skylib::Relation_e;

    class Cached_Leveled_t
    {
    public:
        String_t                        name;
        some<Leveled_Actor_Base_t*>     leveled;
        Vector_t<some<Actor_Base_t*>>   bases;
        Vector_t<some<Race_t*>>         races;

        Cached_Leveled_t(some<Leveled_Actor_Base_t*> leveled);

        Vector_t<some<Actor_Base_t*>> Actor_Bases();

        void Race_Names(Vector_t<String_t>& output);
        void Actor_Base_Names(Vector_t<String_t>& output);

        size_t Byte_Count();

        friend Bool_t operator==(const some<Cached_Leveled_t*> a, const maybe<Leveled_Actor_Base_t*> b);
    };

}
