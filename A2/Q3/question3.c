#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int simpleParse(const char *exp);
void organize(const char* exp, char** operations, int** numbers);
int update_ops(char** operations, int index, int size);
int update_nums(int** numbers, int index, int size, int output);


int update_ops(char** operations, int index, int size){
  // update_ops shifts all elements in the character array starting
  // at index, one to the left, and then reallocates the size of the array

  while (index < size -1) {
    (*operations)[index] = (*operations)[index+1];
    index++;
  }

  size--;
  *operations = realloc(*operations, size*sizeof(char));

  return size;

}


int update_nums(int** numbers, int index, int size, int output) {
  // update_operations shifts all elements in the character array starting
  // at index, one to the left, and then reallocates the size of the array

  (*numbers)[index] = output;
  index++;

  while (index < size - 1) {
    (*numbers)[index] = (*numbers)[index + 1];
    index++;
  }

  size--;
  *numbers = realloc(*numbers, size*sizeof(int));

  return size;
  
}






void organize(const char* exp, char** operations, int** numbers) {
  /*
    organize passes two references to two null pointers,
    and mutates pointer such that operation characters stored
    in str are stored in *operations and integer values are stored
    in numbers
   */

  int array_length = strlen(exp) + 1;
  char temp[array_length];
  strcpy(temp, exp);
  char *token;
  *operations = (char*) malloc(sizeof(char)); // references the address of the array increase size to 1
  *numbers = (int*) malloc(sizeof(int)); // references the address of the array and increase size to 1

  token = strtok(temp, " ");
  int size_o = 1;
  int index_o = 0;

  int size_n = 0;
  int index_n = 0;
  char* endptr;

   while (token != NULL) {
    if (ispunct(token[0])) {
      size_o++;
      *operations = realloc(*operations, size_o*sizeof(char));
      (*operations)[index_o] = token[0];
      index_o++;
    } else {
      size_n++;
      *numbers = realloc(*numbers, size_n*sizeof(int));
      (*numbers)[index_n] = strtol(token, &endptr, 10);
      index_n++;
      
    }

    token = strtok(NULL, " ");
  }

   (*operations)[index_o] = '\0';

  
}



int simpleParse(const char *exp) {
  /*
    simpleParse returns an integer value
    equal to the evaluation of the expressioncd
    exp, which is provided as a constant char
    array.

    simpleParse: char[] => int
    requires: char contains no leading '-', prefixes or postfixes, and
              use the following operations: +, -, /, *, %

    Example:
        simpleParse("2 + 2") => 4
	.. variable space can exsist between characters

	Note: to mutate an array/pointer to a series of memory address, 
	      you need to pass by reference which wouuld be passing the address of the pointer
	      that references your array - thus ??
   */

  char *operators = NULL;
  int *numbers = NULL;
  organize(exp, &operators, &numbers);
  
  int size_o = strlen(operators);
  int size_n = size_o + 1;
  int output;

  //BEDMAS
  //MULT/DIVISION LOOP
  for (int i = 0; i < size_o; i++) {
    if (operators[i] == '/' || operators[i] == '*' || operators[i] == '\%') {
      switch(operators[i]){
      case '/':
	output = numbers[i] / numbers[i+1];
	break;
      case '*':
	 output = numbers[i] * numbers[i+1];
	 break;
      case '\%':
	 output = numbers[i] % numbers[i+1];
	 break;
      }
      size_o = update_ops(&operators, i, size_o + 1) - 1; // must account for '\0'
      size_n = update_nums(&numbers, i, size_n, output);
      i--;
    }
  }


  //ADD/SUB LOOP
  for (int i = 0; i < size_o; i++) {
    if (operators[i] == '+'|| operators[i] == '-') {
      switch(operators[i]){
      case '+':
	output = numbers[i] + numbers[i+1];
	break;
      case '-':
	output = numbers[i] - numbers[i+1];
	break;
      }
      size_o = update_ops(&operators, i, size_o + 1) - 1; // must account for '\0'
      size_n = update_nums(&numbers, i, size_n, output);
      i--;
    }
  }
  
  
  return numbers[0];



  

}


int main() {
    char exp1[] = "2 + 2";
    printf("%s = %d\n", exp1, simpleParse(exp1));
    // Expected Value = 4
    char exp2[] = "3 + 7 - 4 * 1";
    printf("%s = %d\n", exp2, simpleParse(exp2));
    // Expected Value = 6
    char exp3[] = "9 * 13 / 2 + 18 * 110 - 812 \% 97 + 3";
    printf("%s = %d\n", exp3, simpleParse(exp3));
    printf("Expected %d\n ", 9 * 13 / 2 + 18 * 110 - 812 % 97 + 3);
    printf("Expected %d\n", 2 + 110 - 812 % 97 + 3);
    printf("812 97 %d", 812 % 97);
    
    // Expected Value = 2005
    
}

