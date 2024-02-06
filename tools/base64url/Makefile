#
# base64url: Base64Url encode or decode FILE, or standard input, to standard output.
#
# Makefile used to build the software
#
# Copyright 2021-2022 Nicolas Mora <mail@babelouest.org>
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
ORCANIA_INCLUDE=../../include
ORCANIA_LOCATION=../../src
DESTDIR=/usr/local

CFLAGS+=-Wall -Werror -Wextra -Wpedantic -Wconversion -I$(ORCANIA_INCLUDE) $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-lc -lorcania -L$(ORCANIA_LOCATION)
ORCANIA_LIBRARY=../../src/liborcania.so
VALGRIND_COMMAND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes

all: base64url

all: ADDITIONALFLAGS= -O3

clean:
	rm -f *.o base64url *.b64

debug: base64url

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

$(ORCANIA_LIBRARY):
	cd $(ORCANIA_LOCATION) && $(MAKE) debug

base64url: $(ORCANIA_LIBRARY) base64url.c
	$(CC) -o base64url $(CFLAGS) base64url.c $(LIBS)

install: base64url
	mkdir -p $(DESTDIR)/bin $(DESTDIR)/man/man1/
	install -m755 base64url $(DESTDIR)/bin
	install -m644 base64url.1 $(DESTDIR)/man/man1/

uninstall:
	rm -f $(DESTDIR)/bin/base64url

manpage: base64url
	help2man ./base64url -s 1 -n "Base64Url encode or decode FILE, or standard input, to standard output." > base64url.1

test: base64url
	echo plop | LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url
	LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -f README.md
	LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -f error || true
	echo ";error;" | LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -d || true
	echo Z3J1dAo | LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -d
	echo ZuJ1dAo | LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -d -i
	echo plop | LD_LIBRARY_PATH=$(ORCANIA_LOCATION) $(VALGRIND_COMMAND) ./base64url -w 2
