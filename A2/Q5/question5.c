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
    char* endptr;
    FILE* file = fopen(inputName, "r");

    while (fgets(line, 100, file) != NULL){
      if (strcmp(&line[0], "\n")){
	token = strtok(line, ",");
	while (token!=NULL){

	  sum += strtof(token, &endptr);
	  token = strtok(NULL, ",");
	 
	}
	 count+=8;
	
      }
    }
     

    fclose(file);
    printf("%f\n", count);

    if (count <= 0) {
      return 0;

    } else {
      return (sum / count);
    }
    
   
    
}	



int main () {
	printf("%f\n", avgCSV("multiline1.csv"));
	// Expected Value = 523.899109
	printf("%f\n", avgCSV("multiline2.csv"));
	// Expected Value = 506.371246

	printf("%f\n", avgCSV("empty.csv"));
	// Expected Value = 0
}
