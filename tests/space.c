#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {
  char *test;
  char *p;
  int i = 1;

  strcpy(test,"cunt1%20cunt2%20cunt3%20");

  //printf("test is: %s\n", test);
  
  do {
    p = test++;
    if (!strcmp(p,"%"))
      printf("<!> %\n");
    i++;
    printf("%d\n", i);
  } while(i != 10);

  return 0;
}

 
