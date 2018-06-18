# Orcania

Potluck with different functions for different purposes that can be shared among C programs.

## Installation

### Distribution packages

[![Packaging status](https://repology.org/badge/vertical-allrepos/orcania.svg)](https://repology.org/metapackage/orcania)

Orcania is available in multiple distributions as official package. Check out your distribution documentation to install the package automatically.

### Pre-compiled packages

You can install Orcania with a pre-compiled package available in the [release pages](https://github.com/babelouest/orcania/releases/latest/). `jansson` development files packages is required to install Orcania.

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

#### CMake - Multi architecture

[CMake](https://cmake.org/download/) minimum 3.5 is required.

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
- `-DCMAKE_BUILD_TYPE=[Debug|Release]` (default `Release`): Compile with debugging symbols or not

#### Good ol' Makefile - Linux only

Go to `src/` directory, compile and install:

```shell
$ cd src
$ make && sudo make install
```

This will install Orcania's files under `/usr/local/` DESTDIR.

If you don't want/need `libjansson` specific functions, you can skip it with the build option `JANSSONFLAG=-DU_DISABLE_JANSSON`

```
$ cd src
$ make JANSSONFLAG=-DU_DISABLE_JANSSON
```

To build and install as a static archive, use the make commands `make static*`:

```shell
$ cd src
$ make static && sudo make static-install # or make DESTDIR=/tmp static-install if you want to install in `/tmp/lib`
```
