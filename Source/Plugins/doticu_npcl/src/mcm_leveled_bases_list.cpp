/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/virtual_macros.h"

#include "mcm_leveled_bases_list.h"
#include "mcm_leveled_bases_filter.h"
#include "mcm_leveled_bases_options.h"
#include "mcm_leveled_bases_item.h"

namespace doticu_npcl { namespace MCM {

    Bool_t              Leveled_Bases_List_t::do_update_items                   = true;

    V::Int_Variable_t*  Leveled_Bases_List_t::Filter_Option_Variable()          { DEFINE_INT_VARIABLE("p_list_filter_option"); }
    V::Int_Variable_t*  Leveled_Bases_List_t::Options_Option_Variable()         { DEFINE_INT_VARIABLE("p_list_options_option"); }
    V::Int_Variable_t*  Leveled_Bases_List_t::Previous_Page_Option_Variable()   { DEFINE_INT_VARIABLE("p_list_previous_page_option"); }
    V::Int_Variable_t*  Leveled_Bases_List_t::Next_Page_Option_Variable()       { DEFINE_INT_VARIABLE("p_list_next_page_option"); }
    V::Int_Variable_t*  Leveled_Bases_List_t::Page_Index_Variable()             { DEFINE_INT_VARIABLE("p_list_page_index"); }

    Int_t Leveled_Bases_List_t::Page_Index()
    {
        return Page_Index_Variable()->Value();
    }

    void Leveled_Bases_List_t::Page_Index(Int_t value)
    {
        Page_Index_Variable()->Value(value);
    }

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

    Vector_t<Leveled_Actor_Base_t*>& Leveled_Bases_List_t::Items()
    {
        static Vector_t<Leveled_Actor_Base_t*> read;
        static Vector_t<Leveled_Actor_Base_t*> write;
        static Vector_t<Leveled_Actor_Base_t*>* items;

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
                [](Leveled_Actor_Base_t** item_a, Leveled_Actor_Base_t** item_b)->Int_t
                {
                    if (!item_a || !*item_a) {
                        return Comparator_e::IS_UNORDERED;
                    } else if (!item_b || !*item_b) {
                        return Comparator_e::IS_ORDERED;
                    } else {
                        Comparator_e result =
                            Main_t::String_Comparator((*item_a)->Any_Name(),
                                                      (*item_b)->Any_Name());
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

    Leveled_Actor_Base_t* Leveled_Bases_List_t::Option_To_Item(Int_t option)
    {
        Int_t relative_idx = mcmlib::Option_t(option).position - HEADERS_PER_PAGE;
        if (relative_idx > -1 && relative_idx < ITEMS_PER_PAGE) {
            Vector_t<Leveled_Actor_Base_t*>& items = Items();
            Int_t absolute_idx = Page_Index() * ITEMS_PER_PAGE + relative_idx;
            if (absolute_idx > -1 && absolute_idx < items.size()) {
                return items[absolute_idx];
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
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

            Filter_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::FILTER_LABEL, ""));
            Options_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, ""));
            if (page_count > 1) {
                Previous_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, ""));
                Next_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, ""));
            } else {
                Previous_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE));
                Next_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE));
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

            Filter_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::FILTER_LABEL, ""));
            Options_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, ""));
            Previous_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE));
            Next_Page_Option_Variable()->Value(mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE));

            mcm->Add_Header_Option(" No Leveled Bases ");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Leveled_Bases_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Filter_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Current_View(View_e::FILTER);
            mcm->Reset_Page();
        } else if (option == Options_Option_Variable()->Value()) {
            mcm->Disable_Option(option);
            Current_View(View_e::OPTIONS);
            mcm->Reset_Page();

        } else if (option == Previous_Page_Option_Variable()->Value()) {
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
        } else if (option == Next_Page_Option_Variable()->Value()) {
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
                Item()->Leveled_Actor_Base_Form_ID(item->form_id);
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
