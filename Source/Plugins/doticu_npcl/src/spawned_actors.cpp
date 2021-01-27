/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

#include "consts.h"
#include "spawned_actors.h"

namespace doticu_npcl {

    std::mutex Spawned_Actors_t::global_mutex;

    Spawned_Actors_t& Spawned_Actors_t::Self()
    {
        static Spawned_Actors_t spawned_actors;
        return spawned_actors;
    }

    size_t Spawned_Actors_t::Spawned_Actor_Count()
    {
        std::lock_guard<std::mutex> guard(global_mutex);

        return Self().actors.size();
    }

    Vector_t<Actor_t*> Spawned_Actors_t::Spawned_Actors()
    {
        Vector_t<Actor_t*> results;
        results.reserve(Spawned_Actor_Count());
        Spawned_Actors(results);
        return std::move(results);
    }

    void Spawned_Actors_t::Spawned_Actors(Vector_t<Actor_t*>& results)
    {
        std::lock_guard<std::mutex> guard(global_mutex);

        Spawned_Actors_t& self = Self();
        for (Index_t idx = 0, end = self.actors.size(); idx < end; idx += 1) {
            Actor_t* actor = self.actors[idx];
            if (actor && actor->Is_Valid()) {
                results.push_back(actor);
            }
        }
    }

    void Spawned_Actors_t::Validate()
    {
        Vector_t<Index_t> invalid_indices;
        invalid_indices.reserve(8);

        std::lock_guard<std::mutex> guard(mutex);
        for (Index_t idx = 0, end = actors.size(); idx < end; idx += 1) {
            Actor_t* actor = actors[idx];
            if (!actor || !actor->Is_Valid()) {
                invalid_indices.push_back(idx);
            }
        }
        guard.~lock_guard();

        for (Index_t idx = 0, end = invalid_indices.size(); idx < end; idx += 1) {
            Remove(invalid_indices[idx]);
        }
    }

    void Spawned_Actors_t::Reserve(size_t count)
    {
        std::lock_guard<std::mutex> guard(mutex);

        actors.reserve(count);
        actor_ids.reserve(count);
        actor_mod_names.reserve(count);
        actor_base_ids.reserve(count);
        actor_base_mod_names.reserve(count);
    }

    Index_t Spawned_Actors_t::Index_Of(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        std::lock_guard<std::mutex> guard(mutex);

        if (actor->Is_Valid()) {
            for (Index_t idx = 0, end = actors.size(); idx < end; idx += 1) {
                if (actors[idx] == actor()) {
                    return idx;
                }
            }
            return -1;
        } else {
            return -1;
        }
    }

    Bool_t Spawned_Actors_t::Has(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Index_Of(actor) > -1;
    }

    static void Add_Impl(Spawned_Actors_t* self, Actor_t* actor, Actor_Base_t* actor_base, String_t actor_base_mod_name)
    {
        std::lock_guard<std::mutex> guard(self->mutex);

        self->actors.push_back(actor);
        self->actor_ids.push_back(actor->form_id);

        self->actor_base_ids.push_back(actor_base->form_id);
        self->actor_base_mod_names.push_back(actor_base_mod_name);

        maybe<Mod_t*> actor_mod = actor->Indexed_Mod();
        if (actor_mod) {
            String_t actor_mod_name = actor_mod->Name();
            if (actor_mod_name) {
                self->actor_mod_names.push_back(actor_mod_name);
            } else {
                self->actor_mod_names.push_back("");
            }
        } else {
            self->actor_mod_names.push_back("");
        }
    }

    Bool_t Spawned_Actors_t::Add(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (actor->Is_Valid() && !Has(actor)) {
            Actor_Base_t* actor_base = actor->Highest_Static_Actor_Base();
            if (actor_base && actor_base->Is_Valid()) {
                maybe<Mod_t*> actor_base_mod = actor_base->Indexed_Mod();
                if (actor_base_mod) {
                    String_t actor_base_mod_name = actor_base_mod->Name();
                    if (actor_base_mod_name) {
                        Add_Impl(this, actor(), actor_base, actor_base_mod_name);
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Spawned_Actors_t::Add(skylib::Form_ID_t actor_id, String_t actor_mod_name, skylib::Form_ID_t actor_base_id, String_t actor_base_mod_name)
    {
        if (actor_base_mod_name) {
            maybe<Mod_t*> actor_base_mod = Mod_t::Active_Mod(actor_base_mod_name.data);
            if (actor_base_mod) {
                if (actor_base_id.Mod(actor_base_mod) && actor_base_id) {
                    if (actor_id.Is_Static()) {
                        if (actor_mod_name) {
                            maybe<Mod_t*> actor_mod = Mod_t::Active_Mod(actor_mod_name.data);
                            if (actor_mod) {
                                if (!actor_id.Mod(actor_mod) || !actor_id) {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    }
                    maybe<Actor_t*> actor = static_cast<maybe<Actor_t*>>(Game_t::Form(actor_id));
                    if (actor && actor->Is_Valid()) {
                        Actor_Base_t* actor_base = actor->Highest_Static_Actor_Base();
                        if (actor_base && actor_base->Is_Valid() && actor_base->form_id == actor_base_id) {
                            Add_Impl(this, actor(), actor_base, actor_base_mod_name);
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Spawned_Actors_t::Add(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(base);

        maybe<Actor_t*> actor = Actor_t::Create(base, do_persist, do_uncombative, do_static);
        if (actor && actor->Is_Valid()) {
            actor->Move_To_Orbit(Consts_t::Skyrim_Player_Actor(), 160.0f, 0.0f);
            return Add(actor());
        } else {
            return false;
        }
    }

    Bool_t Spawned_Actors_t::Add(some<Leveled_Actor_Base_t*> leveled_base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(leveled_base);

        maybe<Actor_t*> actor = Actor_t::Create(leveled_base, do_persist, do_uncombative, do_static);
        if (actor && actor->Is_Valid()) {
            actor->Move_To_Orbit(Consts_t::Skyrim_Player_Actor(), 160.0f, 0.0f);
            return Add(actor());
        } else {
            return false;
        }
    }

    Bool_t Spawned_Actors_t::Remove(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Remove(Index_Of(actor));
    }

    Bool_t Spawned_Actors_t::Remove(Index_t index)
    {
        std::lock_guard<std::mutex> guard(mutex);

        size_t end = actors.size();
        if (index > -1 && index < end) {
            if (index == end - 1) {
                actors.erase(actors.end() - 1);
                actor_ids.erase(actor_ids.end() - 1);
                actor_mod_names.erase(actor_mod_names.end() - 1);
                actor_base_ids.erase(actor_base_ids.end() - 1);
                actor_base_mod_names.erase(actor_base_mod_names.end() - 1);
                return true;
            } else {
                actors[index] = actors[end - 1];
                actors.erase(actors.end() - 1);

                actor_ids[index] = actor_ids[end - 1];
                actor_ids.erase(actor_ids.end() - 1);

                actor_mod_names[index] = actor_mod_names[end - 1];
                actor_mod_names.erase(actor_mod_names.end() - 1);

                actor_base_ids[index] = actor_base_ids[end - 1];
                actor_base_ids.erase(actor_base_ids.end() - 1);

                actor_base_mod_names[index] = actor_base_mod_names[end - 1];
                actor_base_mod_names.erase(actor_base_mod_names.end() - 1);

                return true;
            }
        } else {
            return false;
        }
    }

    void Spawned_Actors_t::Clear()
    {
        std::lock_guard<std::mutex> guard(mutex);

        actors.clear();
        actor_ids.clear();
        actor_mod_names.clear();
        actor_base_ids.clear();
        actor_base_mod_names.clear();
    }

}
