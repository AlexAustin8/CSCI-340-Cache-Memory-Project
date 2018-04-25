CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(mem basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: runProject

runProject: project.c
	$(CC) project.c -o runProject

clean:
	/bin/rm -f runProject *.o *~

