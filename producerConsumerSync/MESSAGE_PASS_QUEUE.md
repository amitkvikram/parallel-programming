### Message Passing between Threads
See [messagePassQueue.cpp](messagePassQueue.cpp) for the code.
##### Problem Statement:
- There are n threads and each thread has to send k(randomly generated for each thread) number of messages to some other thread. Each time thread wants to send a message, it generates the message, chooses dstination thread randomly and then sends the message.
- Each thread have a shared memory queue, each time src thread wants to send a message it enqueues in queue of destination thread and if a thread wants to receive a message it dequeue from its queue.

###### Mutual Exclusion:
- Only one thread can access a queue at a time. To ensure the mutual exclusion one unnamed semaphore is used for each queue. When a thread wants to enqueue in queue or dequeue from queue it first locks the semaphore then do some work on queue and then unlock the semaphore.
- Only one thread prints the message on termianl at a time. To ensure the mutual exclusion one semaphore is used for the terminal.

###### Possibility of Deadlock:
- Is there any possibility of deadlock when accessing the queue? Since each thread chooses destination thread randomly there might be the case that thread X sends a message to thread Y and thread Y sends a message to thread X. Can this situation cause a deadlock?
- Actually there is no possibility of deadlock because necessary HOLD AND WAIT condition for deadlock is not satisfied. Let's say queues are resources. For hold and wait condition to be satisfied A thread must be holding at least one resource and waiting to acquire additional resources. But this condition is not satisfied because one thread is acquiring at most one resource at a time and if it wants to acquire additional resource it first realeases the acquired resource. 

###### Barrier: 
- Before any thread starts message passing we want to print some initial information e.g. how many messages each thread will send.
- To ensure this we implement barrier. See [Barrier:README.md](../thread_barrier/README.md) for more information about implementation of barrier.

###### Working:
Any thread executes in the following way:
- For k(=number of messages thead will send) times:
  - generate a message.
  - Choose destination randomly.
  - Lock queue of destination thread.
  - Enqueue in queue of destination thread.
  - Unlock queue of destination thread.
  - Lock its own queue.
  - If there is any message in queue, dequeue and print it.
  - Unlock its own queue.
- Until All threads have sent messages or there is any message is current thread's queue
  - Lock its own queue.
  - If there is any message in queue, dequeue and print it.
  - Unlock its own queue.
  
##### References:
1. [An Introduction to Parallel Programming by Peter S. Pacheco](https://www.amazon.in/Introduction-Parallel-Programming-Peter-Pacheco/dp/0123742609): Concept of Producer Consumer Queue.
2. [Operating System Concepts by Silberschartz, Galvin, Gagne](https://www.amazon.in/Operating-System-Concepts-Abraham-Silberschatz/dp/0470128720): Concept of Deadlock.
