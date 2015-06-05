CFLAGS = -DDEBUG -Wall -Wextra

.PHONY: all
all : simple test_smart_string_append test_smart_string_append_sprintf sane

simple: simple.o smart_string.o
	cc $(CFLAGS) -o simple simple.o smart_string.o
test_smart_string_append: test_smart_string_append.o smart_string.o
	cc $(CFLAGS) -o test_smart_string_append test_smart_string_append.o smart_string.o
test_smart_string_append_sprintf: test_smart_string_append_sprintf.o smart_string.o
	cc $(CFLAGS) -o test_smart_string_append_sprintf test_smart_string_append_sprintf.o smart_string.o
sane: sane.o smart_string.o
	cc $(CFLAGS) -o sane sane.o smart_string.o
smart_simple.o: simple.c
	cc $(CFLAGS) -c simple.c
smart_string.o: ../smart_string.c
	cc $(CFLAGS) -c ../smart_string.c
.PHONY: clean
clean:
	rm -f *.o *.exe simple
