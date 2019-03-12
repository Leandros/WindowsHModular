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

/* Memory Protection */
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08
#define PAGE_TARGETS_INVALID 0x40000000
#define PAGE_TARGETS_NO_UPDATE 0x40000000
#define PAGE_GUARD 0x100
#define PAGE_NOCACHE 0x200
#define PAGE_WRITECOMBINE 0x400

/* Virtual Alloc */
#define MEM_COMMIT                          0x00001000
#define MEM_RESERVE                         0x00002000
#define MEM_RESET                           0x00080000
#define MEM_RESET_UNDO                      0x1000000
#define MEM_LARGE_PAGES                     0x20000000
#define MEM_PHYSICAL                        0x00400000
#define MEM_TOP_DOWN                        0x00100000
#define MEM_WRITE_WATCH                     0x00200000

/* Virtual Free */
#define MEM_COALESCE_PLACEHOLDERS           0x00000001
#define MEM_PRESERVE_PLACEHOLDER            0x00000002
#define MEM_DECOMMIT                        0x00004000
#define MEM_RELEASE                         0x00008000

LPVOID WINAPI VirtualAlloc(
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD  flAllocationType,
    DWORD  flProtect
);

BOOL WINAPI VirtualFree(
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD  dwFreeType
);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif /* WINDOWS_IO_H */
#endif /* _WINDOWS_ */
