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

The only directory of interest is `include`, it includes:

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

