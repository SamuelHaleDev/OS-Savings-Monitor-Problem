CFLAGS= -g
LDFLAGS= -pthread
CC=g++

all: savingsProblemA

# To make an executable
savingsProblemA: savingsProblemA.o 
	$(CC) $(LDFLAGS) -o savingsProblemA savingsProblemA.o


# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm savingsProblemA *.o

