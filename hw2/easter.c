#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN_YEAR  1582   /* Minimum year for program to work */
#define MAX_YEAR  39999  /* Maximum year for program to work */

#define ERROR_IN_DATE   0   /* Error code returned for invalid year input */
 
int calculate_Easter_date(int yr);
int compute_Zeller_congruence(int yr, int easter_date);
void write_Easter_date(int yr, int easter_date);

int main(void) {
  
  int result; /* The return of scanf, to check when EOF occurs */
  int yr; /* The year to be read in from input */
  
  int easter_date; /* The calculated easter date */
  
  while (1) {
    result = scanf("%d", &yr);
    
    /* Leaves the loop when EOF is reached */
    if (result == EOF) {
      break;
    }
    
    /* Calculates the occurence of easter given the year */
    easter_date = calculate_Easter_date(yr);
    
    /*
     * Error checking: When the easter_date is ERROR_DATE, the program
     * will print the error message to stderr
     */
    if (easter_date == ERROR_IN_DATE) {
      fprintf(stderr, "Invalid year %d: Out of Range\n", yr);
      return -1;
    }
    else {
      assert(compute_Zeller_congruence(yr, easter_date) == 1);
      /* Prints the easter date to output */
      write_Easter_date(yr, easter_date);
    }
  }
  return 0;
}

/*
 * calculate_Easter_date: finds the occurence of Easter
 * arguments: yr: year to calculate the Easter of
 * return value: int specifying when Easter occurs, where the sign
 *               corresponds to the month (negative for March, positive 
 *               for April), and the absolute value of the return is the 
 *               day it falls on.
 */

int calculate_Easter_date(int yr) {
  
  int golden_yr; /* golden year in Metonic cycle */
  int century; /* century of the year */
  int skipped_leap_yr; /* leap years that were skipped */
  int correction; /* correction factor for the moon's orbit */
  
  int sunday; /* March ((-sunday) mod 7 + 7) falls on a Sunday */
  int epact; /* specifies when the full moon occurs */
  int easter_day; /* return value for the day easter_occurs */
  
  /* Checks if the input year is within the year boundaries */
  if (yr < MIN_YEAR || yr > MAX_YEAR) {
    return ERROR_IN_DATE;
  }
  
  golden_yr = yr % 19 + 1;
  century = yr /100 + 1;
  skipped_leap_yr = (3 * century) / 4 - 12;
  correction = (8 * century + 5) / 25 - 5;
  
  sunday = (int)(5 * yr) / (int)4 - skipped_leap_yr - 10;
  epact = (11 * golden_yr + 20 + correction - skipped_leap_yr) % 30;
  if ((epact == 25 && golden_yr > 11) || (epact == 24)) {
    epact++;
  }

  easter_day = 44 - epact;
  if (easter_day < 21) {
    easter_day += 30;
  }
  easter_day = easter_day + 7 - (sunday + easter_day) % 7;
  
  if (easter_day < 31) {
    /* handles formatting output when easter is in March */
    easter_day *= -1;
  }
  else {
    /* handles output when easter is in April */
    easter_day -= 31;
  }
  
  return easter_day;
}

/*
 * compute_Zeller_congruence: finds the day of the week a date falls
 * arguments: yr: year of date as an int
 *            date: date as an int (- for March, + for April)
 * return value: date of the week (0 = Sat, 1 = Sun, ..., 6 = Fri)
 */   
int compute_Zeller_congruence(int yr, int date) {
  int month; /* the month number */
  int day_of_month; /* day of the month */
  int century; /* zero-based century */
  int year_of_century; /* year of the century */

  int day_of_week; /* day of the week */
  
  /* If date is negative, month is March, else it is April */
  month = (date < 0) ? 3 : 4;
  day_of_month = abs(date);
  
  century = yr / 100;
  year_of_century = yr % 100;

  day_of_week = (day_of_month + (13 * (month + 1) / 5) + year_of_century
                 + (year_of_century / 4) + (century / 4) + 5 * century)
                 % 7;
  
  return day_of_week;

}

/*
 * write_Easter_date: prints easter date to output in the following form:
 *                    '<year> - <month> <day>'
 * arguments: yr: year of the easter date as an int, 
 *            easter: day easter falls on, as an int
 */

void write_Easter_date(int yr, int easter_date) {
  /* 
   * The easter falls in April if its positive, and March
   * otherwise.
   */
  if (easter_date > 0) {
    printf("%d - April %d\n", yr, easter_date);
  }
  else {
    printf("%d - March %d\n", yr, abs(easter_date));
  }
}
