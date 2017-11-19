The crappy http 0.9 webserver

This is about as simple as a webserver could get.
Functionality is at cost however.

issues at current

       * massive buffer overflow!	
       * get RID of / on end of http_base
       * parser still sucks, working on it
       * needs support for dir listings, working on it
       * needs support for "%20" spaces, sigh
       * 404 error checking needs to be improved
	
