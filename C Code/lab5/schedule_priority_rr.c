/**
 * @file schedule_priority_rr.c
 * @author Michele akeson akesonm@mcmaster.ca
 * @brief This script executes all Tasks in the linked list referenced by mainHead using the priority round robin scheduling
 * algorithm. Note Task are provided through at .txt file which is passed as an argument via the command line
 * 
 * 
 * This scheduling algorithm works by executing Tasks in order of higest priority for the duration of their burst.
 * In the event of a tie for higest priority, each Task tied will be run using the round robin scheduling algorithm.
 * Here, each tied Task will be run for a given QUANTUM or their burst time (which ever is smaller) while their is a tie for highest
 * priority. 
 * 
 * Implementation:
 * This script uses two node pointers, mainHead, and tiedHead, each which are used to refernece the start of a linked list:
 *      mainHead: references the linked list of all Tasks to be run
 *      tiedHead: references the linked list of Tasks that are tied for the highest priority
 * 
 * schedule() is called by main, which iterates over Tasks in the linked list referneced by mainHead. On every iteration, this
 * script calls hasTies() which checks if there's a multiple Tasks tie for highest priority:
 *      - if a tie exsist, all Tasks tied for highest priority are stored in a linked list refereneced by tiedHead. Each task
 *        in this linked list is then executed in round robin fashion while a multiple Tasks are tied for highest priority
 *              - Upon completion of the Task, it is removed from both linked lists, mainHead, and tiedHead, via delete
 *      - if no tie exsists, the Task with the highest priority is selected and run for its burst
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include<unistd.h>
#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list containing all tasks
struct node *mainHead = NULL;
// reference to the head of the secondary list holding all Tasks tied for highest priority
struct node *tiedHead = NULL;
struct node *tiedPointer = NULL;


/*

PROTOTYPES:

*/


void add(char *name, int priority, int burst);
bool hasTies();
Task *pickNextTask();
void runRoundRobin();






/**
 * @brief iterates over all tasks in the linkedList of Task elements and runs
 * tasks in order of highest priority, following the priority queue with round robin
 * scheduling. 
 * 
 * Here, a task is run to completion if it has the highest priority of all tasks in the queue
 * 
 * If there is a tie for highest priority, all tasks that are tied are run using the round robin
 * scheduling algorithm; every task is run for a given quantum or for their reamining burst time
 * if that value is less than the quantum.
 * 
 */
void schedule() {
    Task* current;

    while (mainHead != NULL) {
        // if more than one task is tied for highest priority, all tasks tied
        // wiill be run via round robin with a quantum
        if (hasTies()){
            // runs all tasks tied via round robin scheduling
            runRoundRobin();
        }

        // if no tie for highest priority, the task with the highest priority is run to completeion
        current = pickNextTask();
        run(current,current->burst);
        delete(&mainHead, current);



    }
    

    
}



/**
 * @brief adds a new task to the linkedlist of tasks
 * 
 * @param name name of the task
 * @param priority the priority value of that task
 * @param burst the burst time (essentially how long it needs to be executed by the CPU)
 */
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks 
    insert(&mainHead, newTask);
}




/**
 * @brief iterates through the list referenced by mainHead, and checks if multiple
 * tasks are tied for the highest priority
 * 
 * If more than one task has the highest prioirty, all tasks which are tied for highest
 * priority are inserted into the secondary list, referneced by tiedHead
 * 
 * @return true if there is more than one task with the highest priority
 * @return false if only one task has the highest priority
 */
bool hasTies(){
    struct node *temp = mainHead->next;
    Task *task = mainHead->task;
    int count = 1;
    while (temp != NULL){
        int nextPriority = temp->task->priority;
        int currentPriority = task->priority;

        // if the task has a greater priority than the current task's priority
        // set the change the task with the highest priority
        if (nextPriority > currentPriority){
            count = 1;
            task = temp->task;

        // if a tie in priority occurs, increment count
        } else if (nextPriority == currentPriority){
            count++;
        }

        temp = temp->next;
    }


    // if a tie for lowest priority exsists
    if (count > 1){
        temp = mainHead;
        // iterates through mainHead and inserts all tasks tied for higesht priority into tiedHead list
        while (temp!=NULL){
            if (task->priority == temp->task->priority){
                insert(&tiedHead, temp->task);
            }

            temp = temp->next;

        }

        // return true if tie
        return true;
        
    }

    // return false if no tie
    return false;

}


/**
 * @brief runs all tasks in the linkedlist referenced 
 * by tiedHead using the round robin scheduling algorithm
 * 
 * Upon completeion of a tasks, that task is removed from both 
 * the linklist referenced by the mainHead, and tiedHead
 * 
 * 
 * if only one element reamins in the tiedHead list, that task is
 * executed to completeion
 */
void runRoundRobin(){
    // while the linked list of task with the highest priority isn't empty
    // run tied tasks in round robin scheduling algorithm
    tiedPointer = tiedHead;
    Task* current;
    while (tiedHead != NULL){
        current = tiedPointer->task;

        // if task is last task in list OR the burst is less than the quantum, run task to completeion
        if (tiedHead->next == NULL || current->burst < QUANTUM){
            run(current, current->burst);
            current->burst = 0;
            printf("Task %s finished.\n",current->name);

            // removes task from both main queue and the tied queue 
            delete(&mainHead, current);
            delete(&tiedHead, current);

        // run task for quantum       
        } else {
            run(current, QUANTUM);
            current->burst -= QUANTUM;
        }

        // iterate to next task in linked list
        tiedPointer = tiedPointer->next;

        // if at the end of the linked list, return to the start
        if (tiedPointer == NULL){
            tiedPointer = tiedHead;
        }    

          
    }

}



/**
 * @brief iterates over every Task in a linked list
 * whose start is reference by the global varaible, mainhead, and returns
 * the task with the highest priority 
 * 
 * @return Task* the task with the highest priority in the linkedlist
 */
Task* pickNextTask(){
    struct node *temp = mainHead->next;
    Task *task = mainHead->task;

    while(temp!=NULL){
        if (temp->task->priority > task->priority){
            task = temp->task;
        }

        temp = temp->next;

    }

    return task;
}

