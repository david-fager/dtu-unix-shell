> Danmarks Tekniske Universitet
> Operativsystemer
> Mandatory assignment 1
> David Fager
> s185120

Assignment:
https://cn.inside.dtu.dk/cnnet/filesharing/download/9e9c16bb-1776-4958-9f86-978fc7b590d0
https://cn.inside.dtu.dk/cnnet/filesharing/download/5a1bac86-c0f4-4722-bd8e-47a94549fffe

This is a readme of the mandatory assignment 1 in the 
operating systems course, where a shell had to be made.

Table of contents:
- How to run & use the shell
- What are system calls?
- How does it I/O redirect?
- The program environment
- Does it background execute?



How to run & use the shell
# To run this shell you will need a form of unix terminal, because this 
# program utilizes calls specifically for unix systems. For more on
# the running environment, see 'The program environment' in this readme.
# When you have booted up your favorite unix terminal, change the
# directory to the root folder of the program. (Use 'cd path' to get there).
# When inside the root folder, run the command: 'gcc main.c' (if prompted
# to install gcc, do so) and when the gcc has compiled the program, run it
# by calling: './a.out'.
# The program is now running in your terminal. Type 'help' for a small list 
# of commands, that the shell can understand. Other commands supported in 
# the shell include, but is not limited to: 'cd path' to change directory, 
# 'ls' to see a directory's contents, 'cat file' to see a file's contents,
# 'nano file' to edit a file from the shell and many more commands.

What are system calls?
# The central part of an operating system is its kernel, which ensures that,
# programs running on the computer can make use of the computer's hardware.
# System calls is a programs way to instruct the kernel of the operating system,
# what the program wants to have happen. These system calls is, for example,
# implemented as part of a shell, where the user can give the shell commands
# and the shell then makes requests to the kernel, through the use of system calls,
# based on the entered command(s).
# This shell utilizes the system calls: 'fork' to duplicate the shell process and
# 'execvp' to execute the user's entered command. The 'pipe' call is also used,
# to transfer data between two processes, for more on piping see 
# 'How does it I/O redirect?' in this readme.

How does it I/O redirect?
# This shell uses the system call 'pipe', which transfers data between a child of
# the shell, and that child's child (grandchild). This is done by the grandchild
# redirecting its stdout to be its own (writing) end of a pipe that the 1. child
# set up, and the 1. child redirects its stdin to its (reading) end of the pipe.
# This makes it possible for the shell to handle commands such as:
# 'cat main.c | head -7', which prints the first 7 lines of the main.c file,
# instead of the whole file. The grandchild first executes 'cat main.c' and
# writes the file contents to the pipe going to the 1. child, and that child
# then reads the file content from the pipe and executes the 'head -7', resulting
# in only the first 7 lines reaching the parent.  

The program environment
# As mentioned in 'How to run & use the shell' in this readme, the program utilizes
# system calls, or rather POSIX calls that for UNIX systems are in almost every case
# directly linked to a system call with the same function. These POSIX calls works
# in UNIX systems, in contrast to Windows' own call system, and therefore the 
# environment in which the program is run, must be a UNIX environment or another
# environment that utilizes the POSIX calls.

Does it background execute?
# The shell does a form of background program execution, or rather it runs background
# processes, without the user's knowledge. As mentioned in 'What are system calls?'
# this program uses POSIX system calls, which includes the 'fork' and 'execvp' calls.
# When the program instructs for a fork to happen, the system duplicates the programs
# main process (parent), with only a few changes. These changes include the process
# identifier of the new process (child), which makes it possible for a program to
# change the new process' course of action. This duplication of processes happens in
# the background of this shell, with the call: 'execvp' to execute and terminate the
# child process.