#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<assert.h>


//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q6
// Date: July 17th, 2021
// Date Modified:July 17th, 2021
//
//
/////////////////////////////////////////////




int isEmpty(const long *start, const long *end);
void push(long **start, long **end, long value);
long pop (long **start, long **end);

void printStack(long **start, long **end) {
    printf("Stack --> [ ");
    if (!isEmpty(*start, *end)) {
        for (int i = 0; *start + i < *end; i++) {
            printf("%ld ", (*start)[i]);
        }
    } 
    printf("]\n");
}




int isEmpty(const long *start, const long *end) {
  /*
    isEmpty() returns an integer value of 1 if the stack
    referenced by pointers *start and *end is empty, returning
    0 otherwise

    the stack is considered empty if:
        1. *start and *end store the same memory address
	2. *start or *end are equal to null

   isEmpty: long* long* => int
   requirs:
   */
 
  if ((start == end) || (start == NULL || end == NULL)) {
    return 1;

  } else {
    return 0;
    
  }
  
}




long pop(long **start, long **end) {
  /*
    pop() returns the top element of the stack referenced by pointer
    *start. If the stack is empty, a value of 0 is returned

    pop: long** long** => long
    requires:
   */
  if (isEmpty(*start, *end)) {
    return 0;
   

  } else {
    int block_index = 0;
    int block_count = 1;
   
    while ((*start + block_index) != *end) {
      block_index++;
      block_count++;
    }

    long pop_output = (*start)[block_index - 1];
    *start = (long*) realloc(*start, (block_count-2) * sizeof(long));
    *end = *start + (block_count - 2);


    return pop_output;
    
  
  }
  

}





void push(long **start, long **end, long value) {
  /* 
     push() returns void, and creates a stack containing one element of type long, value, if the stack 
     referenced at *start is empty. Otherwise, push() reallocates more memory to the stack and appends
     value to the top of the stack, changing the memory address stored by ponter *end to the next memory 
     address following the top of the stack
     
     double pointers:
     **start => &start
     *(**start) => address of stack

   */

 
  if (isEmpty(*start, *end)) {
   *start = (long*) malloc(sizeof(long)); // creates a stack of size 1;
   *start[0] = value;
   *end = *start + 1; // sets end_block to point to memory block following top of stack

  } else {
    int block_index = 0;
    int block_count = 1;
    
    while ((*start + block_index) != *end) {
      block_index++;
      block_count++;

    }

    *start = (long*) realloc(*start, (block_count) * sizeof(long));
    (*start)[block_index] = value;
    *end = *start + block_count;


  }

}








int main () {
    printf("Starting...\n");
    long *start = NULL;
    long *stop = NULL;
    printStack(&start, &stop);
    push(&start, &stop, 1L);
    printStack(&start, &stop);
    push(&start, &stop, 2L);
    printStack(&start, &stop);
    push(&start, &stop, 3L);
    printStack(&start, &stop);
    push(&start, &stop, 4L);
    printStack(&start, &stop);
    push(&start, &stop, 5L);
    printStack(&start, &stop);
    
    long out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    
    out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    
    out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    
    out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    
    out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    
    out = pop(&start, &stop);
    printf("popped %ld\n", out);
    printStack(&start, &stop);
    

    /**** EXPECTED OUTPUT
	 Starting...
	 Stack --> [ ]
	 Stack --> [ 1 ]
	 Stack --> [ 1 2 ]
	 Stack --> [ 1 2 3 ]
	 Stack --> [ 1 2 3 4 ]
	 Stack --> [ 1 2 3 4 5 ]
	 popped 5
	 Stack --> [ 1 2 3 4 ]
	 popped 4
	 Stack --> [ 1 2 3 ]
	 popped 3
	 Stack --> [ 1 2 ]
	 popped 2
	 Stack --> [ 1 ]
	 popped 1
	 Stack --> [ ]
	 popped 0
	 Stack --> [ ]
	 
    ******/


}





