#pragma once
#include <queue>
#include <iostream>
#include "bread.h"
#include <stdexcept>

using std::queue, std::cout, std::endl;

// A BreadBuffer is a fixed-capacity queue of Bread objects.  It is up to the
// user to ensure that the buffer is not full before adding a Bread, or empty 
// before removing one.  BreadBuffers are not thread-safe, so the user must
// ensure that access to them is properly synchronized.
class BreadBuffer {
private:

    int capacity;

    queue<Bread> q;

public:
    BreadBuffer(int cap) : capacity(cap) {
    }

    void add(Bread bread) {
        if (q.size() < capacity)
            q.push(bread);
        else
            throw std::runtime_error("Adding to full BreadBuffer!");
    }

    Bread remove() {
        if (q.size() == 0)
            throw std::runtime_error("Removing from empty BreadBuffer!");

        Bread loaf = q.front();
        q.pop();
        
        return loaf;
    }

    const int getCapacity() {
        return capacity;
    }

    const int getSize() {
        return q.size();
    }

    const bool checkCorrect(int desiredNumber, State desiredState) {
        bool correctNumber = q.size() == desiredNumber;
        bool correctState = true;

        // BAD: This is ugly.  We need to loop over all queue elements, which
        // is not a very "queuey" thing to do.  We do it here by popping all
        // elements from a temporary queue and checking their states.
        queue tempQ = q;
        while (!tempQ.empty() && correctState) {
            if (tempQ.front().state != desiredState) 
                correctState = false;
            tempQ.pop();
        } 

        if (correctNumber && correctState)
            return true;
        else {
            cout << "\tBreadBuffer check failed! " << endl;
            cout << "\tdesired number: " << desiredNumber << ", actual: " << q.size() << endl;
            cout << "\tdesired state: " << desiredState << endl;
            cout << "\tPrinting the state of all breads in the queue:" << endl;
            queue<Bread> tempQ = q;
            while (!tempQ.empty()) {
                cout << "\tBread state: " << tempQ.front().getStateString() << endl;
                tempQ.pop();
            }
            return false;
        }
    }
};