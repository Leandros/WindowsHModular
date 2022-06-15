/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_IO_H
#define WINDOWS_IO_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#ifndef WINDOWS_BASE_H
#include "windows_base.h"
#endif
#if defined(__cplusplus)
extern "C" {
#endif

/* GetStdHandle: */
#define STD_INPUT_HANDLE        ((DWORD)-10)
#define STD_OUTPUT_HANDLE       ((DWORD)-11)
#define STD_ERROR_HANDLE        ((DWORD)-12)
#define INVALID_HANDLE_VALUE    ((HANDLE)(LONG_PTR)-1)
#define ATTACH_PARENT_PROCESS   ((DWORD)-1)

#define HANDLE_FLAG_INHERIT             0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE  0x00000002

/* Console Colors: */
#define FOREGROUND_BLUE         0x0001
#define FOREGROUND_GREEN        0x0002
#define FOREGROUND_RED          0x0004
#define FOREGROUND_INTENSITY    0x0008
#define BACKGROUND_BLUE         0x0010
#define BACKGROUND_GREEN        0x0020
#define BACKGROUND_RED          0x0040
#define BACKGROUND_INTENSITY    0x0080

/* Console Handler */
#define CTRL_C_EVENT            0x0
#define CTRL_BREAK_EVENT        0x1
#define CTRL_CLOSE_EVENT        0x2
#define CTRL_LOGOFF_EVENT       0x5
#define CTRL_SHUTDOWN_EVENT     0x6

/* Console Input Mode flags */
#define ENABLE_PROCESSED_INPUT              0x0001
#define ENABLE_LINE_INPUT                   0x0002
#define ENABLE_ECHO_INPUT                   0x0004
#define ENABLE_WINDOW_INPUT                 0x0008
#define ENABLE_MOUSE_INPUT                  0x0010
#define ENABLE_INSERT_MODE                  0x0020
#define ENABLE_QUICK_EDIT_MODE              0x0040
#define ENABLE_EXTENDED_FLAGS               0x0080
#define ENABLE_AUTO_POSITION                0x0100
#define ENABLE_VIRTUAL_TERMINAL_INPUT       0x0200

/* Console Output Mode flags */
#define ENABLE_PROCESSED_OUTPUT             0x0001
#define ENABLE_WRAP_AT_EOL_OUTPUT           0x0002
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#define DISABLE_NEWLINE_AUTO_RETURN         0x0008
#define ENABLE_LVB_GRID_WORLDWIDE           0x0010

/* HeapAlloc, HeapReAlloc, etc: */
#define HEAP_NO_SERIALIZE           0x00000001
#define HEAP_ZERO_MEMORY            0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY  0x00000010

/* Heap / Memory: */
typedef enum _HEAP_INFORMATION_CLASS {
    HeapCompatibilityInformation = 0,
    HeapEneableTerminationOnCorruption = 1,
    HeapOptimizeResources = 3
} HEAP_INFORMATION_CLASS;

/* VirtualAlloc.flAllocationType: */
#define MEM_COMMIT                  0x00001000
#define MEM_RESERVE                 0x00002000
#define MEM_RESET                   0x00080000
#define MEM_RESET_UNDO              0x01000000
#define MEM_LARGE_PAGES             0x20000000
#define MEM_PHYSICAL                0x00400000
#define MEM_TOP_DOWN                0x00100000
#define MEM_WRITE_WATCH             0x00200000

/* VirtualAlloc.flProtect: */
#define PAGE_EXECUTE                0x10
#define PAGE_EXECUTE_READ           0x20
#define PAGE_EXECUTE_READWRITE      0x40
#define PAGE_EXECUTE_WRITECOPY      0x80
#define PAGE_NOACCESS               0x01
#define PAGE_READONLY               0x02
#define PAGE_READWRITE              0x04
#define PAGE_WRITECOPY              0x08
#define PAGE_TARGETS_INVALID        0x40000000
#define PAGE_TARGETS_NO_UPDATE      0x40000000
#define PAGE_GUARD                  0x100
#define PAGE_NOCACHE                0x200
#define PAGE_WRITECOMBINE           0x400

/* VirtualFree.dwFreeType: */
#define MEM_DECOMMIT                0x4000
#define MEM_RELEASE                 0x8000

/* VirtualQuery State and Type: */
#define MEM_FREE                    0x10000
#define MEM_IMAGE                   0x1000000
#define MEM_MAPPED                  0x40000
#define MEM_PRIVATE                 0x20000


/* ========================================================================== */
/* Structures:                                                                */
typedef struct _COORD {
    SHORT       X;
    SHORT       Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
    SHORT       Left;
    SHORT       Top;
    SHORT       Right;
    SHORT       Bottom;
} SMALL_RECT;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD       dwSize;
    COORD       dwCursorPosition;
    WORD        wAttributes;
    SMALL_RECT  srWindow;
    COORD       dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

typedef BOOL (WINAPI *PHANDLER_ROUTINE)(DWORD dwCtrlType);

typedef struct _MEMORY_BASIC_INFORMATION32 {
    DWORD       BaseAddress;
    DWORD       AllocationBase;
    DWORD       AllocationProtect;
    DWORD       RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
} MEMORY_BASIC_INFORMATION32, *PMEMORY_BASIC_INFORMATION32;

typedef struct __declspec(align(16)) _MEMORY_BASIC_INFORMATION64 {
    ULONGLONG   BaseAddress;
    ULONGLONG   AllocationBase;
    DWORD       AllocationProtect;
    DWORD       __alignment1;
    ULONGLONG   RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
    DWORD       __alignment2;
} MEMORY_BASIC_INFORMATION64, *PMEMORY_BASIC_INFORMATION64;
#if defined(_WIN64)
typedef MEMORY_BASIC_INFORMATION64  MEMORY_BASIC_INFORMATION;
typedef PMEMORY_BASIC_INFORMATION64 PMEMORY_BASIC_INFORMATION;
#else
typedef MEMORY_BASIC_INFORMATION32  MEMORY_BASIC_INFORMATION;
typedef PMEMORY_BASIC_INFORMATION32 PMEMORY_BASIC_INFORMATION;
#endif


/* ========================================================================== */
/* I/O Functions: */
HANDLE WINAPI GetStdHandle(
        DWORD nStdHandle);
BOOL WINAPI GetConsoleScreenBufferInfo(
        HANDLE hConsoleOutput,
        PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);
BOOL WINAPI SetConsoleTextAttribute(
        HANDLE hConsoleOutput,
        WORD wAttributes);
BOOL WINAPI GetConsoleMode(
        HANDLE hConsoleHandle,
        LPDWORD lpMode);
BOOL WINAPI SetConsoleMode(
        HANDLE hConsoleHandle,
        DWORD dwMode);
BOOL WINAPI CloseHandle(
        HANDLE hObject);
BOOL WINAPI SetHandleInformation(
        HANDLE hObject,
        DWORD  dwMask,
        DWORD  dwFlags);
BOOL WINAPI DuplicateHandle(
        HANDLE hSourceProcessHandle,
        HANDLE hSourceHandle,
        HANDLE hTargetProcessHandle,
        LPHANDLE lpTargetHandle,
        DWORD dwDesiredAccess,
        BOOL bInheritHandle,
        DWORD dwOptions);


LPSTR WINAPI GetCommandLineA(void);
LPWSTR WINAPI GetCommandLineW(void);
#ifdef UNICODE
#define GetCommandLine GetCommandLineW
#else
#define GetCommandLine GetCommandLineA
#endif

/* ========================================================================== */
/* Console Functions: */
BOOL WINAPI AllocConsole(void);
BOOL WINAPI FreeConsole(void);
BOOL WINAPI AttachConsole(
        DWORD dwProcessId);
BOOL WINAPI WriteConsoleA(
        HANDLE hConsoleOutput,
        const void *lpBuffer,
        DWORD nNumberOfCharsToWrite,
        LPDWORD lpNumberOfCHarsWritten,
        LPVOID lpReserved);
BOOL WINAPI WriteConsoleW(
        HANDLE hConsoleOutput,
        const void *lpBuffer,
        DWORD nNumberOfCharsToWrite,
        LPDWORD lpNumberOfCHarsWritten,
        LPVOID lpReserved);
BOOL WINAPI SetConsoleCtrlHandler(
        PHANDLER_ROUTINE HandlerRoutine,
        BOOL Add);
HWND WINAPI GetConsoleWindow(void);
BOOL WINAPI SetConsoleOutputCP(
    UINT wCodePageID);
UINT WINAPI GetConsoleOutputCP(void);

/* ========================================================================== */
/* Heap Functions: */
HANDLE WINAPI GetProcessHeap(void);
LPVOID WINAPI HeapAlloc(
        HANDLE hHeap,
        DWORD dwFlags,
        SIZE_T dwBytes);
LPVOID WINAPI HeapReAlloc(
        HANDLE hHeap,
        DWORD dwFlags,
        LPVOID lpMem,
        SIZE_T dwBytes);
BOOL WINAPI HeapFree(
        HANDLE hHeap,
        DWORD dwFlags,
        LPVOID lpMem);
BOOL WINAPI HeapsetInformation(
        HANDLE HeapHandle,
        HEAP_INFORMATION_CLASS HeapInformationClass,
        PVOID HeapInformation,
        SIZE_T HeapInformationLength);
LPVOID WINAPI VirtualAlloc(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD flAllocationType,
        DWORD flProtect);
SIZE_T WINAPI VirtualQuery(
        LPCVOID lpAddress,
        PMEMORY_BASIC_INFORMATION lpBuffer,
        SIZE_T dwLength);
BOOL WINAPI VirtualFree(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD dwFreeType);
BOOL WINAPI VirtualProtect(
        LPVOID lpAddress,
        SIZE_T dwSize,
        DWORD flNewProtect,
        PDWORD lpflOldProtect);
BOOL WINAPI FlushInstructionCache(
        HANDLE hProcess,
        LPCVOID lpBaseAddress,
        SIZE_T dwSize);


/* ========================================================================== */
/* Pipe Functions: */
BOOL WINAPI CreatePipe(
        PHANDLE hReadPipe,
        PHANDLE hWritePipe,
        LPSECURITY_ATTRIBUTES lpPipeAttributes,
        DWORD nSize);
BOOL WINAPI PeekNamedPipe(
        HANDLE  hNamedPipe,
        LPVOID  lpBuffer,
        DWORD   nBufferSize,
        LPDWORD lpBytesRead,
        LPDWORD lpTotalBytesAvail,
        LPDWORD lpBytesLeftThisMessage);

/* ========================================================================== */
/* Path Functions: */
DWORD WINAPI GetFullPathNameA(
        LPCSTR lpFileName,
        DWORD   nBufferLength,
        LPSTR  lpBuffer,
        LPSTR  *lpFilePart);
DWORD WINAPI GetFullPathNameW(
        LPCWSTR lpFileName,
        DWORD   nBufferLength,
        LPWSTR  lpBuffer,
        LPWSTR  *lpFilePart);
BOOL WINAPI SetCurrentDirectoryA(
        LPCSTR lpPathName);
BOOL WINAPI SetCurrentDirectoryW(
        LPCWSTR lpPathName);
DWORD WINAPI GetCurrentDirectoryA(
        DWORD  nBufferLength,
        LPSTR lpBuffer);
DWORD WINAPI GetCurrentDirectoryW(
        DWORD  nBufferLength,
        LPWSTR lpBuffer);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_IO_H */
#endif /* _WINDOWS_ */

