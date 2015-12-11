#include <stdio.h>

int main(void) {
  char s[100];
  
  printf("what is your first name?\n ");  
  scanf("%99s", s);
  
  printf("hello, %s\n", s);

  return 0;
} 
