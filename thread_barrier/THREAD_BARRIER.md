## THREAD BARRIER
**Wikipedia Definiotion:** In parallel computing, a barrier is a type of synchronization method. A barrier for a group of threads or processes in the source code means any thread/process must stop at this point and cannot proceed until all other threads/processes reach this barrier.

- [threadBarrier1.cpp](threadBarrier1.cpp) implements thread barrier using counting semaphore. 
  - Logic is to keep a counter of how many threads reached barrier point. A thread is locked by calling sem_wait() when it reaches barrier point and counter is incremented by 1. However when last thread(when counter = number of thread) reaches barrier point semaphore is incremented (number of thread - 1) times so that all threads can proceed further.
