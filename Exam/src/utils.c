#include<stdio.h>
#include<stdlib.h>

void displayImage(const char *filename) {
  // QUESTION 2 GOES HERE!
  char buffer[255];
  FILE* file = fopen(filename, "r");

  while (fgets(buffer, 100, file) != NULL) {
    printf("%s", buffer);
  }

  fclose(file);
}

