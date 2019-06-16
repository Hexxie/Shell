objects = ./src/main.o

wish : $(objects)
	cc -o wish $(objects)

main.o : ./src/defs.h

clean : 
		rm wish $(objects)