#
# Orcania Library
#
# Makefile used to build the software
#
# Copyright 2014-2018 Nicolas Mora <mail@babelouest.org>
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
ORCANIA_INCLUDE=../include
CONFIG_TEMPLATE=$(ORCANIA_INCLUDE)/orcania-cfg.h.in
CONFIG_FILE=$(ORCANIA_INCLUDE)/orcania-cfg.h
CC=gcc
CFLAGS+=-c -fPIC -Wall -Werror -Wextra -I$(ORCANIA_INCLUDE) -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
OUTPUT=liborcania.so
VERSION=1.2.7

ifndef JANSSONFLAG
DISABLE_JANSSON=0
LJANSSON=-ljansson
else
DISABLE_JANSSON=1
endif

LIBS=-lc $(LJANSSON)

all: release

config:
	@if [ -f $(CONFIG_FILE) ]; then rm -f $(CONFIG_FILE); fi
	@cp $(CONFIG_TEMPLATE) $(CONFIG_FILE)
	@sed -i -e 's/$${PROJECT_VERSION}/$(VERSION)/g' $(CONFIG_FILE)        
	@if [ "$(DISABLE_JANSSON)" = "1" ]; then \
		sed -i -e 's/\#cmakedefine DISABLE_JANSSON/\#define U_DISABLE_JANSSON/g' $(CONFIG_FILE); \
	else \
		sed -i -e 's/\#cmakedefine DISABLE_JANSSON/\/* #undef U_DISABLE_JANSSON *\//g' $(CONFIG_FILE); \
	fi
	@echo Config file $(CONFIG_FILE) generated

liborcania.so: config memory.o orcania.o base64.o
	$(CC) -shared -fPIC -Wl,-soname,$(OUTPUT) -o $(OUTPUT).$(VERSION) orcania.o memory.o base64.o $(LIBS) $(LDFLAGS)
	ln -sf $(OUTPUT).$(VERSION) $(OUTPUT)

liborcania.a: config memory.o orcania.o base64.o
	ar rcs liborcania.a memory.o orcania.o base64.o

%.o: %.c ../include/orcania.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $<

clean:
	rm -f *.o *.so *.a $(OUTPUT) $(OUTPUT).* $(CONFIG_FILE)

install: all
	install $(OUTPUT).$(VERSION) $(DESTDIR)/lib
	install ../include/orcania.h $(DESTDIR)/include
	install $(CONFIG_FILE) $(DESTDIR)/include
	-ldconfig

static-install: static
	install liborcania.a $(DESTDIR)/lib
	install ../include/orcania.h $(DESTDIR)/include
	install $(CONFIG_FILE) $(DESTDIR)/include

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
