### Message Passing between Threads
##### Problem Statement:
- There are n thread and each thread has to send k(different for each thread) number of messages to some other thread. Each time a source thread chooses its destination thread randomly. 
- Each thread have a shared memory queue, each time src thread wants to sends message it enqueues in queue of destination thread and if a thread wants to receive a message it dequeue from its queue.

