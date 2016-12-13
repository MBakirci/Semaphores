#
#	Makefile for PRC3
#
#	(c) Fontys 2016 Jeffrey Kain & Mehmet Bakirci
#

BINARIES = Read_shm main
READ_OBJS =

#CC = i586-linux-g++
CC = g++
CFLAGS =  -lrt -lpthread
LDLIBS =

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

Read_shm: Read_shm.o $(READ_OBJS) $(CFLAGS)
main: main.o $(READ_OBJS) $(CFLAGS)




