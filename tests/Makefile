# test programs, should use the ../Makefile but hey
# 
# Shaun Bradley

CC = gcc

TOK_SRC = parse.c
BUF_SRC = buf_test.c
SPC_SRC = space.c
CPY_SRC = stringcopy.c
RDR_SRC = readdir.c

TOK_BIN = parse
BUF_BIN = buf_test
SPC_BIN = space
CPY_BIN = stringcopy
RDR_BIN = readdir


all: clean tok buf space stringcopy readdir

tok:          
	      $(CC) $(TOK_SRC) -o $(TOK_BIN)
buf:
	      $(CC) $(BUF_SRC) -o $(BUF_BIN)
space:
		$(CC) $(SPC_SRC) -o $(SPC_BIN)

stringcopy:

		$(CC) $(CPY_SRC) -o $(CPY_BIN)

readdir:
		$(CC) $(RDR_SRC) -o $(RDR_BIN)

clean:	      
	      rm -Rf *.o *~ $(TOK_BIN) $(BUF_BIN) $(SPC_BIN) $(CPY_BIN) $(RDR_BIN)
