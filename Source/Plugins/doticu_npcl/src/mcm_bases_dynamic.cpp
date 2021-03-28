/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/reference.h"

#include "consts.h"
#include "filter.h"
#include "spawned_actors.h"
#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_bases_dynamic.h"
#include "mcm_global_options.h"

namespace doticu_npcl { namespace MCM {

    using Base_t = Dynamic_Bases_Base_t;
    using Item_t = Dynamic_Bases_Base_t::Item_t;

    String_t                        Dynamic_Bases_Base_t::Class_Name()  { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases_dynamic"); }
    V::Class_t*                     Dynamic_Bases_Base_t::Class()       { DEFINE_CLASS(); }
    V::Object_t*                    Dynamic_Bases_Base_t::Object()      { DEFINE_OBJECT_METHOD(); }

    some<Dynamic_Bases_t*>          Dynamic_Bases_Base_t::Self()        { return static_cast<some<Dynamic_Bases_t*>>(Consts_t::NPCL_MCM_Quest()); }
    some<Dynamic_Bases_List_t*>     Dynamic_Bases_Base_t::List()        { return reinterpret_cast<Dynamic_Bases_List_t*>(this); }
    some<Dynamic_Bases_Filter_t*>   Dynamic_Bases_Base_t::Filter()      { return reinterpret_cast<Dynamic_Bases_Filter_t*>(this); }
    some<Dynamic_Bases_Options_t*>  Dynamic_Bases_Base_t::Options()     { return reinterpret_cast<Dynamic_Bases_Options_t*>(this); }
    some<Dynamic_Bases_Item_t*>     Dynamic_Bases_Base_t::Item()        { return reinterpret_cast<Dynamic_Bases_Item_t*>(this); }

}}

namespace doticu_npcl { namespace MCM {



}}

namespace doticu_npcl { namespace MCM {

    Vector_t<Item_t>& Dynamic_Bases_List_t::Items()
    {
        if (!items || do_update_items) {
            do_update_items = false;

            read.reserve(2048);
            read.clear();
            Actor_Base_t::Dynamic_Actor_Bases(read);

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

    Vector_t<Item_t> Dynamic_Bases_List_t::Default_Items()
    {
        return Actor_Base_t::Dynamic_Actor_Bases();
    }

    Item_t Dynamic_Bases_List_t::Null_Item()
    {
        return nullptr;
    }

    void Dynamic_Bases_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        if (!is_refresh) {
            do_update_items = true;
        }

        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Vector_t<Item_t>& actor_bases = Items();
        size_t actor_base_count = actor_bases.size();
        if (actor_base_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index() = page_index;
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index() = page_index;
            }

            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, actor_base_count, page_index, page_count));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, actor_base_count, page_index, page_count));
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
            if (end > actor_base_count) {
                end = actor_base_count;
            }
            for (; begin < end; begin += 1) {
                Item_t actor_base = actor_bases[begin];
                mcm->Add_Text_Option(actor_base->Any_Name(), Main_t::_DOTS_);
            }
        } else {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, 0, 0, 1));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, 0, 0, 1));
            }

            Filter_Option() = mcm->Add_Text_Option(Main_t::CENTER_FILTER, Main_t::_NONE_);
            Options_Option() = mcm->Add_Text_Option(Main_t::CENTER_OPTIONS, Main_t::_NONE_);
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);

            mcm->Add_Header_Option(Main_t::NO_DYNAMIC_BASES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Dynamic_Bases_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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

            Vector_t<Item_t>& actor_bases = Items();
            size_t actor_base_count = actor_bases.size();
            if (actor_base_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
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

            Vector_t<Item_t>& actor_bases = Items();
            size_t actor_base_count = actor_bases.size();
            if (actor_base_count > 0) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
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
                    Item()->Dynamic_Form_ID() = item->form_id;
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    Toggle_Type_e Dynamic_Bases_Filter_t::Toggle_Type()
    {
        return Toggle_Type_e::EITHER;
    }

    void Dynamic_Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

        Build_Filters(Main_t::DYNAMIC_BASE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Dynamic_Bases_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, Main_t::SAFE_COMPONENT_OPTIONS));
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

    V::Variable_tt<Form_ID_t>& Dynamic_Bases_Item_t::Dynamic_Form_ID() { DEFINE_VAR(Form_ID_t, "p_item_dynamic_form_id"); }

    Item_t Dynamic_Bases_Item_t::Current_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item && List()->Items().Has(item())) {
            return item();
        } else {
            return nullptr;
        }
    }

    Bool_t Dynamic_Bases_Item_t::Current_Item(Item_t item)
    {
        if (item && item->Is_Valid()) {
            Dynamic_Form_ID() = item->form_id;
            return true;
        } else {
            return false;
        }
    }

    Item_t Dynamic_Bases_Item_t::Previous_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item) {
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

    Item_t Dynamic_Bases_Item_t::Next_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item) {
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

    void Dynamic_Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        Reset_Option_Ints();

        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            maybe<size_t> item_index = items.Index_Of(item());
            if (item_index.Has_Value()) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_DYNAMIC_BASE, item->Any_Name(), item_index.Value(), items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASE, item->Any_Name(), item_index.Value(), items.size())
                    );
                }

                mcm->Current_Cursor_Position() = 0;
                mcm->Current_Cursor_Mode() = Cursor_e::LEFT_TO_RIGHT;

                Build_Header(spawn_option, Main_t::CENTER_SPAWN, List()->Items().size());
                {
                    Vector_t<Buildable_i*> buildables;
                    buildables.reserve(6);

                    Buildable_Base_t<Base_t, Item_t> buildable_base(this, item(), Main_t::DYNAMIC_BASE);
                    Buildable_Factions_t<Base_t, Item_t> buildable_factions(this, item->Factions_And_Ranks());
                    Buildable_Keywords_t<Base_t, Item_t> buildable_keywords(this, item->Keywords());
                    Buildable_Mods_t<Base_t, Item_t> buildable_mods(this, item->Mods());
                    Buildable_Race_t<Base_t, Item_t> buildable_race(this, item->Race());
                    Buildable_Templates_t<Base_t, Item_t> buildable_templates(this, item->Templates());

                    buildables.push_back(&buildable_base);
                    buildables.push_back(&buildable_factions);
                    buildables.push_back(&buildable_keywords);
                    buildables.push_back(&buildable_mods);
                    buildables.push_back(&buildable_race);
                    buildables.push_back(&buildable_templates);

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

    void Dynamic_Bases_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (Try_On_Option_Select(option, lcallback)) {
            return;

        } else {
            mcm->Destroy_Latent_Callback(lcallback);

        }
    }

}}
