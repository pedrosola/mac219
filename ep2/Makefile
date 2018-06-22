CC      = gcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic
LDFLAGS = -lpthread -lm


main: main.o matrix.o reduction.o
	$(CC) $(CFLAGS) -o $@ $^
test: test.o matrix.o reduction.o
	$(CC) $(CFLAGS) -o $@ $^
	#./test 1000

test.o: test.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c $<

reduction.o: reduction.c reduction.h
	$(CC) $(CFLAGS) -c $<
# clean
clean:
	rm -f *.o main test
