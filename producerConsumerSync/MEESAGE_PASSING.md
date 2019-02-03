### Message Passing using Semaphore
##### Poblem Statement
Threre are n number of threads and thread0 sends a message to thread1, thread1 sends a message to thread2, .... , thread t-2 sends a message to thread t-1, thread t-1 sends a message to thread t and thread t sends a message to thread 0. After a thread sends a message it recives the message sent to it and prints the message and terminate.

##### Working:
- There are t message buffers one for each thread.
- Each message buffer is associated with a semaphore. All semaphores are initialized to 0 by main thread.
- Any Thread exuctes in following sequence:
  - Generate a message.
  - Copy message in message buffer of destination thread.
  - Increment the semaphore associated with message buffer of destination thread.
  - Lock the semaphore associated with its own message buffer.
  - Read the message in its own buffer.
  - Unlock the semaphore associated with its own message buffer.
  - Exit.
    
    
