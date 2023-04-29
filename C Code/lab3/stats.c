/*
stats.c:
The process created from stats.c uses POSIX threads to calculate statistical values from a list of numbers provided through the 
command line, and then outputs those values to the console. This script generates 3 worker threads via pthread_create():
-	The first thread works to calculates the average value (as an int) of the list of numbers provided through the command line
-	The second thread works to calculate the maximum value of the list of numbers provided through the command line
-	The third and thread will work to calculate the minimum maximum value of the list of numbers provided through the command line


After the creation of each thread, the program will wait for the completion of each thread via calling pthread_join(thread_id) to wait for 
the thread with the corresponding thread id to complete its execution before continuing execution of the program 

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// max, min, and mean, are global varaibles; this are visible and accessible by all threads created by this process as they all have a shared address space
// each variable cooresponds to its statistical value in the list of numbers of the command line
int max, min, mean;

// the number of numbers passed through the command line - global to assist threads 
// in iterating through array and not exceeding memory address of the array 
int size;

void* maximum(void* argument); // executed by thread to calculate the maximum value from the list of numbers provided through the command line, which is stored in the global int variable, max
void* average(void* argument); // executed by thread to calculate the average value from the list of numbers provided through the command line which is stored in the global int variable, mean
void* minimum(void* argument); // executed by thread to calculate the minimum value from the list of numbers provided through the command line which is stored in the global int variable, min


int main(int argc, char const *argv[]) {

    
    size = argc-1;

    
    // int[] storing numbers passed through command line
    int numbers[size];

    // threadIds that will be assigned threads
    pthread_t maxThread, averageThread, minThread;

    //iterates through all numbers 
    for(int i = 1; i < argc; i++){
        numbers[i-1] = atoi(argv[i]);
    }

    // creates thread to get the maximum value from numbers provided from the command line
    // the address of the first integer in the numbers array is passed as an argument to the void* maximum function
    pthread_create(&maxThread, NULL, maximum, &numbers); 

    // creates thread to get the average value of numbers provided from the command line
    // the address of the first integer in the numbers array is passed as an argument to the void* average function

    pthread_create(&averageThread, NULL, average, &numbers);  

    // creates thread to get the minimum value of numbers provided from the command line
    // the address of the first integer in the numbers array is passed as an argument to the void* minimum function

    pthread_create(&minThread, NULL, minimum, &numbers);  

    // sets parent thread to wait for each thread to complete before continuing execution
    pthread_join(maxThread, NULL); 
    pthread_join(averageThread, NULL);
    pthread_join(minThread, NULL);


    // after all threads have terminated, the statistical values are outputted to the console
    printf("The average value is %d\n", mean);
    printf("The mininmum value is %d\n", min);
    printf("The maximum value is %d\n", max);




    return 0;
}


/**
 * @brief iterates through the array of numbers and
 * determines the maximum value in that array
 * 
 * @param argument an int[]
 * @return void* 
 */
void* maximum(void* argument){
    // void* argument must be cast to the type of what's passed
    // in this case, we are passing a int pointer, being the start of our numbers[] array
    int* nums = (int*) argument;

    int currentMax = 0;

    for (int i = 0; i < size; i++){
        if (nums[i] > currentMax){
            currentMax = nums[i];
        }
    }

    max = currentMax;
    
}


/**
 * @brief iterates through the array of numbers and
 * determines the average of values in that array
 * 
 * @param argument an int[]
 * @return void* 
 */
void* average(void* argument){
    // void* argument must be cast to the type of what's passed
    // in this case, we are passing a int pointer, being the start of our numbers[] array
    int* nums = (int*) argument;
    int sum = 0;

    for (int i = 0; i < size; i++){
        sum += nums[i];
    }

    mean = (int) sum/size;
    


}



/**
 * @brief iterates through the array of numbers and
 * determines the minimum of values in that array
 * 
 * @param argument an int[]
 * @return void* 
 */
void* minimum(void* argument){
    // void* argument must be cast to the type of what's passed
    // in this case, we are passing a int pointer, being the start of our numbers[] array
    int* nums = (int*) argument;
    int currentMin = nums[0];

    for (int i = 0; i<size; i++){
        if (nums[i]<currentMin){
            currentMin = nums[i];
        }
    }

    min = currentMin;
    
}





