#pragma once
#include "bakery.h"

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
