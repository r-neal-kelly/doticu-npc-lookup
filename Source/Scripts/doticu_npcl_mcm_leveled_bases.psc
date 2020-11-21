; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcl_mcm_leveled_bases extends Quest

; Base
string  p_current_view                      =      ""

; List
int     p_list_filter_option                =      -1
int     p_list_options_option               =      -1
int     p_list_previous_page_option         =      -1
int     p_list_next_page_option             =      -1
int     p_list_page_index                   =      -1

; Filter
int     p_filter_back_option                =      -1
int     p_filter_clear_option               =      -1

int     p_filter_mod_search_option          =      -1
int     p_filter_mod_select_option          =      -1
int     p_filter_mod_negate_option          =      -1
string  p_filter_mod_argument               =      ""
bool    p_filter_mod_do_negate              =   false

int     p_filter_race_search_option         =      -1
int     p_filter_race_select_option         =      -1
int     p_filter_race_negate_option         =      -1
string  p_filter_race_argument              =      ""
bool    p_filter_race_do_negate             =   false

int     p_filter_base_search_option         =      -1
int     p_filter_base_select_option         =      -1
int     p_filter_base_negate_option         =      -1
string  p_filter_base_argument              =      ""
bool    p_filter_base_do_negate             =   false

int     p_filter_relation_select_option     =      -1
int     p_filter_relation_negate_option     =      -1
int     p_filter_relation_argument          =      -1
bool    p_filter_relation_do_negate         =   false

int     p_filter_has_male_option            =      -1
int     p_filter_has_female_option          =      -1
int     p_filter_male_female_quaternary     =       0

int     p_filter_has_unique_option          =      -1
int     p_filter_has_generic_option         =      -1
int     p_filter_unique_generic_quaternary  =       0

; Options
int     p_options_back_option               =      -1
int     p_options_reset_option              =      -1

int     p_options_smart_select_option       =      -1
bool    p_options_do_smart_select           =    true

; Item
int     p_item_back_option                  =      -1
int     p_item_previous_option              =      -1
int     p_item_next_option                  =      -1
int     p_item_leveled_actor_base_form_id   =       0
