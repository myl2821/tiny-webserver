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

tiny:tiny.o
	$(CC) $(CFLAGS) tiny.o doit.o \
	clienterror.o parse_url.o \
	serve_static.o serve_dynamic.o $(LDIR)/csapp.o -o $@
	rm *.o

tiny.o: $(SDIR)/tiny.c $(SDIR)/doit.c \
	$(SDIR)/clienterror.c $(SDIR)/parse_url.c \
	$(SDIR)/serve_static.c $(SDIR)/serve_dynamic.c $(DEPS)
	$(CC) $(CFLAGS) -c $^  


.PHONY: clean

clean:
	-rm -rf *~ *.o $(CGIOBJS) tiny
	

