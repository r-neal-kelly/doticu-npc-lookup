/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/race.h"

#include "cached_leveled.h"

namespace doticu_npcl {

    Cached_Leveled_t::Cached_Leveled_t(some<Leveled_Actor_Base_t*> leveled) :
        name(leveled->Any_Name()), leveled(leveled)
    {
        class Iterator_t :
            public skylib::Iterator_i<Actor_Base_t*>
        {
        public:
            Vector_t<some<Actor_Base_t*>>&  bases;
            Vector_t<some<Race_t*>>&        races;
            Iterator_t(Vector_t<some<Actor_Base_t*>>& bases, Vector_t<some<Race_t*>>& races) :
                bases(bases), races(races)
            {
            }
            skylib::Iterator_e operator() (Actor_Base_t* actor_base)
            {
                if (actor_base && actor_base->Is_Valid()) {
                    some<Actor_Base_t*> base = actor_base;
                    if (!bases.Has(base)) {
                        bases.push_back(base);
                    }

                    some<Race_t*> race = base->Race();
                    if (race && !races.Has(race)) {
                        races.push_back(race);
                    }
                }
                return skylib::Iterator_e::CONTINUE;
            }
        } iterator(bases, races);

        leveled->Iterate_Actor_Bases(iterator);
    }

    Vector_t<some<Actor_Base_t*>> Cached_Leveled_t::Actor_Bases()
    {
        size_t actor_base_count = bases.size();

        Vector_t<some<Actor_Base_t*>> results;
        results.reserve(actor_base_count);

        for (size_t idx = 0, end = actor_base_count; idx < end; idx += 1) {
            results.push_back(bases[idx]);
        }

        return results;
    }

    void Cached_Leveled_t::Race_Names(Vector_t<String_t>& output)
    {
        for (size_t idx = 0, end = races.size(); idx < end; idx += 1) {
            output.push_back(races[idx]->Get_Editor_ID());
        }
    }

    void Cached_Leveled_t::Actor_Base_Names(Vector_t<String_t>& output)
    {
        for (size_t idx = 0, end = bases.size(); idx < end; idx += 1) {
            String_t base_name = bases[idx]->Any_Name();
            if (!output.Has(base_name)) {
                output.push_back(base_name);
            }
        }
    }

    size_t Cached_Leveled_t::Byte_Count()
    {
        size_t byte_count = 0;

        byte_count += sizeof(name);
        byte_count += sizeof(leveled);

        for (size_t idx = 0, end = bases.size(); idx < end; idx += 1) {
            some<Actor_Base_t*> base = bases[idx];
            byte_count += sizeof(base);
        }

        for (size_t idx = 0, end = races.size(); idx < end; idx += 1) {
            some<Race_t*> race = races[idx];
            byte_count += sizeof(race);
        }

        return byte_count;
    }

    Bool_t operator==(const some<Cached_Leveled_t*> a, const maybe<Leveled_Actor_Base_t*> b)
    {
        return a->leveled() == b();
    }

}
