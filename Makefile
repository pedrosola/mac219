CC      = gcc
CFLAGS  = -O3 -march=native -flto -g -Wall -pedantic
LDFLAGS = -lpthread -lm


main: main.o multi.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

#.PHONY: test
#test: test.o bakery.o gate.o general_lock.o
#	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
#	./test

main.o: main.c
	$(CC) $(CFLAGS) -c $<

multi.o: multi.c multi.h
	$(CC) $(CFLAGS) -c $<

#.PHONY: clean
clean:
	rm -f *.o main
