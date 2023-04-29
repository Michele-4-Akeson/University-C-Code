
/*
dining.c:
This script uses POSIX mutex locks and conditional varaiables to provide a solution to the synchronization 
issues that arise from the 'Dining Philosopher' problem:

The implemented solution is as follows:
In main, 5 threads are genetred using pthread_create(), and are each set to execute the void* function runPhilosopher(), which
is passed as an argument, an integer pointer cooresponding to the index of the philosopher that thread will repersent:
-   the runPhilosopher() function initiates a while loop that results in a philosopher alternating
    between either a THINKING or EATING state after a 1-3 seconds
-   When a philosopher wants to start EATING, it will call the pickup_forks() function
    which attempts to aquire a mutex lock to check if either its left or right neighbor at
    the table is eating. If no neighbor is eating, the philosopher will be set to EATING
    and releases the aquired mutex lock

    Otherwise, the thread enters into a loop and call pthread_cond_wait() on its cooresponding
    conditional varaible canEat[i]. The use of this variable ensure that the philosopher only 
    checks to see if it can start EATING if it is signaled by a neighbor

-   When a philosopher is done EATING,and wants to be THINKING, it calls return_forks() which
    sets the calling thread's philosopher to THINKING && calls pthread_cond_signal() on both the
    left and right neighboring philosopher's conditional varaible to inform that that they can check to see of
    they can start eating (a.k.a - it signals the conditional varaible, resulting in the assoicated
    philosopher being unblocked, and completing the loop again to see if either of its neigbhors are
    eating; if it can start EATING).

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#include <time.h>

// the number of philosophers
#define SIZE 5

pthread_mutex_t mutex;

/*
global array of conditional varaible associated with the ith philosopher such that
when canEat[i] is signaled, the ith philosopher checks if they can eat
*/
pthread_cond_t canEat[SIZE];

/*
enum repersenting the a philosopher (either THINKING or EATING)
*/
enum philosopher {THINKING, EATING};

/*
global array of philosophers which are either THINKING or EATING
*/
enum philosopher philosophers[SIZE];



//////////////////////
// PROTOTYPES
/////////////////////


/**
 * @brief function to be executed by each thread, which will 
 * start the cycle of having a philosopher alternate between 
 * EATING and THINKING when chopsticks/forks are avaiable
 * 
 * @param arg pointer to the index of the philosopher
 */
void* runPhilosopher(void* arg);


/**
 * @brief sets the philosopher to EATING for a random amount of time 
 * between 1 and 3 seconds if forks are avaiaible, otherwise seting 
 * the philosopher to wait until signaled by a neighbor
 * 
 * @param philosopher_number the index of the philosopher which will be set to
 * EATING
 */
void pickup_forks(int philosopher_number);


/**
 * @brief sets the philosopher to THINKING for and signals to adjacent 
 * philosophers that that they may eat
 * @param philosopher_number he index of the philosopher which will be set to
 * THINKING
 */
void return_forks(int philosopher_number);


/**
 * @param philosopher_number the index of the philosopher checking if either of its neighbors
 * are currently in the EATING state
 * @return true if either of the neighbors are EATING
 * @return false if neither of the neigbors are EATING
 */
bool neighborsEating(int philosopher_number);


/**
 * @param i the upper limit the random number can be 
 * @return a random number between 1 and i 
 */
int getRandom(int i);


int main() {
    //creates and initalize mutex lock with default attributes
    pthread_mutex_init(&mutex, NULL);
    pthread_t philosopherThread[SIZE];

    //initializes condition varaibles
    for (int i = 0; i < SIZE; i++){
        pthread_cond_init(&canEat[i], NULL);
    }

    //creates a thread for each philosopher and provides the philospher at index i as an argument
    int id[SIZE] = {0, 1, 2, 3, 4};
    for (int i = 0; i < SIZE; i++){
        pthread_create(&philosopherThread[i], NULL, runPhilosopher, &id[i]);
    }


    //sets the process to wait for completeion of each thread before terminating the process
    for (int i = 0; i < SIZE; i++){
        pthread_join(philosopherThread[i], NULL);
    }


    return 0;
}








void* runPhilosopher(void* arg){
    //cats the arg to an int pointer and retrieves the value at that address
    int p = *((int*) arg);

    while (true){
        //philosopher thinks for 1-3 seconds
        sleep(getRandom(3));
        //philosopher tries to pick up forks to eat
        pickup_forks(p);
        //philosopher puts forks back down and signals neighbors that they may eat
        return_forks(p);
    }
      

}


void pickup_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);
    while (neighborsEating(philosopher_number)){
        /*
        sets the philosopher to waut to check if its neighbors
        are eating, where the condtion is only check if signaled by 
        neighbor
        */
       printf("%d: waiting to eat..\n", philosopher_number);
       pthread_cond_wait(&canEat[philosopher_number], &mutex);
    }
    //sets philosopher to be EATING
    printf("%d: eating..\n", philosopher_number);
    philosophers[philosopher_number] = EATING;

    pthread_mutex_unlock(&mutex);


    //sets thread to sleep for 1-3 seconds
    sleep(getRandom(3));

    
}


void return_forks(int philosopher_number){
    pthread_mutex_lock(&mutex);
    philosophers[philosopher_number] = THINKING;
    //signals philospher to the left that they may start eating
    pthread_cond_signal(&canEat[(philosopher_number + 4) % SIZE]);
    //signals philospher to the right that they may start eating
    pthread_cond_signal(&canEat[(philosopher_number + 1) % SIZE]);
    printf("%d: done eating..\n", philosopher_number);
    pthread_mutex_unlock(&mutex);

}









/*
HELPER FUNCTIONS
*/



bool neighborsEating(int philosopher_number){
    bool leftEating = philosophers[(philosopher_number + 4) % SIZE] == EATING;
    bool rightEating = philosophers[(philosopher_number + 1) % SIZE] == EATING;

    return leftEating || rightEating;

}



int getRandom(int i){
    srand(time(NULL));

    return (rand() % i) + 1;
}





