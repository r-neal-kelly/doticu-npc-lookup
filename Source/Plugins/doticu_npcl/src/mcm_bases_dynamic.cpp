/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/reference.h"

#include "consts.h"
#include "filter.h"
#include "spawned_actors.h"
#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_bases_dynamic.h"
#include "mcm_global_options.h"

namespace doticu_npcl { namespace MCM {

    using Item_t = Dynamic_Bases_Base_t::Item_t;

    String_t                    Dynamic_Bases_Base_t::Class_Name()          { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases_dynamic"); }
    V::Class_t*                 Dynamic_Bases_Base_t::Class()               { DEFINE_CLASS(); }
    V::Object_t*                Dynamic_Bases_Base_t::Object()              { DEFINE_OBJECT(); }

    Dynamic_Bases_t*            Dynamic_Bases_Base_t::Self()                { return static_cast<Dynamic_Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    Dynamic_Bases_List_t*       Dynamic_Bases_Base_t::List()                { return reinterpret_cast<Dynamic_Bases_List_t*>(this); }
    Dynamic_Bases_Filter_t*     Dynamic_Bases_Base_t::Filter()              { return reinterpret_cast<Dynamic_Bases_Filter_t*>(this); }
    Dynamic_Bases_Options_t*    Dynamic_Bases_Base_t::Options()             { return reinterpret_cast<Dynamic_Bases_Options_t*>(this); }
    Dynamic_Bases_Item_t*       Dynamic_Bases_Base_t::Item()                { return reinterpret_cast<Dynamic_Bases_Item_t*>(this); }

    Toggle_Type_e               Dynamic_Bases_Base_t::Toggle_Type()         { return Toggle_Type_e::EITHER; }

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

        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Vector_t<Item_t>& actor_bases = Items();
        size_t actor_base_count = actor_bases.size();
        if (actor_base_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(actor_base_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index(page_index);
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index(page_index);
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
                Page_Index(page_index);
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
                    Item()->Dynamic_Form_ID(item->form_id);
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Dynamic_Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Build_Filters(Main_t::DYNAMIC_BASE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Dynamic_Bases_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_DYNAMIC_BASES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASES, Main_t::SAFE_COMPONENT_OPTIONS));
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Reset_Option() = mcm->Add_Text_Option(Main_t::CENTER_RESET, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::_NONE_);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Smart_Select_Option() = mcm->Add_Toggle_Option(Main_t::SMART_SELECT, Do_Smart_Select());
        Uncombative_Spawns_Option() = mcm->Add_Toggle_Option(Main_t::UNCOMBATIVE_SPAWNS, Do_Uncombative_Spawns());
        Persistent_Spawns_Option() = mcm->Add_Toggle_Option(Main_t::PERSISTENT_SPAWNS, Do_Persistent_Spawns());
        Static_Spawns_Option() = mcm->Add_Toggle_Option(Main_t::STATIC_SPAWNS, Do_Static_Spawns());

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Dynamic_Bases_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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
        } else if (option == Uncombative_Spawns_Option()) {
            Bool_t value = Do_Uncombative_Spawns();
            Do_Uncombative_Spawns(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Persistent_Spawns_Option()) {
            Bool_t value = Do_Persistent_Spawns();
            Do_Persistent_Spawns(!value);
            mcm->Toggle_Option_Value(option, !value);
        } else if (option == Static_Spawns_Option()) {
            Bool_t value = Do_Static_Spawns();
            Do_Static_Spawns(!value);
            mcm->Toggle_Option_Value(option, !value);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  Dynamic_Bases_Item_t::Dynamic_Form_ID_Variable()        { DEFINE_INT_VARIABLE("p_item_dynamic_form_id"); }

    Form_ID_t           Dynamic_Bases_Item_t::Dynamic_Form_ID()                 { return Dynamic_Form_ID_Variable()->Value(); }
    void                Dynamic_Bases_Item_t::Dynamic_Form_ID(Form_ID_t value)  { Dynamic_Form_ID_Variable()->Value(value); }

    Item_t Dynamic_Bases_Item_t::Current_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item && List()->Items().Has(item)) {
            return item;
        } else {
            return nullptr;
        }
    }

    Bool_t Dynamic_Bases_Item_t::Current_Item(Item_t item)
    {
        if (item && item->Is_Valid()) {
            Dynamic_Form_ID(item->form_id);
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

    Item_t Dynamic_Bases_Item_t::Next_Item()
    {
        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item) {
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

    void Dynamic_Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        maybe<Item_t> item = static_cast<maybe<Item_t>>(Game_t::Form(Dynamic_Form_ID()));
        if (item && item->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t item_index = items.Index_Of(item);
            if (item_index > -1) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_DYNAMIC_BASE, item->Any_Name(), item_index, items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_DYNAMIC_BASE, item->Any_Name(), item_index, items.size())
                    );
                }

                mcm->Cursor_Position(0);
                mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

                Build_Header(Main_t::CENTER_SPAWN, List()->Items().size());
                Build_Base(item, Main_t::DYNAMIC_BASE);
                Build_Race(item->Race());
                Build_Templates(item->Templates());
                Build_Factions_And_Ranks(item->Factions_And_Ranks());
                Build_Keywords(item->Keywords());
                Build_Mod_Names(item->Mod_Names());
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
        Main_t* mcm = Main_t::Self();

        if (option == Primary_Option()) {
            mcm->Flicker_Option(option);
            Spawn(Item()->Current_Item());
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (Try_On_Option_Select(option, lcallback)) {
            return;

        } else {
            mcm->Destroy_Latent_Callback(lcallback);

        }
    }

    void Dynamic_Bases_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t item = Current_Item();
        if (item && item->Is_Valid()) {
            if (option == Primary_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_SPAWN);

            } else if (option == Race_Name_Option()) {
                Race_t* race = item->Race();
                if (race) {
                    const char* name = race->Name();
                    const char* editor_id = race->Get_Editor_ID();
                    const char* form_id = race->Form_ID_String().data;
                    mcm->Info_Text(mcm->Pretty_ID(name, editor_id, form_id));
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}
