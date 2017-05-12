/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "windows_base.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* MessageBox customizations: */
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_CANCELTRYCONTINUE        0x00000006L
#define MB_HELP                     0x00004000L
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_RETRYCANCEL              0x00000005L
#define MB_YESNO                    0x00000004L
#define MB_YESNOCANCEL              0x00000003L

#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONWARNING              0x00000030L
#define MB_ICONINFORMATION          0x00000040L
#define MB_ICONASTERISK             0x00000040L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONSTOP                 0x00000010L
#define MB_ICONERROR                0x00000010L
#define MB_ICONHAND                 0x00000010L

#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#define MB_DEFBUTTON4               0x00000300L

#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L

#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_TOPMOST                  0x00040000L
#define MB_SERVICE_NOTIFICATION     0x00200000L

#define IDABORT                     (3)
#define IDCANCEL                    (2)
#define IDCONTINUE                  (11)
#define IDIGNORE                    (5)
#define IDNO                        (7)
#define IDOK                        (1)
#define IDRETRY                     (4)
#define IDTRYAGAIN                  (10)
#define IDYES                       (6)

/* Window Styles: */
#define WS_OVERLAPPED               0x00000000L
#define WS_POPUP                    0x80000000L
#define WS_CHILD                    0x40000000L
#define WS_MINIMIZE                 0x20000000L
#define WS_VISIBLE                  0x10000000L
#define WS_DISABLED                 0x08000000L
#define WS_CLIPSIBLINGS             0x04000000L
#define WS_CLIPCHILDREN             0x02000000L
#define WS_MAXIMIZE                 0x01000000L
#define WS_CAPTION                  0x00C00000L
#define WS_BORDER                   0x00800000L
#define WS_DLGFRAME                 0x00400000L
#define WS_VSCROLL                  0x00200000L
#define WS_HSCROLL                  0x00100000L
#define WS_SYSMENU                  0x00080000L
#define WS_THICKFRAME               0x00040000L
#define WS_GROUP                    0x00020000L
#define WS_TABSTOP                  0x00010000L

#define WS_MINIMIZEBOX              0x00020000L
#define WS_MAXIMIZEBOX              0x00010000L


#define WS_TILED                    WS_OVERLAPPED
#define WS_ICONIC                   WS_MINIMIZE
#define WS_SIZEBOX                  WS_THICKFRAME
#define WS_TILEDWINDOW              WS_OVERLAPPEDWINDOW

/* Common Window Styles: */
#define WS_OVERLAPPEDWINDOW         (WS_OVERLAPPED     | \
                                     WS_CAPTION        | \
                                     WS_SYSMENU        | \
                                     WS_THICKFRAME     | \
                                     WS_MINIMIZEBOX    | \
                                     WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW              (WS_POPUP          | \
                                     WS_BORDER         | \
                                     WS_SYSMENU)
#define WS_CHILDWINDOW              (WS_CHILD)

#define CW_USEDEFAULT               ((int)0x80000000)

/* Class Styles: */
#define CS_OWNDC                        0x0020
#define CS_VREDRAW                      0x0001
#define CS_HREDRAW                      0x0002

/* Messages: */
#define PM_NOREMOVE                 0x0000
#define PM_REMOVE                   0x0001
#define PM_NOYIELD                  0x0002

#define WM_NULL                     0x0000
#define WM_CREATE                   0x0001
#define WM_DESTROY                  0x0002
#define WM_MOVE                     0x0003
#define WM_SIZE                     0x0005
#define WM_SETFOCUS                 0x0007
#define WM_KILLFOCUS                0x0008
#define WM_ENABLE                   0x000A
#define WM_SETREDRAW                0x000B
#define WM_SETTEXT                  0x000C
#define WM_GETTEXT                  0x000D
#define WM_GETTEXTLENGTH            0x000E
#define WM_PAINT                    0x000F
#define WM_CLOSE                    0x0010
#define WM_QUIT                     0x0012
#define WM_ERASEBKGND               0x0014
#define WM_SYSCOLORCHANGE           0x0015
#define WM_SHOWWINDOW               0x0018
#define WM_WININICHANGE             0x001A
#define WM_NCDESTROY                0x0082

#define WM_KEYDOWN                  0x0100
#define WM_KEYUP                    0x0101
#define WM_SYSKEYDOWN               0x0104
#define WM_SYSKEYUP                 0x0105

#define WM_SYSCOMMAND               0x0112

#define WM_ENTERSIZEMOVE            0x0231
#define WM_EXITSIZEMOVE             0x0232

#define WM_ACTIVATE                 0x0006
#define WA_INACTIVE                 0
#define WA_ACTIVE                   1
#define WA_CLICKACTIVE              2

#define SC_KEYMENU                  0xF100

/* Events: */
#define EVENT_ALL_ACCESS            0x1F0003
#define EVENT_MODIFY_STATE          0x0002

/* Virtual Keys: */
#define VK_BACK                         0x08
#define VK_TAB                          0x09
#define VK_SHIFT                        0x10
#define VK_CONTROL                      0x11
#define VK_MENU                         0x12
#define VK_RETURN                       0x0C

#define VK_ESCAPE                       0x1B

#define VK_SPACE                        0x20
#define VK_PRIOR                        0x21
#define VK_NEXT                         0x22
#define VK_END                          0x23
#define VK_HOME                         0x24
#define VK_LEFT                         0x25
#define VK_UP                           0x26
#define VK_RIGHT                        0x27
#define VK_DOWN                         0x28
#define VK_SELECT                       0x29
#define VK_PRINT                        0x2A
#define VK_EXECUTE                      0x2B
#define VK_SNAPSHOT                     0x2C
#define VK_INSERT                       0x2D
#define VK_DELETE                       0x2E
#define VK_HELP                         0x2F

#define VK_LWIN                         0x5B
#define VK_RWIN                         0x5C
#define VK_PROCESSKEY                   0xE5


/* ========================================================================== */
/* Structures:                                                                */
typedef struct _RECT {
    LONG        left;
    LONG        top;
    LONG        right;
    LONG        bottom;
} RECT, *PRECT, *LPRECT;

/* Window: */
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef struct tagWNDCLASS {
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCTSTR     lpszMenuName;
    LPCTSTR     lpszClassName;
} WNDCLASS, *PWNDCLASS;

/* Messages: */
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT;

typedef struct tagMSG {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
} MSG, *PMSG, *LPMSG;


/* ========================================================================== */
/* Window Functions: */
int WINAPI MessageBoxA(
        HWND    hWND,
        LPCSTR  lpText,
        LPCSTR  lpCaption,
        UINT    uType);
int WINAPI MessageBoxW(
        HWND    hWND,
        LPCWSTR lpText,
        LPCWSTR lpCaption,
        UINT    uType);
ATOM WINAPI RegisterClassA(
        WNDCLASS *lpWndClass);
ATOM WINAPI RegisterClassW(
        WNDCLASS *lpWndClass);
BOOL WINAPI UnregisterClassA(
        LPCSTR  lpClassName,
        HINSTANCE hInstance);
BOOL WINAPI UnregisterClassW(
        LPCWSTR lpClassName,
        HINSTANCE hInstance);
HWND WINAPI CreateWindowExA(
        DWORD   dwExStyle,
        LPCSTR  lpClassName,
        LPCSTR  lpWindowName,
        DWORD   dwStyle,
        int     x,
        int     y,
        int     nWidth,
        int     nHeight,
        HWND    hWndParent,
        HMENU   hMenu,
        HINSTANCE hInstance,
        LPVOID  lpParam);
HWND WINAPI CreateWindowExW(
        DWORD   dwExStyle,
        LPCWSTR lpClassName,
        LPCWSTR lpWindowName,
        DWORD   dwStyle,
        int     x,
        int     y,
        int     nWidth,
        int     nHeight,
        HWND    hWndParent,
        HMENU   hMenu,
        HINSTANCE hInstance,
        LPVOID  lpParam);
BOOL WINAPI ShowWindow(
        HWND    hWnd,
        int     nCmdShow);
BOOL WINAPI UpdateWindow(
        HWND    hWnd);
LRESULT WINAPI DefWindowProcA(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);
LRESULT WINAPI DefWindowProcW(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);
BOOL WINAPI DestroyWindow(
        HWND    hWnd);
BOOL WINAPI AdjustWindowRectEx(
        LPRECT  lpRect,
        DWORD   dwStyle,
        BOOL    bMenu,
        DWORD   dwExStyle);
BOOL WINAPI GetClientRect(
        HWND    hWnd,
        LPRECT  lpRect);
int WINAPI GetSystemMetrics(
        int     nIndex);

/* ========================================================================== */
/* Message Queue: */
BOOL WINAPI PeekMessageA(
        LPMSG   lpMsg,
        HWND    hWnd,
        UINT    wMsgFilterMin,
        UINT    wMsgFilterMax,
        UINT    wRemoveMsg);
BOOL WINAPI PeekMessageW(
        LPMSG   lpMsg,
        HWND    hWnd,
        UINT    wMsgFilterMin,
        UINT    wMsgFilterMax,
        UINT    wRemoveMsg);
BOOL WINAPI TranslateMessage(
        const MSG *lpMsg);
LRESULT WINAPI DispatchMessageA(
        const MSG *lpMsg);
LRESULT WINAPI DispatchMessageW(
        const MSG *lpMsg);
void WINAPI PostQuitMessage(
        int nExitCode);

/* ========================================================================== */
/* Events: */
HANDLE WINAPI CreateEventA(
        LPSECURITY_ATTRIBUTES lpEventAttributes,
        BOOL    bManualReset,
        BOOL    bInitialState,
        LPCSTR  lpName);
HANDLE WINAPI CreateEventW(
        LPSECURITY_ATTRIBUTES lpEventAttributes,
        BOOL    bManualReset,
        BOOL    bInitialState,
        LPCWSTR lpName);
HANDLE WINAPI OpenEventA(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCSTR  lpName);
HANDLE WINAPI OpenEventW(
        DWORD   dwDesiredAccess,
        BOOL    bInheritHandle,
        LPCWSTR lpName);
BOOL WINAPI ResetEvent(
        HANDLE  hEvent);
BOOL WINAPI SetEvent(
        HANDLE  hEvent);
SHORT WINAPI GetKeyState(
        int     nVirtKey);

#if defined(__cplusplus)
}
#endif

#endif /* WINDOWS_WINDOW_H */

