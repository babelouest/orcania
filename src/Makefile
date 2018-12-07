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
VERSION=1.2.9
OBJECTS=orcania.o memory.o base64.o
LIBS=-lc

ifndef JANSSONFLAG
DISABLE_JANSSON=0
LIBS+= -ljansson
else
DISABLE_JANSSON=1
endif

ifdef STRSTRFLAG
STRSTR=1
else
STRSTR=0
endif

all: release

$(CONFIG_FILE):
	@cp $(CONFIG_TEMPLATE) $(CONFIG_FILE)
	@echo Config file $(CONFIG_FILE) generated
	@sed -i -e 's/$${PROJECT_VERSION}/$(VERSION)/g' $(CONFIG_FILE)        
	@if [ "$(DISABLE_JANSSON)" = "1" ]; then \
		sed -i -e 's/\#cmakedefine DISABLE_JANSSON/\#define U_DISABLE_JANSSON/g' $(CONFIG_FILE); \
		echo "JANSSON SUPPORT         DISABLED"; \
	else \
		sed -i -e 's/\#cmakedefine DISABLE_JANSSON/\/* #undef U_DISABLE_JANSSON *\//g' $(CONFIG_FILE); \
		echo "JANSSON SUPPORT         ENABLED"; \
	fi
	@if [ "$(STRSTR)" = "1" ]; then \
		sed -i -e 's/\#cmakedefine STRSTR/\#define O_STRSTR/g' $(CONFIG_FILE); \
		echo "FORCE IMPLEMENT STRSTR  ENABLED"; \
	else \
		sed -i -e 's/\#cmakedefine STRSTR/\/* #undef O_STRSTR *\//g' $(CONFIG_FILE); \
		echo "FORCE IMPLEMENT STRSTR  DISABLED"; \
	fi

liborcania.so: $(CONFIG_FILE) $(OBJECTS)
	$(CC) -shared -fPIC -Wl,-soname,$(OUTPUT) -o $(OUTPUT).$(VERSION) $(OBJECTS) $(LIBS) $(LDFLAGS)
	ln -sf $(OUTPUT).$(VERSION) $(OUTPUT)

liborcania.a: $(CONFIG_FILE) $(OBJECTS)
	ar rcs liborcania.a $(OBJECTS)

%.o: %.c ../include/orcania.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $<

clean:
	rm -f *.o *.so *.a $(OUTPUT) $(OUTPUT).* $(CONFIG_FILE)

install: all
	install $(OUTPUT).$(VERSION) $(DESTDIR)/lib
	install -m644 ../include/orcania.h $(DESTDIR)/include
	install -m644 $(CONFIG_FILE) $(DESTDIR)/include
	-ldconfig

static-install: static
	install liborcania.a $(DESTDIR)/lib
	install -m644 ../include/orcania.h $(DESTDIR)/include
	install -m644 $(CONFIG_FILE) $(DESTDIR)/include

uninstall:
	rm -f $(DESTDIR)/lib/$(OUTPUT) $(DESTDIR)/lib/liborcania.a
	rm -f $(DESTDIR)/lib/$(OUTPUT).*
	rm -f $(DESTDIR)/include/orcania.h
	rm -f $(DESTDIR)/include/orcania-cfg.h

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: liborcania.so

release: ADDITIONALFLAGS=-O3

release: liborcania.so

static-debug: ADDITIONALFLAGS=-DDEBUG -g -O0

static-debug: liborcania.a

static: ADDITIONALFLAGS=-O3

static: liborcania.a
