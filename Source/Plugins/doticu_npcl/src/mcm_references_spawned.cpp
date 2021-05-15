/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/translations.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_utility.h"

#include "consts.h"
#include "filter.h"
#include "spawned_actors.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_spawned.h"
#include "mcm_markers.h"

namespace doticu_npcl { namespace MCM {

    using Base_t = Spawned_References_Base_t;
    using Item_t = Spawned_References_Base_t::Item_t;

    String_t                            Spawned_References_Base_t::Class_Name() { DEFINE_CLASS_NAME("doticu_npcl_mcm_references_spawned"); }
    V::Class_t*                         Spawned_References_Base_t::Class()      { DEFINE_CLASS(); }
    V::Object_t*                        Spawned_References_Base_t::Object()     { DEFINE_OBJECT_METHOD(); }

    some<Spawned_References_t*>         Spawned_References_Base_t::Self()       { return static_cast<some<Spawned_References_t*>>(Consts_t::NPCL_MCM_Quest()); }
    some<Spawned_References_List_t*>    Spawned_References_Base_t::List()       { return reinterpret_cast<Spawned_References_List_t*>(this); }
    some<Spawned_References_Filter_t*>  Spawned_References_Base_t::Filter()     { return reinterpret_cast<Spawned_References_Filter_t*>(this); }
    some<Spawned_References_Options_t*> Spawned_References_Base_t::Options()    { return reinterpret_cast<Spawned_References_Options_t*>(this); }
    some<Spawned_References_Item_t*>    Spawned_References_Base_t::Item()       { return reinterpret_cast<Spawned_References_Item_t*>(this); }

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    V::Variable_tt<Vector_t<Form_ID_t>>&    Spawned_References_List_t::Actor_IDs()              { DEFINE_VAR(Vector_t<Form_ID_t>, "p_actor_ids"); }
    V::Variable_tt<Vector_t<String_t>>&     Spawned_References_List_t::Actor_Mod_Names()        { DEFINE_VAR(Vector_t<String_t>, "p_actor_mod_names"); }
    V::Variable_tt<Vector_t<Form_ID_t>>&    Spawned_References_List_t::Actor_Base_IDs()         { DEFINE_VAR(Vector_t<Form_ID_t>, "p_actor_base_ids"); }
    V::Variable_tt<Vector_t<String_t>>&     Spawned_References_List_t::Actor_Base_Mod_Names()   { DEFINE_VAR(Vector_t<String_t>, "p_actor_base_mod_names"); }

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

    void Spawned_References_List_t::On_Init()
    {
        References_List_t<Spawned_References_Base_t, Item_t>::On_Init();

        Spawned_Actors_t& spawned = Spawned_Actors_t::Self();
        spawned.Clear();
    }

    void Spawned_References_List_t::On_Load()
    {
        References_List_t<Spawned_References_Base_t, Item_t>::On_Load();

        Spawned_Actors_t& spawned = Spawned_Actors_t::Self();
        spawned.Clear();

        V::Array_t* actor_ids = Actor_IDs().Array();
        V::Array_t* actor_mod_names = Actor_Mod_Names().Array();
        V::Array_t* actor_base_ids = Actor_Base_IDs().Array();
        V::Array_t* actor_base_mod_names = Actor_Base_Mod_Names().Array();
        if (actor_ids && actor_mod_names && actor_base_ids && actor_base_mod_names) {
            if (actor_mod_names->count == actor_ids->count &&
                actor_base_ids->count == actor_ids->count &&
                actor_base_mod_names->count == actor_ids->count) {
                for (size_t idx = 0, end = actor_ids->count; idx < end; idx += 1) {
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

    void Spawned_References_List_t::On_Save()
    {
        References_List_t<Spawned_References_Base_t, Item_t>::On_Save();

        Spawned_Actors_t& spawned = Spawned_Actors_t::Self();

        Actor_IDs() = spawned.actor_ids;
        Actor_Mod_Names() = spawned.actor_mod_names;
        Actor_Base_IDs() = spawned.actor_base_ids;
        Actor_Base_Mod_Names() = spawned.actor_base_mod_names;
    }

    void Spawned_References_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        if (!is_refresh) {
            do_update_items = true;
        }

        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Vector_t<Item_t>& items = Items();
        size_t item_count = items.size();
        if (item_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
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
                maybe<size_t> maybe_idx = items.Index_Of(current_item);
                if (maybe_idx.Has_Value()) {
                    size_t idx = maybe_idx.Value();
                    page_index = idx / ITEMS_PER_PAGE;
                    Page_Index() = page_index;
                }
            }

            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, item_count, page_index, page_count));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, item_count, page_index, page_count));
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
            if (end > item_count) {
                end = item_count;
            }
            for (; begin < end; begin += 1) {
                Item_t item = items[begin];
                mcm->Add_Text_Option(item->Any_Name(), Main_t::_DOTS_);
            }
        } else {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, 0, 0, 1));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, 0, 0, 1));
            }

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
                Page_Index() = page_index;
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

    Toggle_Type_e Spawned_References_Filter_t::Toggle_Type()
    {
        return Toggle_Type_e::EITHER;
    }

    void Spawned_References_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Build_Filters(Main_t::SPAWNED_REFERENCE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    Int_t Spawned_References_Options_t::do_verify_unspawns_option = -1;

    void Spawned_References_Options_t::Reset_Option_Ints()
    {
        do_verify_unspawns_option = -1;

        References_Options_t<Base_t, Item_t>::Reset_Option_Ints();
    }

    V::Variable_tt<Bool_t>& Spawned_References_Options_t::Do_Verify_Unspawns() { DEFINE_VAR(Bool_t, "p_options_do_verify_unspawns"); }

    void Spawned_References_Options_t::Reset()
    {
        Do_Verify_Unspawns() = true;

        References_Options_t<Base_t, Item_t>::Reset();
    }

    Bool_t Spawned_References_Options_t::Try_On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == do_verify_unspawns_option) {
            Main_t::Self()->Toggle_And_Update(Do_Verify_Unspawns(), option, lcallback);
            return true;

        } else if (References_Options_t<Base_t, Item_t>::Try_On_Option_Select(option, lcallback)) {
            return true;

        } else {
            return false;

        }
    }

    Bool_t Spawned_References_Options_t::Try_On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        if (option == do_verify_unspawns_option) {
            Main_t::Self()->Highlight(Main_t::HIGHLIGHT_VERIFY_UNSPAWNS, lcallback);
            return true;



        } else if (References_Options_t<Base_t, Item_t>::Try_On_Option_Highlight(option, lcallback)) {
            return true;



        } else {
            return false;

        }
    }

    void Spawned_References_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_SPAWNED_REFERENCES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCES, Main_t::SAFE_COMPONENT_OPTIONS));
        }

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Build_Header_Options();
        Build_General_Options();
        do_verify_unspawns_option = mcm->Add_Toggle_Option(Main_t::VERIFY_UNSPAWNS, Do_Verify_Unspawns());
        Build_Section_Options();

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Variable_tt<Form_ID_t>& Spawned_References_Item_t::Actor_Form_ID() { DEFINE_VAR(Form_ID_t, "p_item_actor_form_id"); }

    Item_t Spawned_References_Item_t::Current_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid() && List()->Items().Has(item())) {
            return item();
        } else {
            return nullptr;
        }
    }

    Bool_t Spawned_References_Item_t::Current_Item(Item_t item)
    {
        if (item && item->Is_Valid()) {
            Actor_Form_ID() = item->form_id;
            return true;
        } else {
            return false;
        }
    }

    Item_t Spawned_References_Item_t::Previous_Item()
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

    Item_t Spawned_References_Item_t::Next_Item()
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

    void Spawned_References_Item_t::Back_To_List(some<Main_t*> mcm, some<Latent_Callback_i*> lcallback)
    {
        SKYLIB_ASSERT_SOME(mcm);
        SKYLIB_ASSERT_SOME(lcallback);

        List()->do_update_items = true;
        Current_View(Bases_View_e::LIST);
        mcm->Reset_Page();
        mcm->Destroy_Latent_Callback(lcallback());
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
                    some<Spawned_References_Item_t*> self;
                    some<Main_t*> mcm;
                    Int_t option;
                    some<Latent_Callback_i*> lcallback;
                    some<Actor_t*> spawn;
                    Verify_Callback_t(some<Spawned_References_Item_t*> self,
                                      some<Main_t*> mcm,
                                      Int_t option,
                                      some<Latent_Callback_i*> lcallback,
                                      some<Actor_t*> spawn) :
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
                            mcm->Destroy_Latent_Callback(lcallback());
                        }
                    }
                };
                mcm->Flicker_Option(option);
                mcm->Show_Message(
                    Main_t::CONFIRM_UNSPAWN,
                    true,
                    Main_t::YES,
                    Main_t::NO,
                    new Verify_Callback_t(this, mcm, option, lcallback, spawn())
                );
            } else {
                mcm->Disable_Option(option);
                Spawned_Actors_t::Self().Remove(spawn());
                Markers_t::Self()->Unmark(spawn());
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
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Actor_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            maybe<size_t> item_index = items.Index_Of(item());
            if (item_index.Has_Value()) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_SPAWNED_REFERENCE, item->Any_Name(), item_index.Value(), items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_SPAWNED_REFERENCE, item->Any_Name(), item_index.Value(), items.size())
                    );
                }

                mcm->Current_Cursor_Position() = 0;
                mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

                Build_Header(unspawn_option, Main_t::CENTER_UNSPAWN, List()->Items().size());
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
                    Buildable_Reference_t<Base_t, Item_t> buildable_reference(this, item(), Main_t::SPAWNED_REFERENCE);
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

    void Spawned_References_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == unspawn_option) {
            Select_Unspawn(mcm, option, lcallback);
            return;

        } else if (option == Mark_On_Map_Option()) {
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

    void Spawned_References_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
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
            References_Item_t<Spawned_References_Base_t, Item_t>::On_Option_Input_Accept(option, value, lcallback);
        }
    }

}}
