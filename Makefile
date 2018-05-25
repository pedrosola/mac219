CC      = gcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic -fopenmp
LDFLAGS = -lpthread -lm 


main: main.o matrix.o multi.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: test.o matrix.o multi.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
#mkdir sample
	./test
#rm -r sample

test.o: test.c
	$(CC) $(CFLAGS) -c $<
main.o: main.c
	$(CC) $(CFLAGS) -c $<

multi.o: multi.c multi.h
	$(CC) $(CFLAGS) -c $<
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c $<

# clean
clean:
	rm -f *.o *.sample main test
