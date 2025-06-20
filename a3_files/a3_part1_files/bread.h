#pragma once
#include <string>
using std::string;

enum State { UNMIXED, MIXED, BAKING, READY };

struct Bread {
    static int lastId;

    int id;
    State state;
    
    Bread() : id(lastId), state(UNMIXED) {
        lastId++;
    }

    string getStateString() {
        switch (state) {
            case UNMIXED: return "UNMIXED";
            case MIXED: return "MIXED";
            case BAKING: return "BAKING";
            case READY: return "READY";
            default: return "INVALID STATE";
        }
    }
};