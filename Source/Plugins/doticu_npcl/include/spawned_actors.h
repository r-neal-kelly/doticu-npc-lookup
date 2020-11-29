/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcl {

    using Actor_t               = skylib::Actor_t;
    using Actor_Base_t          = skylib::Actor_Base_t;
    using Form_t                = skylib::Form_t;
    using Form_ID_t             = skylib::Form_ID_t;
    using Game_t                = skylib::Game_t;
    using Leveled_Actor_Base_t  = skylib::Leveled_Actor_Base_t;
    using Mod_t                 = skylib::Mod_t;

    class Spawned_Actors_t {
    public:
        static Spawned_Actors_t&    Self();

        static size_t               Spawned_Actor_Count();
        static Vector_t<Actor_t*>   Spawned_Actors();
        static void                 Spawned_Actors(Vector_t<Actor_t*>& results);

    public:
        Vector_t<Actor_t*>  actors;
        Vector_t<Form_ID_t> actor_ids;
        Vector_t<String_t>  actor_mod_names;
        Vector_t<Form_ID_t> actor_base_ids;
        Vector_t<String_t>  actor_base_mod_names;

    public:
        void    Validate();
        void    Reserve(size_t count);

        Index_t Index_Of(Actor_t* actor);
        Bool_t  Has(Actor_t* actor);
        Bool_t  Add(Actor_t* actor);
        Bool_t  Add(Form_ID_t actor_id, String_t actor_mod_name, Form_ID_t actor_base_id, String_t actor_base_mod_name);
        Bool_t  Add(Actor_Base_t* base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        Bool_t  Add(Leveled_Actor_Base_t* leveled_base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        Bool_t  Remove(Actor_t* actor);
        Bool_t  Remove(Index_t index);
        void    Clear();
    };

}
