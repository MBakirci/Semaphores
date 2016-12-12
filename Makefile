#
#	Makefile for PRC3
#
#	(c) Fontys 2016 Jeffrey Kain & Mehmet Bakirci
#

BINARIES = Main
SOURCES =

#CC = i586-linux-g++
CC = g++
CFLAGS = -o

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

TCPChatClient: TCPChatClient.o $(CLIENT_AUX_OBJS)




