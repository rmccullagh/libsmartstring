CCFLAGS = -g -Wall -Wextra

simple: simple.o smart_string.o
	cc $(CCFLAGS) -o simple simple.o smart_string.o
test_smart_string_append: test_smart_string_append.o smart_string.o
	cc $(CCFLAGS) -o test_smart_string_append test_smart_string_append.o smart_string.o
sane: sane.o smart_string.o
	cc $(CCFLAGS) -o sane sane.o smart_string.o
smart_simple.o: simple.c
	cc $(CCFLAGS) -c simple.c
smart_string.o: ../smart_string.c
	cc $(CCFLAGS) -c ../smart_string.c
clean:
	rm -f *.o *.exe simple
