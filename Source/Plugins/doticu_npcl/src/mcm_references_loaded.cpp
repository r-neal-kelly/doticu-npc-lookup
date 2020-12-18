/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/worldspace.h"

#include "doticu_skylib/virtual_utils.h"

#include "consts.h"
#include "filter.h"
#include "mcm_references.h"
#include "mcm_references.inl"
#include "mcm_references_loaded.h"
#include "mcm_markers.h"

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
        if (!is_refresh) {
            do_update_items = true;
        }

        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

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
                Loaded_Actor_t loaded_actor = loaded_actors[begin];
                mcm->Add_Text_Option(loaded_actor.actor->Any_Name(), Main_t::_DOTS_);
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
            Vector_t<Item_t>& items = Items();
            Index_t item_index = mcm->Option_To_Item_Index(
                option, items.size(), Page_Index(), HEADERS_PER_PAGE, ITEMS_PER_PAGE
            );
            if (item_index > -1) {
                Item_t item = items[item_index];
                if (item.Is_Valid()) {
                    mcm->Disable_Option(option);
                    Item()->Actor_Form_ID(item.actor->form_id);
                    Item()->Cell_Form_ID(item.cell->form_id);
                    Current_View(Bases_View_e::ITEM);
                    mcm->Reset_Page();
                }
            }
        }

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Loaded_References_Filter_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, Main_t::COMPONENT_FILTER));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, Main_t::SAFE_COMPONENT_FILTER));
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Build_Filters(Main_t::LOADED_REFERENCE);

        mcm->Destroy_Latent_Callback(lcallback);
    }

}}

namespace doticu_npcl { namespace MCM {

    void Loaded_References_Options_t::On_Page_Open(Bool_t is_refresh, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Reset_Option_Ints();

        if (mcm->Should_Translate_Page_Titles()) {
            mcm->Translated_Title_Text(mcm->Plural_Title(Main_t::COMPONENT_LOADED_REFERENCES, Main_t::COMPONENT_OPTIONS));
        } else {
            mcm->Title_Text(mcm->Plural_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCES, Main_t::SAFE_COMPONENT_OPTIONS));
        }

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

        Back_Option() = mcm->Add_Text_Option(Main_t::CENTER_BACK, Main_t::_NONE_);
        Reset_Option() = mcm->Add_Text_Option(Main_t::CENTER_RESET, Main_t::_NONE_);

        mcm->Add_Header_Option(Main_t::_NONE_);
        mcm->Add_Header_Option(Main_t::_NONE_);
        Smart_Select_Option() = mcm->Add_Toggle_Option(Main_t::SMART_SELECT, Do_Smart_Select());

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

    Bool_t Loaded_References_Item_t::Current_Item(Item_t item)
    {
        if (item.Is_Valid()) {
            Actor_Form_ID(item.actor->form_id);
            Cell_Form_ID(item.cell->form_id);
            return true;
        } else {
            return false;
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

        Reset_Option_Ints();

        Item_t item(Actor_Form_ID(), Cell_Form_ID());
        if (item.Is_Valid()) {
            Vector_t<Item_t>& items = List()->Items();
            Index_t item_index = items.Index_Of(item);
            if (item_index > -1) {
                if (mcm->Should_Translate_Page_Titles()) {
                    mcm->Translated_Title_Text(
                        mcm->Singular_Title(Main_t::COMPONENT_LOADED_REFERENCE, item.actor->Any_Name(), item_index, items.size())
                    );
                } else {
                    mcm->Title_Text(
                        mcm->Singular_Title(Main_t::SAFE_COMPONENT_LOADED_REFERENCE, item.actor->Any_Name(), item_index, items.size())
                    );
                }

                mcm->Cursor_Position(0);
                mcm->Cursor_Fill_Mode(Cursor_e::LEFT_TO_RIGHT);

                Build_Header(Main_t::_NONE_, List()->Items().size());
                Build_Reference(item.actor, Main_t::LOADED_REFERENCE);
                Build_Race(item.actor->Race());
                Build_Bases(item.actor->Actor_Bases());
                Build_Cell(item.cell);
                Build_Locations(item.cell->Locations());
                Build_Factions_And_Ranks(item.actor->Factions_And_Ranks());
                Build_Keywords(item.actor->Keywords());
                Build_Quests(item.actor->Quests());
                Build_Mod_Names(item.actor->Mod_Names());
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
        Main_t* mcm = Main_t::Self();

        if (option == Mark_On_Map_Option()) {
            mcm->Flicker_Option(option);
            Loaded_Actor_t loaded_actor = Current_Item();
            if (loaded_actor.Is_Valid()) {
                Markers_t* markers = Markers_t::Self();
                if (markers->Has_Marked(loaded_actor.actor)) {
                    Markers_t::Self()->Unmark(loaded_actor.actor);
                } else {
                    Markers_t::Self()->Mark(loaded_actor.actor);
                }
                mcm->Reset_Page();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Move_To_Player_Option()) {
            mcm->Flicker_Option(option);
            Loaded_Actor_t loaded_actor = Current_Item();
            if (loaded_actor.Is_Valid()) {
                loaded_actor.actor->Move_To_Orbit(Consts_t::Skyrim_Player_Actor(), 160.0f, 0.0f);
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Go_To_Reference_Option()) {
            mcm->Disable_Option(option);
            Loaded_Actor_t loaded_actor = Current_Item();
            if (loaded_actor.Is_Valid()) {
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
                skylib::Virtual::Utils_t::Close_Menus(new Callback_t(loaded_actor.actor));
            } else {
                mcm->Enable_Option(option);
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Enable_Disable_Option()) {
            mcm->Flicker_Option(option);
            Loaded_Actor_t loaded_actor = Current_Item();
            if (loaded_actor.Is_Valid()) {
                if (loaded_actor.actor->Is_Disabled()) {
                    loaded_actor.actor->Enable();
                } else {
                    loaded_actor.actor->Disable();
                }
                mcm->Reset_Page();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (option == Select_In_Console_Option()) {
            mcm->Flicker_Option(option);
            Loaded_Actor_t loaded_actor = Current_Item();
            if (loaded_actor.Is_Valid()) {
                loaded_actor.actor->Select_In_Console();
            }
            mcm->Destroy_Latent_Callback(lcallback);

        } else if (Try_On_Option_Select(option, lcallback)) {
            return;

        } else {
            mcm->Destroy_Latent_Callback(lcallback);

        }
    }

    void Loaded_References_Item_t::On_Option_Highlight(Int_t option, Latent_Callback_i* lcallback)
    {
        Main_t* mcm = Main_t::Self();

        Item_t item = Current_Item();
        if (item.Is_Valid()) {
            if (option == Mark_On_Map_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_ADD_REMOVE_MAP_MARKER);
            } else if (option == Move_To_Player_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_MOVE_TO_PLAYER);
            } else if (option == Go_To_Reference_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_GO_TO_REFERENCE);
            } else if (option == Enable_Disable_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_ENABLE_DISABLE_REFERENCE);
            } else if (option == Select_In_Console_Option()) {
                mcm->Info_Text(Main_t::HIGHLIGHT_SELECT_IN_CONSOLE);

            } else if (option == Race_Name_Option()) {
                Race_t* race = item.actor->Race();
                if (race) {
                    const char* name = race->Name();
                    const char* editor_id = race->Get_Editor_ID();
                    const char* form_id = race->Form_ID_String().data;
                    mcm->Info_Text(mcm->Pretty_ID(name, editor_id, form_id));
                }
            } else if (option == Cell_Name_Option()) {
                Cell_t* cell = item.actor->Cell();
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
