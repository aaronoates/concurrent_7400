#pragma once
#include "configs.h"

// Run the bakery simulation with the given configuration, returning whether 
// the simulation's final statematches the config's expected output.
bool run(Config config);