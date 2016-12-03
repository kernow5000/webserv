#include <stdio.h>
#include <unistd.h>
#include <string.h>

// dynamic/static buffer test, 
// will we ever be unlocked from a static buffer?
// will it take up all the RAM, who knows?
#define notfound404 "<HTML><H1>404 not found.</H1> <p>The document you have requested has not been found on the server</p> <p><i>kernserv 0.1</i></p></html>"

int main() {
  
  char *buf;
  int len = 0;


  // load buffer with 404 data
  strcpy(buf, notfound404);
 
  len = strlen(buf);

  printf("%d bytes long\n", len);
  
  
  return 0;
}
