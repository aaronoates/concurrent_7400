#include <iostream>
#include "configs.h"
#include "run.h"
using std::cout, std::endl, std::vector;

// Run the simulation with each config and print whether each test passed.
int main() {
    vector<Config> configs = getConfigs();
    int numPassed = 0;
    cout << std::boolalpha; // Print bools as true/false instead of 1/0.
    for (int i = 0; i < configs.size(); i++) {
        cout << "Testing with config " << i <<  ": " << endl;
        if (run(configs[i])) {
            cout << "Test passed!" << endl << endl;
            numPassed++;
        } else {
            cout << "Test failed!" << endl << endl;
        }
    }
    cout << "Passed " << numPassed << " out of " << configs.size() << " tests." << endl;
    return 0;
}