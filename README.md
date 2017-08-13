# Orcania

Potluck with different functions for different purposes that can be shared among angharad programs

Used for my other projects.

## Installation

### Prerequisites

You need [Jansson library](http://www.digip.org/jansson/) in order to install Orcania.

On a Debain based distribution, simply run the following command:

```shell
$ sudo apt-get install libjansson-dev
```

If you don't want `libjansson` specific functions, you can skip it with the build option `JANSSONFLAG=-DU_DISABLE_JANSSON`

```
$ cd src
$ make JANSSONFLAG=-DU_DISABLE_JANSSON
```

### Install Orcania library

Download Orcania source code from Github, compile and install:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania/src
$ make && sudo make install
```

#### Install in a different directory

To install Orcania library on a dfferent library, use a different $(PREFIX) value during install.

Example: install orcania in /tmp/lib directory

```shell
$ cd src
$ make && make PREFIX=/tmp install
```

#### Install as a static archive

To install Orcania library as a static archive, `liborcania.a`, use the make commands `make static*`:

```shell
$ cd src
$ make static && sudo make static-install # or make PREFIX=/tmp static-install if you want to install in `/tmp/lib`
```
