CC=gcc
CFLAGS=-I.
DEPS = shutdown.h

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

pauseChecker: pauseChecker.o shutdown.o
	$(CC) -o pauseChecker pauseChecker.o shutdown.o