CWD = $(shell pwd)

LDIR = $(CWD)/lib
DEPS += $(LDIR)/*.h
SDIR = $(CWD)/src
CGI = $(CWD)/cgi-bin
CGISRC = $(wildcard $(CGI)/*.c)
CGIOBJS += $(patsubst %.c, %, $(CGISRC))

CC = cc
CFLAGS += -Wall -g -I$(LDIR) 

OBJS += csapp.o tiny.o 
TARGET += tiny $(CGIOBJS)

all: $(TARGET)

tiny: csapp.o tiny.o
	$(CC) $(CFLAGS) $^ -o $@ 

csapp.o: $(LDIR)/csapp.c
	$(CC) $(CFLAGS) -c $^

tiny.o: $(SDIR)/tiny.c $(DEPS)
	$(CC) $(CFLAGS) -c $^

.PHONY: clean

clean:
	-rm -rf *~ *.o $(CGIOBJS) 
	

