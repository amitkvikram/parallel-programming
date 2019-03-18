Parallelize Text Editor_. 

### Task: 
Task is to parallelize a given serial text editor. Serial version of the text editor can be created by following this tutorial [KiloTextEditor](https://viewsourcecode.org/snaptoken/kilo/index.html). 

#### What to parallelize
Although the serial version of editor is working fast enough but if we try to open a large file then because of large I/O it takes few seconds to load. Similarly while saving a large file it can take few seconds. File Saving and File Opening tasks can be parallelized to improve the speed of editor.
 - File Opening: We create a thread to load the file. Main thread waits until at least 1000 lines of file has been loaded in memory. Once 1000 lines are loaded the file is displayed. Other thread keeps on loading the file in the memory. 
 - File Saving: We create a thread to save the file. When user saves file, main thread first convert file data in a single string. Then we create another thread which writes data to file. 
 
 ### Result
 We have seen significant improvement while opening large files. 
 
 ### How to run:
 
