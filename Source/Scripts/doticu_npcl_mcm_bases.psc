; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcl_mcm_bases extends Quest

; General
string  p_current_view                      =      ""

; List
int     p_list_page_index                   =      -1

; Filter
string  p_filter_mod_argument               =      ""
bool    p_filter_mod_do_negate              =   false

string  p_filter_race_argument              =      ""
bool    p_filter_race_do_negate             =   false

string  p_filter_base_argument              =      ""
bool    p_filter_base_do_negate             =   false

string  p_filter_template_argument          =      ""
bool    p_filter_template_do_negate         =   false

string  p_filter_faction_argument           =      ""
bool    p_filter_faction_do_negate          =   false

string  p_filter_keyword_argument           =      ""
bool    p_filter_keyword_do_negate          =   false

string  p_filter_relation_argument          =      ""
bool    p_filter_relation_do_negate         =   false

int     p_filter_male_female_argument       =       0
int     p_filter_unique_generic_argument    =       0

; Options
bool    p_options_do_smart_select           =    true
bool    p_options_do_uncombative_spawns     =    true
bool    p_options_do_persistent_spawns      =    true
bool    p_options_do_static_spawns          =    true

; Item
string  p_item_nested_view                  =      ""
int     p_item_nested_index                 =      -1
int     p_item_nested_form                  =      -1
