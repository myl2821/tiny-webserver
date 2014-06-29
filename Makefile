CWD = $(shell pwd)

LDIR = $(CWD)/lib
DEPS += $(LDIR)/*.h
SDIR = $(CWD)/src
CGIDIR = $(CWD)/cgi-bin

SSRC = $(wildcard $(SDIR)/*.c $(LDIR)/*.c)
SLIST = $(patsubst %.c, %, $(SSRC))
SOBJS = $(patsubst %, %.o, $(SLIST))

CC = cc
CFLAGS += -Wall -g -I$(LDIR) 

TARGET += tiny cgi

all: $(TARGET)

tiny: $(SOBJS)
	$(CC) $(CFLAGS) $^ -o $@

define  genobj
$1.o: $1.c $(DEPS)
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(foreach m, $(SLIST), $(eval $(call genobj, $(m))))

export
cgi:
	$(MAKE) -C $(CGIDIR)

.PHONY: clean

clean:
	-rm -rf tiny $(SOBJS)
	$(MAKE) -C $(CGIDIR) clean
	

