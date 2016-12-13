#
#	Makefile for PRC3
#
#	(c) Fontys 2016 Jeffrey Kain & Mehmet Bakirci
#

BINARIES = Read_shm Main
OBJECTS =

#CC = i586-linux-g++
CC = g++
CFLAGS =  -lrt -lpthread
LDLIBS =

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

Read_shm: Read_shm.o $(OBJECTS) $(CFLAGS)

Main: Main.o $(OBJECTS) $(CFLAGS)




