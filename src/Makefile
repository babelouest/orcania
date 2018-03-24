#
# Ulfius Framework
#
# Makefile used to build the software
#
# Copyright 2014-2017 Nicolas Mora <mail@babelouest.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation;
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU GENERAL PUBLIC LICENSE for more details.
#
# You should have received a copy of the GNU General Public
# License along with this library.	If not, see <http://www.gnu.org/licenses/>.
#
DESTDIR=/usr/local
CC=gcc
CFLAGS+=-c -fPIC -Wall -Werror -Wextra -D_REENTRANT $(ADDITIONALFLAGS) $(JANSSONFLAG)
OUTPUT=liborcania.so
VERSION=1.2.1

ifndef JANSSONFLAG
LJANSSON=-ljansson
endif

LIBS=-lc $(LJANSSON)

all: release

liborcania.so: memory.o orcania.o base64.o
	$(CC) -shared -Wl,-soname,$(OUTPUT).$(VERSION) -o $(OUTPUT).$(VERSION) orcania.o memory.o base64.o $(LIBS) $(LDFLAGS)
	ln -sf $(OUTPUT).$(VERSION) $(OUTPUT)

liborcania.a: memory.o orcania.o base64.o
	ar rcs liborcania.a memory.o orcania.o base64.o

%.o: %.c ../include/orcania.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $<

clean:
	rm -f *.o *.so *.a $(OUTPUT) $(OUTPUT).*

install: all
	install $(OUTPUT).$(VERSION) $(DESTDIR)/lib
	install ../include/orcania.h $(DESTDIR)/include
	-ldconfig

static-install: static
	install liborcania.a $(DESTDIR)/lib
	install ../include/orcania.h $(DESTDIR)/include

uninstall:
	rm -f $(DESTDIR)/lib/$(OUTPUT) $(DESTDIR)/lib/liborcania.a
	rm -f $(DESTDIR)/lib/$(OUTPUT).*
	rm -f $(DESTDIR)/include/orcania.h

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: liborcania.so

release: ADDITIONALFLAGS=-O3

release: liborcania.so

static-debug: ADDITIONALFLAGS=-DDEBUG -g -O0

static-debug: liborcania.a

static: ADDITIONALFLAGS=-O3

static: liborcania.a
