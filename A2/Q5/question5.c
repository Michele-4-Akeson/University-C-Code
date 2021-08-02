#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

float avgCSV (char* inputName);


float avgCSV (char* inputName){
    char line[100];
    char* token;
    float sum = 0;
    float count = 0;
    int line_count =0;
    int row_count = 0;
    char* endptr;
    FILE* file = fopen(inputName, "r");

    while (fgets(line, 100, file) != NULL){
      if (strcmp(&line[0], "\n")){
	line_count++;
	token = strtok(line, ",");
	while (token!=NULL){
	  row_count++;
	  sum += strtof(token, &endptr);
	  token = strtok(NULL, ",");
	  count++;
	}
	
      }
    }
     

    fclose(file);
    printf("%d\n", line_count);
    printf("%f\n", count);
    return sum / count-1;
    
}	



int main () {
	printf("%f\n", avgCSV("multiline1.csv"));
	// Expected Value = 523.899109
	printf("%f\n", avgCSV("multiline2.csv"));
	// Expected Value = 506.371246
}
