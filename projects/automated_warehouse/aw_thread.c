#include "projects/automated_warehouse/aw_thread.h"

//
// You need to read carefully thread/synch.h and thread/synch.c
// 
// In the code, a fucntion named "sema_down" implements blocking thread and 
// makes list of blocking thread
// 
// And a function named "sema_up" implements unblocing thread using blocking list
//
// You must implement blocking list using "blocking_threads" in this code.
// Then you can also implement unblocking thread.
//


struct list blocked_threads;

/**
 * A function unblocking all blocked threads in "blocked_threads" 
 * It must be called by robot threads
 */
void block_thread(){
    // You must implement this

    // Code below is example
    enum intr_level old_level;
    old_level = intr_disable ();
    list_push_back(&blocked_threads, running_thread());
    thread_block ();
    intr_set_level (old_level);
}

/**
 * A function unblocking all blocked threads in "blocked_threads" 
 * It must be called by central control thread
 */
void unblock_threads(){ 
    enum intr_level old_level;

    old_level = intr_disable();
    while (!list_empty(block_thread))
    {
        thread_unblock(list_pop_front(block_thread));
    }
    intr_set_level(old_level);
    // you must implement this
}