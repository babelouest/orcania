# Orcania Changelog

## 2.3.4

- Minor bugfixes
- Build with flag `-Wpedantic`

## 2.3.3

- Enforce base64decode

## 2.3.2

- Improve cmake script and MSVC support
- Build with flag `-Wconversion`

## 2.3.1

- Minor bugfixes

## 2.3.0

- Add `o_base64_encode_alloc`, `o_base64_decode_alloc`, `o_base64url_encode_alloc`, `o_base64url_decode_alloc`, `o_base64url_2_base64_alloc`, `o_base64_2_base64url_alloc`
- Fix pkg-config file with absolute path for `CMAKE_INSTALL_{INCLUDE,LIB}DIR`, Closes #27

## 2.2.2

- Add `o_strnullempty`
- Breaking: `trimwhitespace` now returns `const char *` instead of `char *`, might give compiler warning
- Refactor `o_base64*` functions

## 2.2.1

- Add ld flags in liborcania.pc on static build

## 2.2.0

- Add command-line tool `base64url` which is similar to GNU `base64` tool but for `base64url` format

## 2.1.1

- Harmonize and fix license
- Fix doc generator
- Rework mstrcatf
- Fix pkgconfig install on Makefile
- Add simple API documentation summary

## 2.1.0

- Add doxygen documentation
- Add functions `pointer_list_clean_free`, `pointer_list_remove_at_free` and `pointer_list_remove_pointer_free`
- `split_string` returns `size_t`
- Add functions `o_strnchr` and `o_strrnchr`
- Add function `trimcharacter`
- Improve `o_base64_decode` if input data is invalid

## 2.0.1

- Fix double free() on `pointer_list_remove_at`
- Fix build for MacOSX (thanks JohnAZoidberg!)
- Clean build process
- Fix config option STRTSR so cmake and makefile will use the same name

## 2.0.0

- Add struct _pointer_list to manage arrays of pointers
- Add string_array_join, string_array_size
- Add o_base64url_encode and o_base64url_decode, and o_base64url_2_base64 to convert base64 url format to base64
- Remove jansson related functions and dependency
- Install pkgconfig file when using Makefile

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
