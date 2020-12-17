/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "mcm_bases.h"

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

    public:
        V::String_Variable_t*   Reference_Argument_Variable();
        V::Bool_Variable_t*     Reference_Do_Negate_Variable();

        V::String_Variable_t*   Worldspace_Argument_Variable();
        V::Bool_Variable_t*     Worldspace_Do_Negate_Variable();

        V::String_Variable_t*   Location_Argument_Variable();
        V::Bool_Variable_t*     Location_Do_Negate_Variable();

        V::String_Variable_t*   Cell_Argument_Variable();
        V::Bool_Variable_t*     Cell_Do_Negate_Variable();

        V::String_Variable_t*   Quest_Argument_Variable();
        V::Bool_Variable_t*     Quest_Do_Negate_Variable();

        V::Int_Variable_t*      Interior_Exterior_Argument_Variable();
        V::Int_Variable_t*      Alive_Dead_Argument_Variable();
        V::Int_Variable_t*      Is_Teammate_Argument_Variable();

    public:
        String_t    Reference_Argument();
        void        Reference_Argument(String_t value);
        Bool_t      Reference_Do_Negate();
        void        Reference_Do_Negate(Bool_t value);

        String_t    Worldspace_Argument();
        void        Worldspace_Argument(String_t value);
        Bool_t      Worldspace_Do_Negate();
        void        Worldspace_Do_Negate(Bool_t value);

        String_t    Location_Argument();
        void        Location_Argument(String_t value);
        Bool_t      Location_Do_Negate();
        void        Location_Do_Negate(Bool_t value);

        String_t    Cell_Argument();
        void        Cell_Argument(String_t value);
        Bool_t      Cell_Do_Negate();
        void        Cell_Do_Negate(Bool_t value);

        String_t    Quest_Argument();
        void        Quest_Argument(String_t value);
        Bool_t      Quest_Do_Negate();
        void        Quest_Do_Negate(Bool_t value);

        Binary_e    Interior_Exterior_Argument();
        void        Interior_Exterior_Argument(Binary_e value);

        Binary_e    Alive_Dead_Argument();
        void        Alive_Dead_Argument(Binary_e value);

        Binary_e    Is_Teammate_Argument();
        void        Is_Teammate_Argument(Binary_e value);

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
        void On_Option_Select(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback);
        void On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback);
        void On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback);
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_Options_t : public Bases_Options_t<Base_t, Item_t>
    {
    public:
    };

}}

namespace doticu_npcl { namespace MCM {

    template <typename Base_t, typename Item_t>
    class References_Item_t : public Bases_Item_t<Base_t, Item_t>
    {
    public:
        Int_t&  Select_In_Console_Option();
        Int_t&  Mark_On_Map_Option();
        Int_t&  Move_To_Player_Option();
        Int_t&  Go_To_Reference_Option();
        Int_t&  Enable_Disable_Option();

    public:
        void    Build_Bases(Vector_t<Actor_Base_t*> actor_bases);
        void    Build_Cell(Cell_t* cell);
        void    Build_Locations(Cell_t* cell);
        void    Build_Quests(Vector_t<Quest_t*> quests);
        void    Build_Reference(Actor_t* actor, const char* type_name);
    };

}}
