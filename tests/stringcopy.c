#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {
  char test[8];
  char p[8];
  

  strcpy(test,"blech");
  strcpy(p, " ");

  printf("%s\n", test);
  printf("%s\n", p);

  return 0;
}

 
