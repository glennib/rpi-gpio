#MACROS

SRCPATH		= ./src
INCPATH		= ./include
OBJPATH		= ./obj
INSTPATH	= ./bin
CC		= g++
CFLAGS		= -std=c++11 -g -Wall -I$(INCPATH)


# TARGETS

all: getobj app putobj

app: main.o Pin.o
	$(CC) $(CFLAGS) -o $(INSTPATH)/light.app main.o Pin.o

main.o: $(SRCPATH)/main.cpp $(INCPATH)/Pin.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/main.cpp

Pin.o: $(SRCPATH)/Pin.cpp $(INCPATH)/Pin.h
	$(CC) $(CFLAGS) -c $(SRCPATH)/Pin.cpp

getobj:
	-mv $(OBJPATH)/*.o .

putobj:
	-mv *.o $(OBJPATH)

clean:
	-rm -f $(OBJPATH)/*.o
	-rm -f $(INSTPATH)/*	
