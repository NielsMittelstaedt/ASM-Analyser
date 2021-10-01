CC=gcc
OBJ = $(file).o

$(file).o: ../examples/ $(file).c
	$(CC) -c $^

output: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm *.o output