#pragma once
#include "buffer.h"
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>

using std::cout, std::endl;
using std::mutex, std::condition_variable, std::unique_lock;
using std::chrono::milliseconds;

struct Bakery {
    int numIngredients;

    BreadBuffer counters;
    BreadBuffer ovens;
    BreadBuffer shelves;

    Bakery(int numIngredients, int counterCapacity, int ovenCapacity,
           int shelfCapacity)
        : numIngredients(numIngredients), counters(counterCapacity),
          ovens(ovenCapacity), shelves(shelfCapacity),
          ingredientsAvailable(numIngredients),
          countersAvailable(counterCapacity),
          ovensAvailable(ovenCapacity),
          shelvesAvailable(shelfCapacity),
          counterItems(0), ovenItems(0), shelfItems(0) {}

    mutex mtx;

    // Ingredient
    condition_variable cv_ingredients;
    int ingredientsAvailable;

    // Counters
    condition_variable cv_counters;
    int countersAvailable;
    condition_variable cv_counterItems;
    int counterItems;

    // Ovens
    condition_variable cv_ovens;
    int ovensAvailable;
    condition_variable cv_ovenItems;
    int ovenItems;

    // Shelves
    condition_variable cv_shelves;
    int shelvesAvailable;
    condition_variable cv_shelfItems;
    int shelfItems;

    // Helper functions with timeout
    bool try_acquire_ingredients(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_ingredients.wait_for(lock, dur, [&] { return ingredientsAvailable > 0; }) 
            ? (--ingredientsAvailable, true) 
            : false;
    }

    void release_ingredients() {
        unique_lock lock(mtx);
        ingredientsAvailable++;
        cv_ingredients.notify_one();
    }

    bool try_acquire_counter(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_counters.wait_for(lock, dur, [&] { return countersAvailable > 0; }) 
            ? (--countersAvailable, true) 
            : false;
    }

    void release_counter() {
        unique_lock lock(mtx);
        countersAvailable++;
        cv_counters.notify_one();
    }

    bool try_acquire_oven(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_ovens.wait_for(lock, dur, [&] { return ovensAvailable > 0; }) 
            ? (--ovensAvailable, true) 
            : false;
    }

    void release_oven() {
        unique_lock lock(mtx);
        ovensAvailable++;
        cv_ovens.notify_one();
    }

    bool try_acquire_shelf(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_shelves.wait_for(lock, dur, [&] { return shelvesAvailable > 0; }) 
            ? (--shelvesAvailable, true) 
            : false;
    }

    void release_shelf() {
        unique_lock lock(mtx);
        shelvesAvailable++;
        cv_shelves.notify_one();
    }

    bool try_acquire_counter_item(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_counterItems.wait_for(lock, dur, [&] { return counterItems > 0; }) 
            ? (--counterItems, true) 
            : false;
    }

    void release_counter_item() {
        unique_lock lock(mtx);
        counterItems++;
        cv_counterItems.notify_one();
    }

    bool try_acquire_oven_item(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_ovenItems.wait_for(lock, dur, [&] { return ovenItems > 0; }) 
            ? (--ovenItems, true) 
            : false;
    }

    void release_oven_item() {
        unique_lock lock(mtx);
        ovenItems++;
        cv_ovenItems.notify_one();
    }

    bool try_acquire_shelf_item(milliseconds dur) {
        unique_lock lock(mtx);
        return cv_shelfItems.wait_for(lock, dur, [&] { return shelfItems > 0; }) 
            ? (--shelfItems, true) 
            : false;
    }

    void release_shelf_item() {
        unique_lock lock(mtx);
        shelfItems++;
        cv_shelfItems.notify_one();
    }
};
