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
PREFIX=/usr/local
CC=gcc
CFLAGS=-c -fPIC -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(JANSSONFLAG)
LIBS=-lc -ljansson
OUTPUT=liborcania.so
VERSION=1.1

ifneq (($(JANSSONFLAG)),"")
LJANSSON=-ljansson
endif

all: release

liborcania.so: memory.o orcania.o base64.o
	$(CC) -shared -Wl,-soname,$(OUTPUT) -o $(OUTPUT).$(VERSION) orcania.o memory.o base64.o $(LIBS)
	ln -sf $(OUTPUT).$(VERSION) $(OUTPUT)

orcania.o: orcania.h orcania.c
	$(CC) $(CFLAGS) orcania.c

memory.o: orcania.h memory.c
	$(CC) $(CFLAGS) memory.c

base64.o: orcania.h base64.c
	$(CC) $(CFLAGS) base64.c

clean:
	rm -f *.o *.so $(OUTPUT) $(OUTPUT).*

install: all
	cp $(OUTPUT).$(VERSION) $(PREFIX)/lib
	cp orcania.h $(PREFIX)/include
	/sbin/ldconfig -r $(PREFIX)

uninstall:
	rm -f $(PREFIX)/lib/$(OUTPUT)
	rm -f $(PREFIX)/lib/$(OUTPUT).*
	rm -f $(PREFIX)/include/orcania.h

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: liborcania.so

release: ADDITIONALFLAGS=-O3

release: liborcania.so
