/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_variable.h"

#include "mcm_bases.h"

namespace doticu_npcl { namespace MCM {

    some<const char*> Bases_Item_Section_e::To_String(Bases_Item_Section_e section_e)
    {
        switch (section_e) {
            case (Bases_Item_Section_e::BASES):     return Main_t::BASES;
            case (Bases_Item_Section_e::COMMANDS):  return Main_t::COMMANDS;
            case (Bases_Item_Section_e::FACTIONS):  return Main_t::FACTIONS;
            case (Bases_Item_Section_e::KEYWORDS):  return Main_t::KEYWORDS;
            case (Bases_Item_Section_e::MODS):      return Main_t::MODS;
            case (Bases_Item_Section_e::RACES):     return Main_t::RACES;
            case (Bases_Item_Section_e::TEMPLATES): return Main_t::TEMPLATES;
            default:                                return Main_t::_NONE_;
        }
    }

    Bases_Item_Section_e Bases_Item_Section_e::From_String(some<const char*> section_str)
    {
        SKYLIB_ASSERT_SOME(section_str);

        const char* str = section_str();
        while (*str == ' ') {
            str += 1;
        }
             if (CString_t::Starts_With(Main_t::BASES, str, true))      return Bases_Item_Section_e::BASES;
        else if (CString_t::Starts_With(Main_t::COMMANDS, str, true))   return Bases_Item_Section_e::COMMANDS;
        else if (CString_t::Starts_With(Main_t::FACTIONS, str, true))   return Bases_Item_Section_e::FACTIONS;
        else if (CString_t::Starts_With(Main_t::KEYWORDS, str, true))   return Bases_Item_Section_e::KEYWORDS;
        else if (CString_t::Starts_With(Main_t::MODS, str, true))       return Bases_Item_Section_e::MODS;
        else if (CString_t::Starts_With(Main_t::RACES, str, true))      return Bases_Item_Section_e::RACES;
        else if (CString_t::Starts_With(Main_t::TEMPLATES, str, true))  return Bases_Item_Section_e::TEMPLATES;
        else                                                            return Bases_Item_Section_e::NONE;
    }

}}

namespace doticu_npcl { namespace MCM {

    Vector_t<Item_Section_t> Item_Sections_t::Current()
    {
        std::lock_guard<std::mutex> guard(mutex);

        size_t item_section_count = item_sections.size();

        Vector_t<Item_Section_t> copy;
        copy.reserve(item_section_count);

        for (Index_t idx = 0, end = item_section_count; idx < end; idx += 1) {
            Item_Section_t item_section = item_sections[idx];
            if (item_section != Bases_Item_Section_e::NONE) {
                copy.push_back(item_section);
            }
        }

        return copy;
    }

    void Item_Sections_t::Reset(Vector_t<Item_Section_t>&& defaults)
    {
        std::lock_guard<std::mutex> guard(mutex);

        size_t default_count = defaults.size();
        item_sections.clear();
        item_sections.reserve(default_count);

        for (Index_t idx = 0, end = default_count; idx < end; idx += 1) {
            item_sections.push_back(defaults[idx]);
        }
    }

    Bool_t Item_Sections_t::Is_Enabled(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        return item_sections.Has(item_section);
    }

    void Item_Sections_t::Enable(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        if (!item_sections.Has(item_section)) {
            item_sections.push_back(item_section);
        }
    }

    void Item_Sections_t::Disable(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Index_t idx = item_sections.Index_Of(item_section);
        if (idx > -1) {
            item_sections.erase(item_sections.begin() + idx);
        }
    }

    Bool_t Item_Sections_t::May_Move_Higher(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        return item_sections.Index_Of(item_section) > 0;
    }

    Bool_t Item_Sections_t::May_Move_Lower(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Index_t idx = item_sections.Index_Of(item_section);
        Index_t last = item_sections.size() - 1;
        return idx > -1 && idx < last;
    }

    void Item_Sections_t::Move_Higher(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Index_t idx = item_sections.Index_Of(item_section);
        if (idx > 0) {
            Item_Section_t item_section = item_sections[idx];
            item_sections[idx] = item_sections[idx - 1];
            item_sections[idx - 1] = item_section;
        }
    }

    void Item_Sections_t::Move_Lower(Item_Section_t item_section)
    {
        std::lock_guard<std::mutex> guard(mutex);

        Index_t idx = item_sections.Index_Of(item_section);
        Index_t last = item_sections.size() - 1;
        if (idx > -1 && idx < last) {
            Item_Section_t item_section = item_sections[idx];
            item_sections[idx] = item_sections[idx + 1];
            item_sections[idx + 1] = item_section;
        }
    }

}}
