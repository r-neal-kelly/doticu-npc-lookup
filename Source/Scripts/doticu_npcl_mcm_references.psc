; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcl_mcm_references extends doticu_npcl_mcm_bases

; Filter
string  p_filter_reference_argument         =      ""
bool    p_filter_reference_do_negate        =   false

string  p_filter_worldspace_argument        =      ""
bool    p_filter_worldspace_do_negate       =   false

string  p_filter_location_argument          =      ""
bool    p_filter_location_do_negate         =   false

string  p_filter_cell_argument              =      ""
bool    p_filter_cell_do_negate             =   false

string  p_filter_quest_argument             =      ""
bool    p_filter_quest_do_negate            =   false

int     p_filter_interior_exterior_argument =       0
int     p_filter_alive_dead_argument        =       0
int     p_filter_is_teammate_argument       =       0

; Item
bool    p_item_do_show_cells                =   false
bool    p_item_do_show_locations            =   false
bool    p_item_do_show_quests               =   false
bool    p_item_do_show_references           =   false
bool    p_item_do_show_worldspaces          =   false
