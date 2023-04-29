/**
 * @file schedule_sjf.c
 * @author michele akeson akesonm@mcmaster.ca
 * @brief This script executes all Tasks in the linked list referenced by mainHead using the shortest job first 
 * scheduling algorithm. Note Task are provided through at .txt file which is passed as an argument via the command line
 * 
 * This algorithm works by selecting the Task with the shorest burst time in the list 
 * of Tasks and running that task for an amount of time equal to its burst time (to completeion). After completeion
 * of a task, that task is removed from the list of Tasks, and the next shortest job is selected to be run
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the linked list of Tasks
struct node *head = NULL;


/*
PROTOTYPES:
*/


Task *pickNextTask();
void add(char *name, int priority, int burst);



/**
 * @brief iterates over all tasks in the linkedList of Task elements
 * and runs each task using the shortest job first (sjf) schduling algorithm
 * 
 * This algorithm invloves selecting the task with the shortest burst time
 * to be executed next by the CPU
 * 
 */
void schedule() {
    Task *current;

    // iterates over all elements in the task linkedlist and runs the task with the shortest burst value
    // on each iteration
    while (head != NULL) {
        // assigns current to be the task with the shortest burst time in the task list
        current = pickNextTask();

        //runs the task, current, for given amount of time equal to its burst time
        run(current,current->burst);

        // removes the current task from the linked list as it has completed execution
        delete(&head, current);
    }
}




/**
 * @brief adds a new task to the linked list of tasks
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
    insert(&head, newTask);
}


/**
 * @brief iterates over every Task in a linked list whose start is reference by the 
 * global varaible, head, and returns the task with the shortest (smallest) burst value 
 *  
 * @return Task* the task with the shortest burst time in the linkedlist
 */
Task* pickNextTask(){
    struct node *temp = head->next;
    Task *task = head->task;

    // iterates over list of tasks and sets task to be the task with the smallest burst time
    while(temp!=NULL){
        // compares two tasks based on burst time and sets task to be the minimum of those tasks
        if (task->burst > temp->task->burst){
            task = temp->task;
        } 

        // iterates temp to be the next node in the list of tasks
        temp = temp->next;
    }

    // returns the task with the shortest burst time
    return task;
}

