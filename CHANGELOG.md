# Orcania Changelog

## 1.3.0

- Add struct _pointer_list to manage arrays of pointers

## 1.2.9

- Add build flag to force inline implementation of strstr if the host system is
  not known to implement strstr but isn't listed as so, like FreeRTOS
  Thanks to Dirk Uhlemann
- Avoid babelouest/ulfius#84

## 1.2.8

- Fix build with Makefile
- Improve build config file and install headers 

## 1.2.7

- Add config file orcania-cfg.h dynamically built with the options

## 1.2.6

- Add Travis CI
- Change cmake option BUILD_TESTING to BUILD_YDER_TESTING
- Add RPM in CMake script package

## 1.2.5

- Fix pkgconfig file

## 1.2.4

- Fix CMake build when /usr/local is not present in default build path

## 1.2.3

- Fix Makefile soname

## 1.2.2

- Upgrade Makefile

## 1.2.1

- Fix string_array_has_trimmed_value

## 1.2.0

- Add CMake installation script
