# Orcania

Potluck with different functions for different purposes that can be shared among c programs.

## Installation

### Debian-ish packages

[![Packaging status](https://repology.org/badge/vertical-allrepos/orcania.svg)](https://repology.org/metapackage/orcania)

Orcania is available in Debian Buster (testing), Debian Sid (unstable) and some Debian based distributions. To install it on your device, use the following command as root:

```shell
# apt install liborcania-dev # Or apt install liborcania1.1 if you don't need the development files
```

### Build from source

Download Orcania source code from Github:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania
```

#### Prerequisites

You should need [Jansson library](http://www.digip.org/jansson/) in order to install Orcania.

On a Debian based distribution, simply run the following command:

```shell
$ sudo apt-get install libjansson-dev
```

If you know you don't need Jansson, refer to the install procedure (Makefile or CMake) on how to disable building Orcania without Jansson.

#### Good ol' Makefile

Go to `src/` directory, compile and install:

```shell
$ cd src
$ make && sudo make install
```

This will install Orcania's files under `/usr/local/` PREFIX.

If you don't want/need `libjansson` specific functions, you can skip it with the build option `JANSSONFLAG=-DU_DISABLE_JANSSON`

```
$ cd src
$ make JANSSONFLAG=-DU_DISABLE_JANSSON
```

To build and install as a static archive, use the make commands `make static*`:

```shell
$ cd src
$ make static && sudo make static-install # or make PREFIX=/tmp static-install if you want to install in `/tmp/lib`
```

#### CMake

Run the cmake script in a subdirectory, example:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania/
$ mkdir build
$ cd build
$ cmake ..
$ make && sudo make install
```

The available options for cmake are:
- `-DBUILD_STATIC=[on|off]` (default `off`): Build the static archive in addition to the shared library
- `-DWITH_JANSSON=[on|off]` (default `on`): Build with Jansson dependency
- `-DBUILD_TESTING=[on|off]` (default `off`): Build unit tests
- `-DINSTALL_HEADER=[on|off]` (default `on`): Install header file `orcania.h`
