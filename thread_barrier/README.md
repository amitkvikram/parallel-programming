## THREAD BARRIER
**Wikipedia Definition:** In parallel computing, a barrier is a type of synchronization method. A barrier for a group of threads or processes in the source code means any thread/process must stop at this point and cannot proceed until all other threads/processes reach this barrier.

- [threadBarrier1.cpp](threadBarrier1.cpp) implements thread barrier using counting semaphore. 
  - Logic is to keep a *counter* of how many threads reached barrier point. A thread is locked by calling sem_wait() when it reaches barrier point and *counter* is incremented by 1. However when last thread(when counter = number of thread) reaches barrier point semaphore is incremented (number of thread - 1) times so that all threads can proceed further.

- [threadBarrier2.cpp](threadBarrier2.cpp) implements thread barrier using binary semaphore.
  - Logic is to keep a *counter* of how many thread reached barrier points. A thread is locked by calling sem_wait() when it reaches barrier point and *counter* is incremented by 1. However when last thread (when *counter* = number of thread) reaches barrier point semaphore is incremented by 1 so that one more thread(which is blocked) can proceed, then thread which gets chance to proceed will increment semaphore by 1 and the one more thread can proceed and then this thread increments the semaphore and so on.

- [threadBarrier3.cpp](threadBarrier3.cpp) implements thread barrier with busy_waiting and a mutex
    - Loginc is to keep *counter* of how many thread reached barrier points. A thread locks mutex increments *counter* by 1 then unlocks mutex and then waits in a loop until counter is less than number of thread. However when last thread reaches barrier point counter becomes equal to number of thread hence all thread can come out of the busy_wait.