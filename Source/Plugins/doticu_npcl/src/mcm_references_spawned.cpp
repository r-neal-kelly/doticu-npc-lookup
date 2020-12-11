/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/translations.h"

#include "doticu_skylib/virtual_function.h"

#include "consts.h"
#include "filter.h"
#include "spawned_actors.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_spawned.h"
#include "mcm_markers.h"

namespace doticu_npcl { namespace MCM {

    using Item_t = Spawned_References_Base_t::Item_t;

    String_t                        Spawned_References_Base_t::Class_Name()         { DEFINE_CLASS_NAME("doticu_npcl_mcm_references_spawned"); }
    V::Class_t*                     Spawned_References_Base_t::Class()              { DEFINE_CLASS(); }
    V::Object_t*                    Spawned_References_Base_t::Object()             { DEFINE_OBJECT(); }

    Spawned_References_t*           Spawned_References_Base_t::Self()               { return static_cast<Spawned_References_t*>(Consts_t::NPCL_MCM_Quest()); }
    Spawned_References_List_t*      Spawned_References_Base_t::List()               { return reinterpret_cast<Spawned_References_List_t*>(this); }
    Spawned_References_Filter_t*    Spawned_References_Base_t::Filter()             { return reinterpret_cast<Spawned_References_Filter_t*>(this); }
    Spawned_References_Options_t*   Spawned_References_Base_t::Options()            { return reinterpret_cast<Spawned_References_Options_t*>(this); }
    Spawned_References_Item_t*      Spawned_References_Base_t::Item()               { return reinterpret_cast<Spawned_References_Item_t*>(this); }

}}

namespace doticu_npcl { namespace MCM {

    void Spawned_References_t::On_Load()
    {
        References_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>::On_Load();

        Spawned_Actors_t& spawned = Spawned_Actors_t::Self();
        spawned.Clear();

        Spawned_References_List_t* list = List();
        V::Array_t* actor_ids = list->Actor_IDs_Array();
        V::Array_t* actor_mod_names = list->Actor_Mod_Names_Array();
        V::Array_t* actor_base_ids = list->Actor_Base_IDs_Array();
        V::Array_t* actor_base_mod_names = list->Actor_Base_Mod_Names_Array();
        if (actor_ids && actor_mod_names && actor_base_ids && actor_base_mod_names) {
            if (actor_mod_names->count == actor_ids->count &&
                actor_base_ids->count == actor_ids->count &&
                actor_base_mod_names->count == actor_ids->count) {
                for (Index_t idx = 0, end = actor_ids->count; idx < end; idx += 1) {
                    V::Variable_t* actor_id = actor_ids->Point(idx);
                    V::Variable_t* actor_mod_name = actor_mod_names->Point(idx);
                    V::Variable_t* actor_base_id = actor_base_ids->Point(idx);
                    V::Variable_t* actor_base_mod_name = actor_base_mod_names->Point(idx);
                    if (actor_id && actor_mod_name && actor_base_id && actor_base_mod_name) {
                        spawned.Add(
                            actor_id->Int(),
                            actor_mod_name->String(),
                            actor_base_id->Int(),
                            actor_base_mod_name->String()
                        );
                    }
                }
            }
        }
    }

    void Spawned_References_t::On_Save()
    {
        References_t<Spawned_References_Base_t, Spawned_References_Base_t::Item_t>::On_Save();

        Spawned_Actors_t& spawned = Spawned_Actors_t::Self();

        Spawned_References_List_t* list = List();
        list->Actor_IDs(spawned.actor_ids);
        list->Actor_Mod_Names(spawned.actor_mod_names);
        list->Actor_Base_IDs(spawned.actor_base_ids);
        list->Actor_Base_Mod_Names(spawned.actor_base_mod_names);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Array_Variable_t<Int_t>*     Spawned_References_List_t::Actor_IDs_Variable()             { DEFINE_ARRAY_VARIABLE(Int_t, "p_actor_ids"); }
    V::Array_Variable_t<String_t>*  Spawned_References_List_t::Actor_Mod_Names_Variable()       { DEFINE_ARRAY_VARIABLE(String_t, "p_actor_mod_names"); }
    V::Array_Variable_t<Int_t>*     Spawned_References_List_t::Actor_Base_IDs_Variable()        { DEFINE_ARRAY_VARIABLE(Int_t, "p_actor_base_ids"); }
    V::Array_Variable_t<String_t>*  Spawned_References_List_t::Actor_Base_Mod_Names_Variable()  { DEFINE_ARRAY_VARIABLE(String_t, "p_actor_base_mod_names"); }

    Vector_t<Form_ID_t> Spawned_References_List_t::Actor_IDs()                                      { return *reinterpret_cast<Vector_t<Form_ID_t>*>(&Actor_IDs_Variable()->Values()); }
    void                Spawned_References_List_t::Actor_IDs(Vector_t<Form_ID_t> values)            { Actor_IDs_Variable()->Values(reinterpret_cast<Vector_t<Int_t>&>(values)); }
    V::Array_t*         Spawned_References_List_t::Actor_IDs_Array()                                { return Actor_IDs_Variable()->Value(); }

    Vector_t<String_t>  Spawned_References_List_t::Actor_Mod_Names()                                { return Actor_Mod_Names_Variable()->Values(); }
    void                Spawned_References_List_t::Actor_Mod_Names(Vector_t<String_t> values)       { Actor_Mod_Names_Variable()->Values(values); }
    V::Array_t*         Spawned_References_List_t::Actor_Mod_Names_Array()                          { return Actor_Mod_Names_Variable()->Value(); }

    Vector_t<Form_ID_t> Spawned_References_List_t::Actor_Base_IDs()                                 { return *reinterpret_cast<Vector_t<Form_ID_t>*>(&Actor_Base_IDs_Variable()->Values()); }
    void                Spawned_References_List_t::Actor_Base_IDs(Vector_t<Form_ID_t> values)       { Actor_Base_IDs_Variable()->Values(reinterpret_cast<Vector_t<Int_t>&>(values)); }
    V::Array_t*         Spawned_References_List_t::Actor_Base_IDs_Array()                           { return Actor_Base_IDs_Variable()->Value(); }

    Vector_t<String_t>  Spawned_References_List_t::Actor_Base_Mod_Names()                           { return Actor_Base_Mod_Names_Variable()->Values(); }
    void                Spawned_References_List_t::Actor_Base_Mod_Names(Vector_t<String_t> values)  { Actor_Base_Mod_Names_Variable()->Values(values); }
    V::Array_t*         Spawned_References_List_t::Actor_Base_Mod_Names_Array()                     { return Actor_Base_Mod_Names_Variable()->Value(); }

    Vector_t<Item_t>& Spawned_References_List_t::Items()
    {
        if (!items || do_update_items) {
            do_update_items = false;

            size_t spawned_actor_count = Spawned_Actors_t::Spawned_Actor_Count();

            read.reserve(spawned_actor_count);
            read.clear();
            Spawned_Actors_t::Spawned_Actors(read);

            write.reserve(spawned_actor_count);
            write.clear();

            items = Filter()->Execute(&read, &write).Results();

            items->Sort(
                [](Item_t* item_a, Item_t* item_b)->Int_t
                {
                    if (!item_a || !*item_a) {
                        return Comparator_e::IS_UNORDERED;
                    } else if (!item_b || !*item_b) {
                        return Comparator_e::IS_ORDERED;
                    } else {
                        Comparator_e result = Main_t::String_Comparator(
                            (*item_a)->Any_Name(),
                            (*item_b)->Any_Name()
                        );
                        if (result == Comparator_e::IS_EQUAL) {
                            return (*item_a)->form_id - (*item_b)->form_id;
                        } else {
                            return result;
                        }
                    }
                }
            );
        }

        return *items;
    }

    Vector_t<Item_t> Spawned_References_List_t::Default_Items()
    {
        return Spawned_Actors_t::Spawned_Actors();
    }

    Item_t Spawned_References_List_t::Null_Item()
    {
        return nullptr;
    }

    void Spawned_References_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (!is_refresh) {
            do_update_items = true;
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Vector_t<Item_t>& items = Items();
        size_t item_count = items.size();
        if (item_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index(page_index);
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index(page_index);
            }

            ////mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, item_count, page_index, page_count));
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, item_count, page_index, page_count));

            Filter_Option() = mcm->Add_Text_Option(Main_t::CENTER_FILTER, Main_t::_NONE_);
            Options_Option() = mcm->Add_Text_Option(Main_t::CENTER_OPTIONS, Main_t::_NONE_);
            if (page_count > 1) {
                Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_);
                Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_);
            } else {
                Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
                Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
            }

            mcm->Add_Header_Option(Main_t::_NONE_);
            mcm->Add_Header_Option(Main_t::_NONE_);

            Int_t begin = ITEMS_PER_PAGE * page_index;
            Int_t end = begin + ITEMS_PER_PAGE;
            if (end > item_count) {
                end = item_count;
            }
            for (; begin < end; begin += 1) {
                Item_t item = items[begin];
                mcm->Add_Text_Option(item->Any_Name(), Main_t::_DOTS_);
            }
        } else {
            ////mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, 0, 0, 1));
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, 0, 0, 1));

            Filter_Option() = mcm->Add_Text_Option(Main_t::CENTER_FILTER, Main_t::_NONE_);
            Options_Option() = mcm->Add_Text_Option(Main_t::CENTER_OPTIONS, Main_t::_NONE_);
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);

            mcm->Add_Header_Option(Main_t::NO_SPAWNED_REFERENCES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Filter_Option()) {
            mcm->Disable_Option(option);
            Current_View(Bases_View_e::FILTER);
            mcm->Reset_Page();
        } else if (option == Options_Option()) {
            mcm->Disable_Option(option);
            Current_View(Bases_View_e::OPTIONS);
            mcm->Reset_Page();

        } else if (option == Previous_Page_Option()) {
            mcm->Disable_Option(option);

            Vector_t<Item_t>& items = Items();
            size_t item_count = items.size();
            if (item_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == 0) {
                    page_index = page_count - 1;
                } else {
                    page_index -= 1;
                }
                Page_Index(page_index);
            }

            mcm->Reset_Page();
        } else if (option == Next_Page_Option()) {
            mcm->Disable_Option(option);

            Vector_t<Item_t>& items = Items();
            size_t item_count = items.size();
            if (item_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == page_count - 1) {
                    page_index = 0;
                } else {
                    page_index += 1;
                }
                Page_Index(page_index);
            }

            mcm->Reset_Page();

        } else {
            Vector_t<Item_t>& items = Items();
            Index_t item_index = mcm->Option_To_Item_Index(
                option, items.size(), Page_Index(), HEADERS_PER_PAGE, ITEMS_PER_PAGE
            );
            if (item_index > -1) {
                Item_t item = items[item_index];
                if (item && item->Is_Valid()) {
                    mcm->Disable_Option(option);
                    Item()->Actor_Form_ID(item->form_id);
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Spawned_References_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        ////mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, Main_t::COMPONENT_FILTER));
        mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, Main_t::SAFE_COMPONENT_FILTER));

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Clear_Option() = mcm->Add_Text_Option(Main_t::CENTER_CLEAR, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::MOD);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Mod_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Mod_Argument());
        Mod_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Mod_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Mod_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RACE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Race_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Race_Argument());
        Race_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Race_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Race_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::BASE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Base_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Base_Argument());
        Base_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Base_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Base_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::SPAWNED_REFERENCE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Reference_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Reference_Argument());
        Reference_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Reference_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Reference_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::TEMPLATE);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Template_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Template_Argument());
        Template_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Template_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Template_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::LOCATION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Location_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Location_Argument());
        Location_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Location_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Location_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::CELL);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Cell_Search_Option() = mcm->Add_Input_Option(Main_t::SEARCH, Cell_Argument());
        Cell_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Main_t::_DOTS_);
        Cell_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Cell_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Main_t::RELATION);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Relation_Select_Option() = mcm->Add_Menu_Option(Main_t::SELECT, Relation_Argument());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(Main_t::NEGATE, Relation_Do_Negate());

        mcm->Add_Header_Option(Main_t::OTHER);
        mcm->Add_Header_Option(Main_t::_NONE_);

        Male_Option() = mcm->Add_Toggle_Option(Main_t::IS_MALE, Male_Female_Argument() == Binary_e::A);
        Female_Option() = mcm->Add_Toggle_Option(Main_t::IS_FEMALE, Male_Female_Argument() == Binary_e::B);

        Unique_Option() = mcm->Add_Toggle_Option(Main_t::IS_UNIQUE, Unique_Generic_Argument() == Binary_e::A);
        Generic_Option() = mcm->Add_Toggle_Option(Main_t::IS_GENERIC, Unique_Generic_Argument() == Binary_e::B);

        Interior_Option() = mcm->Add_Toggle_Option(Main_t::IN_INTERIOR, Interior_Exterior_Argument() == Binary_e::A);
        Exterior_Option() = mcm->Add_Toggle_Option(Main_t::IN_EXTERIOR, Interior_Exterior_Argument() == Binary_e::B);

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Filter_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Clear_Option()) {
            mcm->Disable_Option(option);
            Clear();
            mcm->Reset_Page();

        } else if (option == Mod_Negate_Option()) {
            Bool_t value = Mod_Do_Negate();
            Mod_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Race_Negate_Option()) {
            Bool_t value = Race_Do_Negate();
            Race_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Base_Negate_Option()) {
            Bool_t value = Base_Do_Negate();
            Base_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Template_Negate_Option()) {
            Bool_t value = Template_Do_Negate();
            Template_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Reference_Negate_Option()) {
            Bool_t value = Reference_Do_Negate();
            Reference_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Location_Negate_Option()) {
            Bool_t value = Location_Do_Negate();
            Location_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Cell_Negate_Option()) {
            Bool_t value = Cell_Do_Negate();
            Cell_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Relation_Negate_Option()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Male_Option()) {
            mcm->Toggle_Either(Male_Female_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Female_Option()) {
            mcm->Toggle_Either(Male_Female_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Unique_Option()) {
            mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Generic_Option()) {
            mcm->Toggle_Either(Unique_Generic_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Interior_Option()) {
            mcm->Toggle_Either(Interior_Exterior_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Exterior_Option()) {
            mcm->Toggle_Either(Interior_Exterior_Argument_Variable(), option - 1, option, Binary_e::B);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Filter_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Mods());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Race_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Races());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Base_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Bases());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Template_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Templates());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Reference_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_References());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Location_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Locations());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Cell_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Cells());
            mcm->Menu_Dialog_Default(0);
        } else if (option == Relation_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> mods = Selectable_Mods();
                    if (idx < mods.size()) {
                        value = mods[idx];
                    }
                }
                Mod_Argument(value);
                mcm->Input_Option_Value(Mod_Search_Option(), value, true);
            }
        } else if (option == Race_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> races = Selectable_Races();
                    if (idx < races.size()) {
                        value = races[idx];
                    }
                }
                Race_Argument(value);
                mcm->Input_Option_Value(Race_Search_Option(), value, true);
            }
        } else if (option == Base_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> bases = Selectable_Bases();
                    if (idx < bases.size()) {
                        value = bases[idx];
                    }
                }
                Base_Argument(value);
                mcm->Input_Option_Value(Base_Search_Option(), value, true);
            }
        } else if (option == Template_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> values = Selectable_Templates();
                    if (idx < values.size()) {
                        value = values[idx];
                    }
                }
                Template_Argument(value);
                mcm->Input_Option_Value(Template_Search_Option(), value, true);
            }
        } else if (option == Reference_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> names = Selectable_References();
                    if (idx < names.size()) {
                        value = names[idx];
                    }
                }
                Reference_Argument(value);
                mcm->Input_Option_Value(Reference_Search_Option(), value, true);
            }
        } else if (option == Location_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> locations = Selectable_Locations();
                    if (idx < locations.size()) {
                        value = locations[idx];
                    }
                }
                Location_Argument(value);
                mcm->Input_Option_Value(Location_Search_Option(), value, true);
            }
        } else if (option == Cell_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::_NONE_;
                if (idx > 0) {
                    Vector_t<String_t> cells = Selectable_Cells();
                    if (idx < cells.size()) {
                        value = cells[idx];
                    }
                }
                Cell_Argument(value);
                mcm->Input_Option_Value(Cell_Search_Option(), value, true);
            }
        } else if (option == Relation_Select_Option()) {
            if (idx > -1) {
                String_t value = Main_t::ANY;
                if (idx > 0) {
                    Vector_t<String_t> relations = Selectable_Relations();
                    if (idx < relations.size()) {
                        value = relations[idx];
                    }
                }
                Relation_Argument(value);
                mcm->Menu_Option_Value(option, value, true);
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Filter_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Search_Option()) {
            Mod_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Race_Search_Option()) {
            Race_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Base_Search_Option()) {
            Base_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Template_Search_Option()) {
            Template_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Reference_Search_Option()) {
            Reference_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Location_Search_Option()) {
            Location_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        } else if (option == Cell_Search_Option()) {
            Cell_Argument(value);
            mcm->Input_Option_Value(option, value, true);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    Int_t&              Spawned_References_Options_t::Do_Verify_Unspawns_Option()       { DEFINE_OPTION(); }

    V::Bool_Variable_t* Spawned_References_Options_t::Do_Verify_Unspawns_Variable()     { DEFINE_BOOL_VARIABLE("p_options_do_verify_unspawns"); }

    inline Bool_t       Spawned_References_Options_t::Do_Verify_Unspawns()              { return Do_Verify_Unspawns_Variable()->Value(); }
    inline void         Spawned_References_Options_t::Do_Verify_Unspawns(Bool_t value)  { Do_Verify_Unspawns_Variable()->Value(value); }

    void Spawned_References_Options_t::Reset()
    {
        References_Options_t<Spawned_References_Base_t, Item_t>::Reset();

        Do_Verify_Unspawns(true);
    }

    void Spawned_References_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        ////mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, Main_t::COMPONENT_OPTIONS));
        mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, Main_t::SAFE_COMPONENT_OPTIONS));

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Reset_Option() = mcm->Add_Text_Option(Main_t::CENTER_RESET, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::_NONE_);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Smart_Select_Option() = mcm->Add_Toggle_Option(Main_t::SMART_SELECT, Do_Smart_Select());
        Do_Verify_Unspawns_Option() = mcm->Add_Toggle_Option(Main_t::VERIFY_UNSPAWNS, Do_Verify_Unspawns());

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Reset_Option()) {
            mcm->Disable_Option(option);
            Reset();
            mcm->Reset_Page();

        } else if (option == Smart_Select_Option()) {
            Bool_t value = Do_Smart_Select();
            Do_Smart_Select(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Do_Verify_Unspawns_Option()) {
            Bool_t value = Do_Verify_Unspawns();
            Do_Verify_Unspawns(!value);
            mcm->Toggle_Option_Value(option, !value);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Options_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Smart_Select_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_SMART_SELECT);
        } else if (option == Do_Verify_Unspawns_Option()) {
            mcm->Info_Text(Main_t::HIGHLIGHT_VERIFY_UNSPAWNS);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  Spawned_References_Item_t::Actor_Form_ID_Variable()         { DEFINE_INT_VARIABLE("p_item_actor_form_id"); }

    Form_ID_t           Spawned_References_Item_t::Actor_Form_ID()                  { return Actor_Form_ID_Variable()->Value(); }
    void                Spawned_References_Item_t::Actor_Form_ID(Form_ID_t value)   { Actor_Form_ID_Variable()->Value(value); }

    Item_t Spawned_References_Item_t::Current_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid() && List()->Items().Has(item)) {
            return item;
        } else {
            return nullptr;
        }
    }

    Item_t Spawned_References_Item_t::Previous_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t idx = items.Index_Of(item);
            if (idx > -1) {
                if (idx == 0) {
                    idx = items.size() - 1;
                } else {
                    idx -= 1;
                }
                return items[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Item_t Spawned_References_Item_t::Next_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t idx = items.Index_Of(item);
            if (idx > -1) {
                if (idx == items.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return items[idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Spawned_References_Item_t::Back_To_List(some<Main_t*> mcm, some<Latent_Callback_i*> lcallback)
    {
        SKYLIB_ASSERT_SOME(mcm);
        SKYLIB_ASSERT_SOME(lcallback);

        List()->do_update_items = true;
        Current_View(Bases_View_e::LIST);
        mcm->Reset_Page();
        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Item_t::Select_Unspawn(some<Main_t*> mcm, Int_t option, some<Latent_Callback_i*> lcallback)
    {
        SKYLIB_ASSERT_SOME(mcm);
        SKYLIB_ASSERT_SOME(lcallback);

        maybe<Actor_t*> spawn = Current_Item();
        if (spawn && spawn->Is_Valid()) {
            if (Options()->Do_Verify_Unspawns()) {
                class Verify_Callback_t : public Callback_i<Bool_t>
                {
                public:
                    Spawned_References_Item_t* self;
                    Main_t* mcm;
                    Int_t option;
                    Latent_Callback_i* lcallback;
                    Actor_t* spawn;
                    Verify_Callback_t(Spawned_References_Item_t* self,
                                      Main_t* mcm,
                                      Int_t option,
                                      Latent_Callback_i* lcallback,
                                      Actor_t* spawn) :
                        self(self),
                        mcm(mcm),
                        option(option),
                        lcallback(lcallback),
                        spawn(spawn)
                    {
                    }
                    void operator()(Bool_t accept)
                    {
                        if (accept) {
                            mcm->Disable_Option(option);
                            Spawned_Actors_t::Self().Remove(spawn);
                            Markers_t::Self()->Unmark(spawn);
                            spawn->Mark_For_Delete();
                            self->Back_To_List(mcm, lcallback);
                        } else {
                            mcm->Destroy_Latent_Callback(lcallback);
                        }
                    }
                };
                mcm->Flicker_Option(option);
                mcm->Show_Message(
                    Main_t::CONFIRM_UNSPAWN,
                    true,
                    Main_t::YES,
                    Main_t::NO,
                    new Verify_Callback_t(this, mcm, option, lcallback, spawn)
                );
            } else {
                mcm->Disable_Option(option);
                Spawned_Actors_t::Self().Remove(spawn);
                Markers_t::Self()->Unmark(spawn);
                spawn->Mark_For_Delete();
                Back_To_List(mcm, lcallback);
            }
        } else {
            mcm->Disable_Option(option);
            Back_To_List(mcm, lcallback);
        }
    }

    void Spawned_References_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t item_index = items.Index_Of(item);
            if (item_index > -1) {
                ////mcm->Translated_Title_Text(
                ////    mcm->Singular_Title(Main_t::COMPONENT_SPAWNED_REFERENCE, item->Any_Name(), item_index, items.size())
                ////);
                mcm->Title_Text(
                    mcm->Singular_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCE, item->Any_Name(), item_index, items.size())
                );

                mcm->Cursor_Position(0);
                mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

                Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
                Primary_Option() = mcm->Add_Text_Option(Main_t::CENTER_UNSPAWN, Main_t::_NONE_);
                if (List()->Items().size() > 1) {
                    Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_);
                    Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_);
                } else {
                    Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
                    Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_ITEM, Main_t::_NONE_, Flag_e::DISABLE);
                }

                mcm->Add_Header_Option(Main_t::SPAWNED_REFERENCE);
                mcm->Add_Header_Option(Main_t::_NONE_);
                {
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + item->Name(), Main_t::_NONE_);
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + item->Form_ID_String().data, Main_t::_NONE_);

                    Actor_Base_t* actor_base = item->Actor_Base();
                    if (actor_base && actor_base->Is_Valid()) {
                        if (actor_base->Is_Male()) {
                            mcm->Add_Text_Option(Main_t::IS_MALE, Main_t::_NONE_);
                        } else {
                            mcm->Add_Text_Option(Main_t::IS_FEMALE, Main_t::_NONE_);
                        }
                        if (actor_base->Is_Unique()) {
                            mcm->Add_Text_Option(Main_t::IS_UNIQUE, Main_t::_NONE_);
                        } else {
                            mcm->Add_Text_Option(Main_t::IS_GENERIC, Main_t::_NONE_);
                        }
                    }
                }

                mcm->Add_Header_Option(Main_t::COMMANDS);
                mcm->Add_Header_Option(Main_t::_NONE_);
                {
                    Markers_t* markers = Markers_t::Self();
                    if (markers->Has_Marked(item)) {
                        Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::REMOVE_MARKER_FROM_MAP, Main_t::_NONE_);
                    } else {
                        if (markers->Has_Space()) {
                            Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::ADD_MARKER_TO_MAP, Main_t::_NONE_);
                        } else {
                            Mark_On_Map_Option() = mcm->Add_Text_Option(Main_t::ADD_MARKER_TO_MAP, Main_t::_NONE_, Flag_e::DISABLE);
                        }
                    }

                    Move_To_Player_Option() = mcm->Add_Text_Option(Main_t::MOVE_TO_PLAYER, Main_t::_NONE_);

                    if (item->Is_Disabled()) {
                        Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::ENABLE_REFERENCE, Main_t::_NONE_);
                    } else {
                        Enable_Disable_Option() = mcm->Add_Text_Option(Main_t::DISABLE_REFERENCE, Main_t::_NONE_);
                    }

                    Select_In_Console_Option() = mcm->Add_Text_Option(Main_t::SELECT_IN_CONSOLE, Main_t::_NONE_);
                }

                Race_t* race = item->Race();
                if (race && race->Is_Valid()) {
                    mcm->Add_Header_Option(Main_t::RACE);
                    mcm->Add_Header_Option(Main_t::_NONE_);
                    Race_Name_Option() = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Get_Editor_ID(), Main_t::_NONE_);
                    mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + race->Form_ID_String().data, Main_t::_NONE_);
                }

                {
                    Vector_t<Actor_Base_t*> actor_bases = item->Actor_Bases();
                    size_t actor_base_count = actor_bases.size();
                    if (actor_base_count > 0 && mcm->Can_Add_Options(2 + actor_base_count)) {
                        mcm->Add_Header_Option(Main_t::BASES);
                        mcm->Add_Header_Option(Main_t::_NONE_);
                        for (Index_t idx = 0, end = actor_base_count; idx < end; idx += 1) {
                            Actor_Base_t* actor_base = actor_bases[idx];
                            const char* name = actor_base->Name();
                            const char* form_id = actor_base->Form_ID_String().data;
                            mcm->Add_Text_Option(
                                Main_t::_SPACE_ + mcm->Pretty_ID(name, Main_t::_NONE_, form_id),
                                Main_t::_NONE_
                            );
                        }
                        if (skylib::Is_Odd(mcm->Cursor_Position())) {
                            mcm->Add_Empty_Option();
                        }
                    }
                }

                Cell_t* cell = item->Cell();
                if (cell && cell->Is_Valid()) {
                    mcm->Add_Header_Option(Main_t::CELL);
                    mcm->Add_Header_Option(Main_t::_NONE_);
                    Cell_Name_Option() = mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + cell->Any_Name().data, Main_t::_NONE_);
                    if (cell->Is_Interior()) {
                        mcm->Add_Text_Option(Main_t::IS_INTERIOR, Main_t::_NONE_);
                    } else {
                        mcm->Add_Text_Option(Main_t::IS_EXTERIOR, Main_t::_NONE_);
                    }
                }

                if (cell && cell->Is_Valid()) {
                    Vector_t<String_t> location_names = cell->Location_Names();
                    size_t location_name_count = location_names.size();
                    if (location_name_count > 0 && mcm->Can_Add_Options(2 + location_name_count)) {
                        mcm->Add_Header_Option(Main_t::LOCATIONS);
                        mcm->Add_Header_Option(Main_t::_NONE_);
                        for (Index_t idx = 0, end = location_name_count; idx < end; idx += 1) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + location_names[idx].data, Main_t::_NONE_);
                        }
                        if (skylib::Is_Odd(mcm->Cursor_Position())) {
                            mcm->Add_Empty_Option();
                        }
                    }
                }

                {
                    Vector_t<String_t> mod_names = item->Mod_Names();
                    size_t mod_name_count = mod_names.size();
                    if (mod_name_count > 0 && mcm->Can_Add_Options(2 + mod_name_count)) {
                        mcm->Add_Header_Option(Main_t::MODS);
                        mcm->Add_Header_Option(Main_t::_NONE_);
                        for (Index_t idx = 0, end = mod_name_count; idx < end; idx += 1) {
                            mcm->Add_Text_Option(std::string(Main_t::_SPACE_) + mod_names[idx].data, Main_t::_NONE_);
                        }
                        if (skylib::Is_Odd(mcm->Cursor_Position())) {
                            mcm->Add_Empty_Option();
                        }
                    }
                }
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
                mcm->Reset_Page();
            }
        } else {
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Spawned_References_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Primary_Option()) {
            Select_Unspawn(mcm, option, lcallback);

        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            Item_t item = Previous_Item();
            if (item && item->Is_Valid()) {
                Actor_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            Item_t item = Next_Item();
            if (item && item->Is_Valid()) {
                Actor_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Mark_On_Map_Option()) {
            mcm->Flicker_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                Markers_t* markers = Markers_t::Self();
                if (markers->Has_Marked(item)) {
                    Markers_t::Self()->Unmark(item);
                } else {
                    Markers_t::Self()->Mark(item);
                }
                mcm->Reset_Page();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Move_To_Player_Option()) {
            mcm->Flicker_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                item->Move_To_Orbit(Consts_t::Skyrim_Player_Actor(), 160.0f, 0.0f);
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Enable_Disable_Option()) {
            mcm->Flicker_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                if (item->Is_Disabled()) {
                    item->Enable();
                } else {
                    item->Disable();
                }
                mcm->Reset_Page();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Select_In_Console_Option()) {
            mcm->Flicker_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                item->Select_In_Console();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else {
            mcm->Destroy_Latent_Callback(lcallback);
        }
    }

    void Spawned_References_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t item = Current_Item();
        if (item && item->Is_Valid()) {
            if (option == Primary_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_UNSPAWN);
            } else if (option == Mark_On_Map_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_ADD_REMOVE_MAP_MARKER);
            } else if (option == Move_To_Player_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_MOVE_TO_PLAYER);
            } else if (option == Enable_Disable_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_ENABLE_DISABLE_REFERENCE);
            } else if (option == Select_In_Console_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_SELECT_IN_CONSOLE);

            } else if (option == Race_Name_Option()) {
                Race_t* race = item->Race();
                if (race) {
                    const char* name = race->Name();
                    const char* editor_id = race->Get_Editor_ID();
                    const char* form_id = race->Form_ID_String().data;
                    mcm->Info_Text(mcm->Pretty_ID(name, editor_id, form_id));
                }
            } else if (option == Cell_Name_Option()) {
                Cell_t* cell = item->Cell();
                if (cell) {
                    const char* name = cell->Name();
                    const char* editor_id = cell->Get_Editor_ID();
                    const char* form_id = cell->Form_ID_String().data;
                    mcm->Info_Text(mcm->Pretty_ID(name, editor_id, form_id));
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}
