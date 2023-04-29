/*
time_shm.c:
This script uses the POSIX shared memory for IPC. As a summary of the functionallity: this script records the 
elasped time required to execute a command (i.e ls) which is provided from the command line. This process
achieves this by creating a shared memory object, and then a child process that records the time of execution, 
passes that data into shared memory, and then executes the command. Following this, the parent process waits until this is complete, records
the time of completeion and computes the elasped time from the both the start and end time of execution  

To implement this script:
A. Create shared memory object to be used by parent and child processes
B. fork a child process that:
    1. records the timestamp of when a command will be executed via gettimeofday()
    2. executes a specified command provided through the command line
    3. stores the recorded start time of the executed command in shared memory
C. Have the parent process wait for completeion of the child process via wait()
    1. following this, the parent process should call gettimeofday() in order
       to record the time since the command was executed
    2. the parent process will then retrieve the recordedstart time of the child process
       and compute the elasphed time (endtime - startime) / 1e6 (to convert from microseconds to seconds)



NOTE:

the elasphed time provided by timeval is either in microseconds or seconds; I divide microseconds by 1e6
to convert them to seconds  

The timeval object, which contains two fields: tv_sec and tv_usec. These represent the number of elapsed
seconds and microseconds since January 1, 1970 (epoch of UNIX)

akesonm@mcmaster.ca
*/



#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

const int SIZE = 4096; // size in bytes of the "shared memory object"

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
    printf("%s %s\n", path, command);
    pid_t forkId;
    struct timeval current;
    int fd; // file descriptor 
    char* name = "timeshare"; // name of shared memory file
    char* object_prt; // pointer to shared memory object

    ///////////////////////////////
    // CREATE SHARED MEMORY OBJECT
    ///////////////////////////////

    // creates the Shared memory object (O_CREATE) if it doesn't already exsists, or sets it to read/write (O_RDWR) if does
    fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

    // sets size of shared memory object
    ftruncate(fd, SIZE); 

    // memory map to the shared memory object - establishes the memory mapped file containing shared memory object
    // returns point to the memory mapped file
    object_prt = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 

    //Create child
    forkId = fork();

    if (forkId < 0){
        return 1;

    }

    if (forkId == 0){
        /*
        child process:
            - records start time of execution of a command 
            - executes specified command through execlp() 
        */

       // records time of day to timeval struct
        gettimeofday(&current, NULL);

        // sprintf writes to shared memory address
        sprintf(object_prt, "%ld\n", current.tv_usec);

        //printf("start time: %ld\n", current.tv_usec); 
        //exec() delete the current process with the specified one 
        execlp(path, command, NULL);
        return 0;

    } else {
        /*
        parent process: 
            - waits for child process to terminate
            - records time; the end time of the execution of the command
            - computes the time that has elasped since execution of command; time take for command to run
        */
        wait(NULL); // waits for child process to complete
        gettimeofday(&current, NULL); // gets timestamp when child process completes


        //printf("end time: %ld\nstart time: %s\n", current.tv_usec, (char*) object_prt);
        int elasped = current.tv_usec - atoi((char*) object_prt); // computes time required to run execlp of command specified
        printf("Elasped Time: %f\n", elasped/1e6); // converts from microseconds to seconds

    }

    return 0;
}