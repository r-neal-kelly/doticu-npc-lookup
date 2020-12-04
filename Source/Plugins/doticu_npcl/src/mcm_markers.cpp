/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/alias_base.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_markers.h"

namespace doticu_npcl { namespace MCM {

    skylib::Stack_Array_t<Alias_Actor_t, Markers_t::MAX_MARKERS> Markers_t::alias_actors;

    String_t        Markers_t::Class_Name() { DEFINE_CLASS_NAME("doticu_npcl_mcm_markers"); }
    V::Class_t*     Markers_t::Class()      { DEFINE_CLASS(); }
    V::Object_t*    Markers_t::Object()     { DEFINE_OBJECT(); }

    Markers_t*      Markers_t::Self()       { return static_cast<Markers_t*>(Consts_t::NPCL_MCM_Quest()); }

    class Mark_Callback_t : public V::Callback_t
    {
    public:
        Quest_t* quest;
        Index_t marker_index;
        Mark_Callback_t(Quest_t* quest, Index_t marker_index) :
            quest(quest), marker_index(marker_index)
        {
        }
        void operator()(V::Variable_t* result)
        {
            quest->Display_Objective(marker_index, true);
        }
    };

    class Unmark_Callback_t : public V::Callback_t
    {
    public:
        Quest_t* quest;
        Index_t marker_index;
        Unmark_Callback_t(Quest_t* quest, Index_t marker_index) :
            quest(quest), marker_index(marker_index)
        {
        }
        void operator()(V::Variable_t* result)
        {
            quest->Undisplay_Objective(marker_index, true);
        }
    };

    Int_t Markers_t::Marked_Count()
    {
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
            for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
                Alias_Actor_t& alias_actor = alias_actors[idx];
                if (!alias_actor.actor) {
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
        for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
            Alias_Actor_t& alias_actor = alias_actors[idx];
            if (alias_actor.actor) {
                alias_actor.alias->Unfill(new Unmark_Callback_t(this, idx));
                alias_actor.actor = none<Actor_t*>();
            }
        }
    }

    void Markers_t::On_Load()
    {
        for (Index_t idx = 0, end = MAX_MARKERS; idx < end; idx += 1) {
            alias_actors.Push(
                Alias_Actor_t(aliases.entries[idx + 1], none<Actor_t*>())
            );
        }

        for (Index_t idx = 0, end = promoted_references.count; idx < end; idx += 1) {
            skylib::Reference_Handle_t reference_handle = promoted_references.entries[idx];
            Reference_t* reference = Reference_t::From_Handle(reference_handle);
            if (reference && reference->Is_Valid()) {
                skylib::Aliases_x* xaliases = reference->xlist.Get<skylib::Aliases_x>();
                if (xaliases) {
                    for (Index_t idx = 0, end = xaliases->instances.count; idx < end; idx += 1) {
                        skylib::Aliases_x::Instance_t* instance = xaliases->instances.entries[idx];
                        if (instance && instance->quest == this && instance->alias_base) {
                            Index_t marker_idx = instance->alias_base->id - 1;
                            if (marker_idx > -1 && marker_idx < MAX_MARKERS) {
                                alias_actors[marker_idx].actor = static_cast<Actor_t*>(reference);
                            }
                        }
                    }
                }
            }
        }
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
        Main_t* mcm = Main_t::Self();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Int_t marked_count = Marked_Count();
        if (marked_count > 0) {
            mcm->Title_Text(mcm->Title_Items(" Markers ", marked_count, MAX_MARKERS));

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            for (Index_t idx = 0, end = alias_actors.count; idx < end; idx += 1) {
                Alias_Actor_t& alias_actor = alias_actors[idx];
                if (alias_actor.actor && alias_actor.actor->Is_Aliased(this, idx + 1)) {
                    mcm->Add_Text_Option(alias_actor.actor->Any_Name(), "...");
                }
            }
        } else {
            mcm->Title_Text(mcm->Title_Items(" Markers ", 0, MAX_MARKERS));

            mcm->Add_Header_Option(" No Markers ");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Markers_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Index_t marker_index = mcm->Option_To_Item_Index(option, MAX_MARKERS, 0, 2, 16);
        if (marker_index > -1 && marker_index < MAX_MARKERS) {
            class Callback_t : public Callback_i<Bool_t>
            {
            public:
                Main_t* mcm;
                Markers_t* self;
                Index_t marker_index;
                Latent_Callback_i* lcallback;
                Callback_t(Main_t* mcm, Markers_t* self, Index_t marker_index, Latent_Callback_i* lcallback) :
                    mcm(mcm), self(self), marker_index(marker_index), lcallback(lcallback)
                {
                }
                void operator()(Bool_t accept)
                {
                    if (accept) {
                        maybe<Actor_t*> actor = self->alias_actors[marker_index].actor;
                        if (actor) {
                            self->Unmark(actor);
                        }
                        mcm->Reset_Page();
                    }
                    mcm->Destroy_Latent_Callback(lcallback);
                }
            };
            mcm->Flicker_Option(option);
            mcm->Show_Message(
                "Remove marker?",
                true,
                "$Accept",
                "$Cancel",
                new Callback_t(mcm, this, marker_index, lcallback)
            );
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
