@echo off

:: Remove old windows.h header, if present.
del /F /Q windows.h

:: Generate skeleton
echo #ifndef _WINDOWS_>> windows.h
echo #pragma once>> windows.h
echo #ifndef _INC_WINDOWS>> windows.h
echo #define _INC_WINDOWS>> windows.h
echo #ifndef WINDOWS_H>> windows.h
echo #define WINDOWS_H>> windows.h
echo:>> windows.h

:: Append files
echo:>> windows.h
type windows_base.h >> windows.h
echo:>> windows.h
type atomic.h >> windows.h
echo:>> windows.h
type dbghelp.h >> windows.h
echo:>> windows.h
type dds.h >> windows.h
echo:>> windows.h
type file.h >> windows.h
echo:>> windows.h
type gdi.h >> windows.h
echo:>> windows.h
type io.h >> windows.h
echo:>> windows.h
type misc.h >> windows.h
echo:>> windows.h
type process.h >> windows.h
echo:>> windows.h
type sysinfo.h >> windows.h
echo:>> windows.h
type threads.h >> windows.h
echo:>> windows.h
type window.h >> windows.h
echo:>> windows.h
type intrin.h >> windows.h
echo:>> windows.h
type fiber.h >> windows.h
echo:>> windows.h

:: Finish skeleton
echo #endif>> windows.h
echo #endif>> windows.h
echo #define _WINDOWS_>> windows.h
echo #endif>> windows.h

