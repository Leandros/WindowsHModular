/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_FILE_H
#define WINDOWS_FILE_H

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

/* CreateFile.dwShareMode Enums: */
#define FILE_SHARE_DELETE           0x00000004
#define FILE_SHARE_READ             0x00000001
#define FILE_SHARE_WRITE            0x00000002

/* Generic Access Rights: */
#define GENERIC_READ                0x80000000L
#define GENERIC_WRITE               0x40000000L
#define GENERIC_EXECUTE             0x20000000L
#define GENERIC_ALL                 0x10000000L

/* Standard Access Rights: */
#define DELETE                      0x00010000L
#define READ_CONTROL                0x00020000L
#define WRITE_DAC                   0x00040000L
#define WRITE_OWNER                 0x00080000L
#define SYNCHRONIZE                 0x00100000L

#define STANDARD_RIGHTS_REQUIRED    0x000F0000L

#define STANDARD_RIGHTS_READ        READ_CONTROL
#define STANDARD_RIGHTS_WRITE       READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE     READ_CONTROL

#define STANDARD_RIGHTS_ALL         0x001F0000L
#define SPECIFIC_RIGHTS_ALL         0x0000FFFFL

/* Commulated Access Rights: */
#define FILE_READ_DATA              0x0001
#define FILE_LIST_DIRECTORY         0x0001
#define FILE_WRITE_DATA             0x0002
#define FILE_ADD_FILE               0x0002
#define FILE_APPEND_DATA            0x0004
#define FILE_ADD_SUBDIRECTORY       0x0004
#define FILE_CREATE_PIPE_INSTANCE   0x0004
#define FILE_READ_EA                0x0008
#define FILE_WRITE_EA               0x0010
#define FILE_EXECUTE                0x0020
#define FILE_TRAVERSE               0x0020
#define FILE_DELETE_CHILD           0x0040
#define FILE_READ_ATTRIBUTES        0x0080
#define FILE_WRITE_ATTRIBUTES       0x0100
#define FILE_ALL_ACCESS             \
    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ           \
    (STANDARD_RIGHTS_READ | \
     FILE_READ_DATA | \
     FILE_READ_ATTRIBUTES | \
     FILE_READ_EA | \
     SYNCHRONIZE)

#define FILE_GENERIC_WRITE          \
    (STANDARD_RIGHTS_WRITE | \
     FILE_WRITE_DATA | \
     FILE_WRITE_ATTRIBUTES | \
     FILE_WRITE_EA | \
     FILE_APPEND_DATA | \
     SYNCHRONIZE)

#define FILE_GENERIC_EXECUTE        \
    (STANDARD_RIGHTS_EXECUTE | \
     FILE_READ_ATTRIBUTES | \
     FILE_EXECUTE | \
     SYNCHRONIZE)

/* Creation Disposition: */
#define CREATE_ALWAYS               2
#define CREATE_NEW                  1
#define OPEN_ALWAYS                 4
#define OPEN_EXISTING               3
#define TRUNCATE_EXISTING           5

/* File Attributes: */
#define INVALID_FILE_ATTRIBUTES         0xffffffff
#define FILE_ATTRIBUTE_HIDDEN           0x2
#define FILE_ATTRIBUTE_NORMAL           0x80
#define FILE_ATTRIBUTE_DIRECTORY        0x10
#define FILE_ATTRIBUTE_TEMPORARY        0x100
#define FILE_ATTRIBUTE_REPARSE_POINT    0x400

/* File Offsets: */
#define FILE_BEGIN                  0
#define FILE_CURRENT                1
#define FILE_END                    2

/* File Mapping: */
#define SECTION_QUERY                   0x0001
#define SECTION_MAP_WRITE               0x0002
#define SECTION_MAP_READ                0x0004
#define SECTION_MAP_EXECUTE             0x0008
#define SECTION_EXTEND_SIZE             0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT    0x0020
#define SECTION_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED |\
     SECTION_QUERY |\
     SECTION_MAP_WRITE |\
     SECTION_MAP_READ |\
     SECTION_MAP_EXECUTE |\
     SECTION_EXTEND_SIZE)

#define FILE_MAP_COPY                   SECTION_QUERY
#define FILE_MAP_WRITE                  SECTION_MAP_WRITE
#define FILE_MAP_READ                   SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS             SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE                SECTION_MAP_EXECUTE_EXPLICIT

#define PAGE_EXECUTE_READ               0x20
#define PAGE_EXECUTE_READWRITE          0x40
#define PAGE_EXECUTE_WRITECOPY          0x80
#define PAGE_READONLY                   0x02
#define PAGE_READWRITE                  0x04
#define PAGE_WRITECOPY                  0x08

/* File Change Notifications: */
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100

/* File Type: */
#define FILE_TYPE_UNKNOWN               0x0000
#define FILE_TYPE_DISK                  0x0001
#define FILE_TYPE_CHAR                  0x0002
#define FILE_TYPE_PIPE                  0x0003
#define FILE_TYPE_REMOTE                0x8000

/* Move Flags: */
#define MOVEFILE_COPY_ALLOWED           0x2
#define MOVEFILE_REPLACE_EXISTING       0x1

typedef DWORD SECURITY_INFORMATION, *PSECURITY_INFORMATION;
typedef HANDLE PSECURITY_DESCRIPTOR;


/* ========================================================================== */
/* Structures: */
typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        };
        PVOID Pointer;
    };
    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

/* File Iteration: */
typedef struct _WIN32_FIND_DATAA {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    CHAR     cFileName[MAX_PATH];
    CHAR     cAlternateFileName[14];
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
typedef struct _WIN32_FIND_DATAW {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    WCHAR    cFileName[MAX_PATH];
    WCHAR    cAlternateFileName[14];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;


/* ========================================================================== */
/* File I/O Functions: */
HANDLE WINAPI CreateFileA(
        LPCSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes,
        HANDLE hTemplateFile);
HANDLE WINAPI CreateFileW(
        LPCWSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes,
        HANDLE hTemplateFile);

BOOL WINAPI WriteFile(
        HANDLE hFile,
        LPCVOID lpBuffer,
        DWORD nNumberOfBytesToWrite,
        LPDWORD lpNumberOfBytesWritten,
        LPOVERLAPPED lpOverlapped);
BOOL WINAPI ReadFile(
        HANDLE hFile,
        LPVOID lpBuffer,
        DWORD nNumberOfBytesToRead,
        LPDWORD lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped);
DWORD WINAPI SetFilePointer(
        HANDLE hFile,
        LONG lDistanceToMove,
        PLONG lpDistanceToMoveHigh,
        DWORD dwMoveMethod);
BOOL WINAPI SetFilePointerEx(
        HANDLE hFile,
        LARGE_INTEGER liDistanceToMove,
        PLARGE_INTEGER lpNewFilePointer,
        DWORD dwMoveMethod);
BOOL WINAPI FlushFileBuffers(
        HANDLE hFile);
DWORD WINAPI GetModuleFileNameA(
        HMODULE hModule,
        LPSTR   lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameW(
        HMODULE hModule,
        LPWSTR  lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameExA(
        HANDLE  hProcess,
        HMODULE hModule,
        LPSTR   lpFileName,
        DWORD   nSize);
DWORD WINAPI GetModuleFileNameExW(
        HANDLE  hProcess,
        HMODULE hModule,
        LPWSTR  lpFileName,
        DWORD   nSize);
HANDLE WINAPI OpenFileMappingA(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCSTR  lpName);
HANDLE WINAPI OpenFileMappingW(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCWSTR lpName);
LPVOID WINAPI MapViewOfFile(
        HANDLE  hFileMappingObject,
        DWORD   dwDesiredAccess,
        DWORD   dwFileOffsetHigh,
        DWORD   dwFileOffsetLow,
        SIZE_T  dwNumberOfBytesToMap);
LPVOID WINAPI MapViewOfFileEx(
        HANDLE  hFileMappingObject,
        DWORD   dwDesiredAccess,
        DWORD   dwFileOffsetHigh,
        DWORD   dwFileOffsetLow,
        SIZE_T  dwNumberOfBytesToMap,
        LPVOID  lpBaseAddress);
HANDLE WINAPI CreateFileMappingA(
        HANDLE                  hFile,
        LPSECURITY_ATTRIBUTES   lpAttributes,
        DWORD                   flProtect,
        DWORD                   dwMaximumSizeHigh,
        DWORD                   dwMaximumSizeLow,
        LPCSTR                  lpName);
HANDLE WINAPI CreateFileMappingW(
        HANDLE                  hFile,
        LPSECURITY_ATTRIBUTES   lpAttributes,
        DWORD                   flProtect,
        DWORD                   dwMaximumSizeHigh,
        DWORD                   dwMaximumSizeLow,
        LPCWSTR                 lpName);
BOOL WINAPI UnmapViewOfFile(
        LPCVOID lpBaseAddress);
DWORD WINAPI GetFileAttributesA(
        LPCSTR lpFileName);
DWORD WINAPI GetFileAttributesW(
        LPCWSTR lpFileName);
BOOL WINAPI GetFileTime(
        HANDLE  hFile,
        LPFILETIME lpCreationTime,
        LPFILETIME lpLastAccessTime,
        LPFILETIME lpLastWriteTime);
BOOL WINAPI SetEndOfFile(
        HANDLE hFile);
BOOL WINAPI CreateDirectoryA(
        LPCSTR      lpPathName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL WINAPI CreateDirectoryW(
        LPCWSTR     lpPathName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL WINAPI CopyFileA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName,
        BOOL    bFailIfExists);
BOOL WINAPI CopyFileW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName,
        BOOL    bFailIfExists);
BOOL WINAPI DeleteFileA(
        LPCSTR  lpFileName);
BOOL WINAPI DeleteFileW(
        LPCWSTR lpFileName);
BOOL WINAPI MoveFileA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName);
BOOL WINAPI MoveFileW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName);
BOOL WINAPI MoveFileExA(
        LPCSTR  lpExistingFileName,
        LPCSTR  lpNewFileName,
        DWORD   dwFlags);
BOOL WINAPI MoveFileExW(
        LPCWSTR lpExistingFileName,
        LPCWSTR lpNewFileName,
        DWORD   dwFlags);
BOOL WINAPI RemoveDirectoryA(
        LPCSTR  lpPathName);
BOOL WINAPI RemoveDirectoryW(
        LPCWSTR lpPathName);
BOOL WINAPI GetFileSizeEx(
        HANDLE  hFile,
        PLARGE_INTEGER lpFileSize);


/* ========================================================================== */
/* File Iteration Functions: */
HANDLE WINAPI FindFirstFileA(
        LPCSTR lpFileName,
        LPWIN32_FIND_DATAA lpFindFileData);
HANDLE WINAPI FindFirstFileW(
        LPCWSTR lpFileName,
        LPWIN32_FIND_DATAW lpFindFileData);
BOOL WINAPI FindNextFileA(
        HANDLE hFindFile,
        LPWIN32_FIND_DATAA lpFindFileData);
BOOL WINAPI FindNextFileW(
        HANDLE hFindFile,
        LPWIN32_FIND_DATAW lpFindFileData);
BOOL WINAPI FindClose(
        HANDLE hFindFile);

/* ========================================================================== */
/* File Change Functions: */
HANDLE WINAPI FindFirstChangeNotificationA(
        LPCSTR  lpPathName,
        BOOL    bWatchSubtree,
        DWORD   dwNotifyFilter);
HANDLE WINAPI FindFirstChangeNotificationW(
        LPCWSTR lpPathName,
        BOOL    bWatchSubtree,
        DWORD   dwNotifyFilter);
BOOL WINAPI FindNextChangeNotification(
        HANDLE  hChangeHandle);
BOOL WINAPI FindCloseChangeNotification(
        HANDLE  hChangeHandle);

/* ========================================================================== */
/* File Misc: */
DWORD WINAPI GetFileType(
        HANDLE hFile);

/* ========================================================================== */
/* Temp File: */
UINT WINAPI GetTempFileNameW(
    LPCWSTR lpPathName,
    LPCWSTR lpPrefixString,
    UINT    uUnique,
    LPWSTR  lpTempFileName
);

DWORD WINAPI GetTempPathW(
    DWORD  nBufferLength,
    LPWSTR lpBuffer
);

/* ========================================================================== */
/* File Security: */
BOOL WINAPI GetFileSecurityA(
    LPCSTR               lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD                nLength,
    LPDWORD              lpnLengthNeeded);
BOOL WINAPI GetFileSecurityW(
    LPCWSTR              lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD                nLength,
    LPDWORD              lpnLengthNeeded);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_FILE_H */
#endif /* _WINDOWS_ */

