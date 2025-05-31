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
        // bakery.ingredientsAvail.try_acquire_for(milliseconds(200));
        // Instead of calling a semaphore's "acquire" method, you should call
        // "try_acquire_for(milliseconds(200))". See this method's description:
        

        if (!bakery.ingredientsAvail.try_acquire_for(milliseconds(200))){ //This will run if the program "DID" try to acquire an available ingredient, but it failed. Explanation:  The ! does NOT mean "there was no try to acquire an ingredient for 200 ms". it just means after trying to acquire the ingredient for 200 ms, it failed. 
            return; //The try failed, meaning no ingredients left. The Mixer has no work left to do.
        } else {
            if (bakery.countersAvail.try_acquire_for(milliseconds(200))){ //The program "Tried" to acquire a free counter space from the counters avail semaphore, and succeeded within 200ms.
                
                Bread bread; // create an instance of the bread struct as defined in the bread.h header file. 
                bread.state = MIXED; //set the state to MIXED 
                bakery.counters.add(bread); //put the bread in th
               

            }
        }

        
        
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

        //counting_semaphore<> 
        
        
        
        // STUDENTS: Once you have filled in functional code above, you should
        // remove the following line.  It serves a purpose here by making all
        // tests fail from the outset (test-driven development).
        
   }
}

void Assistant::operator()() {
    while (true) {
        // STUDENTS: See comments above in Mixer::operator().
        Bread bread;


    
        if (bakery.ovensAvail.try_acquire_for(milliseconds(200))) {
            bread.state = BAKING;
            bakery.ovens.add(bread);
            bakery.countersAvail.release(); //A counter space was acquired, used to put the bread in the oven, and now the counter space can be released.
        } else {
            bakery.counters.add(bread); //put the bread back on the counter if no spaces available.
            return;
        }

        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        
    }
}

void Baker::operator()() {
    while (true) {
        // STUDENTS: See comments above in Mixer::operator().
        Bread bread;
        if (bakery.shelvesAvail.try_acquire_for(milliseconds(200))) {
            bread.state = READY;
            bakery.shelves.add(bread);
            bakery.ovensAvail.release(); //A counter space was acquired, used to put the bread in the oven, and now the counter space can be released.
        } else { 
            bakery.ovens.add(bread);
            return;
        }

        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        
    }
}