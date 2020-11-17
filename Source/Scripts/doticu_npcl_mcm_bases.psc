; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcl_mcm_bases extends Quest

string  p_current_view              =      ""
int     p_options_offset            =      -1

; List
int     p_filter_option             =      -1
int     p_options_option            =      -1
int     p_previous_page_option      =      -1
int     p_next_page_option          =      -1
int     p_page_index                =      -1

; Filter
int     p_back_option               =      -1
int     p_reset_option              =      -1

int     p_name_option               =      -1
string  p_name_argument             =      ""
int     p_negate_name_option        =      -1
bool    p_do_negate_name            =   false

int     p_race_option               =      -1
string  p_race_argument             =      ""
int     p_negate_race_option        =      -1
bool    p_do_negate_race            =   false
int     p_select_race_option        =      -1

int     p_mod_option                =      -1
string  p_mod_argument              =      ""
int     p_negate_mod_option         =      -1
bool    p_do_negate_mod             =   false
int     p_select_mod_option         =      -1

int     p_relation_option           =      -1
int     p_relation_argument         =      -1
string  p_relation_view             = " Any "
int     p_negate_relation_option    =      -1
bool    p_do_negate_relation        =   false

int     p_is_male_option            =      -1
int     p_is_female_option          =      -1
int     p_male_female_ternary       =       0

int     p_is_unique_option          =      -1
int     p_is_generic_option         =      -1
int     p_unique_generic_ternary    =       0
