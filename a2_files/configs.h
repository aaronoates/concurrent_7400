#pragma once
#include <vector>
using std::vector;

struct InputConfig {
    const int numMixers;
    const int numAssistants;
    const int numBakers;
    const int numIngredients;
    const int counterCapacity;
    const int ovenCapacity;
    const int shelfCapacity;
};

struct OutputConfig {
    const int countersInUse;
    const int ovensInUse;
    const int shelvesInUse;
};

struct Config {
    const InputConfig input;
    const OutputConfig output;
};

vector<Config> getConfigs();