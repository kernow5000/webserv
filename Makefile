# A crappy webserver
# 
# Shaun Bradley
# Aug/2003

CC = gcc
CFLAGS = -Wall -I./include

SERVER_SRC = kern_httpd.c
SERVER_BIN = kern_httpd
READDIR_SRC = read_dir.c
READDIR_BIN = read_dir.o

ARCHIVE = mywebserv-devel


all: clean read_dir server

server:      
	      $(CC) $(CFLAGS) $(READDIR_BIN) $(SERVER_SRC) -o $(SERVER_BIN)

read_dir:
	      $(CC) $(CFLAGS) -c $(READDIR_SRC)	


clean:	      
	      rm -Rf *.o *~ $(SERVER_BIN) $(READDIR_BIN)

backup:
	      tar cf $(ARCHIVE).tar *
	      gzip $(ARCHIVE).tar
	      mv $(ARCHIVE).tar.gz $(HOME)
