#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <math.h> 




//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q1
// Date: July 15th, 2021
// Date Modified:July 15th, 2021
//
//
/////////////////////////////////////////////



double mean(int* x, int size); 
double median(int* x, int size); 
int mode(int* x, int size);

void printArray(int array[], int size) {
  printf("[");
  for (int i = 0; i < size; i++) {
    if ( i == size - 1) {
      printf("%d", array[i]);

    } else {
      printf("%d, ", array[i]);
    }

  }

  printf("]");

}





int main() {
  int array_1[] = {1, 2, 3, 4, 5};
  int array_2[] = {0};
  int array_3[] = {};
  int array_4[] = {1, 2};
  int array_5[] = {3, 5, 6, 7, 100, 230, 200};
  int array_6[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  int array_7[] = {1, 2, 3, 3, 3, 4, 5, 5, 5, 5};
  int array_8[] = {1, 2, 2, 3, 3, 4, 4};
  
  int length_1 = sizeof(array_1) / sizeof(array_1[0]);
  int length_2 = sizeof(array_2) / sizeof(array_2[0]);
  int length_3 = sizeof(array_3) / sizeof(array_3[0]);
  int length_4 = sizeof(array_4) / sizeof(array_4[0]);
  int length_5 = sizeof(array_5) / sizeof(array_5[0]);
  int length_6 = sizeof(array_6) / sizeof(array_6[0]);
  int length_7 = sizeof(array_7) / sizeof(array_7[0]);
  int length_8 = sizeof(array_8) / sizeof(array_8[0]);
  
  mean(array_1, length_1);
  mean(array_2, length_2);
  mean(array_3, length_3);
  mean(array_4, length_4);
  mean(array_5, length_5);
  mean(array_6, length_6);

  median(array_1, length_1);
  median(array_2, length_2);
  median(array_3, length_3);
  median(array_4, length_4);
  median(array_5, length_5);
  median(array_6, length_6);

  mode(array_1, length_1);
  mode(array_2, length_2);
  mode(array_3, length_3);
  mode(array_4, length_4);
  mode(array_5, length_5);
  mode(array_6, length_6);
  mode(array_7, length_7);
  mode(array_8, length_8);
  


  return 0;
  


}






double mean(int* x, int size) {
  /*
   mean() returns the mean value (average) of a sorted integer 
   array, x, as a double value. integer size, is the length of 
   array x

   mean: int[] int => double
   requires: x is a sorted array

   Examples:
       mean({1, 2, 3, 4, 5}, 5) => 3.00000
       mean({}, 0) => 0.000000
       mean({0}, 1) => 0.000000
       mean({1, 2}, 2) => 1.500000
   */

  double average = 0.000000;

  if (size == 0) {
    return average;
  }
  
  int sum = 0;

  for (int i = 0; i < size; i++) {
    sum += x[i];

  }

  average = (double) sum / size; // may need to cast each seperatly first
  printArray(x, size);
  printf("mean %lf \n ", average);
  
  return average;

}




double median(int* x, int size) {
  /*
    mediean() returns the double value of the integer located at the middle index
    of the sorted integer array, x. The integer, size, is the length of array x. 
    if the length of array x is even, then the average of the two middle elements 
    is returned

    median: int[] int => double
    require: x is a sorted array

    Example:
        median({1, 2, 3}, 3) => 2.000000
	median({1, 2, 3, 4}, 4) => 2.750000
	median({0}, 1) => 0.000000
	median({10, 10}, 2) => 10.000000
    

   */

  double median_value = 0.000000;

  if (size == 0) {
    return median_value;
  }
  
  if (size == 1) {
    // array of size 1
    median_value = (double) x[0];

  } else if (size % 2 == 0) {
    // array_length is even
    
    int index_1 = size / 2;
    int index_2 = index_1 - 1;
    int sum = x[index_1] + x[index_2];
    median_value = (double) sum / 2;
    
    

  } else
    median_value = (double) x[size / 2];

  printArray(x, size);
  printf("median %lf \n ", median_value);

  return median_value;
}

int mode(int* x, int size) {
  /*
    mode() returns the double value of the integer which occurs most
    freqently in the integer array, x, where integer size, is the length 
    of the array. If two or more integers occur and equal numnber of times
    in the array, the minimum of those integers is returned

    mode: int[] int => double
    requires: x is a sorted array

    Example:
       mode({1, 2, 3, 3, 3, 4, 5, 5, 5, 5}, 10) => 5.000000
       mode({1, 2, 2, 3, 3, 4, 4}, 7) => 2.000000
       mode({1}, 1) => 1.000000;
       mode({}, 0) => 0.000000;


   */

  // interate through array keeping track of count for each number
  // if count is equal to max_count -> append number to mode_array -> but if equal, doesn't matter becuase we want the smallest magnitude integer
  // if count exceeds max_count -> replace current_mode

  if (size == 0) {
    return 0;
  }
  
  int max_count = 0;
  double current_mode = (double) x[0];
  int count = 1;
  int index = 0;
  int number = x[index];

  while (index < size) {
    index++;
    if (number == x[index]) {
      count++;

      if (count > max_count) {
	current_mode = (double) number;
	max_count = count;
      }

    } else {
      number = x[index]; // sets new number as number to be checked
      count = 1;

    }

  }

  printArray(x, size);
  printf("mode %lf \n", current_mode);

  return current_mode;

  

}




