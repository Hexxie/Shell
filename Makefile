objects = main.o

wish : $(objects)
	cc -o wish $(objects)

main.o : defs.h

clean : 
		rm wish $(objects)