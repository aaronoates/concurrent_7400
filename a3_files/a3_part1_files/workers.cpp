#include "workers.h"

void Mixer::operator()() {
    while (true) {
        if (!bakery.try_acquire_ingredients(milliseconds(200))) { // if no ingredients can be acquired, this line will return true.
            return;
        }

        if (bakery.try_acquire_counter(milliseconds(200))) { // if a counter space is available
            Bread bread;
            bread.state = MIXED; //change the bread state
            bakery.counters.add(bread); // put the bread on the counter
            bakery.release_counter_item(); // notify all others that there is a bread on the counter
        } else {
            bakery.release_ingredients(); // ingredient was acquired but not used, so we have to re-release it.
            return;
        }
    }
}

void Assistant::operator()() {
    while (true) {
        if (!bakery.try_acquire_counter_item(milliseconds(200))) { // if there is no bread on the counter, the assistant has no work to do.
            return;
        }

        if (bakery.try_acquire_oven(milliseconds(200))) { // if an oven space is available
            Bread bread = bakery.counters.remove(); //remove the bread from the counter
            bread.state = BAKING; //change its state
            bakery.ovens.add(bread); // put the bread in the oven
            bakery.release_counter(); // the counter space where the bread was is no longer in use
            bakery.release_oven_item(); // notify all others that there is a piece of bread in the oven
        } else {
            bakery.release_counter_item(); // a counter item was acquired but nothing was done with it, so we re-release it.
            return;
        }
    }
}

void Baker::operator()() {
    while (true) {
        if (!bakery.try_acquire_oven_item(milliseconds(200))) { // if there is no bread in the oven, the baker has no work to do.
            return;
        }

        if (bakery.try_acquire_shelf(milliseconds(200))) { //if there is an available shelf space
            Bread bread = bakery.ovens.remove(); // taek the bread out of the oven
            bread.state = READY; // change the state to ready
            bakery.shelves.add(bread); // put the bread on the shelf
            bakery.release_oven(); // an oven space is now free
            bakery.release_shelf_item(); // there is a piece of bread on the shelf now
        } else {
            bakery.release_oven_item(); // an oven item was acquired but not used, so it has to be re-released.
            return;
        }
    }
}
