### Task: Simulate Hare and turtoise race using processes.

- There will be four processes named Hare, Turtoise, God and Reporter
- There is one master process which will fork all the four processes.
- Hare process will represent hare.
- Turtoise process will represent turtoise.

God Process:
  - God process can reposition hare and turtle by reading values from the terminal.
 
 Reporter Process:
  - Reporter porcess should pring current position of hare and turtoise on terminal.
  
  **Working**:
  - Running of each process is done in while loop.
  - In each iteration first hare process takes a step(depeding on the step size of hare) then it tells turtoise process to take one step.
  - In each iteration before taking any step, hare and turtoise process check if God has reposition them. If god has reposition them then they update their current position to the values assigned by God.
  - God process wakes up and asks user if they want to reposition the Hare and turtoise. If user inputs yes then God read values from terminal and tell hare and turtoise to update their position. 
  - Reporter process wakes up and prints current position of hare and turtoise.
  
  **Process Communication**:
  - Communication between processes is done using pipes.
  - [Pipes](http://man7.org/linux/man-pages/man2/pipe.2.html) provide one way communication. One end of pipe works as a writer and other end of pipe works as reader.
  - By default reading from pipe is blocking but one can change the setting using following command:
    ``` fcntl(pipeFileDescripor, F_SETFL, O_NONBLOCK);```
  - 6 pipes are used: 
      - hareToTurtle: Hare is writer and turtle is reader. After taking one step hare tells turtoise to take one step by writing  in pipe. Turtoise will be waiting for message from hare in blocking mode. Once hare writes the message turtoise reads it and take one step. 
       - turtoise to Hare. Turtoise is writer and Hare is reader. After taking one step turtoise tells hare to take one step by writing in pipe. Hare will be waiting for message from turtoise in blocking mode.Once turtoise writes the message hare reads it and take one step.
       - gotToTurotise: God is writer and Turtoise is reader. God writes position where it wants to reposition the turtoise(by reading values from terminal), if god doesn't want to reposition turtoise it writes -1 in the pipe. Turtoise waits for reading the data from this pipe in blocking mode.
       - godToHare: God is writer and Hare is reader. God writes position where it wants to reposition the hare(by reading values form terminal), if god doesn't want to repostion hare it writes -1 in the pipe.
       - hareToReporter: Hare is wirter and Reporter is reader. Hare process writes position of both Hare and Turtoise in this pipe. Reporter reads from this in **non blocking mode** and after reading prints on terminal.
       - hareToMaster: Hare is writer and Master is reader. After forking all the processes hare reads from this pipe in blocking mode. When race is finished hare writes time taken by hare and turtoese to this pipe. After reading from this pipe master decides which is winner.
     
 #### Challenges
 1. ##### Reporter should print current position:
    * After turtoise and hare both have taken one step, hare writes position of both of the in pipe hareToReporter. But reporter will not get scheduled after each step hence wehen reporter is scheduled there are many positions in the pipe hareToReporter. Reporter should print the most recent data. Since pipe is a FIFO(conceptually) hence reporter will have to read and throw data from pipe until only one data is left in the pipe and then print the last data to terminal.
    * To acheive this reading from pipe hareToReporter is set to be non blocking. Reporter keeps on reading from pipe until there is no data and then prints the last available data.
   
2. ##### Named semaphore should be handled properly:
    * Kernel doesn't explicitly removes named semaphore. However if sem_unlink() is called then semaphore is destoyed if there is no open reference to the semaphore and if there are open references to the semaphore then it will be destroyed when all the open references are closed. Open refrences are closed by calling sem_close and also OS will  explicitly close it when process exits.
    * 
