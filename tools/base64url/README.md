# base64url: Base64Url encode or decode FILE, or standard input, to standard output.

Copyright 2021 Nicolas Mora <mail@babelouest.org>

This program is free software; you can redistribute it and/or modify it under the terms of the GPL3 License.

## Options

Options available:

```shell
-d, --decode
	Decode data
-i, --ignore-garbage
	when decoding, ignore non-alphabet characters
-w, --wrap <COLS>
	wrap encoded lines after COLS character (default 76).  Use 0 to disable line wrapping
-f, --file <FILE_NAME>
	Encode or decode FILE_NAME content - if this option is missing, red from stdin
-h, --help
	display this help and exit
-v, --version
	output version information and exit
```
