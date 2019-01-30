#### Named Semaphore

1. [sem_open](http://man7.org/linux/man-pages/man3/sem_open.3.html):  
    ```
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
    ```
    - if oflag = O_CREAT then semphore is created if it doesn't exist.
    - mode argument specifies permission for semaphore.
    - value specifies the initial value of semaphore.
    - If semaphore already exist then mode and value argument are ignored.
     
2. [sem_close](http://man7.org/linux/man-pages/man3/sem_close.3.html)
    ```
    int sem_close(sem_t *sem)
    ```
    - Closes open reference sem
  
3. [sem_unlink](http://man7.org/linux/man-pages/man3/sem_unlink.3.html)
    ```
    int sem_unlink(const char *sem_name)
    ```
    
    - Removes the named semaphore. 
 
 **Destory Semaphore**:
  1. sem_close closes the open reference. However when process exits all the open references are automatically closed.
