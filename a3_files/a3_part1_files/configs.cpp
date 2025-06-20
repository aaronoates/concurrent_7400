#include "configs.h"

vector<Config> getConfigs() {
    return {

        // This will be our basic configuration, varied in particular ways below.
        Config{InputConfig{1, 1, 1, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}

        // As above, but limit the number of ingredients to 3.
        , Config{InputConfig{1, 1, 1, 3, 5, 5, 5}, OutputConfig{0, 0, 3}}

        // Now try just enough, and then an excessive number of ingredients.
        , Config{InputConfig{1, 1, 1, 15, 5, 5, 5}, OutputConfig{5, 5, 5}}
        , Config{InputConfig{1, 1, 1, 1000, 5, 5, 5}, OutputConfig{5, 5, 5}}

        // Vary the number of mixers, assistants, and bakers.  It should not
        // affect the output as long as all are above 0.
        , Config{InputConfig{4, 1, 1, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 4, 1, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 1, 4, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{40, 1, 1, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 40, 1, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 1, 40, 7, 5, 5, 5}, OutputConfig{0, 2, 5}}

        // Okay, see what happens when we have 0 of each worker.
        // , Config{InputConfig{0, 1, 1, 7, 5, 5, 5}, OutputConfig{0, 0, 0}}
        , Config{InputConfig{1, 0, 1, 7, 5, 5, 5}, OutputConfig{5, 0, 0}}
        , Config{InputConfig{1, 1, 0, 7, 5, 5, 5}, OutputConfig{2, 5, 0}}

        // Zeroing the capacity of the counters, ovens, and shelves.
        // , Config{InputConfig{1, 1, 1, 7, 0, 5, 5}, OutputConfig{0, 0, 0}}
        , Config{InputConfig{1, 1, 1, 7, 5, 0, 5}, OutputConfig{5, 0, 0}}
        , Config{InputConfig{1, 1, 1, 7, 5, 5, 0}, OutputConfig{2, 5, 0}}

        // Doubling the capacity of the counters, ovens, and shelves.
        , Config{InputConfig{1, 1, 1, 7, 10, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 1, 1, 7, 5, 10, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 1, 1, 7, 5, 5, 10}, OutputConfig{0, 0, 7}}

        // Trying capacity 1 for the counters, ovens, and shelves.
        , Config{InputConfig{1, 1, 1, 7, 1, 5, 5}, OutputConfig{0, 2, 5}}
        , Config{InputConfig{1, 1, 1, 7, 5, 1, 5}, OutputConfig{1, 1, 5}}
        , Config{InputConfig{1, 1, 1, 7, 5, 5, 1}, OutputConfig{1, 5, 1}}
    };
}