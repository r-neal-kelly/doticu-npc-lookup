/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/reference.h"

#include "consts.h"
#include "filter.h"
#include "mcm_bases.h"
#include "mcm_bases.inl"
#include "mcm_bases_leveled.h"

namespace doticu_npcl { namespace MCM {

    using View_e = Bases_View_e;
    using Item_t = Leveled_Bases_Base_t::Item_t;

    String_t                    Leveled_Bases_Base_t::Class_Name()  { DEFINE_CLASS_NAME("doticu_npcl_mcm_bases_leveled"); }
    V::Class_t*                 Leveled_Bases_Base_t::Class()       { DEFINE_CLASS(); }
    V::Object_t*                Leveled_Bases_Base_t::Object()      { DEFINE_OBJECT(); }

    Leveled_Bases_t*            Leveled_Bases_Base_t::Self()        { return static_cast<Leveled_Bases_t*>(Consts_t::NPCL_MCM_Quest()); }
    Leveled_Bases_List_t*       Leveled_Bases_Base_t::List()        { return reinterpret_cast<Leveled_Bases_List_t*>(this); }
    Leveled_Bases_Filter_t*     Leveled_Bases_Base_t::Filter()      { return reinterpret_cast<Leveled_Bases_Filter_t*>(this); }
    Leveled_Bases_Options_t*    Leveled_Bases_Base_t::Options()     { return reinterpret_cast<Leveled_Bases_Options_t*>(this); }
    Leveled_Bases_Item_t*       Leveled_Bases_Base_t::Item()        { return reinterpret_cast<Leveled_Bases_Item_t*>(this); }

}}

namespace doticu_npcl { namespace MCM {

    void Leveled_Bases_t::On_Config_Open()
    {
        List()->do_update_items = true;
    }

    void Leveled_Bases_t::On_Config_Close()
    {
        List()->Clear();
    }

    void Leveled_Bases_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Page_Open(is_refresh, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Page_Open(is_refresh, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Select(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Select(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Menu_Accept(option, idx, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Menu_Accept(option, idx, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Open(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Open(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Slider_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Slider_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Input_Accept(option, value, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Input_Accept(option, value, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Keymap_Change(option, key, conflict, mod, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Default(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Default(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

    void Leveled_Bases_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        View_e current_view = Current_View();
             if (current_view == View_e::LIST)      List()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::FILTER)    Filter()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::OPTIONS)   Options()->On_Option_Highlight(option, lcallback);
        else if (current_view == View_e::ITEM)      Item()->On_Option_Highlight(option, lcallback);
        else                                        SKYLIB_ASSERT(false);
    }

}}

namespace doticu_npcl { namespace MCM {

    Bool_t              Leveled_Bases_List_t::do_update_items    = true;
    Vector_t<Item_t>    Leveled_Bases_List_t::read               = Vector_t<Item_t>();
    Vector_t<Item_t>    Leveled_Bases_List_t::write              = Vector_t<Item_t>();
    Vector_t<Item_t>*   Leveled_Bases_List_t::items              = nullptr;

    String_t Leveled_Bases_List_t::Title(Int_t item_count, Int_t page_index, Int_t page_count)
    {
        std::string items =
            std::string("Leveled Bases: ") +
            std::to_string(item_count);

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return items + "               " + pages;
    }

    Vector_t<Item_t>& Leveled_Bases_List_t::Items()
    {
        if (!items || do_update_items) {
            do_update_items = false;

            size_t item_reserve = Leveled_Actor_Base_t::Leveled_Actor_Base_Count();

            read.reserve(item_reserve);
            read.clear();
            Leveled_Actor_Base_t::Leveled_Actor_Bases(read);

            write.reserve(item_reserve);
            write.clear();

            items = Filter()->Execute(&read, &write);

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

    Vector_t<Item_t> Leveled_Bases_List_t::Default_Items()
    {
        return Leveled_Actor_Base_t::Leveled_Actor_Bases();
    }

    Item_t Leveled_Bases_List_t::Option_To_Item(Int_t option)
    {
        Int_t relative_idx = mcmlib::Option_t(option).position - HEADERS_PER_PAGE;
        if (relative_idx > -1 && relative_idx < ITEMS_PER_PAGE) {
            Vector_t<Item_t>& actor_bases = Items();
            Int_t absolute_idx = Page_Index() * ITEMS_PER_PAGE + relative_idx;
            if (absolute_idx > -1 && absolute_idx < actor_bases.size()) {
                return actor_bases[absolute_idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void Leveled_Bases_List_t::Clear()
    {
        do_update_items = true;
        read.clear();
        write.clear();
    }

    void Leveled_Bases_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (!is_refresh) {
            do_update_items = true;
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Vector_t<Leveled_Actor_Base_t*>& items = Items();
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

            mcm->Title_Text(Title(item_count, page_index, page_count));

            Filter_Option() = mcm->Add_Text_Option(Main_t::FILTER_LABEL, "");
            Options_Option() = mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, "");
            if (page_count > 1) {
                Previous_Page_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "");
                Next_Page_Option() = mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "");
            } else {
                Previous_Page_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE);
                Next_Page_Option() = mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE);
            }

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            Int_t begin = ITEMS_PER_PAGE * page_index;
            Int_t end = begin + ITEMS_PER_PAGE;
            if (end > item_count) {
                end = item_count;
            }
            for (; begin < end; begin += 1) {
                Leveled_Actor_Base_t* item = items[begin];
                mcm->Add_Text_Option(item->Any_Name(), "...");
            }
        } else {
            mcm->Title_Text(Title(0, 0, 1));

            Filter_Option() = mcm->Add_Text_Option(Main_t::FILTER_LABEL, "");
            Options_Option() = mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, "");
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE);

            mcm->Add_Header_Option(" No Leveled Bases ");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Filter_Option()) {
            mcm->Disable_Option(option);
            Current_View(View_e::FILTER);
            mcm->Reset_Page();
        } else if (option == Options_Option()) {
            mcm->Disable_Option(option);
            Current_View(View_e::OPTIONS);
            mcm->Reset_Page();

        } else if (option == Previous_Page_Option()) {
            mcm->Disable_Option(option);

            Vector_t<Leveled_Actor_Base_t*>& items = Items();
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

            Vector_t<Leveled_Actor_Base_t*>& items = Items();
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
            Leveled_Actor_Base_t* item = Option_To_Item(option);
            if (item) {
                mcm->Disable_Option(option);
                Item()->Leveled_Form_ID(item->form_id);
                Current_View(View_e::ITEM);
                mcm->Reset_Page();
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    Vector_t<Item_t>* Leveled_Bases_Filter_t::Execute(Vector_t<Item_t>* read, Vector_t<Item_t>* write)
    {
        Actor_Base_t* relatable_base = Consts_t::Skyrim_Player_Actor_Base();
        Relation_e relation_argument = Relation_e::From_String(Relation_Argument());

        Filter_State_t<Item_t> filter_state(read, write);

        Mod_Filter_t<Item_t>(filter_state, Mod_Argument(), Mod_Do_Negate());
        Race_Filter_t<Item_t>(filter_state, Race_Argument(), Race_Do_Negate());
        Base_Filter_t<Item_t>(filter_state, Base_Argument(), Base_Do_Negate());
        Relation_Filter_t<Item_t>(filter_state, relatable_base, relation_argument, Relation_Do_Negate());
        Male_Female_Filter_t<Item_t>(filter_state, Male_Female_Argument());
        Unique_Generic_Filter_t<Item_t>(filter_state, Unique_Generic_Argument());

        return filter_state.Results();
    }

    void Leveled_Bases_Filter_t::Clear()
    {
        Mod_Argument("");
        Mod_Do_Negate(false);

        Race_Argument("");
        Race_Do_Negate(false);

        Base_Argument("");
        Base_Do_Negate(false);

        Relation_Argument("");
        Relation_Do_Negate(false);

        Male_Female_Argument(Binary_e::NONE);
        Unique_Generic_Argument(Binary_e::NONE);
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Mods()
    {
        return Mod_Selectables_t<Leveled_Bases_Base_t, Item_t>().Results();
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Races()
    {
        return Race_Selectables_t<Leveled_Bases_Base_t, Item_t>().Results();
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Bases()
    {
        return Base_Selectables_t<Leveled_Bases_Base_t, Item_t>().Results();
    }

    Vector_t<String_t> Leveled_Bases_Filter_t::Selectable_Relations()
    {
        return Relation_Selectables_t<Leveled_Bases_Base_t, Item_t>(Consts_t::Skyrim_Player_Actor_Base()).Results();
    }

    void Leveled_Bases_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Leveled Bases: Filter ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::BACK_LABEL, "");
        Clear_Option() = mcm->Add_Text_Option(Main_t::CLEAR_LABEL, "");

        mcm->Add_Header_Option(" Mod ");
        mcm->Add_Header_Option("");
        Mod_Search_Option() = mcm->Add_Input_Option(" Search ", Mod_Argument());
        Mod_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Mod_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Mod_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Race ");
        mcm->Add_Header_Option("");
        Race_Search_Option() = mcm->Add_Input_Option(" Search ", Race_Argument());
        Race_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Race_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Race_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Base ");
        mcm->Add_Header_Option("");
        Base_Search_Option() = mcm->Add_Input_Option(" Search ", Base_Argument());
        Base_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Base_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Base_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Relation ");
        mcm->Add_Header_Option("");
        Relation_Select_Option() = mcm->Add_Menu_Option(" Select ", Relation_Argument());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Relation_Do_Negate());

        mcm->Add_Header_Option(" Other ");
        mcm->Add_Header_Option("");

        Binary_e male_female_argument = Male_Female_Argument();
        Male_Option() = mcm->Add_Toggle_Option(
            " Has Male ",
            male_female_argument == Binary_e::A ||
            male_female_argument == Binary_e::ALL
        );
        Female_Option() = mcm->Add_Toggle_Option(
            " Has Female ",
            male_female_argument == Binary_e::B ||
            male_female_argument == Binary_e::ALL
        );

        Binary_e unique_generic_argument = Unique_Generic_Argument();
        Unique_Option() = mcm->Add_Toggle_Option(
            " Has Unique ",
            unique_generic_argument == Binary_e::A ||
            unique_generic_argument == Binary_e::ALL
        );
        Generic_Option() = mcm->Add_Toggle_Option(
            " Has Generic ",
            unique_generic_argument == Binary_e::B ||
            unique_generic_argument == Binary_e::ALL
        );

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(View_e::LIST);
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
        } else if (option == Relation_Negate_Option()) {
            Bool_t value = Relation_Do_Negate();
            Relation_Do_Negate(!value);
            mcm->Toggle_Option_Value(option, !value);

        } else if (option == Male_Option()) {
            mcm->Toggle_Any(Male_Female_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Female_Option()) {
            mcm->Toggle_Any(Male_Female_Argument_Variable(), option - 1, option, Binary_e::B);

        } else if (option == Unique_Option()) {
            mcm->Toggle_Any(Unique_Generic_Argument_Variable(), option, option + 1, Binary_e::A);
        } else if (option == Generic_Option()) {
            mcm->Toggle_Any(Unique_Generic_Argument_Variable(), option - 1, option, Binary_e::B);

        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
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
        } else if (option == Relation_Select_Option()) {
            mcm->Flicker_Option(option);
            mcm->Menu_Dialog_Values(Selectable_Relations());
            mcm->Menu_Dialog_Default(0);
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Mod_Select_Option()) {
            if (idx > -1) {
                String_t value = "";
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
                String_t value = "";
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
                String_t value = "";
                if (idx > 0) {
                    Vector_t<String_t> bases = Selectable_Bases();
                    if (idx < bases.size()) {
                        value = bases[idx];
                    }
                }
                Base_Argument(value);
                mcm->Input_Option_Value(Base_Search_Option(), value, true);
            }
        } else if (option == Relation_Select_Option()) {
            if (idx > -1) {
                String_t value = " Any ";
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

    void Leveled_Bases_Filter_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
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
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Filter_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Leveled_Bases_Options_t::Reset()
    {
        Do_Smart_Select(true);
    }

    void Leveled_Bases_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(" Leveled Bases: Options ");

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::BACK_LABEL, "");
        Reset_Option() = mcm->Add_Text_Option(Main_t::RESET_LABEL, "");

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");
        Smart_Select_Option() = mcm->Add_Toggle_Option(" Smart Select ", Do_Smart_Select());
        Uncombative_Spawns_Option() = mcm->Add_Toggle_Option(" Uncombative Spawns ", Do_Uncombative_Spawns());
        Persistent_Spawns_Option() = mcm->Add_Toggle_Option(" Persistent Spawns ", Do_Persistent_Spawns());

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(View_e::LIST);
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
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Options_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  Leveled_Bases_Item_t::Leveled_Form_ID_Variable()        { DEFINE_INT("p_item_leveled_form_id"); }

    Form_ID_t           Leveled_Bases_Item_t::Leveled_Form_ID()                 { return Leveled_Form_ID_Variable()->Value(); }
    void                Leveled_Bases_Item_t::Leveled_Form_ID(Form_ID_t value)  { Leveled_Form_ID_Variable()->Value(value); }

    Item_t Leveled_Bases_Item_t::Current_Item()
    {
        Item_t item = static_cast<Item_t>(Game_t::Form(Leveled_Form_ID()));
        if (item && List()->Items().Has(item)) {
            return item;
        } else {
            return nullptr;
        }
    }

    Item_t Leveled_Bases_Item_t::Previous_Item()
    {
        Item_t item = static_cast<Item_t>(Game_t::Form(Leveled_Form_ID()));
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

    Item_t Leveled_Bases_Item_t::Next_Item()
    {
        Item_t item = static_cast<Item_t>(Game_t::Form(Leveled_Form_ID()));
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

    void Leveled_Bases_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Leveled_Actor_Base_t* item = Current_Item();
        if (item) {
            mcm->Title_Text(std::string(" Leveled Base: ") + item->Any_Name().data);

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Back_Option() = mcm->Add_Text_Option(Main_t::BACK_LABEL, "");
            Spawn_Option() = mcm->Add_Text_Option(Main_t::SPAWN_LABEL, "");
            if (List()->Items().size() > 1) {
                Previous_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "");
                Next_Option() = mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "");
            } else {
                Previous_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "", Flag_e::DISABLE);
                Next_Option() = mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "", Flag_e::DISABLE);
            }

            mcm->Add_Header_Option(" Leveled Base ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + item->Leveled_Name().data, "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + item->Form_ID_String().data, "");

            auto Is_Odd_Option = [&mcm]()->Bool_t
            {
                return skylib::Is_Odd(mcm->Cursor_Position());
            };

            Vector_t<String_t> mod_names = item->Mod_Names();
            size_t mod_name_count = mod_names.size();
            if (mod_name_count > 0 && mcm->Can_Add_Options(2 + mod_name_count)) {
                mcm->Add_Header_Option(" Mods ");
                mcm->Add_Header_Option("");
                for (Index_t idx = 0, end = mod_name_count; idx < end; idx += 1) {
                    String_t mod_name = mod_names[idx];
                    mcm->Add_Text_Option(mod_name, "");
                }
                if (Is_Odd_Option()) {
                    mcm->Add_Empty_Option();
                }
            }
        } else {
            List()->do_update_items = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Spawn_Option()) {
            mcm->Flicker_Option(option);
            Leveled_Actor_Base_t* item = Current_Item();
            if (item && item->Is_Valid()) {
                Bool_t do_persist = Options()->Do_Persistent_Spawns();
                Actor_t* actor = static_cast<Actor_t*>
                    (skylib::Reference_t::Create(item, 1, Consts_t::Skyrim_Player_Actor(), do_persist, false));
                if (actor) {
                    if (Options()->Do_Uncombative_Spawns()) {
                        actor->Set_Actor_Value(Actor_Value_e::AGGRESSION, 0.0f);
                    }
                }
            }
        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            Leveled_Actor_Base_t* item = Previous_Item();
            if (item) {
                Leveled_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            Leveled_Actor_Base_t* item = Next_Item();
            if (item) {
                Leveled_Form_ID(item->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(View_e::LIST);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Slider_Open(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Default(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t::Self()->Destroy_Latent_Callback(lcallback);
    }

}}
