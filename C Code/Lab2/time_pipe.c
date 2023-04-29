/*
time_pipe.c:
This script uses the POSIX ordinary pipes for IPC. As a summary of the functionallity: this script records the 
elasped time required to execute a command (i.e ls) which is provided from the command line. This process
achieves this by creating pipe, and a child process that records the start time of execution, writes that data
to through the write end of the pipe, and then executes the command. Following this, the parent process waits 
until data is present at the read end of the pipe. The parent process then records the time of completeion and 
computes the elasped time from the both the start and end time of execution 

To implement this script:
A. The pipe will be created and used by both parent and child process as the pipe is 
   special type of file; child process inherit this allowing for pipes to be used for IPC

B. fork a child process that:
    1. records the timestamp of when a command will be executed via gettimeofday()
    2. executes a specified command provided through the command line
    3. writes the recorded start time of the executed command to the pipe (closes read end of pipe first)
C. Have the parent process wait for completeion of the child process via waiting for a value to be passed through 
   the write end of the pipe
    1. following this, the parent process should call gettimeofday() in order
       to record the time since the command was executed
    2. the parent process will then retrieve the recorded start time of the child process
       and compute the elasphed time (endtime - startime) / 1e6 (to convert from microseconds to seconds)


NOTE:

the elasphed time provided by timeval is either in microseconds or seconds; I divide microseconds by 1e6
to convert them to seconds  

The timeval object, which contains two fields: tv_sec and tv_usec. These represent the number of elapsed
seconds and microseconds since January 1, 1970 (epoch of UNIX)

akesonm@mcmaster.ca
*/

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#define READ_END 0
#define WRITE_END 1



int main(int argc, char* argv[]){
    /*
    check for correct number of arguments for script
    */
    if (argc != 2){
        printf("Incorrect number of arguments: expected 1, got: %d\n", argc - 1);
        return -1;
    }


    char path[] = "/bin/";
    char* command = argv[1];
    strcat(path, command);
    //printf("%s %s\n", path, command);
    struct timeval current;
    int fd[2]; // file descriptor
    pid_t forkId;

    ///////////////////////
    // CREATE PIPE
    ///////////////////////
    if (pipe(fd) == -1){
        return 1;
    } // creates pipe at address of fd -- both parent and child processes have access to this

    forkId = fork();

    if (forkId == -1){
        return 1;
    }

    if (forkId == 0){
        /* 
        child process: 
            writes timestamp of when command is executed and sends pointer to parent through write end of pipe
        */
        close(fd[READ_END]);

        gettimeofday(&current, NULL);
        //printf("start time: %ld %p\n", current.tv_usec, &(current.tv_usec));
        long int n = current.tv_usec; // time in microseconds when command execution is stared
        write(fd[WRITE_END], &n, sizeof(n)); // passes the address of n (which stores the timestamp in microseconds)
        close(fd[WRITE_END]);
        execlp(path, command, NULL);

    } else{
        /*
        parent process:
            parent waits for child process to complete as it's waiting for a value to
            be passed through the write end of the pipe

        */
        wait(NULL);
        close(fd[WRITE_END]);
        long int n;
        read(fd[READ_END], &n, sizeof(n)); // reads in the value and applies ito the the address of n
        gettimeofday(&current, NULL);

        //printf("current Time: %ld\npipe-read: %ld\n", current.tv_usec, n);
        int elasped = current.tv_usec - n; // computes time required to run execlp of command specified
        printf("Elasped Time: %f\n", elasped/1e6);
        close(fd[READ_END]);

    }

    return 0;

}