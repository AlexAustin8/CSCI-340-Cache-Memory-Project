CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(mem basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: runProject


runProject: project.c
	$(CC) project.c -o runProject

#mem.o: mem.c mem.h
#	$(CC) $(CFLAGS) mem.c

#main.o:	project.c
#	$(CC) $(CFLAGS) project.c

clean:
	/bin/rm -f runProject *.o *~

