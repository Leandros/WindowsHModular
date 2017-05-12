# Modular Windows.h Header File

The Windows.h header file for the Win32 API is a behemoth of include file,
adding hundreds of thousands of new macros, structs and functions.

This project aims to modularize the Windows.h file, to only include what you
require.


## Contribution

**All contributions are welcome**, if we make this a crowdsourced effort, this
can be completed a lot quicker. If any functions are missing, please feel free
to add them and submit a pull request. I'll merge them as soon as possible


## Usage

The only directory of interest is `include`, copy the contents of the directory
over to your project, set the include path to point to the directory containing
the `win32` directory.

Due to very generic naming and danger of naming collisions, it's recommended
to always keep them in the `win32` directory and keep it explicit in the include
directives: `#include <win32/file.h>`.


The `win32` directory contains the following:

- Modular include files:
	- `windows_base.h`
	- `atomic.h`
	- `dbghelp.h`
	- `dds.h`
	- `file.h`
	- `gdi.h`
	- `io.h`
	- `misc.h`
	- `process.h`
	- `sysinfo.h`
	- `threads.h`
	- `window.h`
- Amalgamated include file (`#include`'ing the files above):
	- `windows_modular.h`
- Full windows include (inlining the files above):
	- `windows.h`

`windows_base.h` is included by each of the modular include files, it contains
the required types, macros and structures used by multiple modules.


## Differences to Microsofts Windows.h

We try to provide a full replacement to Microsofts own headers, while keeping
a reasonable amount of compatability and to not break any existing code.

However, there are a few breaking changes you should be aware off:

1. Functions which exist in two variants, unicode and ascii are missing the generic macro.
You have to manually specify if you wish to call the unicode or ascii variant by appending
either `A` or `W`, for example `CreateFileA` and `CreateFileW`.
2. `MIN`/`MAX` macros are not provided, equivalent to `#define NOMINMAX`.
3. Many, many functions are still missing. Please provide us with what you need and
we try to integrate them as soon as possible.


## Testing

The `test` directory contains a simple test case.

The test case consists of compiling each module file with full warnings turned
on, this will make sure all dependencies are met and no warnings are emitted.

It can be executed by calling:

```
$ nmake
```

Requires `CL.EXE` and `NMAKE.EXE` in your path.


## License

This project is dual-licensed under the "MIT" & "Unlicense" license.

