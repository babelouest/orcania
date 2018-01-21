#
# Orcania library
#
# Makefile used to build the tests
#
# Copyright 2017 Nicolas Mora <mail@babelouest.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU GENERAL PUBLIC LICENSE
# License as published by the Free Software Foundation;
# version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU GENERAL PUBLIC LICENSE for more details.
#
# You should have received a copy of the GNU General Public
# License along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC=gcc
CFLAGS=-Wall -D_REENTRANT -DDEBUG -g -O0
ORCANIA_LOCATION=../src
LIBS=-lc -lorcania -ljansson -lcheck -lpthread -lm -lrt -lsubunit -L$(ORCANIA_LOCATION)

all: test

clean:
	rm -f *.o str_test split_test memory_test jansson_test valgrind.txt

liborcania.so:
	cd $(ORCANIA_LOCATION) && $(MAKE) debug

str_test: str_test.c
	$(CC) $(CFLAGS) str_test.c -o str_test $(LIBS)

test_str_test: liborcania.so str_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./str_test

split_test: split_test.c
	$(CC) $(CFLAGS) split_test.c -o split_test $(LIBS)

test_split_test: liborcania.so split_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./split_test

memory_test: memory_test.c
	$(CC) $(CFLAGS) memory_test.c -o memory_test $(LIBS)

test_memory_test: liborcania.so memory_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./memory_test

jansson_test: jansson_test.c
	$(CC) $(CFLAGS) jansson_test.c -o jansson_test $(LIBS)

test_jansson_test: liborcania.so jansson_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./jansson_test

test: test_str_test test_split_test test_jansson_test
