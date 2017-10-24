# Orcania

Potluck with different functions for different purposes that can be shared among c programs

Used for my other projects.

## Installation

### Debian and Ubuntu packages

Orcania is now available in Debian Buster (testing), Debian sid and since Ubuntu 17.10 "The Artful Aardvark". To install it on your device, use the following command as root:

```shell
# apt install liborcania-dev # Or apt install liborcania1.1 if you don't need the development files
```

### Manual install

#### Prerequisites

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

#### Install Orcania library

Download Orcania source code from Github, compile and install:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania/src
$ make && sudo make install
```

##### Install in a different directory

To install Orcania library on a dfferent library, use a different $(PREFIX) value during install.

Example: install orcania in /tmp/lib directory

```shell
$ cd src
$ make && make PREFIX=/tmp install
```

You can install Orcania without root permission if your user has write access to `$(PREFIX)`.
A `ldconfig` command is executed at the end of the install, it will probably fail if you don't have root permission, but this is harmless.
If you choose to install Orcania in another directory, you must set your environment variable `LD_LIBRARY_PATH` properly.

##### Install as a static archive

To install Orcania library as a static archive, `liborcania.a`, use the make commands `make static*`:

```shell
$ cd src
$ make static && sudo make static-install # or make PREFIX=/tmp static-install if you want to install in `/tmp/lib`
```
