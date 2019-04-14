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
PROJECT_NAME=orcania
PROJECT_DESCRIPTION="Potluck with different functions for different purposes that can be shared among programs"
PROJECT_BUGREPORT_PATH="https://github.com/babelouest/orcania/issues"
PKGCONF_REQ=""
PKGCONF_REQ_PRIVATE=""
DESTDIR=/usr/local
ORCANIA_INCLUDE=../include
CONFIG_TEMPLATE=$(ORCANIA_INCLUDE)/orcania-cfg.h.in
CONFIG_FILE=$(ORCANIA_INCLUDE)/orcania-cfg.h
PKGCONFIG_FILE=../liborcania.pc
PKGCONFIG_TEMPLATE=../liborcania.pc.in
CC=gcc
CFLAGS+=-c -fPIC -Wall -Werror -Wextra -I$(ORCANIA_INCLUDE) -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
OUTPUT=liborcania.so
VERSION=2.0.0
OBJECTS=orcania.o memory.o base64.o
LIBS=-lc

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
	@if [ "$(STRSTR)" = "1" ]; then \
		sed -i -e 's/\#cmakedefine STRSTR/\#define O_STRSTR/g' $(CONFIG_FILE); \
		echo "FORCE IMPLEMENT STRSTR  ENABLED"; \
	else \
		sed -i -e 's/\#cmakedefine STRSTR/\/* #undef O_STRSTR *\//g' $(CONFIG_FILE); \
		echo "FORCE IMPLEMENT STRSTR  DISABLED"; \
	fi

$(PKGCONFIG_FILE):
	@cp $(PKGCONFIG_TEMPLATE) $(PKGCONFIG_FILE)
	@echo Pkgconfig file $(PKGCONFIG_FILE) generated
	@sed -i -e 's#@CMAKE_INSTALL_PREFIX@#$(DESTDIR)#g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@CMAKE_INSTALL_LIBDIR@/lib/g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@CMAKE_INSTALL_INCLUDEDIR@/include/g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@PROJECT_NAME@/$(PROJECT_NAME)/g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@PROJECT_DESCRIPTION@/$(PROJECT_DESCRIPTION)/g' $(PKGCONFIG_FILE)
	@sed -i -e 's|@PROJECT_BUGREPORT_PATH@|$(PROJECT_BUGREPORT_PATH)|g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@LIBRARY_VERSION@/$(VERSION)/g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@PKGCONF_REQ@/$(PKGCONF_REQ)/g' $(PKGCONFIG_FILE)
	@sed -i -e 's/@PKGCONF_REQ_PRIVATE@/$(PKGCONF_REQ_PRIVATE)/g' $(PKGCONFIG_FILE)

liborcania.so: $(OBJECTS)
	$(CC) -shared -fPIC -Wl,-soname,$(OUTPUT) -o $(OUTPUT).$(VERSION) $(OBJECTS) $(LIBS) $(LDFLAGS)
	ln -sf $(OUTPUT).$(VERSION) $(OUTPUT)

liborcania.a: $(OBJECTS)
	ar rcs liborcania.a $(OBJECTS)

%.o: %.c $(CONFIG_FILE) ../include/orcania.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o *.so *.a $(OUTPUT) $(OUTPUT).* $(CONFIG_FILE) $(PKGCONFIG_FILE)

install: all $(PKGCONFIG_FILE)
	install $(OUTPUT).$(VERSION) $(DESTDIR)/lib
	install $(PKGCONFIG_FILE) $(DESTDIR)/lib/pkgconfig
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
	rm -f $(DESTDIR)/lib/pkgconfig/$(PKGCONFIG_FILE)

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: liborcania.so

release: ADDITIONALFLAGS=-O3

release: liborcania.so

static-debug: ADDITIONALFLAGS=-DDEBUG -g -O0

static-debug: liborcania.a

static: ADDITIONALFLAGS=-O3

static: liborcania.a
