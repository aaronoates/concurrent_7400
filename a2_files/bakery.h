#pragma once
#include "buffer.h"
#include <iostream>
#include <semaphore>
using std::cout, std::endl, std::counting_semaphore, std::chrono::milliseconds;

// A Bakery is a collection of BreadBuffers representing the counters, ovens,
// and shelves.  It also contains semaphores to control access to these buffers.
struct Bakery {

    int numIngredients;

    BreadBuffer counters;
    BreadBuffer ovens;
    BreadBuffer shelves;

    Bakery(int numIngredients, int counterCapacity, int ovenCapacity,
            int shelfCapacity)
        : numIngredients(numIngredients), counters(counterCapacity),
          ovens(ovenCapacity), shelves(shelfCapacity) {}

    // STUDENTS: Declare all of the semaphores you want to use here and
    // determine the sizes they should be initialized to.
    //
    // Keep this first semaphore and add more as needed.
    //
    // NOTE: Don't forget to include the <> after counting_semaphore.
    //
    counting_semaphore<> ingredientsAvail{numIngredients}; //for the first set of configs, this should be 7. Once it reaches -1, the current thread is blocked and placed in a queue. 
    counting_semaphore<> countersAvail{counters.getCapacity()}; //for the first set of configs, this should be 5.
    counting_semaphore<> ovensAvail{ovens.getCapacity()};// for the first set of configs, this should be 5.
    counting_semaphore<> shelvesAvail{shelves.getCapacity()}; //for the first set of configs, this should be 5.

};