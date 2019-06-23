PROJECT = wish
BUILD   = build 
SRC     = src
T_TEST    = tests 
CFLAGS  = -c -Wall -I./include

OBJS = $(SRC)/main.o \
		$(SRC)/shell.o \
		$(SRC)/utils.o	

TEST_OBJS = ./tests/test_shell.o \
			./tests/test_util.o \
			

all: wish test 

wish : $(OBJS)
	cc -o wish $(OBJS)

test : $(TEST_OBJS)
	cc -o ./tests/test_wish $(TEST_OBJS)


main.o : $(SRC)/defs.h
shell.o: $(SRC)/shell.h
utils.o: $(SRC)/utils.h

test_shell.o: ./tests/test_shell.h

clean : 
	rm wish $(OBJS)
	rm ./tests/test_wish $(TEST_OBJS)