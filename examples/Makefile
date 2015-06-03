CCFLAGS = -g -Wall -Wextra

default: simple.o smart_string.o
	cc $(CCFLAGS) -o simple simple.o smart_string.o
smart_simple.o: simple.c
	cc $(CCFLAGS) -c simple.c
smart_string.o: ../smart_string.c
	cc $(CCFLAGS) -c ../smart_string.c
clean:
	rm -f *.o *.exe simple
