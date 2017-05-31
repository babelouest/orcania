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

Download Orania source code from Github, compile and install:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania/src
$ make && sudo make install
```
