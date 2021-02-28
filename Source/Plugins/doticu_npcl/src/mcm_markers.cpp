/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/forward_list.inl"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest_objective.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_markers.h"

namespace doticu_npcl { namespace MCM {

    std::mutex Markers_t::cache_mutex;
    skylib::Stack_Array_t<Alias_Actor_t, Markers_t::MAX_MARKERS> Markers_t::alias_actors;

    String_t            Markers_t::Class_Name() { DEFINE_CLASS_NAME("doticu_npcl_mcm_markers"); }
    V::Class_t*         Markers_t::Class()      { DEFINE_CLASS(); }
    V::Object_t*        Markers_t::Object()     { DEFINE_OBJECT_METHOD(); }
    some<Markers_t*>    Markers_t::Self()       { return static_cast<some<Markers_t*>>(Consts_t::NPCL_MCM_Quest()); }

    class Mark_Callback_t : public V::Callback_t
    {
    public:
        Markers_t* self;
        Index_t marker_index;
        Mark_Callback_t(Markers_t* self, Index_t marker_index) :
            self(self), marker_index(marker_index)
        {
        }
        void operator()(V::Variable_t* result)
        {
            class Display_Callback_t : public V::Callback_t
            {
            public:
                Markers_t* self;
                Display_Callback_t(Markers_t* self) :
                    self(self)
                {
                }
                void operator()(V::Variable_t* result)
                {
                    self->Refresh_Menu();
                }
            };
            self->Display_Objective(marker_index, true, new Display_Callback_t(self));
        }
    };

    class Unmark_Callback_t : public V::Callback_t
    {
    public:
        Markers_t* self;
        Index_t marker_index;
        Unmark_Callback_t(Markers_t* self, Index_t marker_index) :
            self(self), marker_index(marker_index)
        {
        }
        void operator()(V::Variable_t* result)
        {
            class Undisplay_Callback_t : public V::Callback_t
            {
            public:
                Markers_t* self;
                Undisplay_Callback_t(Markers_t* self) :
                    self(self)
                {
                }
                void operator()(V::Variable_t* result)
                {
                    self->Refresh_Menu();
                }
            };
            self->Undisplay_Objective(marker_index, false, new Undisplay_Callback_t(self));
        }
    };

    void Markers_t::Refresh_Cache()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        alias_actors.Clear();
        for (Index_t idx = 0, end = MAX_MARKERS; idx < end; idx += 1) {
            maybe<Alias_Base_t*> alias_base = this->aliases[idx + 1];
            if (alias_base) {
                maybe<Alias_Reference_t*> alias_reference = alias_base->As_Alias_Reference();
                if (alias_reference) {
                    alias_actors.Push(
                        Alias_Actor_t(alias_reference(), none<Actor_t*>())
                    );
                } else {
                    SKYLIB_ASSERT(false);
                }
            } else {
                SKYLIB_ASSERT(false);
            }
        }

        for (Index_t idx = 0, end = promoted_references.Count(); idx < end; idx += 1) {
            skylib::Reference_Handle_t reference_handle = promoted_references[idx];
            Reference_t* reference = Reference_t::From_Handle(reference_handle);
            if (reference && reference->Is_Valid()) {
                maybe<skylib::Extra_Aliases_t*> xaliases = reference->x_list.Get<skylib::Extra_Aliases_t>();
                if (xaliases) {
                    skylib::Read_Locker_t locker(xaliases->lock);
                    for (Index_t idx = 0, end = xaliases->instances.Count(); idx < end; idx += 1) {
                        maybe<skylib::Extra_Aliases_t::Instance_t*> instance = xaliases->instances[idx];
                        if (instance && instance->quest == this && instance->alias_base) {
                            Index_t marker_idx = instance->alias_base->id - 1;
                            if (marker_idx > -1 && marker_idx < MAX_MARKERS) {
                                Actor_t* actor = static_cast<Actor_t*>(reference);
                                alias_actors[marker_idx].actor = actor;
                            }
                        }
                    }
                }
            }
        }

        guard.~lock_guard();

        Refresh_Menu();
    }

    void Markers_t::Refresh_Menu()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        some<Player_t*> player = Player_t::Self();
        for (Index_t idx = 0, end = player->objectives.Count(); idx < end; idx += 1) {
            auto& player_objective = player->objectives[idx];
            auto* objective = player_objective.objective;
            if (objective && objective->quest == this) {
                Index_t marker_idx = objective->index;
                if (marker_idx > -1 && marker_idx < alias_actors.count) {
                    maybe<Actor_t*> actor = alias_actors[marker_idx].actor;
                    if (actor) {
                        objective->state = skylib::Quest_Objective_State_e::DISPLAYED;
                        objective->display_text = std::string("NPC Lookup: ") + actor->Any_Name().data;
                    } else {
                        objective->state = skylib::Quest_Objective_State_e::DORMANT;
                    }
                    player_objective.state = objective->state;
                }
            }
        }
    }

    Int_t Markers_t::Marked_Count()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        Int_t count = 0;

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (alias_actor.actor) {
                count += 1;
            }
        }

        return count;
    }

    Bool_t Markers_t::Has_Space()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (!alias_actor.actor) {
                return true;
            }
        }

        return false;
    }

    Bool_t Markers_t::Has_Marked(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        std::lock_guard<std::mutex> guard(cache_mutex);

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (alias_actor.actor && alias_actor.actor() == actor()) {
                return true;
            }
        }

        return false;
    }

    Bool_t Markers_t::Mark(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (!Has_Marked(actor)) {
            std::lock_guard<std::mutex> guard(cache_mutex);

            for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
                Alias_Actor_t& alias_actor = alias_actors[idx];
                if (!alias_actor.actor) {
                    maybe<skylib::Quest_Objective_t**> objective = objectives.Point(idx);
                    if (objective && *objective) {
                        (*objective)->display_text = std::string("NPC Lookup: ") + actor->Any_Name().data;
                    }
                    alias_actor.alias->Fill(actor, new Mark_Callback_t(this, idx));
                    alias_actor.actor = actor();
                    return true;
                }
            }
        } else {
            return false;
        }

        return false;
    }

    Bool_t Markers_t::Unmark(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        std::lock_guard<std::mutex> guard(cache_mutex);

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (alias_actor.actor && alias_actor.actor() == actor()) {
                alias_actor.alias->Unfill(new Unmark_Callback_t(this, idx));
                alias_actor.actor = none<Actor_t*>();
                return true;
            }
        }

        return false;
    }

    void Markers_t::Unmark_All()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            alias_actor.alias->Unfill(new Unmark_Callback_t(this, idx));
            alias_actor.actor = none<Actor_t*>();
        }
    }

    Vector_t<Alias_Actor_t*> Markers_t::Alias_Actors()
    {
        std::lock_guard<std::mutex> guard(cache_mutex);

        Vector_t<Alias_Actor_t*> results;
        results.reserve(MAX_MARKERS);

        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (alias_actor.actor) {
                if (alias_actor.actor->Is_Valid()) {
                    if (alias_actor.actor->Is_Aliased(this, alias_actor.alias->id)) {
                        results.push_back(&alias_actor);
                    } else {
                        alias_actor.actor = none<Actor_t*>();
                    }
                } else {
                    alias_actor.alias->Unfill(new Unmark_Callback_t(this, idx));
                    alias_actor.actor = none<Actor_t*>();
                }
            }
        }

        results.Sort(
            [](Alias_Actor_t** item_a, Alias_Actor_t** item_b)->Int_t
            {
                if (!item_a || !*item_a) {
                    return Comparator_e::IS_UNORDERED;
                } else if (!item_b || !*item_b) {
                    return Comparator_e::IS_ORDERED;
                } else {
                    Comparator_e result = Form_t::Compare_Names(
                        (*item_a)->actor->Any_Name(),
                        (*item_b)->actor->Any_Name()
                    );
                    if (result == Comparator_e::IS_EQUAL) {
                        return (*item_a)->actor->form_id - (*item_b)->actor->form_id;
                    } else {
                        return result;
                    }
                }
            }
        );

        return results;
    }

    void Markers_t::On_Init()
    {
        Refresh_Cache();
    }

    void Markers_t::On_Load()
    {
        Refresh_Cache();
    }

    void Markers_t::On_Save()
    {
    }

    void Markers_t::On_Config_Open()
    {
    }

    void Markers_t::On_Config_Close()
    {
    }

    void Markers_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Int_t marked_count = Marked_Count();
        if (marked_count > 0) {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_MARKED_REFERENCES, marked_count, MAX_MARKERS));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_MARKED_REFERENCES, marked_count, MAX_MARKERS));
            }

            mcm->Add_Header_Option(Main_t::_NONE_);
            mcm->Add_Header_Option(Main_t::_NONE_);

            Vector_t<Alias_Actor_t*> alias_actors = Alias_Actors();
            for (Index_t idx = 0, end = alias_actors.size(); idx < end; idx += 1) {
                Alias_Actor_t* alias_actor = alias_actors[idx];
                mcm->Add_Text_Option(alias_actor->actor->Any_Name(), Main_t::_DOTS_);
            }
        } else {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_MARKED_REFERENCES, 0, MAX_MARKERS));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_MARKED_REFERENCES, 0, MAX_MARKERS));
            }

            mcm->Add_Header_Option(Main_t::NO_MARKED_REFERENCES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Index_t marker_index = mcm->Option_To_Item_Index(option, MAX_MARKERS, 0, 2, 16);
        if (marker_index > -1 && marker_index < MAX_MARKERS) {
            class Callback_t : public Callback_i<Bool_t>
            {
            public:
                some<Main_t*> mcm;
                Markers_t* self;
                Index_t marker_index;
                Latent_Callback_i* lcallback;
                Callback_t(some<Main_t*> mcm, Markers_t* self, Index_t marker_index, Latent_Callback_i* lcallback) :
                    mcm(mcm), self(self), marker_index(marker_index), lcallback(lcallback)
                {
                }
                void operator()(Bool_t accept)
                {
                    if (accept) {
                        Vector_t<Alias_Actor_t*> alias_actors = self->Alias_Actors();
                        if (marker_index > -1 && marker_index < alias_actors.size()) {
                            Alias_Actor_t* alias_actor = alias_actors[marker_index];
                            alias_actor->alias->Unfill(new Unmark_Callback_t(self, marker_index));
                            alias_actor->actor = none<Actor_t*>();
                        }
                        mcm->Reset_Page();
                    }
                    mcm->Destroy_Latent_Callback(lcallback);
                }
            };
            mcm->Flicker_Option(option);
            mcm->Show_Message(
                Main_t::CONFIRM_REMOVE_MARKER,
                true,
                Main_t::YES,
                Main_t::NO,
                new Callback_t(mcm, this, marker_index, lcallback)
            );
        } else {
            mcm->Destroy_Latent_Callback(lcallback);
        }
    }

    void Markers_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
