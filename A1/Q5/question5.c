#include <stdio.h>
#include <assert.h>
#include <math.h>


//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q5
// Date: July 16th, 2021
// Date Modified:July 16th, 2021
//
//
/////////////////////////////////////////////






int insertionsort(int* x, int size);
void swap(int* x, int m, int n);
void printArray(int array[], int size);




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




int insertionsort(int* x, int size) {
  /*
    insertionsort() mutates the integer array, x, which is of
    length, size, to be in sorted acending order by using the 
    insertion sort algorithem and returns the number of examinations
    (comparisons) performed during execution.
    
    A examination is considered any comparison mae regardless of swap 
    action

    insertionsort: int[] int => 
    requires:

    Examples:
        array[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128}
	insertionsort(array, 14) => 58   array is mutated to {73, 128, 258, 289, 385, 522, 548, 731, 808, 809, 845, 891, 906, 988}

	


   */
  printf("Unsorted:   ");
  printArray(x, size);

  if (size <= 1) {
    printf("array is of size 1 or less is already sorted and requires no examination");
    return 0;
  }

  
  int check_index;
  int left_index;
  int examinations = 0;
  for (int i = 1; i < size; i++) {
    check_index = i;
    left_index = check_index - 1;

    if (x[left_index] > x[check_index]) {
      examinations++;
      swap(x, left_index, check_index);
      check_index--;
      left_index--;

      // need to make sure false while condition is accounted for
      while (left_index >= 0 && x[left_index] > x[check_index]) {
	examinations++;
	swap(x, left_index, check_index);
	check_index--;
	left_index--;
	 
      }

      if (left_index >= 0) {
	examinations++;
      }
      

    } else {
      examinations++;

    }
    

  }


  printf("examinations:  %d\n ", examinations);
  printf("Sorted:   ");
  printArray(x, size);


  return examinations;
    
    
    

  

}




int main() {

  int a[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
  int b[] = {2, 1};
  int c[] = {0};
  int d[] = {};
  int e[] = {9, 4, 7, 1, 7, 3, 6};

  int al = sizeof(a) / sizeof(a[0]);
  int bl = sizeof(b) / sizeof(b[0]);
  int cl = sizeof(c) / sizeof(c[0]);
  int dl = sizeof(d) / sizeof(d[0]);
  int el = sizeof(e) / sizeof(e[0]);
  

  insertionsort(a, al);
  insertionsort(b, bl);
  insertionsort(c, cl);
  insertionsort(d, dl);
  insertionsort(e, el);

  

  


  return 0;
}
