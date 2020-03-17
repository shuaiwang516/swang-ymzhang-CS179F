# Project of virtual memory on [XV6](https://github.com/mit-pdos/xv6-public) #

 ## Introduction
 
Senior Design of CS179F Winter 2020 under the supervision of Professor Heng Yin at University of California Riverside. 
Implemented virtual memory on XV6.<br>
* Copy-on-Write
* mmap
* ASLR

 ## Setup and Compilation
 
  ### Setup a container on [Docker](https://hub.docker.com/r/ws7474741/ucr-cs179f) (Recommand)

Pull the Docker image
```
$ docker pull ws7474741/ucr-cs179f
```
Run your container
```
$ docker run -it ws7474741/cs179f
$ cd ~/swang-ymzhang-CS179F 
```
 Now, you are in the directory of the project. Use qemu to boot the xv6 and do all the tests on it.
 To compile the project and boot the XV6, run the command:
```
$ make qemu-nox
```
 Now, XV6 has booted. You can do all the tests on it.
 
 ### Setup on your own machine (Not Recommand)
 Firstly following [here](https://www.cs.ucr.edu/~csong/cs153/19f/xv6.html#getting-started-vm) to setup your own machine.
 
 Secondly use Git to clone all the code to your own machine: 
 ```
 $ git clone https://github.com/ws7474741/swang-ymzhang-CS179F.git
 $ cd swang-ymzhang-CS179F 
 ```
 Now, you are in the directory of the project. Use qemu to boot the xv6 and do all the tests on it.
 To compile the project and boot the XV6, run the command:
```
$ make qemu-nox
```
 Now, XV6 has booted. You can do all the tests on it.
 

 ## Project Content
 
 ### Copy-on-Write
 
 In XV6, fork() function uses copyuvm() method to copy parent process’s page tables and allocates new physical pages. 
 It returns a new identical pgdir for the child process.<br>
 
 Copy on Write is kind of resource management technique. The child process will not allocate new physical pages after created. 
 It will point to the parent process’s physical address. Additionally, both the pages of parent and child process will be 
 set to be read-only. Once the process is trying to write, the operating system will detect the behavior and trap a page fault,  
 which will create a new physical page for the process. That is Copy-on-Write, which can save resources significantly for unmodified copies.<br>
 
 To test Copy-on-Write, run the command:
 ```
$ cowtest
 ```
 
  ### mmap
  
  mmap maps files into memory. It is a method of memory-mapped file I/O. It implements demand paging, because file 
  contents are not read from disk directly and initially do not use physical RAM at all. The actual reads from disk are 
  performed in a "lazy" manner, after a specific location is accessed. <br>
  
  To test mmap, run the command:
  ```
 $ mmaptest
  ```
 
  ### ASLR
  
  In XV6, Text and Code grow from 0 of a process's address space. The stack grows right above the code and text and the 
  heap grows right above the stack.<br>

  Address Space Layout Randomization (ASLR) is a computer security technique which involves randomly positioning the base 
  address of an executable and the position of libraries, heap, and stack, in a process's address space.<br>

  We also implement the growing of the stack. In XV6, stack only has one page size. Now, the stack can be grown if needed.
  We write a recursive function to expand the size of the stack.
  
  To test ASLR, run the command:
  ```
 $ aslrtest <# an integer number >
  ```
 The test program will not only show the random position of the stack and the heap but also
 show the sum from 1 to the number you input. The number of stack pages will also be shown after that.
