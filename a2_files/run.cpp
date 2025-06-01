#include <thread>
#include <vector>
#include "run.h"
#include "workers.h"
using std::thread, std::vector;

bool test(Bakery &bakery, const OutputConfig &output) {
    cout << "\tChecking correctness of counters..." << endl;
    bool countersCorrect =
        bakery.counters.checkCorrect(output.countersInUse, State::MIXED);
    cout << "\tChecking correctness of ovens..." << endl;
    bool ovensCorrect =
        bakery.ovens.checkCorrect(output.ovensInUse, State::BAKING);
    cout << "\tChecking correctness of shelves..." << endl;
    bool shelvesCorrect =
        bakery.shelves.checkCorrect(output.shelvesInUse, State::READY);
    cout << std::boolalpha; // Print bools as true/false instead of 1/0.

    cout << "\tcountersCorrect: " << countersCorrect << endl;
    cout << "\tovensCorrect: " << ovensCorrect << endl;
    cout << "\tshelvesCorrect: " << shelvesCorrect << endl;

    return countersCorrect && ovensCorrect && shelvesCorrect;
}

bool run(Config config) {
    InputConfig input = config.input; // takes the "config" struct parameter passed into the run function and stores the "input config" struct within the "config" struct in the variable "input".

    Bakery bakery{input.numIngredients, input.counterCapacity, input.ovenCapacity, input.shelfCapacity}; //Defines a Bakery object called bakery, and assigns the contents of "input" to the corresponding parameters in the constructor of bakery.

    vector<Mixer> mixers(input.numMixers, Mixer(bakery)); //creates a vector of Mixer objects with a size equal to the number of Mixers. Each Mixer is constructed with the "bakery" as a parameter (same bakery for every mixer.)
    vector<Assistant> assistants(input.numAssistants, Assistant(bakery)); //Same as above but for the Assistants.
    vector<Baker> bakers(input.numBakers, Baker(bakery)); //Same as the two above but for the Bakers.

    thread mixerThreads[input.numMixers];
    thread assistantThreads[input.numAssistants];
    thread bakerThreads[input.numBakers];
    for (int i = 0; i < input.numMixers; i++)
        mixerThreads[i] = thread(mixers[i]);
    for (int i = 0; i < input.numAssistants; i++)
        assistantThreads[i] = thread(assistants[i]);
    for (int i = 0; i < input.numBakers; i++)
        bakerThreads[i] = thread(bakers[i]);

    for (int i = 0; i < input.numMixers; i++)
        mixerThreads[i].join();
    for (int i = 0; i < input.numAssistants; i++)
        assistantThreads[i].join();
    for (int i = 0; i < input.numBakers; i++)
        bakerThreads[i].join();

    return test(bakery, config.output);
}