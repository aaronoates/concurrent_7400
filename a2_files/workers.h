#pragma once
#include <iostream>
#include "bakery.h"
using std::cout, std::endl, std::mutex, std::lock_guard;

struct Mixer {
    Bakery &bakery;
    Mixer(Bakery &bakery) : bakery(bakery) {}
    void operator()();
};

struct Assistant {
    Bakery &bakery;
    Assistant(Bakery &bakery) : bakery(bakery) {}
    void operator()();
};

struct Baker {
    Bakery &bakery;
    Baker(Bakery &bakery) : bakery(bakery) {}
    void operator()();
};
