## PTHREAD

**Interface:**
- Every thread has a thread id. A thread id is represented by pthread_t datatype.
- To compare tow thread id, pthread_equal function is used.
  ```
  int pthread_equal( pthread_t tidp1, pthread_t tidp2)
  ```
  Returns non zero if equql, 0 otherwise.
- New thread can be created by calling [pthread_create](http://man7.org/linux/man-pages/man3/pthread_create.3.html).
  ```
  int pthread_create( pthreada_t *tidp, 
                      const pthread_attr_t * restrict attr, 
                      void *(*start_rtn)(void*), 
                      void *restrict arg)
  ```
  Return 0 if OK, error number on failure.

**Thread Termination:**
- If any thread withing the process call exit, \_Exit or \_exit 0R main thred calls return then entire **process** terminaties.
- Similarly when default action is to terminate the process, a signal setn to a thread will terminate the entire process.
- A single thread can exist in three ways:
  - The thread can simply return from the statrt routine. The return value is thread's exit code.
  - The thread can be canceled by another thread in *same process*.
  - The thread can call pthread_exit.
  ```
  void pthread_exit( void *rval_ptr )
  ```
    rval_ptr is available to othere threads in the process by calling pthread_join.
    
**A thread can run in two modes**:
- Joinable Mode
- Detached Mode
- By default a thread runs in joinable mode. However a thread can be created in detached mode.

**Joining Thread**:
- A joinable thread can be joined by calling:
```
int pthread_join( pthread_t thread, void **rval_ptr)
```
  - pthread_join is blocking call and blocks the calling thread until target thread exits.
  - If the thread has already terminated then pthrea_join returns immediately. Calling pthread_join for a terminated thread release system resource of thread. 
  - Calling pthred_join will aoutomatically place the thread with which we're joining in detach mode.

**Detach Thread**:
- A joinable thread can be detached by calling:
```
int pthread_detach( pthread_t tid)
```
Usually istead of calling pthread_detach, thread is created in detached state.

**Resource Release of a Thread**:
- When a thread exits then system resources of thread will be release if thread is in deatch state(or mode). If thread is not in detach state then thread's termination state is retained until we call pthread_join on that thread.
- Either pthread_join or pthread_detach should be called for each thread that an appliction creates, so that resources for the thread can be released once the thread terminates.
- When process exits all the thread are terminated and system resources of thread are released regardless of state of thread.
