
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>



//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q3
// Date: July 15th, 2021
// Date Modified:July 15th, 2021
//
//
/////////////////////////////////////////////






void removeDups(int* in, int size);
void zero_duplicates(int* in,int size);


void printArray(int array[], int size) {
  printf("\n[");
  for (int i = 0; i < size; i++) {
    if ( i == size - 1) {
      printf("%d", array[i]);

    } else {
      printf("%d, ", array[i]);
    }

  }

  printf("]\n");

}



void zero_duplicates(int* in, int size) {
  /*
    zero_duplicates() returns none and mutates the integer array,
    in, by changing all duplicate values to 0. The integer, size, is
    the length of array, in

   */
  int current_number;
  int check_number;
  int j = 0;
  
  for (int i = 0; i < size; i++) {
    current_number = in[i];
    j = i + 1;

    if (j == size) {
      break;
    }

    while (j < size) {
      check_number = in[j];

      if (current_number == check_number) {
	in[j] = 0;
      }

      j++;
    }
  
  }

}


void removeDups(int* in, int size) {
  /*

    removeDups() returns void and mutates an integer array, in, such
    that all but the first occurrence of a number is removed. removeDups
    keeps the relative order of appearence of the numbers, and replaces
    remaining indices with 0s. The integer size, is the length of array,
    in

    removeDups: int[] int => void
    requires:

    Example:
        array[] = {1, 2, 2, 2, 3, 3, 4, 2, 4, 5, 6, 6}
        removeDups(array, 12) => void      array is mutated to {1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0}
   */

  if (size > 1) {
    printf("\ninput array: ");
    printArray(in, size);
    zero_duplicates(in, size);
    
    int j;
    for (int i = 0; i < size; i++) {
      j = i + 1;
      if (i == 0 && in[i] == 0) {
	continue;
      }

      while (in[i] == 0 && j < size) {
	if (in[j] != 0) {
	  in[i] = in[j];
	  in[j] = 0;
	} else {
	  j++;
	}
	
      }
      
      
    }

    printf("\noutput array: ");
    printArray(in, size);
  }
  
}


int main() {

  int a[] = {1, 2, 2, 2, 3, 3, 4, 2, 4, 5, 6, 6};
  int b[] = {0, 1, 3, 4, 4, 5, 1, 2, 1, 4, 0, 3};
  int c[] = {1, 2};
  int d[] = {};

  int al = sizeof(a) / sizeof(a[0]);
  int bl = sizeof(b) / sizeof(b[0]);


  removeDups(a, al);
  removeDups(b, bl);
  removeDups(c, 2);
  removeDups(d, 0);

  return 0;

}
