##### Task: Simulate Hare and turtoise race using processes.

- There will be four processes named Hare, Turtoise, God and Reporter
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
  - God process wakes up and asks user if they want to reposition the Hare and turtoise. If user inputs yes then God reas values from terminal and tell hare and turtoise to update their poistion. 
  - Reporter process wakes up and prints current position of hare and turtoise.
  
  **Process Communication**:
  - Communication between processes is done using pipes.
