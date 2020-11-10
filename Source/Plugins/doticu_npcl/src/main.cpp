/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PluginAPI.h"

#include "main.h"

extern "C" {

    bool SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return false;
    }

    bool SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return false;
    }

}
