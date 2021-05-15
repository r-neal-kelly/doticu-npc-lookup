/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    class References_Item_Section_e : public Bases_Item_Section_e
    {
    public:
        enum : value_type
        {
            CELLS = Bases_Item_Section_e::_END_,
            LOCATIONS,
            QUESTS,
            REFERENCES,
            WORLDSPACES,

            _END_,
        };
        using Bases_Item_Section_e::Bases_Item_Section_e;

        static some<const char*>            To_String(References_Item_Section_e section_e);
        static References_Item_Section_e    From_String(some<const char*> section_str);
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_t : public Bases_t<Base_t, Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_List_t : public Bases_List_t<Base_t, Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_Filter_t : public Bases_Filter_t<Base_t, Item_t>
    {
    public:
        Int_t&  Reference_Search_Option();
        Int_t&  Reference_Select_Option();
        Int_t&  Reference_Negate_Option();

        Int_t&  Worldspace_Search_Option();
        Int_t&  Worldspace_Select_Option();
        Int_t&  Worldspace_Negate_Option();

        Int_t&  Location_Search_Option();
        Int_t&  Location_Select_Option();
        Int_t&  Location_Negate_Option();

        Int_t&  Cell_Search_Option();
        Int_t&  Cell_Select_Option();
        Int_t&  Cell_Negate_Option();

        Int_t&  Quest_Search_Option();
        Int_t&  Quest_Select_Option();
        Int_t&  Quest_Negate_Option();

        Int_t&  Interior_Option();
        Int_t&  Exterior_Option();

        Int_t&  Alive_Option();
        Int_t&  Dead_Option();

        Int_t&  Is_Teammate_Option();
        Int_t&  Isnt_Teammate_Option();

        void    Reset_Option_Ints();

    public:
        V::Variable_tt<String_t>&   Reference_Argument();
        V::Variable_tt<Bool_t>&     Reference_Do_Negate();

        V::Variable_tt<String_t>&   Worldspace_Argument();
        V::Variable_tt<Bool_t>&     Worldspace_Do_Negate();

        V::Variable_tt<String_t>&   Location_Argument();
        V::Variable_tt<Bool_t>&     Location_Do_Negate();

        V::Variable_tt<String_t>&   Cell_Argument();
        V::Variable_tt<Bool_t>&     Cell_Do_Negate();

        V::Variable_tt<String_t>&   Quest_Argument();
        V::Variable_tt<Bool_t>&     Quest_Do_Negate();

        V::Variable_tt<Binary_e>&   Interior_Exterior_Argument();
        V::Variable_tt<Binary_e>&   Alive_Dead_Argument();
        V::Variable_tt<Binary_e>&   Is_Teammate_Argument();

    public:
        void                    Clear();
        Filter_State_t<Item_t>  Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write);

        Vector_t<String_t>      Selectable_References();
        Vector_t<String_t>      Selectable_Worldspaces();
        Vector_t<String_t>      Selectable_Locations();
        Vector_t<String_t>      Selectable_Cells();
        Vector_t<String_t>      Selectable_Quests();

    public:
        void Build_Filters(const char* type_name);

    public:
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);

        void    On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void    On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void    On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_Options_t : public Bases_Options_t<Base_t, Item_t>
    {
    public:
        static Int_t    cells_section_option;
        static Int_t    locations_section_option;
        static Int_t    quests_section_option;
        static Int_t    references_section_option;
        static Int_t    worldspaces_section_option;

        void            Reset_Option_Ints();

    public:
        Vector_t<Item_Section_t>    Default_Item_Sections();

        void                        Build_Section_Options_Impl();

    public:
        Bool_t  Try_On_Load();
        Bool_t  Try_On_Save();
        Bool_t  Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_Item_t : public Bases_Item_t<Base_t, Item_t>
    {
    public:
        static Int_t unspawn_option;

        static Int_t show_cells_option;
        static Int_t show_locations_option;
        static Int_t show_quests_option;
        static Int_t show_references_option;
        static Int_t show_worldspaces_option;

        static Int_t cell_name_option;

        Int_t&  Select_In_Console_Option();
        Int_t&  Mark_On_Map_Option();
        Int_t&  Move_To_Player_Option();
        Int_t&  Go_To_Reference_Option();
        Int_t&  Enable_Disable_Option();

        static Int_t rename_reference_option;

        void    Reset_Option_Ints();

    public:
        V::Variable_tt<Bool_t>& Do_Show_Cells();
        V::Variable_tt<Bool_t>& Do_Show_Locations();
        V::Variable_tt<Bool_t>& Do_Show_Quests();
        V::Variable_tt<Bool_t>& Do_Show_References();
        V::Variable_tt<Bool_t>& Do_Show_Worldspaces();

    public:
        void    Build_Bases(Vector_t<Actor_Base_t*> actor_bases);
        void    Build_Cell(Cell_t* cell);
        void    Build_Commands(Actor_t* actor);
        void    Build_Locations(Vector_t<some<Location_t*>> locations);
        void    Build_Quests(Vector_t<some<Quest_t*>> quests);
        void    Build_Reference(Actor_t* actor, const char* type_name);
        void    Build_Worldspaces(Vector_t<some<Worldspace_t*>> worldspaces);

        void    Highlight_Cell_Option(Actor_t* actor, Latent_Callback_i* lcallback);

    public:
        Bool_t  Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        Bool_t  Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback);
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Bases_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Vector_t<Actor_Base_t*>             bases;

        Buildable_Bases_t(References_Item_t<Base_t, Item_t>* builder, Vector_t<Actor_Base_t*>&& bases) :
            builder(builder), bases(std::move(bases))
        {
        }
        virtual         ~Buildable_Bases_t()                = default;
        virtual Bool_t  Can_Enable()            override    { return bases.size() > 0; }
        virtual Bool_t  Can_Show()              override    { return builder->Do_Show_Bases(); }
        virtual void    Build()                 override    { builder->Build_Bases(bases); }
        virtual Type_t  Type()                  override    { return References_Item_Section_e::BASES; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Cell_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Cell_t*                             cell;

        Buildable_Cell_t(References_Item_t<Base_t, Item_t>* builder, Cell_t* cell) :
            builder(builder), cell(cell)
        {
        }
        virtual         ~Buildable_Cell_t()             = default;
        virtual Bool_t  Can_Enable()        override    { return cell && cell->Is_Valid(); }
        virtual Bool_t  Can_Show()          override    { return builder->Do_Show_Cells(); }
        virtual void    Build()             override    { builder->Build_Cell(cell); }
        virtual Type_t  Type()              override    { return References_Item_Section_e::CELLS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Commands_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Actor_t*                            actor;

        Buildable_Commands_t(References_Item_t<Base_t, Item_t>* builder, Actor_t* actor) :
            builder(builder), actor(actor)
        {
        }
        virtual         ~Buildable_Commands_t()             = default;
        virtual Bool_t  Can_Enable()            override    { return actor && actor->Is_Valid(); }
        virtual Bool_t  Can_Show()              override    { return builder->Do_Show_Commands(); }
        virtual void    Build()                 override    { builder->Build_Commands(actor); }
        virtual Type_t  Type()                  override    { return References_Item_Section_e::COMMANDS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Locations_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Vector_t<some<Location_t*>>         locations;

        Buildable_Locations_t(References_Item_t<Base_t, Item_t>* builder, Vector_t<some<Location_t*>>&& locations) :
            builder(builder), locations(std::move(locations))
        {
        }
        virtual         ~Buildable_Locations_t()                = default;
        virtual Bool_t  Can_Enable()                override    { return locations.size() > 0; }
        virtual Bool_t  Can_Show()                  override    { return builder->Do_Show_Locations(); }
        virtual void    Build()                     override    { builder->Build_Locations(locations); }
        virtual Type_t  Type()                      override    { return References_Item_Section_e::LOCATIONS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Quests_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Vector_t<some<Quest_t*>>            quests;

        Buildable_Quests_t(References_Item_t<Base_t, Item_t>* builder, Vector_t<some<Quest_t*>>&& quests) :
            builder(builder), quests(std::move(quests))
        {
        }
        virtual         ~Buildable_Quests_t()               = default;
        virtual Bool_t  Can_Enable()            override    { return quests.size() > 0; }
        virtual Bool_t  Can_Show()              override    { return builder->Do_Show_Quests(); }
        virtual void    Build()                 override    { builder->Build_Quests(quests); }
        virtual Type_t  Type()                  override    { return References_Item_Section_e::QUESTS; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Reference_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Actor_t*                            actor;
        const char*                         type_name;

        Buildable_Reference_t(References_Item_t<Base_t, Item_t>* builder, Actor_t* actor, const char* type_name) :
            builder(builder), actor(actor), type_name(type_name)
        {
        }
        virtual         ~Buildable_Reference_t()                = default;
        virtual Bool_t  Can_Enable()                override    { return actor && actor->Is_Valid() && type_name; }
        virtual Bool_t  Can_Show()                  override    { return builder->Do_Show_References(); }
        virtual void    Build()                     override    { builder->Build_Reference(actor, type_name); }
        virtual Type_t  Type()                      override    { return References_Item_Section_e::REFERENCES; }
    };

    template <typename Base_t, typename Item_t>
    class Buildable_Worldspaces_t : public Buildable_i
    {
    public:
        References_Item_t<Base_t, Item_t>*  builder;
        Vector_t<some<Worldspace_t*>>       worldspaces;

        Buildable_Worldspaces_t(References_Item_t<Base_t, Item_t>* builder, Vector_t<some<Worldspace_t*>>&& worldspaces) :
            builder(builder), worldspaces(std::move(worldspaces))
        {
        }
        virtual         ~Buildable_Worldspaces_t()              = default;
        virtual Bool_t  Can_Enable()                override    { return worldspaces.size() > 0; }
        virtual Bool_t  Can_Show()                  override    { return builder->Do_Show_Worldspaces(); }
        virtual void    Build()                     override    { builder->Build_Worldspaces(worldspaces); }
        virtual Type_t  Type()                      override    { return References_Item_Section_e::WORLDSPACES; }
    };

}}
