#pragma once

// TODO load from lua
struct Resources {
    Resources() :
        money(100),
        aluminium(0), coal(0), copper(0), diamond(0), gold(0), iron(0), max_workers(1)
    { }
    int money, aluminium, coal, copper, diamond, gold, iron;
    int max_workers;
};

