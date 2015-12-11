#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  
  int n; /* random number 1 to 10 */
  int i; /* loop index */
 
  char s[100];
  
  printf("what is your name? \n");
  scanf("%99s", s);

  /* 
   * Generates a random number between 0 and RANDMAX, and takes the number
   * mod 10 to constrain to 0 to 9, then add 1 to change to 1 to 10.
   */

  srand(time(0));
  n = rand() % 10 + 1;

  if (n % 2 == 0) {
    for (i = 0; i < n; i++) {
      printf("%d: hello, %s!\n", n, s);
    }
  }
  else {
    for (i = 0; i < n; i++) {
      printf("%d: hi there, %s!\n" , n, s);
    }
  }

  return 0;
}
  
