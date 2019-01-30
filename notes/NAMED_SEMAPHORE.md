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
  1. sem_close: closes the open reference. However when process exits all the open references are automatically closed.
  2. sem_unlink(): removes the semaphore name immediately. Semaphore is destroyed immediately if there are no open reference to the semaphore. If there are open references when sem_unlink is called then sempahore is destroyed once all references are closed(remember that you don't have to call sem_unlik again).
  3. So For semaphore to be destroyed sem_unlink must be called once before process exits.
  
  **Life Scope of Semaphore**:
- if *sem_unlink* is not called explicitly then semaphore exists untill system reboots.
- Semaphore value is saved across processes. So if you create a semaphore and when you exit from process semaphore value is x then next time you open semaphore anywhere its initial value will be x(Remember that since semaphore is already created then value argument in sem_open is ignored).
- Run program
