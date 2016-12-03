#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {
  char buf[512];            // test string
  char fixedresource[512];  // fixed string
  
   strcpy(buf, "twat%20features%20cunty%20cunt");
   char *token;            // next token

   token = strtok(buf,"%20");   // skip over GET
   printf("CNT");
   token = strtok(NULL," ");  // get the resource

  if(!strcmp(token, "%20")) {
    strcat(fixedresource," ");
    printf("<!> omg percent 20);
  }

  return 0;
}

 
