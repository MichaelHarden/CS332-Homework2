#  Homework 2
Homework 2 traverses a directory and prints all of its content. The Flags 
`<Ssft>` can be use to change the output

`-S` prints the size of each file
`-s size` prints a file only if its size is greater than the size provided
`-f substring` prints a file only if the file name contains the substring
`-t df` if d is provided only directories are printed. if f is provided only 
        files are printed   

## Running Code
to run the code make sure homework2.c, homework.h, and Makefile are all contained
 the the directory you wish to traverse. 
1.  run the command `make`
2.  run the command `./search <Ssft> <directory>`
    directory is optional. If it is not provided the traversal will begin at
    the current directory. If it provided it must be a path to that directory.

## Sources
- I used my code from lab5 
- Portions of code from the lab 5 assignment file were used
- https://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c

