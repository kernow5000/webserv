// kern_httpd.c

// not limited in file size anymore !!! woooo
// adding readdir() and scanforindex() support now

// whats needed to make it better? 

//      ** immediately needed **
//    * a better parser, again
//    * proper 404 reporting for not only .html files.. why is this working again? ? 
//    * a parser that supports "%20" spaces
//    * a searchdirfor_index() function, that searches the dir for an index page, 
//    * and gets its name if it exists, else lists the files in the base dir if it doesn't



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>

// my custom headers
#include <httpd_config.h>    // new server include header
#include <read_dir.h>

// globals, nasty eh
struct sockaddr_in local;   // struct for an incoming connection?
int s;                      // uhm
int s1;                     // descriptor
int len = 0;                // for sizeofs
int infile = 0;             // current input file
int result;                 // result code for functions
char recv_buf[bufsize];     // recieve buffer
char send_buf[bufsize];     // send buffer
// end globals


// prototypes
int  scanfor_index(char *path);
void kern_httpd_init(int port);
void kern_httpd_run();
void kern_httpd_serve(char *resource);
void kern_httpd_404();
void kern_httpd_usage();

// think about modularising the server code
// return codes? they are all void for fucks sake
// end protos



int scanfor_index(char *path) {
  
  //  if(scandir(indexpage_name)
  //  return 0   // success
  //  else
  // return 1   // fail, boo

  return 0;
}








void kern_httpd_init(int port) {

  // get a socket and a port from the OS
  
  local.sin_family = AF_INET;
  local.sin_port = htons( port );
  local.sin_addr.s_addr = htonl( INADDR_ANY );
  s = socket( AF_INET, SOCK_STREAM, 0 );
  if ( s < 0 )
    {
      perror( "socket call failed" );
      exit( 1 );
    }
  result = bind( s, ( struct sockaddr * )&local, sizeof( local ) );
  if ( result < 0 )
    {
      perror( "bind call failure" );
      exit( 1 );
    }
}



void kern_httpd_run() {
  
  // start waiting for clients and dealing with them
  
  char *token;    // next token when parsing
  char resource[512]; // the requested resource
  //char *tmp;
  
  // running part, hmm must be a better way
  while (1) {
    result = listen( s, 5 );
    if ( result )
      {
	perror( "listen call failed" );
	exit( 1 );
      }
    
    s1 = accept( s, NULL, NULL );
    if ( s1 < 0 )
      {
	perror( "accept call failed" );
	exit( 1 );
      }

    // now the server has accept()'ed a connection, 
    // we can try and recv something into a buffer
    strcpy(recv_buf,"");
    len = sizeof(recv_buf);
    result = recv( s1, recv_buf, len, 0 );
    if ( result <= 0 )
      {
	perror( "recv call failed" );
	exit( 1 );
      }
    
    // the first thing a web server gets is GET
    token = strtok(recv_buf," ");
    if(!strcmp(token,"GET")) {
      printf("<!> GET handler called\n");
      
      // begin PARSING here
      token = strtok(NULL," ");  // get the resource  
      // this needs to work with
      // e.g http://localhost/ms3/
      if(!strcmp(token, "/")) {
	// I need a rewrite of this
	// it needs to searchforindex, 
	// if that fails, it needs to readdir, if that fails
	// it needs to http_serve("404.html");
	// easy! in theory
	
	// add an index? 
	// an example string to tokenize would be:
	// GET /info.html HTTP/1.1
	//token = strtok(NULL," ");
	//printf("<t> token is %s\n", token);
	strcpy(resource,http_base);
	strcat(resource,"/");
	strcat(resource,http_default_index);

	// turn a / into an index, should I be searchingforindex()?
      } 
      else {
	// this is a normal resource, non index
	printf("<t> token is %s\n", token);
	strcpy(resource,http_base);
	strcat(resource,token);
      }
      
      printf("resource is : %s\n", resource); // debug
      
      // send a simple http 0.9 reply, just a body
      kern_httpd_serve(resource);


    } // end of GET handler
    
    close (s1);  // always close after, single packet based http protocol
    
  } // end client serving loop
  
}


void kern_httpd_serve(char *resource) {

  int bytesread;   //file size in bytes .. hmm

  // attempt to open and serve the file
  // must deal with nonexistant files, i.e 404's
  printf("<!> opening resource: %s\n", resource);
  
  if ( (infile = open(resource, O_RDONLY)) == -1) {
    printf("<x> Error opening %s\n", resource);     // can't open/find
    // send a 404 page, and error code somehow too
    printf("<x> Sending a 404 file instead\n");
    kern_httpd_serve("404.html");
  } else { 
    
    // now that the resource is open, we need to read from it into send_buf
    
    do {
      // I need to loop, sending chunks until EOF reached, then close
      
      result = read(infile,send_buf,bufsize); // read
      if(result == -1) {
	printf("<x> Error reading from %s\n", resource);
	// send a 404 if this happens? hmm
	printf("<x> Sending a 404 file instead\n");
	kern_httpd_serve("404.html");
      } else bytesread = result;    
      
    
    // now send buffer[bytesread] to client, i.e 892 bytes or something.
      //if (bytesread > 0)
	result = send( s1, send_buf, bytesread, 0);
    if ( result <= 0 )
      perror( "send call failed" );
    
  } while (result == bufsize);

  close(infile);  

  }
}


void kern_httpd_404() {
  // uh, hmm
  
  // open the 404 file
  
  
}


void kern_httpd_usage() {

  printf("kern_httpd %s", kern_httpd_version);
  printf("\nusage: kern_httpd <port>\n");
}



int main(int argc, char **argv)
{
  
  if(argc == 2) 
    {
      kern_httpd_init(atoi(argv[1]) );      // initialise/bind to port
      kern_httpd_run();                     // start running, forevar
    } 
  else kern_httpd_usage();  // show usage info 
  
  return 0;
}
