/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"

#include "consts.h"
#include "filter.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_loaded.h"

namespace doticu_npcl { namespace MCM {

    using Item_t = Loaded_References_Base_t::Item_t;

    String_t                        Loaded_References_Base_t::Class_Name()          { DEFINE_CLASS_NAME("doticu_npcl_mcm_references_loaded"); }
    V::Class_t*                     Loaded_References_Base_t::Class()               { DEFINE_CLASS(); }
    V::Object_t*                    Loaded_References_Base_t::Object()              { DEFINE_OBJECT(); }

    Loaded_References_t*            Loaded_References_Base_t::Self()                { return static_cast<Loaded_References_t*>(Consts_t::NPCL_MCM_Quest()); }
    Loaded_References_List_t*       Loaded_References_Base_t::List()                { return reinterpret_cast<Loaded_References_List_t*>(this); }
    Loaded_References_Filter_t*     Loaded_References_Base_t::Filter()              { return reinterpret_cast<Loaded_References_Filter_t*>(this); }
    Loaded_References_Options_t*    Loaded_References_Base_t::Options()             { return reinterpret_cast<Loaded_References_Options_t*>(this); }
    Loaded_References_Item_t*       Loaded_References_Base_t::Item()                { return reinterpret_cast<Loaded_References_Item_t*>(this); }

    const char*                     Loaded_References_Base_t::Item_Type_Singular()  { return "Loaded Reference"; }
    const char*                     Loaded_References_Base_t::Item_Type_Plural()    { return "Loaded References"; }

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
            Actor_t::Loaded_Actors(read);

            write.reserve(2048);
            write.clear();

            items = Filter()->Execute(&read, &write).Results();

            items->Sort(
                [](Item_t* item_a, Item_t* item_b)->Int_t
                {
                    if (!item_a || !item_a->Is_Valid()) {
                        return Comparator_e::IS_UNORDERED;
                    } else if (!item_b || !item_b->Is_Valid()) {
                        return Comparator_e::IS_ORDERED;
                    } else {
                        Comparator_e result = Main_t::String_Comparator(
                            item_a->actor->Any_Name(),
                            item_b->actor->Any_Name()
                        );
                        if (result == Comparator_e::IS_EQUAL) {
                            return item_a->actor->form_id - item_b->actor->form_id;
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
        return Actor_t::Loaded_Actors();
    }

    Item_t Loaded_References_List_t::Null_Item()
    {
        return Item_t();
    }

    void Loaded_References_List_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (!is_refresh) {
            do_update_items = true;
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Vector_t<Loaded_Actor_t>& loaded_actors = Items();
        size_t loaded_actor_count = loaded_actors.size();
        if (loaded_actor_count) {
            Int_t page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(loaded_actor_count) / static_cast<Float_t>(ITEMS_PER_PAGE)
            ));

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = 0;
                Page_Index(page_index);
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
                Page_Index(page_index);
            }

            mcm->Title_Text(Title(loaded_actor_count, page_index, page_count));

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
            if (end > loaded_actor_count) {
                end = loaded_actor_count;
            }
            for (; begin < end; begin += 1) {
                Loaded_Actor_t loaded_actor = loaded_actors[begin];
                mcm->Add_Text_Option(loaded_actor.actor->Any_Name(), "...");
            }
        } else {
            mcm->Title_Text(Title(0, 0, 1));

            Filter_Option() = mcm->Add_Text_Option(Main_t::FILTER_LABEL, "");
            Options_Option() = mcm->Add_Text_Option(Main_t::OPTIONS_LABEL, "");
            Previous_Page_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_PAGE_LABEL, "", Flag_e::DISABLE);
            Next_Page_Option() = mcm->Add_Text_Option(Main_t::NEXT_PAGE_LABEL, "", Flag_e::DISABLE);

            mcm->Add_Header_Option(std::string(" No ") + Item_Type_Plural() + " ");
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Loaded_References_List_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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

            Vector_t<Loaded_Actor_t>& loaded_actors = Items();
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
                Page_Index(page_index);
            }

            mcm->Reset_Page();
        } else if (option == Next_Page_Option()) {
            mcm->Disable_Option(option);

            Vector_t<Loaded_Actor_t>& loaded_actors = Items();
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
                Page_Index(page_index);
            }

            mcm->Reset_Page();

        } else {
            Loaded_Actor_t loaded_actor = Option_To_Item(option);
            if (loaded_actor.Is_Valid()) {
                mcm->Disable_Option(option);
                Item()->Actor_Form_ID(loaded_actor.actor->form_id);
                Item()->Cell_Form_ID(loaded_actor.cell->form_id);
                Current_View(Bases_View_e::ITEM);
                mcm->Reset_Page();
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Loaded_References_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(Title());

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

        mcm->Add_Header_Option(std::string(" ") + Item_Type_Singular() + " ");
        mcm->Add_Header_Option("");
        Reference_Search_Option() = mcm->Add_Input_Option(" Search ", Reference_Argument());
        Reference_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Reference_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Reference_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Template ");
        mcm->Add_Header_Option("");
        Template_Search_Option() = mcm->Add_Input_Option(" Search ", Template_Argument());
        Template_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Template_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Template_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Location ");
        mcm->Add_Header_Option("");
        Location_Search_Option() = mcm->Add_Input_Option(" Search ", Location_Argument());
        Location_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Location_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Location_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Cell ");
        mcm->Add_Header_Option("");
        Cell_Search_Option() = mcm->Add_Input_Option(" Search ", Cell_Argument());
        Cell_Select_Option() = mcm->Add_Menu_Option(" Select ", "...");
        Cell_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Cell_Do_Negate());
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Relation ");
        mcm->Add_Header_Option("");
        Relation_Select_Option() = mcm->Add_Menu_Option(" Select ", Relation_Argument());
        Relation_Negate_Option() = mcm->Add_Toggle_Option(" Negate ", Relation_Do_Negate());

        mcm->Add_Header_Option(" Other ");
        mcm->Add_Header_Option("");

        Male_Option() = mcm->Add_Toggle_Option(" Is Male ", Male_Female_Argument() == Binary_e::A);
        Female_Option() = mcm->Add_Toggle_Option(" Is Female ", Male_Female_Argument() == Binary_e::B);

        Unique_Option() = mcm->Add_Toggle_Option(" Is Unique ", Unique_Generic_Argument() == Binary_e::A);
        Generic_Option() = mcm->Add_Toggle_Option(" Is Generic ", Unique_Generic_Argument() == Binary_e::B);

        Interior_Option() = mcm->Add_Toggle_Option(" In Interior ", Interior_Exterior_Argument() == Binary_e::A);
        Exterior_Option() = mcm->Add_Toggle_Option(" In Exterior ", Interior_Exterior_Argument() == Binary_e::B);

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Loaded_References_Filter_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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

    void Loaded_References_Filter_t::On_Option_Menu_Open(Int_t option, Latent_Callback_i* lcallback)
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

    void Loaded_References_Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx, Latent_Callback_i* lcallback)
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
        } else if (option == Template_Select_Option()) {
            if (idx > -1) {
                String_t value = "";
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
                String_t value = "";
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
                String_t value = "";
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
                String_t value = "";
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

    void Loaded_References_Filter_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_Callback_i* lcallback)
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

    void Loaded_References_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Title_Text(Title());

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::BACK_LABEL, "");
        Reset_Option() = mcm->Add_Text_Option(Main_t::RESET_LABEL, "");

        mcm->Add_Header_Option("");
        mcm->Add_Header_Option("");
        Smart_Select_Option() = mcm->Add_Toggle_Option(" Smart Select ", Do_Smart_Select());

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Loaded_References_Options_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
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
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    V::Int_Variable_t*  Loaded_References_Item_t::Actor_Form_ID_Variable()          { DEFINE_INT_VARIABLE("p_item_actor_form_id"); }
    V::Int_Variable_t*  Loaded_References_Item_t::Cell_Form_ID_Variable()           { DEFINE_INT_VARIABLE("p_item_cell_form_id"); }

    Form_ID_t           Loaded_References_Item_t::Actor_Form_ID()                   { return Actor_Form_ID_Variable()->Value(); }
    void                Loaded_References_Item_t::Actor_Form_ID(Form_ID_t value)    { Actor_Form_ID_Variable()->Value(value); }
    Form_ID_t           Loaded_References_Item_t::Cell_Form_ID()                    { return Cell_Form_ID_Variable()->Value(); }
    void                Loaded_References_Item_t::Cell_Form_ID(Form_ID_t value)     { Cell_Form_ID_Variable()->Value(value); }

    Item_t Loaded_References_Item_t::Current_Item()
    {
        Item_t item(Actor_Form_ID(), Cell_Form_ID());
        if (item.Is_Valid() && List()->Items().Has(item)) {
            return std::move(item);
        } else {
            return std::move(Item_t());
        }
    }

    Item_t Loaded_References_Item_t::Previous_Item()
    {
        Item_t item(Actor_Form_ID(), Cell_Form_ID());
        if (item.Is_Valid()) {
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
                return std::move(Item_t());
            }
        } else {
            return std::move(Item_t());
        }
    }

    Item_t Loaded_References_Item_t::Next_Item()
    {
        Item_t item(Actor_Form_ID(), Cell_Form_ID());
        if (item.Is_Valid()) {
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
                return std::move(Item_t());
            }
        } else {
            return std::move(Item_t());
        }
    }

    void Loaded_References_Item_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Loaded_Actor_t loaded_actor = Current_Item();
        if (loaded_actor.Is_Valid()) {
            mcm->Title_Text(Title(loaded_actor.actor->Any_Name()));

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

            Back_Option() = mcm->Add_Text_Option(Main_t::BACK_LABEL, "");
            mcm->Add_Empty_Option();
            if (List()->Items().size() > 1) {
                Previous_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "");
                Next_Option() = mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "");
            } else {
                Previous_Option() = mcm->Add_Text_Option(Main_t::PREVIOUS_ITEM_LABEL, "", Flag_e::DISABLE);
                Next_Option() = mcm->Add_Text_Option(Main_t::NEXT_ITEM_LABEL, "", Flag_e::DISABLE);
            }

            mcm->Add_Header_Option(std::string(" ") + Item_Type_Singular() + " ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + loaded_actor.actor->Name(), "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + loaded_actor.actor->Form_ID_String().data, "");
            if (loaded_actor.actor->base_form && loaded_actor.actor->base_form->Is_Valid()) {
                mcm->Add_Text_Option(std::string(" Base Form ID: ") + loaded_actor.actor->base_form->Form_ID_String().data, "");
                mcm->Add_Empty_Option();
            }

            mcm->Add_Header_Option(" Cell ");
            mcm->Add_Header_Option("");
            mcm->Add_Text_Option(std::string(" Name: ") + loaded_actor.cell->Name(), "");
            mcm->Add_Text_Option(std::string(" Editor ID: ") + loaded_actor.cell->Get_Editor_ID(), "");
            mcm->Add_Text_Option(std::string(" Form ID: ") + loaded_actor.cell->Form_ID_String().data, "");
            mcm->Add_Empty_Option();

            Race_t* race = loaded_actor.actor->Race();
            if (race) {
                mcm->Add_Header_Option(" Race ");
                mcm->Add_Header_Option("");
                mcm->Add_Text_Option(std::string(" Name: ") + race->Name(), "");
                mcm->Add_Text_Option(std::string(" Editor ID: ") + race->Get_Editor_ID(), "");
                mcm->Add_Text_Option(std::string(" Form ID: ") + race->Form_ID_String().data, "");
                mcm->Add_Empty_Option();
            }

            {
                Vector_t<String_t> mod_names = loaded_actor.actor->Mod_Names();
                size_t mod_name_count = mod_names.size();
                if (mod_name_count > 0 && mcm->Can_Add_Options(2 + mod_name_count)) {
                    mcm->Add_Header_Option(" Mods ");
                    mcm->Add_Header_Option("");
                    for (Index_t idx = 0, end = mod_name_count; idx < end; idx += 1) {
                        String_t mod_name = mod_names[idx];
                        mcm->Add_Text_Option(mod_name, "");
                    }
                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
                        mcm->Add_Empty_Option();
                    }
                }
            }

            {
                Vector_t<String_t> location_names = loaded_actor.cell->Location_Names();
                size_t location_name_count = location_names.size();
                if (location_name_count > 0 && mcm->Can_Add_Options(2 + location_name_count)) {
                    mcm->Add_Header_Option(" Locations ");
                    mcm->Add_Header_Option("");
                    for (Index_t idx = 0, end = location_name_count; idx < end; idx += 1) {
                        String_t location_name = location_names[idx];
                        mcm->Add_Text_Option(location_name, "");
                    }
                    if (skylib::Is_Odd(mcm->Cursor_Position())) {
                        mcm->Add_Empty_Option();
                    }
                }
            }

            {
                Vector_t<Actor_Base_t*> actor_bases = loaded_actor.actor->Actor_Bases();
                size_t actor_base_count = actor_bases.size();
                if (actor_base_count > 0 && mcm->Can_Add_Options(2 + actor_base_count)) {
                    mcm->Add_Header_Option(" Bases ");
                    mcm->Add_Header_Option("");
                    for (Index_t idx = 0, end = actor_base_count; idx < end; idx += 1) {
                        Actor_Base_t* actor_base = actor_bases[idx];
                        mcm->Add_Text_Option(actor_base->Any_Name(), "");
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

        mcm->Destroy_Latent_Callback(lcallback);
    }

    void Loaded_References_Item_t::On_Option_Select(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        if (option == Back_Option()) {
            mcm->Disable_Option(option);
            List()->do_update_items = true;
            Current_View(Bases_View_e::LIST);
            mcm->Reset_Page();
        } else if (option == Previous_Option()) {
            mcm->Disable_Option(option);
            Loaded_Actor_t loaded_actor = Previous_Item();
            if (loaded_actor.Is_Valid()) {
                Actor_Form_ID(loaded_actor.actor->form_id);
                Cell_Form_ID(loaded_actor.cell->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
        } else if (option == Next_Option()) {
            mcm->Disable_Option(option);
            Loaded_Actor_t loaded_actor = Next_Item();
            if (loaded_actor.Is_Valid()) {
                Actor_Form_ID(loaded_actor.actor->form_id);
                Cell_Form_ID(loaded_actor.cell->form_id);
            } else {
                List()->do_update_items = true;
                Current_View(Bases_View_e::LIST);
            }
            mcm->Reset_Page();
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}
