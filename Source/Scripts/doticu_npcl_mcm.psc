; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcl_mcm extends SKI_ConfigBase

string p_current_page = ""

event OnConfigOpen()
    ModName = " NPC Lookup "
    
    Pages = Utility.CreateStringArray(2, "")
    Pages[0] = " Bases "
    Pages[1] = " References "
endEvent

event OnPageReset(String current_page) native
event OnOptionSelect(int option) native
event OnOptionMenuOpen(int option) native
event OnOptionMenuAccept(int option, int idx) native
event OnOptionSliderOpen(int option) native
event OnOptionSliderAccept(int option, float value) native
event OnOptionInputAccept(int option, string value) native
event OnOptionKeymapChange(int option, int key_code, string conflict, string conflicting_mod) native
event OnOptionDefault(int option) native
event OnOptionHighlight(int option) native
