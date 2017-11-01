/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef WINDOWS_GDI_H
#define WINDOWS_GDI_H

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

/* GDI: */
#define BLACK_BRUSH                 4


/* Icons / Cursor: */
#define MAKEINTRESOURCE(res)        ((ULONG_PTR)(USHORT)res)
#define IDI_APPLICATION             MAKEINTRESOURCE(32512)
#define IDC_ARROW                   MAKEINTRESOURCE(32512)


/* ========================================================================= */
/* Functions                                                                 */
HCURSOR WINAPI LoadCursorA(
        HINSTANCE hInstance,
        LPCSTR  lpCursorName);
HCURSOR WINAPI LoadCursorW(
        HINSTANCE hInstance,
        LPCWSTR lpCursorName);
HICON WINAPI LoadIconA(
        HINSTANCE hInstance,
        LPCSTR  lpIconName);
HICON WINAPI LoadIconW(
        HINSTANCE hInstance,
        LPCWSTR lpIconName);
HGDIOBJ WINAPI GetStockObject(
        int     fnObject);
HCURSOR WINAPI SetCursor(
        HCURSOR hCursor);


#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_GDI_H */

