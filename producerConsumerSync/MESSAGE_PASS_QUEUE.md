### Message Passing between Threads
See [messagePassQueue.cpp](messagePassQueue.cpp) for the code.
##### Problem Statement:
- There are n thread and each thread has to send k(randomly generated for each thread) number of messages to some other thread. Each time thread wants to send a message, it generates the message, choose dstination thread randomly and then sends the message.
- Each thread have a shared memory queue, each time src thread wants to sends message it enqueues in queue of destination thread and if a thread wants to receive a message it dequeue from its queue.

###### Mutual Exclusion:
- Only one thread can access a queue at a time. To ensure the mutual exclusion one unnamed semaphore is used for each queue. When a thread want to enqueue in queue or dequeue from queue it first locks the semaphore then do some work on queue and then unlock the semaphore.
- Only one thread prints the message on termianl at a time. To ensure the mutual exclusion one semaphore is used.
