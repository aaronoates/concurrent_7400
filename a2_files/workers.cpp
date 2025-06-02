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
            if (bakery.countersAvail.try_acquire_for(milliseconds(200))){ //The program "Tried" to acquire a free counter space from the counters avail semaphore, and succeeded within 200ms. For the first set of configs, it was once 5 spots, and is now 4.
                
                Bread bread; // create an instance of the bread struct as defined in the bread.h header file. 
                bread.state = MIXED; //set the state to MIXED 
                bakery.counters.add(bread); //calls the add function of buffer.h, which first locks access to the "counters" bread buffer so that no other threads can access "counters" while add() is running. If the size of the queue is less than the capacity of the "counter", the "bread" object is added to the queue. Else, it throws a runtime error. Finally, access to this buffer is unlocked again so other threads can access it.
                bakery.counterItems.release(); //There is now an item on the counter, so increment this semaphore.

            } else {
                bakery.ingredientsAvail.release(); //There was an ingredient acquired, but no counter space was available. Therefore, we have to re-release the ingredient since it was never actually used.
                return;
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
        if (!bakery.counterItems.try_acquire_for(milliseconds(200))) {
            return; //There are no items on the counter, therefore the assistant has no work to do.
        } 
        

        
    
        if (bakery.ovensAvail.try_acquire_for(milliseconds(200))) { //If there is an oven available, this line will be true.
            Bread bread = bakery.counters.remove(); //Have to remove the bread from the counter before putting it in the oven.
            bread.state = BAKING; //this bread is now baking
            bakery.ovens.add(bread); //Put the bread in the oven after it comes off the counter.
            bakery.countersAvail.release(); //A counter space was acquired, used to put the bread in the oven, and now the counter space can be released.
            bakery.ovenItems.release(); //The bread was put in the oven.
        } else {
            bakery.counterItems.release(); //If there is no ovens available, put the item back on the counter.
            return;
        }

        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        
    }
}

void Baker::operator()() {
    while (true) {
        // STUDENTS: See comments above in Mixer::operator().
        if (!bakery.ovenItems.try_acquire_for(milliseconds(200))) {
            return; //If there are no items in the oven, then the Baker has no work to do.
        }

        if (bakery.shelvesAvail.try_acquire_for(milliseconds(200))) {
            Bread bread = bakery.ovens.remove(); //have to remove the bread from the oven befroe putting it on the shelf.
            bread.state = READY; //this bread is now ready
            bakery.shelves.add(bread); //put the bread on the shelf after taking it out of the oven.
            bakery.ovensAvail.release(); //An oven space was acquired, used to bake the bread, and now the oven space is free.
            bakery.shelfItems.release(); //The bread is put on the shelf.
        } else {
            bakery.ovenItems.release(); //There was an oven item acquired, but no available shelves. Therefore, put the bread back in the oven.
            return;
        }
        
        // STUDENTS: See the comment at the bottom of Mixer::operator().
        
    }
}