#include <thread>
#include <vector>
#include "run.h"
#include "workers.h"
using std::thread, std::vector;

bool test(Bakery &bakery, const OutputConfig &output) {
    cout << "\tChecking correctness of counters..." << endl; //don't mind the slash t, it's just another way to output to console.
    bool countersCorrect =
        bakery.counters.checkCorrect(output.countersInUse, State::MIXED);// calls the checkCorrect function on the counters, passing in "output.countersInUse" as the desired number and State::MIXED as the desired state.
    cout << "\tChecking correctness of ovens..." << endl; // same as before
    bool ovensCorrect =
        bakery.ovens.checkCorrect(output.ovensInUse, State::BAKING); //calls the checkCorrect function on the ovens, passing in "output.ovensInUse" as the desired number and State::BAKING as the desired state.
    cout << "\tChecking correctness of shelves..." << endl; // same as before.
    bool shelvesCorrect =
        bakery.shelves.checkCorrect(output.shelvesInUse, State::READY); //calls the checkCorrect function on the shelves, passing in "output.shelvesInUse" as the desired number and State::READY as the desired state.
    cout << std::boolalpha; // Print bools as true/false instead of 1/0.

    cout << "\tcountersCorrect: " << countersCorrect << endl; 
    cout << "\tovensCorrect: " << ovensCorrect << endl;
    cout << "\tshelvesCorrect: " << shelvesCorrect << endl;

    return countersCorrect && ovensCorrect && shelvesCorrect; //This needs to be true to pass the assignment in.
}

bool run(Config config) {
    InputConfig input = config.input; // takes the "config" struct parameter passed into the run function and stores the "input config" struct within the "config" struct in the variable "input".

    Bakery bakery{input.numIngredients, input.counterCapacity, input.ovenCapacity, input.shelfCapacity}; //Defines a Bakery object called bakery, and assigns the contents of "input" to the corresponding parameters in the constructor of bakery.

    vector<Mixer> mixers(input.numMixers, Mixer(bakery)); //creates a vector of Mixer objects with a size equal to the number of Mixers. Each Mixer is constructed with the "bakery" as a parameter (same bakery for every mixer.)
    vector<Assistant> assistants(input.numAssistants, Assistant(bakery)); //Same as above but for the Assistants.
    vector<Baker> bakers(input.numBakers, Baker(bakery)); //Same as the two above but for the Bakers.

    thread mixerThreads[input.numMixers]; //creates an array of threads called mixerThreads, with a size equal to input.numMixers. Each element of the array represents one of the mixer threads.
    thread assistantThreads[input.numAssistants]; //same as above, but for the Assistants.
    thread bakerThreads[input.numBakers]; //same as the two above, but for the Bakers.
    for (int i = 0; i < input.numMixers; i++) //this for loop iterates once for each of the mixers.
        mixerThreads[i] = thread(mixers[i]); //starts a thread of the operator of the ith mixer, and stores this thread at the ith index of mixerThreads.
    for (int i = 0; i < input.numAssistants; i++) // this for loop iterates once for each of the assistants.
        assistantThreads[i] = thread(assistants[i]); //starts a thread of the operator of the ith Assistant, and stores this thread at the ith index of assistantThreads.
    for (int i = 0; i < input.numBakers; i++) //this for loop iterates once for each of the bakers.
        bakerThreads[i] = thread(bakers[i]); //starts a thread of the operator of the ith Baker, and stores this thread at the ith index of baker threads.

    for (int i = 0; i < input.numMixers; i++)
        mixerThreads[i].join(); //blocks the current thread until mixerThreads[i] finishes its execution. 
    for (int i = 0; i < input.numAssistants; i++)
        assistantThreads[i].join(); //blocks the current thread until assistantThreads[i] finishes its execution.
    for (int i = 0; i < input.numBakers; i++) 
        bakerThreads[i].join(); //blocks the current thread until bakerThreads[i] finishes its execution.

    return test(bakery, config.output); // returns the output of the test function, with the contents of the Bakery object bakery and the contents of the Output config object config.output as its parameters.
}