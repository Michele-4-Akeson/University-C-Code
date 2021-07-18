#include <stdio.h>
#include <assert.h>
#include <math.h>



//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q4
// Date: July 15th, 2021
// Date Modified:July 15th, 2021
//
//
/////////////////////////////////////////////




int bubblesort(int* x, int size);
void swap(int* x, int m, int n);


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




void swap(int* x, int m, int n) {
  /*
    swap() mutates the integer array, x, by swaping
    elements located at index m, and index n

    swap: int[] int int => void
    requires:

   */
  int temp = x[m];
  x[m] = x[n];
  x[n] = temp;
  
}



int bubblesort(int* x, int size) {
  /*
    bubblesort() mutates the integer array, x, into acending order,
    and returns the total number of swaps made as an integer. bubblesort 
    makes n-1 passes of the array, where n is the length of the array. The 
    integer, size, is the length of array x.

    bubblesort: int[] int => int
    requires:

    Example:
        array[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128}
        bubblesort(array, 14) => 47  array is mutated to {73, 128, 258, 289, 385, 522, 548, 731, 808, 809, 845, 891, 906, 988}

	array[] = {2, 1}
	buublesort(array, 2) => 1    array is mutated to {1, 2}

	array[] = {0}
	bublesort(array, 1) => 0     array is not mutated

	array[] = {}
	bubblesort(array, 0) => 0    array is not mutated
    
   */

  printf("Unsorted:   ");
  printArray(x, size);
  
  if (size <= 1) {
    return 0;
  }

  int end = size - 1;
  int swap_count = 0;
  int passes = 0;

  int index = 0;
  while (end > 0) {
    if (index == end) {
      index = 0;
      end = end - 1;
      passes++;

    } else if (x[index] > x[index + 1]) {
      swap(x, index, index + 1);
      swap_count++;
      index++;

    } else {
      index++;
      
    }
  
    
  }

  printf("\nswap count: %d  passess: %d  \n", swap_count, passes);
  printf("Sorted:  ");
  printArray(x, size);
  return swap_count;
  

}


int main() {

  int a[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
  int b[] = {2, 1};
  int c[] = {0};
  int d[] = {};

  int al = sizeof(a) / sizeof(a[0]);
  int bl = sizeof(b) / sizeof(b[0]);
  int cl = sizeof(c) / sizeof(c[0]);
  int dl = sizeof(d) / sizeof(d[0]);
  

  bubblesort(a, al);
  bubblesort(b, bl);
  bubblesort(c, cl);
  bubblesort(d, dl);

  

  


  return 0;
}
