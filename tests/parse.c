#include <stdio.h>
#include <unistd.h>
#include <string.h>

// an example string to tokenize would be:
// GET /info.html HTTP/1.1
// now, we need to get the GET part, for the GET handler
// but we also need to get the second token which is the filename
// but remove the leading '/' from it, not too hard with a function


int main() {

  char buf[512];          // test string
  char *token;            // next token
  char resource[512];    // resource 
  char *http_base = "htdocs";
  char *index_default = "index.html";
  char *t;

  // our test buffer content strings
  //strcpy(buf, "GET /info.html HTTP/1.1");
  //strcpy(buf, "GET / HTTP/1.1");
  //strcpy(buf, "GET /usmweb/main.htm HTTP/1.1");
  //strcpy(buf, "GET /neogeo/hyper64/posters/SSWR-1.jpg HTTP/1.1");
  //strcpy(buf, "GET /CUNTY1/CUNTY2/FUCK3/SUBDIR4/SUBDIR5/SUBDIR6/cunt.jpg HTTP/1.1");
  strcpy(buf, "GET /testweb/ HTTP/1.1");

  token = strtok(buf," ");   // skip over GET
  token = strtok(NULL," ");  // get the resource

  if(!strcmp(token, "/")) {
    strcat(token, index_default);
    printf("<!> / has been redirected to %s \n", token);
  }
  
  // I need to add a bit of logic to 
  // look for the index.html 
  // when the resource is htdocs/testweb/ e.g

  printf("<!> token is %s\n", token);
  printf("<!> adding http_base\n");

  strcpy(resource, http_base);
  strcat(resource, token);

  

  //if(!strcmp(token,"/")) {
  //  strcat(token, index_default);
  //  printf("<!> Added index.html default\n");
  //}

  printf("resource is : %s\n", resource);

  return 0;
}
