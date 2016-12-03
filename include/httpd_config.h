// basic header for my webserva

// a few basic defines


// send/recv buffer size, soon to be dynamic somehow, this is a waste of RAM
#define bufsize 8192


char *http_base = "htdocs";
char *http_default_index = "index.html";
char *http_secondary_index = "index.htm";
char *kern_httpd_version = "0.1";
char *http_protocol_version = "0.9";
