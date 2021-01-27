/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "intrinsic.h"

namespace doticu_npcl {

    class Spawned_Actors_t
    {
    public:
        static std::mutex global_mutex;

        static Spawned_Actors_t&    Self();

        static size_t               Spawned_Actor_Count();
        static Vector_t<Actor_t*>   Spawned_Actors();
        static void                 Spawned_Actors(Vector_t<Actor_t*>& results);

    public:
        std::mutex          mutex;
        Vector_t<Actor_t*>  actors;
        Vector_t<Form_ID_t> actor_ids;
        Vector_t<String_t>  actor_mod_names;
        Vector_t<Form_ID_t> actor_base_ids;
        Vector_t<String_t>  actor_base_mod_names;

    public:
        void    Validate();
        void    Reserve(size_t count);

        Index_t Index_Of(some<Actor_t*> actor);
        Bool_t  Has(some<Actor_t*> actor);
        Bool_t  Add(some<Actor_t*> actor);
        Bool_t  Add(skylib::Form_ID_t actor_id, String_t actor_mod_name, skylib::Form_ID_t actor_base_id, String_t actor_base_mod_name);
        Bool_t  Add(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        Bool_t  Add(some<Leveled_Actor_Base_t*> leveled_base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        Bool_t  Remove(some<Actor_t*> actor);
        Bool_t  Remove(Index_t index);
        void    Clear();
    };

}
