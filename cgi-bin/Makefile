CGIBINS = adder

all: $(CGIBINS)

define genbin
$1: $1.o $(DEPS)
	$(CC) $(CFLAGS) $$< -o $$@
endef

$(foreach bin, $(CGIBINS), $(eval $(call genbin, $(bin))))

.PHONY: clean


clean:
	-rm -rf $(CGIBINS) *.o
