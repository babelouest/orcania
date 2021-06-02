#
# Public domain, no copyright. Use at your own risk.
#

CC=gcc
CFLAGS+=-Wall -D_REENTRANT -DDEBUG -g -O0 -I$(INCLUDE_LOCATION) $(CPPFLAGS)
ORCANIA_LOCATION=../src
INCLUDE_LOCATION=../include
ORCANIA_LIBRARY=$(ORCANIA_LOCATION)/liborcania.so
LDFLAGS=-lc -lorcania $(shell pkg-config --libs check) -L$(ORCANIA_LOCATION)
VALGRIND_COMMAND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all
TARGET=str_test split_test memory_test pointer_list_test
VERBOSE=0
MEMCHECK=0

all: test

clean:
	rm -f *.o $(TARGET) *.log valgrind-*.txt

$(ORCANIA_LIBRARY): $(ORCANIA_LOCATION)/orcania.c $(ORCANIA_LOCATION)/memory.c $(ORCANIA_LOCATION)/base64.c
	cd $(ORCANIA_LOCATION) && $(MAKE) debug  $*

%: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: $(ORCANIA_LIBRARY) $(TARGET) test_str_test test_split_test test_memory_test test_pointer_list_test

check: test

test_%: % $(ORCANIA_LIBRARY)
	@if [ "$(VERBOSE)" = "0" ] && [ "$(MEMCHECK)" = "0" ]; then \
		LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./run_test.sh ./$^; \
	elif [ "$(MEMCHECK)" = "0" ]; then \
		LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./$^ ; \
	else \
		CK_FORK=no LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./$^ 2>valgrind-$@.txt; \
	fi
