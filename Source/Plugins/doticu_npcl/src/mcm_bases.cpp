/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

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
