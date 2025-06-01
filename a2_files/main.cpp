#include <iostream>
#include "configs.h"
#include "run.h"
using std::cout, std::endl, std::vector;

// Run the simulation with each config and print whether each test passed.
int main() {
    vector<Config> configs = getConfigs(); //Creates a vector of Config objects, where each Config is a struct that contain structs of input configurations (num of workers, ingredients, buffer capacities) and structs of output configurations (number of buffers in use). 
    int numPassed = 0; // will be used to store the number of passed test cases.
    cout << std::boolalpha; // Print bools as true/false instead of 1/0.
    for (int i = 0; i < configs.size(); i++) { //iterates through the Config objects in the configs vector.
        cout << "Testing with config " << i <<  ": " << endl; //prints the current Config object
        if (run(configs[i])) { // calls the run function defined in run.h and run.cpp. If it returns true, this if statement will run.
            cout << "Test passed!" << endl;
            numPassed++;
        } else {
            cout << "Test failed!" << endl;
        }
    }
    cout << "Passed " << numPassed << " out of " << configs.size() << " tests." << endl;
    return 0;
}