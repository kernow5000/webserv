/* read_dir.c */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//#include <read_dir.h>


int read_dir(char *dir) {

  DIR *dirp;        // open directory descriptor
  struct dirent *dp;   // directory entry pointer
  FILE *outfile;     // html file to be rendered

  dirp = opendir(dir);    // open the dir
  if ( !dirp ) {
    perror("opendir(3)");
    return 1;
  }
  errno = 0;


  // open output file
  if ( (outfile = fopen ("list.html", "w")) == NULL)
    {
      return 1;
    }


  // create html file output

  fprintf (outfile,"<html>\n");
  
  // write to file
  while( (dp = readdir(dirp)) != NULL) {
    fprintf (outfile,"<br><a href=htdocs/%s>%s</a>", dp->d_name,dp->d_name);
    errno = 0;
  }

  if ( errno != 0)
    perror("readdir(3)");
  
  fprintf (outfile,"<br><p>This page is being served by kern_httpd 0.1 (2004)</p>");
  fprintf (outfile,"</html>\n");


  // tidy up

  fclose(outfile);

  if( closedir(dirp) == -1 )
    perror("closedir(3)");

  return 0;

}

	 
// end of read_dir() function
