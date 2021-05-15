/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/worldspace.h"

#include "consts.h"
#include "filter.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_loaded.h"
#include "mcm_markers.h"

namespace doticu_npcl { namespace MCM {

    using Base_t = Loaded_References_Base_t;
    using Item_t = Loaded_References_Base_t::Item_t;

    String_t                            Loaded_References_Base_t::Class_Name()  { DEFINE_CLASS_NAME("doticu_npcl_mcm_references_loaded"); }
    V::Class_t*                         Loaded_References_Base_t::Class()       { DEFINE_CLASS(); }
    V::Object_t*                        Loaded_References_Base_t::Object()      { DEFINE_OBJECT_METHOD(); }

    some<Loaded_References_t*>          Loaded_References_Base_t::Self()        { return static_cast<some<Loaded_References_t*>>(Consts_t::NPCL_MCM_Quest()); }
    some<Loaded_References_List_t*>     Loaded_References_Base_t::List()        { return reinterpret_cast<Loaded_References_List_t*>(this); }
    some<Loaded_References_Filter_t*>   Loaded_References_Base_t::Filter()      { return reinterpret_cast<Loaded_References_Filter_t*>(this); }
    some<Loaded_References_Options_t*>  Loaded_References_Base_t::Options()     { return reinterpret_cast<Loaded_References_Options_t*>(this); }
    some<Loaded_References_Item_t*>     Loaded_References_Base_t::Item()        { return reinterpret_cast<Loaded_References_Item_t*>(this); }

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    Vector_t<Item_t>& Loaded_References_List_t::Items()
    {
        if (!items || do_update_items) {
            do_update_items = false;

            read.reserve(2048);
            read.clear();
            Actor_t::All(reinterpret_cast<Vector_t<some<Item_t>>&>(read));

            write.reserve(2048);
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

    Vector_t<Item_t> Loaded_References_List_t::Default_Items()
    {
        return *reinterpret_cast<Vector_t<Item_t>*>(&Actor_t::All());
    }

    Item_t Loaded_References_List_t::Null_Item()
    {
        return Item_t();
    }

    void Loaded_References_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        if (!is_refresh) {
            do_update_items = true;
        }

        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Vector_t<Item_t>& loaded_actors = Items();
        size_t loaded_actor_count = loaded_actors.size();
        if (loaded_actor_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(loaded_actor_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Item_t current_item = Item()->Current_Item();
            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index() = page_index;
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index() = page_index;
            } else if (current_item && current_item->Is_Valid()) {
                maybe<size_t> maybe_idx = loaded_actors.Index_Of(current_item);
                if (maybe_idx.Has_Value()) {
                    size_t idx = maybe_idx.Value();
                    page_index = idx / ITEMS_PER_PAGE;
                    Page_Index() = page_index;
                }
            }

            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, loaded_actor_count, page_index, page_count));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, loaded_actor_count, page_index, page_count));
            }

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
            if (end > loaded_actor_count) {
                end = loaded_actor_count;
            }
            for (; begin < end; begin += 1) {
                Item_t loaded_actor = loaded_actors[begin];
                mcm->Add_Text_Option(loaded_actor->Any_Name(), Main_t::_DOTS_);
            }
        } else {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, 0, 0, 1));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, 0, 0, 1));
            }

            Filter_Option() = mcm->Add_Text_Option(Main_t::CENTER_FILTER, Main_t::_NONE_);
            Options_Option() = mcm->Add_Text_Option(Main_t::CENTER_OPTIONS, Main_t::_NONE_);
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);

            mcm->Add_Header_Option(Main_t::NO_LOADED_REFERENCES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Loaded_References_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

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

            Vector_t<Item_t>& loaded_actors = Items();
            size_t loaded_actor_count = loaded_actors.size();
            if (loaded_actor_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(loaded_actor_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == 0) {
                    page_index = page_count - 1;
                } else {
                    page_index -= 1;
                }
                Page_Index() = page_index;
            }

            mcm->Reset_Page();
        } else if (option == Next_Page_Option()) {
            mcm->Disable_Option(option);

            Vector_t<Item_t>& loaded_actors = Items();
            size_t loaded_actor_count = loaded_actors.size();
            if (loaded_actor_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(loaded_actor_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Page_Index();
                if (page_index == page_count - 1) {
                    page_index = 0;
                } else {
                    page_index += 1;
                }
                Page_Index() = page_index;
            }

            mcm->Reset_Page();

        } else {
            Vector_t<Item_t>& items = Items();
            maybe<size_t> item_index = mcm->Option_To_Item_Index(
                option, items.size(), Page_Index(), HEADERS_PER_PAGE, ITEMS_PER_PAGE
            );
            if (item_index.Has_Value()) {
                Item_t item = items[item_index.Value()];
                if (item && item->Is_Valid()) {
                    mcm->Disable_Option(option);
                    Item()->Actor_Form_ID() = item->form_id;
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    Toggle_Type_e Loaded_References_Filter_t::Toggle_Type()
    {
        return Toggle_Type_e::EITHER;
    }

    void Loaded_References_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Build_Filters(Main_t::LOADED_REFERENCE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Loaded_References_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, Main_t::SAFE_COMPONENT_OPTIONS));
        }

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Build_Header_Options();
        Build_General_Options();
        Build_Section_Options();

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Variable_tt<Form_ID_t>& Loaded_References_Item_t::Actor_Form_ID() { DEFINE_VAR(Form_ID_t, "p_item_actor_form_id"); }

    Item_t Loaded_References_Item_t::Current_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid() && List()->Items().Has(item())) {
            return item();
        } else {
            return nullptr;
        }
    }

    Bool_t Loaded_References_Item_t::Current_Item(Item_t item)
    {
        if (item && item->Is_Valid()) {
            Actor_Form_ID() = item->form_id;
            return true;
        } else {
            return false;
        }
    }

    Item_t Loaded_References_Item_t::Previous_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            maybe<size_t> maybe_idx = items.Index_Of(item());
            if (maybe_idx.Has_Value()) {
                size_t idx = maybe_idx.Value();
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

    Item_t Loaded_References_Item_t::Next_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            maybe<size_t> maybe_idx = items.Index_Of(item());
            if (maybe_idx.Has_Value()) {
                size_t idx = maybe_idx.Value();
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

    void Loaded_References_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            maybe<size_t> item_index = items.Index_Of(item());
            if (item_index.Has_Value()) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_LOADED_REFERENCE, item->Any_Name(), item_index.Value(), items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCE, item->Any_Name(), item_index.Value(), items.size())
                    );
                }

                mcm->Current_Cursor_Position() = 0;
                mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

                Int_t unused_option;
                Build_Header(unused_option, Main_t::_NONE_, List()->Items().size());
                {
                    Vector_t<Buildable_i*> buildables;
                    buildables.reserve(11);

                    Buildable_Bases_t<Base_t, Item_t> buildable_bases(this, item->Actor_Bases());
                    Buildable_Commands_t<Base_t, Item_t> buildable_commands(this, item());
                    Buildable_Factions_t<Base_t, Item_t> buildable_factions(this, item->Factions_And_Ranks());
                    Buildable_Keywords_t<Base_t, Item_t> buildable_keywords(this, item->Keywords());
                    Buildable_Mods_t<Base_t, Item_t> buildable_mods(this, item->Mods());
                    Buildable_Race_t<Base_t, Item_t> buildable_race(this, item->Race()());

                    Buildable_Cell_t<Base_t, Item_t> buildable_cell(this, item->Cell(true)());
                    Buildable_Locations_t<Base_t, Item_t> buildable_locations(this, item->Locations());
                    Buildable_Quests_t<Base_t, Item_t> buildable_quests(this, item->Quests());
                    Buildable_Reference_t<Base_t, Item_t> buildable_reference(this, item(), Main_t::LOADED_REFERENCE);
                    Buildable_Worldspaces_t<Base_t, Item_t> buildable_worldspaces(this, item->Worldspaces());

                    buildables.push_back(&buildable_bases);
                    buildables.push_back(&buildable_commands);
                    buildables.push_back(&buildable_factions);
                    buildables.push_back(&buildable_keywords);
                    buildables.push_back(&buildable_mods);
                    buildables.push_back(&buildable_race);

                    buildables.push_back(&buildable_cell);
                    buildables.push_back(&buildable_locations);
                    buildables.push_back(&buildable_quests);
                    buildables.push_back(&buildable_reference);
                    buildables.push_back(&buildable_worldspaces);

                    Build_Sections(buildables);
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

    void Loaded_References_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == Mark_On_Map_Option()) {
            mcm->Flicker_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                some<Markers_t*> markers = Markers_t::Self();
                if (markers->Has_Marked(item)) {
                    markers->Unmark(item);
                } else {
                    markers->Mark(item);
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

        } else if (option == Go_To_Reference_Option()) {
            mcm->Disable_Option(option);
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                struct Callback_t : public skylib::Callback_i<Bool_t>
                {
                    Actor_t* actor;
                    Callback_t(Actor_t* actor) :
                        actor(actor)
                    {
                    }
                    void operator()(Bool_t did_close)
                    {
                        if (did_close && actor && actor->Is_Valid()) {
                            Consts_t::Skyrim_Player_Actor()->Move_To_Orbit(actor, 160.0f, 0.0f);
                        }
                    }
                };
                V::Input_t::Close_Menus(new Callback_t(item));
            } else {
                mcm->Enable_Option(option);
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

        } else if (Try_On_Option_Select(option, lcallback)) {
            return;

        } else {
            mcm->Destroy_Latent_Callback(lcallback);

        }
    }

    void Loaded_References_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == rename_reference_option) {
            Item_t item = Current_Item();
            if (item && item->Is_Valid()) {
                if (value) {
                    item->Name(value);
                } else {
                    item->Name(item->Base_Name());
                }
                mcm->Reset_Page();
            }
            mcm->Destroy_Latent_Callback(lcallback);
        } else {
            References_Item_t<Loaded_References_Base_t, Item_t>::On_Option_Input_Accept(option, value, lcallback);
        }
    }

}}
