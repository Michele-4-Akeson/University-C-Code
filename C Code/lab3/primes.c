/*
primes.c:
The process created from primes.c uses POSIX threads to generate a thread that outputs all prime numbers (natural numbers greater
than 1 that are only divisible by 1 and themselves -- e.g 2, 3, 5, 7....) less than or equal to the number provided through the command
line.

The script works by:
1. Converting the number provided through the command line to an integer
2. Creating a thread via pthread_create() and having that thread execute the void* showPrimes function
   which operates to output all prime numbers less than or equal to the number provided through the command line
3. The program waits for the thread to complete via pthread_join()
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void* showPrimes(void* arg); // executed by thread to determine and output all prime numbers less than or equal to the number provided through the commandline

int main(int argc, char const *argv[])
{
    
    // the number argument provided through the command line
    int number = atoi(argv[1]);

    // the threadId to be used to create the worker trhead
    pthread_t primesThread;


    // creates a worker thread that executes void* showPrimes(), and passess &number as a argument
    pthread_create(&primesThread, NULL, showPrimes, &number);

    // sets process to wait until the primesThread has completed to continue execution of the process 
    pthread_join(primesThread, NULL);


    return 0;
}



/**
 * @brief determines and outputs all prime numbers less than or equal to the int value stored at address of arg
 * 
 * @param arg a void pointer that can be cast to the type of pointer that is being passed, allowing us to access the value passed to the thread to execute on 
 * @return void* 
 */
void* showPrimes(void* arg){
    // stores the int value stored at arg inside number - this is the number passed through the commandline
    int number = *((int*) arg);
    int count = 0;

    // iterates through numbers 2 to number and outputs all number
    // which are only divisible by 1 and the itself
    for (int i = 2; i <= number; i++){
        count = 0;
        for (int j = 2; j <= i; j++){
            if (i % j == 0){
                count++;
            }
        }

        if (count == 1){
            printf("%d\n", i);
        }
    }
}


