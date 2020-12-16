/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/interface.h"

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
#include "mcm_bases_leveled.h"

namespace doticu_npcl { namespace MCM {

    using Item_t = Leveled_Bases_Base_t::Item_t;

    String_t                    Leveled_Bases_Base_t::Class_Name()          { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases_leveled"); }
    V::Class_t*                 Leveled_Bases_Base_t::Class()               { DEFINE_CLASS(); }
    V::Object_t*                Leveled_Bases_Base_t::Object()              { DEFINE_OBJECT(); }

    Leveled_Bases_t*            Leveled_Bases_Base_t::Self()                { return static_cast<Leveled_Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    Leveled_Bases_List_t*       Leveled_Bases_Base_t::List()                { return reinterpret_cast<Leveled_Bases_List_t*>(this); }
    Leveled_Bases_Filter_t*     Leveled_Bases_Base_t::Filter()              { return reinterpret_cast<Leveled_Bases_Filter_t*>(this); }
    Leveled_Bases_Options_t*    Leveled_Bases_Base_t::Options()             { return reinterpret_cast<Leveled_Bases_Options_t*>(this); }
    Leveled_Bases_Item_t*       Leveled_Bases_Base_t::Item()                { return reinterpret_cast<Leveled_Bases_Item_t*>(this); }

    Toggle_Type_e               Leveled_Bases_Base_t::Toggle_Type()         { return Toggle_Type_e::ANY; }

}}

namespace doticu_npcl { namespace MCM {

    void Leveled_Bases_t::On_Load()
    {
        Bases_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>::On_Load();

        List()->On_Load();
    }

    void Leveled_Bases_t::On_Save()
    {
        Bases_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>::On_Save();

        List()->On_Save();
    }

    void Leveled_Bases_t::On_Config_Open()
    {
        Bases_t<Leveled_Bases_Base_t, Leveled_Bases_Base_t::Item_t>::On_Config_Open();

        List()->On_Config_Open();
    }

}}

namespace doticu_npcl { namespace MCM {

    Vector_t<Cached_Leveled_t>  Leveled_Bases_List_t::cached_leveleds = Vector_t<Cached_Leveled_t>();
    std::mutex                  Leveled_Bases_List_t::cached_leveleds_mutex;

    void Leveled_Bases_List_t::On_Load()
    {
        
    }

    void Leveled_Bases_List_t::On_Save()
    {

    }

    void Leveled_Bases_List_t::On_Config_Open()
    {
        Refresh_Cache();
    }

    void Leveled_Bases_List_t::Refresh_Cache()
    {
        std::lock_guard<std::mutex> guard(cached_leveleds_mutex);

        cached_leveleds.clear();
        cached_leveleds.reserve(Leveled_Actor_Base_t::Leveled_Actor_Base_Count());

        Vector_t<Leveled_Actor_Base_t*> leveled_actor_bases = Leveled_Actor_Base_t::Leveled_Actor_Bases();
        for (Index_t idx = 0, end = leveled_actor_bases.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base = leveled_actor_bases[idx];
            if (leveled_actor_base && leveled_actor_base->Is_Valid()) {
                cached_leveleds.push_back(std::move(Cached_Leveled_t(leveled_actor_base)));
            }
        }
    }

    Vector_t<Item_t>& Leveled_Bases_List_t::Items()
    {
        if (!items || do_update_items) {
            do_update_items = false;

            size_t cached_leveled_count = cached_leveleds.size();

            read.reserve(cached_leveled_count);
            read.clear();

            write.reserve(cached_leveled_count);
            write.clear();

            for (Index_t idx = 0, end = cached_leveled_count; idx < end; idx += 1) {
                read.push_back(&cached_leveleds[idx]);
            }

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
                            (*item_a)->name,
                            (*item_b)->name
                        );
                        if (result == Comparator_e::IS_EQUAL) {
                            return (*item_a)->leveled->form_id - (*item_b)->leveled->form_id;
                        } else {
                            return result;
                        }
                    }
                }
            );
        }

        return *items;
    }

    Vector_t<Item_t> Leveled_Bases_List_t::Default_Items()
    {
        size_t cached_leveled_count = cached_leveleds.size();

        Vector_t<Item_t> items;
        items.reserve(cached_leveled_count);

        for (Index_t idx = 0, end = cached_leveled_count; idx < end; idx += 1) {
            read.push_back(&cached_leveleds[idx]);
        }

        return items;
    }

    Item_t Leveled_Bases_List_t::Null_Item()
    {
        return nullptr;
    }

    void Leveled_Bases_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
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

            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LEVELED_BASES, item_count, page_index, page_count));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LEVELED_BASES, item_count, page_index, page_count));
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
                mcm->Add_Text_Option(item->name, Main_t::_DOTS_);
            }
        } else {
            if (mcm->Should_Translate_Page_Titles()) {
                mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LEVELED_BASES, 0, 0, 1));
            } else {
                mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LEVELED_BASES, 0, 0, 1));
            }

            Filter_Option() = mcm->Add_Text_Option(Main_t::CENTER_FILTER, Main_t::_NONE_);
            Options_Option() = mcm->Add_Text_Option(Main_t::CENTER_OPTIONS, Main_t::_NONE_);
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);

            mcm->Add_Header_Option(Main_t::NO_LEVELED_BASES);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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
                if (item && item->leveled && item->leveled->Is_Valid()) {
                    mcm->Disable_Option(option);
                    Item()->Leveled_Form_ID(item->leveled->form_id);
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Leveled_Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LEVELED_BASES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LEVELED_BASES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Build_Filters(Main_t::LEVELED_BASE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Leveled_Bases_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LEVELED_BASES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LEVELED_BASES, Main_t::SAFE_COMPONENT_OPTIONS));
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

    void Leveled_Bases_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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

    V::Int_Variable_t*  Leveled_Bases_Item_t::Leveled_Form_ID_Variable()        { DEFINE_INT_VARIABLE("p_item_leveled_form_id"); }

    Form_ID_t           Leveled_Bases_Item_t::Leveled_Form_ID()                 { return Leveled_Form_ID_Variable()->Value(); }
    void                Leveled_Bases_Item_t::Leveled_Form_ID(Form_ID_t value)  { Leveled_Form_ID_Variable()->Value(value); }

    Item_t Leveled_Bases_Item_t::Current_Item()
    {
        maybe<Leveled_Actor_Base_t*> leveled =
            static_cast<maybe<Leveled_Actor_Base_t*>>(Game_t::Form(Leveled_Form_ID()));
        if (leveled) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t idx = items.Index_Of(leveled);
            if (idx > -1) {
                return items[idx];
            } else {
                return none<Item_t>();
            }
        } else {
            return none<Item_t>();
        }
    }

    Item_t Leveled_Bases_Item_t::Previous_Item()
    {
        maybe<Leveled_Actor_Base_t*> leveled =
            static_cast<maybe<Leveled_Actor_Base_t*>>(Game_t::Form(Leveled_Form_ID()));
        if (leveled) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t idx = items.Index_Of(leveled);
            if (idx > -1) {
                if (idx == 0) {
                    idx = items.size() - 1;
                } else {
                    idx -= 1;
                }
                return items[idx];
            } else {
                return none<Item_t>();
            }
        } else {
            return none<Item_t>();
        }
    }

    Item_t Leveled_Bases_Item_t::Next_Item()
    {
        maybe<Leveled_Actor_Base_t*> leveled =
            static_cast<maybe<Leveled_Actor_Base_t*>>(Game_t::Form(Leveled_Form_ID()));
        if (leveled) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t idx = items.Index_Of(leveled);
            if (idx > -1) {
                if (idx == items.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return items[idx];
            } else {
                return none<Item_t>();
            }
        } else {
            return none<Item_t>();
        }
    }

    Vector_t<some<Actor_Base_t*>> Leveled_Bases_Item_t::Nested_Items()
    {
        Item_t current_item = Current_Item();
        if (current_item && current_item->leveled && current_item->leveled->Is_Valid()) {
            Vector_t<some<Actor_Base_t*>> nested_items = current_item->Actor_Bases();
            nested_items.Sort(Actor_Base_t::Compare_Names);
            return nested_items;
        } else {
            return Vector_t<some<Actor_Base_t*>>();
        }
    }

    maybe<Actor_Base_t*> Leveled_Bases_Item_t::Current_Nested_Item()
    {
        maybe<Actor_Base_t*> nested_item = static_cast<maybe<Actor_Base_t*>>(Game_t::Form(Nested_Form()));
        if (nested_item && Nested_Items().Has(nested_item)) {
            return nested_item;
        } else {
            return nullptr;
        }
    }

    maybe<Actor_Base_t*> Leveled_Bases_Item_t::Previous_Nested_Item()
    {
        maybe<Actor_Base_t*> nested_item = static_cast<maybe<Actor_Base_t*>>(Game_t::Form(Nested_Form()));
        if (nested_item) {
            Vector_t<some<Actor_Base_t*>> nested_items = Nested_Items();
            Index_t idx = nested_items.Index_Of(nested_item);
            if (idx > -1) {
                if (idx == 0) {
                    idx = nested_items.size() - 1;
                } else {
                    idx -= 1;
                }
                return nested_items[idx]();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    maybe<Actor_Base_t*> Leveled_Bases_Item_t::Next_Nested_Item()
    {
        maybe<Actor_Base_t*> nested_item = static_cast<maybe<Actor_Base_t*>>(Game_t::Form(Nested_Form()));
        if (nested_item) {
            Vector_t<some<Actor_Base_t*>> nested_items = Nested_Items();
            Index_t idx = nested_items.Index_Of(nested_item);
            if (idx > -1) {
                if (idx == nested_items.size() - 1) {
                    idx = 0;
                } else {
                    idx += 1;
                }
                return nested_items[idx]();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Leveled_Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Bases_Item_View_e info_view = Nested_View();
             if (info_view == Bases_Item_View_e::ITEM)          On_Page_Open_Item(is_refresh, lcallback);
        else if (info_view == Bases_Item_View_e::BASES)         On_Page_Open_Bases(is_refresh, lcallback);
        else if (info_view == Bases_Item_View_e::BASES_ITEM)    On_Page_Open_Bases_Item(is_refresh, lcallback);
        else                                                    On_Page_Open_Item(is_refresh, lcallback);
    }

    void Leveled_Bases_Item_t::On_Page_Open_Item(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        maybe<Leveled_Actor_Base_t*> leveled = static_cast<maybe<Leveled_Actor_Base_t*>>(Game_t::Form(Leveled_Form_ID()));
        if (leveled && leveled->Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t item_index = items.Index_Of(leveled);
            Item_t item = items[item_index];
            if (item_index > -1) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_LEVELED_BASE, item->name, item_index, items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_LEVELED_BASE, item->name, item_index, items.size())
                    );
                }

                mcm->Cursor_Position(0);
                mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

                Build_Header(Main_t::CENTER_SPAWN, List()->Items().size());
                Build_Leveled_Base(item->leveled);
                Build_Mod_Names(item->leveled->Mod_Names());
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

    void Leveled_Bases_Item_t::On_Page_Open_Bases(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t item = Current_Item();
        if (item && item->leveled && item->leveled->Is_Valid()) {
            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Vector_t<some<Actor_Base_t*>> items = Nested_Items();
            size_t item_count = items.size();
            if (item_count) {
                Int_t page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                ));

                Int_t page_index = Nested_Index();
                if (page_index < 0) {
                    page_index = 0;
                    Nested_Index(page_index);
                } else if (page_index >= page_count) {
                    page_index = page_count - 1;
                    Nested_Index(page_index);
                }

                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_INTERNAL_BASES, item_count, page_index, page_count));
                } else {
                    mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_INTERNAL_BASES, item_count, page_index, page_count));
                }

                Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
                Primary_Option() = mcm->Add_Text_Option(Main_t::_NONE_, Main_t::_NONE_);
                if (page_count > 1) {
                    Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_);
                    Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_);
                } else {
                    Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
                    Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
                }

                mcm->Add_Header_Option(Main_t::_NONE_);
                mcm->Add_Header_Option(Main_t::_NONE_);

                Int_t begin = ITEMS_PER_PAGE * page_index;
                Int_t end = begin + ITEMS_PER_PAGE;
                if (end > item_count) {
                    end = item_count;
                }
                for (; begin < end; begin += 1) {
                    Actor_Base_t* item = items[begin];
                    mcm->Add_Text_Option(item->Any_Name(), Main_t::_DOTS_);
                }
            } else {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_INTERNAL_BASES, 0, 0, 1));
                } else {
                    mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_INTERNAL_BASES, 0, 0, 1));
                }

                Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
                Primary_Option() = mcm->Add_Text_Option(Main_t::_NONE_, Main_t::_NONE_);
                Previous_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_PREVIOUS_PAGE, Main_t::_NONE_, Flag_e::DISABLE);
                Next_Option() = mcm->Add_Text_Option(Main_t::CENTER_GO_TO_NEXT_PAGE, Main_t::_NONE_, Flag_e::DISABLE);

                mcm->Add_Header_Option(Main_t::NO_INTERNAL_BASES);
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Page_Open_Bases_Item(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t current_item = Current_Item();
        if (current_item && current_item->leveled && current_item->leveled->Is_Valid()) {
            maybe<Actor_Base_t*> nested_item = static_cast<maybe<Actor_Base_t*>>(Game_t::Form(Nested_Form()));
            if (nested_item && nested_item->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>> nested_items = Nested_Items();
                Index_t nested_index = nested_items.Index_Of(nested_item);
                if (nested_index > -1) {
                    if (mcm->Should_Translate_Page_Titles()) {
                        mcm->Translated_Title_Text(
                            mcm->Singular_Title(Main_t::COMPONENT_INTERNAL_BASE, nested_item->Any_Name(), nested_index, nested_items.size())
                        );
                    } else {
                        mcm->Title_Text(
                            mcm->Singular_Title(Main_t::SAFE_COMPONENT_INTERNAL_BASE, nested_item->Any_Name(), nested_index, nested_items.size())
                        );
                    }

                    mcm->Cursor_Position(0);
                    mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

                    Build_Header(Main_t::CENTER_SPAWN, nested_items.size());
                    Build_Base(nested_item, Main_t::INTERNAL_BASE);
                    Build_Race(nested_item->Race());
                    Build_Templates(nested_item->Templates());
                    Build_Factions_And_Ranks(nested_item->Factions_And_Ranks());
                    Build_Keywords(nested_item->Keywords());
                    Build_Mod_Names(nested_item->Mod_Names());
                } else {
                    Nested_View(Bases_Item_View_e::BASES);
                    Nested_Form(0);
                    mcm->Reset_Page();
                }
            } else {
                Nested_View(Bases_Item_View_e::BASES);
                Nested_Form(0);
                mcm->Reset_Page();
            }
        } else {
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            Nested_View(Bases_Item_View_e::ITEM);
            Nested_Index(0);
            Nested_Form(0);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_Item_View_e info_view = Nested_View();
             if (info_view == Bases_Item_View_e::ITEM)          On_Option_Select_Item(option, lcallback);
        else if (info_view == Bases_Item_View_e::BASES)         On_Option_Select_Bases(option, lcallback);
        else if (info_view == Bases_Item_View_e::BASES_ITEM)    On_Option_Select_Bases_Item(option, lcallback);
        else                                                    On_Option_Select_Item(option, lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Primary_Option()) {
            mcm->Flicker_Option(option);
            Spawn(Current_Item()->leveled);
        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            Item_t item = Previous_Item();
            if (item) {
                Leveled_Form_ID(item->leveled->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            Item_t item = Next_Item();
            if (item) {
                Leveled_Form_ID(item->leveled->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();

        } else if (option == View_Bases_Option()) {
            mcm->Disable_Option(option);
            Nested_View(Bases_Item_View_e::BASES);
            Nested_Index(0);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select_Bases(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            Nested_View(Bases_Item_View_e::ITEM);
            Nested_Index(0);
            mcm->Reset_Page();

        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);

            Item_t item = Current_Item();
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>> items = Nested_Items();
                size_t item_count = items.size();
                if (item_count > 0) {
                    Int_t page_count = static_cast<Int_t>(ceilf(
                        static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                    ));

                    Int_t page_index = Nested_Index();
                    if (page_index == 0) {
                        page_index = page_count - 1;
                    } else {
                        page_index -= 1;
                    }
                    Nested_Index(page_index);
                }
            }

            mcm->Reset_Page();
        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);

            Item_t item = Current_Item();
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>> items = Nested_Items();
                size_t item_count = items.size();
                if (item_count > 0) {
                    Int_t page_count = static_cast<Int_t>(ceilf(
                        static_cast<Float_t>(item_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
                    ));

                    Int_t page_index = Nested_Index();
                    if (page_index == page_count - 1) {
                        page_index = 0;
                    } else {
                        page_index += 1;
                    }
                    Nested_Index(page_index);
                }
            }

            mcm->Reset_Page();

        } else {
            Item_t item = Current_Item();
            if (item && item->leveled->Is_Valid()) {
                Vector_t<some<Actor_Base_t*>> items = Nested_Items();
                Index_t item_index = mcm->Option_To_Item_Index(
                    option, items.size(), Nested_Index(), HEADERS_PER_PAGE, ITEMS_PER_PAGE
                );
                if (item_index > -1) {
                    Actor_Base_t* item = items[item_index];
                    if (item && item->Is_Valid()) {
                        mcm->Disable_Option(option);
                        Item()->Nested_Form(item->form_id);
                        Nested_View(Bases_Item_View_e::BASES_ITEM);
                        mcm->Reset_Page();
                    }
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select_Bases_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            Nested_View(Bases_Item_View_e::BASES);
            Nested_Form(0);
            mcm->Reset_Page();

        } else if (option == Primary_Option()) {
            mcm->Flicker_Option(option);
            Spawn(Current_Nested_Item());

        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            Actor_Base_t* nested_item = Previous_Nested_Item();
            if (nested_item) {
                Nested_Form(nested_item->form_id);
            } else {
                Nested_View(Bases_Item_View_e::BASES);
                Nested_Form(0);
            }
            mcm->Reset_Page();

        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            Actor_Base_t* nested_item = Next_Nested_Item();
            if (nested_item) {
                Nested_Form(nested_item->form_id);
            } else {
                Nested_View(Bases_Item_View_e::BASES);
                Nested_Form(0);
            }
            mcm->Reset_Page();

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Bases_Item_View_e info_view = Nested_View();
             if (info_view == Bases_Item_View_e::ITEM)          On_Option_Highlight_Item(option, lcallback);
        else if (info_view == Bases_Item_View_e::BASES)         On_Option_Highlight_Bases(option, lcallback);
        else if (info_view == Bases_Item_View_e::BASES_ITEM)    On_Option_Highlight_Bases_Item(option, lcallback);
        else                                                    On_Option_Highlight_Item(option, lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t item = Current_Item();
        if (item) {
            if (option == Primary_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_SPAWN_LEVELED);

            } else if (option == View_Bases_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_VIEW_INTERNAL_BASES);
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight_Bases(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight_Bases_Item(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        maybe<Actor_Base_t*> item = Current_Nested_Item();
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
