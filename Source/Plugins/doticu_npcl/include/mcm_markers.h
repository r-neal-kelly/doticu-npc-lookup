/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/collections.h"

#include "mcm_main.h"

namespace doticu_npcl { namespace MCM {

    class Alias_Actor_t
    {
    public:
        some<Alias_Reference_t*>    alias;
        maybe<Actor_t*>             actor;

    public:
        Alias_Actor_t(some<Alias_Reference_t*> alias, maybe<Actor_t*> actor) :
            alias(alias), actor(actor)
        {
        }
    };

    class Markers_t : public Quest_t
    {
    public:
        static constexpr size_t MAX_MARKERS = 16;

    public:
        static std::mutex cache_mutex;
        static skylib::Stack_Array_t<Alias_Actor_t, MAX_MARKERS> alias_actors;

    public:
        static String_t         Class_Name();
        static V::Class_t*      Class();
        V::Object_t*            Object();
        static some<Markers_t*> Self();

    public:
        void                        Refresh_Cache();
        void                        Refresh_Menu();

        Int_t                       Marked_Count();
        Bool_t                      Has_Space();
        Bool_t                      Has_Marked(some<Actor_t*> actor);
        Bool_t                      Mark(some<Actor_t*> actor);
        Bool_t                      Unmark(some<Actor_t*> actor);
        void                        Unmark_All();

        Vector_t<Alias_Actor_t*>    Alias_Actors();

    public:
        void On_Init();
        void On_Load();
        void On_Save();
        void On_Config_Open();
        void On_Config_Close();
        void On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback);
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
        void On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback);
        void On_Option_Default(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

}}
