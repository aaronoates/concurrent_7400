#include "workers.h"

void Mixer::operator()() {
    while (true) {
        if (!bakery.try_acquire_ingredients(milliseconds(200))) {
            return;
        }

        if (bakery.try_acquire_counter(milliseconds(200))) {
            Bread bread;
            bread.state = MIXED;
            bakery.counters.add(bread);
            bakery.release_counter_item();
        } else {
            bakery.release_ingredients();
            return;
        }
    }
}

void Assistant::operator()() {
    while (true) {
        if (!bakery.try_acquire_counter_item(milliseconds(200))) {
            return;
        }

        if (bakery.try_acquire_oven(milliseconds(200))) {
            Bread bread = bakery.counters.remove();
            bread.state = BAKING;
            bakery.ovens.add(bread);
            bakery.release_counter();
            bakery.release_oven_item();
        } else {
            bakery.release_counter_item();
            return;
        }
    }
}

void Baker::operator()() {
    while (true) {
        if (!bakery.try_acquire_oven_item(milliseconds(200))) {
            return;
        }

        if (bakery.try_acquire_shelf(milliseconds(200))) {
            Bread bread = bakery.ovens.remove();
            bread.state = READY;
            bakery.shelves.add(bread);
            bakery.release_oven();
            bakery.release_shelf_item();
        } else {
            bakery.release_oven_item();
            return;
        }
    }
}
