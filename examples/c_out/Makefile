CC=gcc
DEPS = stack/stack.h
OBJ = $(file).o stack.o

stack.o: stack/stack.c $(DEPS)
	$(CC) -c $^

$(file).o: $(file).c $(DEPS)
	$(CC) -c $^

output: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm *.o output