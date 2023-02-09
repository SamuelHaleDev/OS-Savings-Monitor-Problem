CFLAGS= -g
LDFLAGS= -pthread
CC=g++

all: savingsProblemB

# To make an executable
savingsProblemB: savingsProblemB.o 
	$(CC) $(LDFLAGS) -o savingsProblemB savingsProblemB.o


# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm savingsProblemB *.o

