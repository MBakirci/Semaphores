#
#	Makefile for PRC3
#
#	(c) Fontys 2016 Jeffrey Kain & Mehmet Bakirci
#

BINARIES = Read_shm Write_shm Read_queue Write_queue
READ_OBJS =

#CC = i586-linux-g++
CC = gcc
CFLAGS =  -lrt -lpthread
LDLIBS =
SRCS = $(wildcard ./*.c)
OBJS = $(subst .c,.o,$(SRCS))

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

Read_shm: Read_shm.o $(READ_OBJS) $(CFLAGS)
Write_shm: Write_shm.o $(READ_OBJS) $(CFLAGS)
Read_queue: Read_queue.o $(READ_OBJS) $(CFLAGS)
Write_queue: Write_queue.o $(READ_OBJS) $(CFLAGS)

producer-consumer: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@



