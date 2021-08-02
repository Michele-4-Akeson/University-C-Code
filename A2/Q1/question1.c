#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>


float fkgrade(char str[]);
int sentence_count(char str[], int length);
int word_count(char str[], int length);
int syllable_count(char str[], int length);
bool isvowel(char c);



int syllable_count(char str[], int length) {
  /*
    syllable_count returns an integer value, being the total number
    of vowel groups in an array of characters, str, of length, length 
    
   */
  int count = 0;
  int end_index = length - 1;
  char current_character = str[0];
  char next_character;

  if (length == 0){
    return count;
  }
  if (isvowel(current_character)) {
    count++;
  }
  
  for (int i = 0; i < end_index; i++){
    current_character = str[i];
    next_character = str[i+1];
    
    if (!isvowel(current_character) && isvowel(next_character)){
      count++;
    }

  }

  return count;
}


bool isvowel(char c) {
  /*
    isvowel returns a boolean of true if character, c, is a vowel, and
    false otherwise ('y' is excluded as a vowel)

   */
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
    return true;
    
  } else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
    return true;
    
  } else {
    return false;
  }
  
  
}




int word_count(char str[], int length) {
  /*
    word_count returns the number of words contained with the character array, str[],
    which is of length, length


   */
  int count = 0;
  int end_index = length - 1;
  char current_character;
  char next_character;

  if (length == 1) {
    if (isalnum(str[0])) {
	count++;
	return count;
      }
  }

  for(int i = 0; i < end_index; i++){
    current_character = str[i];
    next_character = str[i+1];

    if (isalnum(current_character) && !isalnum(next_character)){
      if (next_character != '-' && next_character != '\'') {
	count++;
      }
    }
    
  }

  if (isalnum(next_character)) {
    count++;
  }

  return count;

  
}


  

int sentence_count(char str[], int length) {
  /*
    sentence_count returns the number of sentences in a character array, str,
    of length, length, as an integer value. (As of current a sentence is indictaed
    by a ! ? or . character) -- further testing should be completed
    
    cases:
       ...  ??? !.!.? 
   */
  int count = 0;
  for(int i = 0; i < length; i++){
    char c = str[i];
    if (c == '!' || c == '?' || c == '.'){
      count++;
      
    }
    
  }

  return count;
}





float fkgrade(char str[]){
  /*
    fkgrade returns a float value, being the Fliesh-Kincaid Grade Level
    for a given passgae, str. 

    fkgrade: char[] => float
    requires: 

    Example:
        fkgrade("hello.") => 8.400000

   */
  int length = strlen(str);
  int sentences = sentence_count(str, length);
  int words = word_count(str, length);
  int syllables = syllable_count(str, length);
  float grade_level = 0;

  if (sentences == 0 && words != 0) {
    sentences = 1;
  } else if (sentences == 1 && words == 0) {
    grade_level = 0;
  } else {
    grade_level = 0.39 * (words/sentences) + 11.8*(syllables/words) - 15.59;
  }

  return grade_level;

  
  
}

int main() {
    char plato[] = "He who is the real tyrant, whatever men may think, is the real slave, and is obliged to practise the greatest adulation and servility, and to be the flatterer of the vilest of mankind.  He has desires which he is utterly unable to satisfy, and has more wants than any one, and is truly poor, if you know how to inspect the whole soul of him: all his life long he is beset with fear and is full of convulsions and distractions, even as the State which he resembles: and surely the resemblance holds?";

    char aurelius[] = "Nothing pertains to human beings except what defines us as human.  No other things can be demanded of us.  They aren't proper to human nature, nor is it incomplete without them.  It follows that they are not our goal, or what helps us reach it -- the good.  If any of them were proper to us, it would be improper to disdain or resist it.  If the things themselves were good, it could hardly be good to give them up.  But in reality, the more we deny ourselves such things (and things like them) -- or are deprived of them involuntarily, even -- the better we become.";

    char descartes[] = "I suppose, accordingly, that all the things which I see are false (fictitious); I believe that none of those objects which my fallacious memory represents ever existed; I suppose that I possess no senses; I believe that body, figure, extension, motion, and place are merely fictions of my mind.  What is there, then, that can be esteemed true?  Perhaps this only, that there is absolutely nothing certain.";
    
    printf("Plato...\nexpected sentences = 2\n  expected words = 94\n  expected syllables = 135\n");

    printf("Sentence Count: %d,  Word Count: %d   Syllable Count:  %d\n", sentence_count(plato, strlen(plato)), word_count(plato, strlen(plato)), syllable_count(plato, strlen(plato)));

    
    float out = fkgrade(plato);
    printf("> Reading Level = %f\n", out);
    printf("Marcus Aurelius...\n  expected sentences = 7\n   expected words = 104\n    expected syllables = 153\n");
    printf("Sentence Count: %d,  Word Count: %d   Syllable Count:  %d\n", sentence_count(aurelius, strlen(aurelius)), word_count(aurelius, strlen(aurelius)), syllable_count(aurelius, strlen(aurelius)));

    out = fkgrade(aurelius);
    printf("> Reading Level = %f\n", out);
    printf("Rene Descartes...\n  expected sentences = 3\n   expected words = 67\n    expected syllables = 113\n");
    printf("Sentence Count: %d,  Word Count: %d   Syllable Count:  %d\n", sentence_count(descartes, strlen(descartes)), word_count(descartes, strlen(descartes)), syllable_count(descartes, strlen(descartes)));

    out = fkgrade(descartes);
    printf("> Reading Level = %f\n", out);
}
