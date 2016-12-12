#
#	Makefile for PRC3
#
#	(c) Fontys 2016 Jeffrey Kain & Mehmet Bakirci
#

BINARIES = Read_shm
READ_OBJS =

#CC = i586-linux-g++
CC = g++
CFLAGS =  -lrt
LDLIBS =

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

Read_shm: Read_shm.o $(READ_OBJS) $(CFLAGS)




