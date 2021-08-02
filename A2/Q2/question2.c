#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void DMY_MonthDY(char *buffer, const char *str);
void MonthDY_DMY(char *buffer, const char *str);
bool equal(char *str1, char* str2);



bool equal(char *str1, char *str2){
  /*
    equal returns a boolean value of true if str1 and str2
    are equal, and false otherwise. This Helper function
    is used as the strcmp return value is syntaxtically 
    poor
   */
  if (strcmp(str1, str2) == 0) {
    printf("strings are equal");
    return true;
    
  } else {
    return false;
    
  }
  
}


void MonthDY_DMY(char *buffer, const char *str) {
  /*
    MonthDY_DMY returns void and mutates a character array, buffer, which is of size 10
    (not including the null termination character), and formats it to be in "DD/MM/YYYY"
    using the character array, str, which is formated in "Month Day, Year"

    MonthDY_DMY: char[] char[] => void
    requires: str is of format "Month Day, Year"

    Example:
        MonthDY_DMY

	char array[] =  "January    1, 1970"
	cahr buffer[]
        DMY_MonthDY(buffer, array)   buffer = "01/01/1970"

  */

  // copies constant char array to a mutable array, temp
  char temp[19];
  strcpy(temp, str);

  
  //char *month = strtok(temp, " ");
  char *month;
  char *day;
  char *year;
  int dayval;
  //char dayr[3];
  int yearval;
  int monthval;
  char *endptr;
  for (int i = 0; i < 3; i++) {
    if (i == 0){
      month = strtok(temp, " ");
    } else if (i == 1) {
      day = strtok(NULL, " ");
    } else {
      year = strtok(NULL, " ");
    }
    
  }

  dayval = strtol(day, &endptr, 10);
  yearval = strtol(year, &endptr, 10);
  //printf("month:%s day:%.2d year:%.4d", month, dayval, yearval);

   if (equal(month, "January")){
     monthval = 1;
   } else if (equal(month, "Febuary")) {
     monthval = 2;
   } else if (equal(month, "March")) {
     monthval = 3;
   } else if (equal(month, "April")) {
     monthval = 4;
   } else if (equal(month, "May")) {
     monthval = 5;
   } else if (equal(month, "June")) {
     monthval = 6;
   } else if (equal(month, "July")) {
     monthval = 7;
   } else if (equal(month, "August")) {
     monthval = 8;
   } else if (equal(month, "September")) {
     monthval = 9;
   } else if (equal(month, "October")) {
     monthval = 10;
   } else if (equal(month, "Novemebr")) {
     monthval = 11;
   } else if (equal(month, "December")) {
     monthval = 12;
   }
 
  
  
  snprintf(buffer, 11, "%.2d/%.2d/%.4d", dayval, monthval, yearval); 

  /*
  while (token != NULL) {
      printf("%s\n", token);
      token = strtok(NULL, " ");
  }

  */

  
  
  
}


void DMY_MonthDY(char *buffer, const char *str) {
  /*
    DMY_MonthDY returns void and mutates a character array, buffer, which is of size 18
    (not including the nulltermination character), and formats it to be
    in "Month Date, Year", using the character array, str, which is formatted
    in DD/MM/YYYY

    DMY_MonthDY: char[] char[] => void
    requires: str is of format DD/MM/YYYY

    Example:
        char array[] = "01/01/1970"
	cahr buffer[]
        DMY_MonthDY(buffer, array)   buffer = "January    1, 1970"
   */

  char day[] = {str[0], str[1], '\0'};
  char month[] = {str[3], str[4], '\0'};
  char year[] = {str[6], str[7], str[8], str[9], '\0'};
  char *endptr;
  int day_number = strtol(day, &endptr, 10);
  int year_number = strtol(year, &endptr, 10);
  char *calendar_name;
  printf("Day %d  Month %s  Year %d\n", day_number, month, year_number);
  
  if (equal(month, "01")){
    calendar_name = "January";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "02")) {
    calendar_name = "February";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "03")) {
    calendar_name = "March";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "04")) {
    calendar_name = "April";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "05")) {
    calendar_name = "May";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "06")) {
    calendar_name = "June";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "07")) {
    calendar_name = "July";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "08")) {
    calendar_name = "August";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "09")) {
    calendar_name = "September";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "10")) {
    calendar_name = "October";
    printf("\n%s is real\n", calendar_name);  
  } else if (equal(month, "11")) {
    calendar_name = "November";
    printf("\n%s is real\n", calendar_name);
  } else if (equal(month, "12")) {
    calendar_name = "December";
    printf("\n%s is real\n", calendar_name);  
  }


  snprintf(buffer, 19, "%-9s %2d, %d", calendar_name, day_number, year_number);


}



int main(){
char format1[12][11] = { "01/01/1970"
                       , "10/02/1763"
                       , "15/03/0044"
                       , "18/04/1982"
                       , "05/05/1789"
                       , "06/06/1944"
                       , "01/07/1867"
                       , "03/08/1492"
                       , "02/09/1945"
                       , "24/10/1917"
                       , "11/11/1918"
                       , "08/12/1980"
                       };
char format2[12][19] = { "January    1, 1970" // First Day of History (according to computers)
                       , "February  10, 1763" // France cedes Canada to England
                       , "March     15,   44" // Assassination of Julius Caesar
                       , "April     18, 1982" // Canada Achieves Sovereignty 
                       , "May        5, 1789" // French Revolution
                       , "June       6, 1944" // D-Day Landings of WWII
                       , "July       1, 1867" // Confederation of Canada
                       , "August     3, 1492" // Christopher Columbus Sets Sail for the Americas
                       , "September  2, 1945" // WWII Surrender of Japan
                       , "October   24, 1917" // October Revolution (Julian Calendar)
                       , "November  11, 1918" // WWI Armistice
                       , "December   8, 1980" // Murder of John Lennon
                       };
    
    char buffer1[12][11];
    char buffer2[12][19];
    
    printf ("-- DD\\MM\\YY to Month DD, YYYY\n");
    for (int i = 0; i < 12; i++) {
      printf("%s\n", format1[i]);
      DMY_MonthDY(buffer2[i], format1[i]);
      printf("-> \"%s\"\n", buffer2[i]);
    }
    
    
    printf ("\n\n-- Month DD, YYYY to DD\\MM\\YY\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\n", format2[i]);
	MonthDY_DMY(buffer1[i], format2[i]);
        printf("-> \"%s\"\n", buffer1[i]);
    }
}

