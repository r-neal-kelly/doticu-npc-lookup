/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "mcm_references.h"

namespace doticu_npcl { namespace MCM {

    some<const char*> References_Item_Section_e::To_String(References_Item_Section_e section_e)
    {
        switch (section_e) {
            case (References_Item_Section_e::CELLS):        return Main_t::CELLS;
            case (References_Item_Section_e::LOCATIONS):    return Main_t::LOCATIONS;
            case (References_Item_Section_e::QUESTS):       return Main_t::QUESTS;
            case (References_Item_Section_e::REFERENCES):   return Main_t::REFERENCES;
            case (References_Item_Section_e::WORLDSPACES):  return Main_t::WORLDSPACES;
            default:                                        return Bases_Item_Section_e::To_String(section_e);
        }
    }

    References_Item_Section_e References_Item_Section_e::From_String(some<const char*> section_str)
    {
        SKYLIB_ASSERT_SOME(section_str);

        const char* str = section_str();
        while (*str == ' ') {
            str += 1;
        }
             if (CString_t::Starts_With(Main_t::CELLS, str, true))          return References_Item_Section_e::CELLS;
        else if (CString_t::Starts_With(Main_t::LOCATIONS, str, true))      return References_Item_Section_e::LOCATIONS;
        else if (CString_t::Starts_With(Main_t::QUESTS, str, true))         return References_Item_Section_e::QUESTS;
        else if (CString_t::Starts_With(Main_t::REFERENCES, str, true))     return References_Item_Section_e::REFERENCES;
        else if (CString_t::Starts_With(Main_t::WORLDSPACES, str, true))    return References_Item_Section_e::WORLDSPACES;
        else                                                                return static_cast<References_Item_Section_e>
                                                                                   (Bases_Item_Section_e::From_String(str));
    }

}}
