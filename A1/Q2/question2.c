#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>




//////////////////////////////////////////////
//
//
// Michele Akeson (400027379)
// CS1XC3 SUMMER: A1 Q2
// Date: July 15th, 2021
// Date Modified:July 15th, 2021
//
//
/////////////////////////////////////////////



void reverse(char* str);
int count(char* str);

int count(char* str){
  /*
    count() returns the number of vowels within the character array, str,
    as an integer value.

    count: char[] => int
    requires:

    Example:
       count("McMaster") => 2
       count("aeiouy") => 6
       count("123456") => 0
       count("mmmAmmm") => 1
       count("AEIOUY") => 6
   */
  int string_length = strlen(str);
  char s;
  
  int count = 0;
  for (int i = 0; i < string_length; i++) {
    s = str[i];

    if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'y') {
      count++;

    } else if (s == 'A' || s == 'E' || s == 'I' || s == 'O' || s == 'U' || s == 'Y') {
      count++;
      
    }
    
  }

  printf("\n vowel count %s : %d \n", str, count);
  return count;

}


void reverse(char* str) {
  /*
    reverse() returns void and mutates the char array , str, by reversing the
    order of charcters in that array
    
    reverse: char[] => void
    requires: 

    Examples:
       word[] = "McMaster"
       reverse(word) => void  word[] is mutated to "retsaMcM"

       word[] = "ab"
       reverse(word) => void  word[] is mutated to "ba"

       word[] = "a"
       reverse(word) => void  word[] is mutated to "a"


   */

  // returns length of character array not
  // including '\O' (null termination character)
  printf("input: %s \n", str);
  
  int  word_length = strlen(str);
  int end_index = word_length - 1;
  int middle_index = (int) floor(word_length / 2);
  char start_character;
  char end_character;

  
  for (int i = 0; i < middle_index; i++) {
    start_character = str[i];
    end_character = str[end_index - i];

    str[i] = end_character;
    str[end_index - i] = start_character;
    
    
    
  }
  

  printf(" \n length %d \n", word_length);
  printf("%d \n", middle_index);
  printf("reversed %s \n", str);
 
}




int main(){

  printf("before anything");
  
  char* str_1 = "McMaster"; // apears to create an inmutable data object -- don't know why, but should learn
  char str_2[] = {'M', 'c', 'M', 'a', 's', 't', 'e', 'r', '\0'};
  // char* str_3 = {'a', 'b', 'c', 'd', '\0'}; // creates error - need to understand why
  char str_4[] = "noseka";
  char str_5[] = "ab";
  char str_6[] = "a";
  char str_7[] = "123456 ";
  char str_8[] = "aeiouy";
  char str_9[] = "AEIOUY";



  //reverse(str_1);
  reverse(str_2);
  // reverse(str_3); 
  reverse(str_4);
  reverse(str_5);
  reverse(str_6);
  reverse(str_7);
  reverse(str_8);
  reverse(str_9);


  count(str_1);
  count(str_2);
  count(str_4);
  count(str_5);
  count(str_6);
  count(str_7);
  count(str_8);
  count(str_9);

  return 0;
}



