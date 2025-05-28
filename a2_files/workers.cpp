#include "workers.h"

// STUDENTS: Implement the operator() methods for the Mixer, Assistant, and Baker.
// Note that only the mixer should change a bread's state from UNMIXED to MIXED,
// only an assistant should change a bread's state from MIXED to BAKING, and only a
// baker should change a bread's state from BAKING to READY.

void Mixer::operator()() {
    while (true) {
        // STUDENTS: Implement the body of this method.  You should acquire the
        // necessary semaphores, make the appropriate changes to the buffers
        // (counters, ovens, shelves), including changing the state of the
        // bread, then release the necessary semaphores.
        //
        // Instead of calling a semaphore's "acquire" method, you should call
        // "try_acquire_for(milliseconds(200))". See this method's description:
        //
        // https://en.cppreference.com/w/cpp/thread/counting_semaphore/try_acquire_for.html
        // 
        // Why not call "acquire" as we've seen in the notes? The issue is
        // termination. At some point, each worker thread will have no work to
        // do. If we used plain "acquire" it would wait forever for the needed
        // resource---even if it was never going to come. By using 
        // "try_acquire_for" we have a built-in timeout. If the timeout expires
        // we give up and return, letting the thread terminate.
        //
        // As such, you should check the return value of "try_acquire_for". The 
        // return value being false indicates that the thread should end its 
        // work.  This does not indicate an error condition, but is a normal 
        // part of the program's operation.


        
        // STUDENTS: Once you have filled in functional code above, you should
        // remove the following line.  It serves a purpose here by making all
        // tests fail from the outset (test-driven development).
        return;
   }
}

void Assistant::operator()() {
    while (true) {
        // STUDENTS: See comments above in Mixer::operator().


        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        return;
    }
}

void Baker::operator()() {
    while (true) {
        // STUDENTS: See comments above in Mixer::operator().


        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        return;
    }
}