/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_ATOMIC_H
#define WINDOWS_ATOMIC_H

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

/* RAWINPUTDEVICE.usUsagePage */
#define HID_USAGE_PAGE_GENERIC      0x01

/* RAWINPUTDEVICE.usUsage */
#define HID_USAGE_GENERIC_MOUSE     0x02
#define HID_USAGE_GENERIC_KEYBOARD  0x06

/* GetRawInputData command flags */
#define RID_INPUT   0x10000003
#define RID_HEADER  0x10000005

/* RAWINPUTHEADER.dwType */
#define RIM_TYPEMOUSE       0
#define RIM_TYPEKEYBOARD    1

/* RAWKEYBOARD.MakeCode with invalid input */
#define KEYBOARD_OVERRUN_MAKE_CODE 0xFF

/* RAWKEYBOARD.Flags */
#define RI_KEY_MAKE     0
#define RI_KEY_BREAK    1
#define RI_KEY_E0       2
#define RI_KEY_E1       4

/* RAWMOUSE.Flags */
#define MOUSE_MOVE_RELATIVE     0
#define MOUSE_MOVE_ABSOLUTE     1
#define MOUSE_VIRTUAL_DESKTOP   2 // the coordinates are mapped to the virtual desktop

/* RAWMOUSE.usButtonFlags */
#define RI_MOUSE_LEFT_BUTTON_DOWN   0x0001
#define RI_MOUSE_LEFT_BUTTON_UP     0x0002
#define RI_MOUSE_RIGHT_BUTTON_DOWN  0x0004
#define RI_MOUSE_RIGHT_BUTTON_UP    0x0008
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010
#define RI_MOUSE_MIDDLE_BUTTON_UP   0x0020

#define RI_MOUSE_BUTTON_1_DOWN      RI_MOUSE_LEFT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_1_UP        RI_MOUSE_LEFT_BUTTON_UP
#define RI_MOUSE_BUTTON_2_DOWN      RI_MOUSE_RIGHT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_2_UP        RI_MOUSE_RIGHT_BUTTON_UP
#define RI_MOUSE_BUTTON_3_DOWN      RI_MOUSE_MIDDLE_BUTTON_DOWN
#define RI_MOUSE_BUTTON_3_UP        RI_MOUSE_MIDDLE_BUTTON_UP

#define RI_MOUSE_BUTTON_4_DOWN      0x0040
#define RI_MOUSE_BUTTON_4_UP        0x0080
#define RI_MOUSE_BUTTON_5_DOWN      0x0100
#define RI_MOUSE_BUTTON_5_UP        0x0200

#define RI_MOUSE_WHEEL              0x0400
#define RI_MOUSE_HWHEEL             0x0800

#define WHEEL_DELTA 120

typedef HANDLE HRAWINPUT;

typedef struct tagRAWINPUTDEVICE {
    USHORT usUsagePage;
    USHORT usUsage;
    DWORD dwFlags;
    HWND hwndTarget;
} RAWINPUTDEVICE, *PRAWINPUTDEVICE, *LPRAWINPUTDEVICE;

typedef struct tagRAWINPUTHEADER {
    DWORD dwType;
    DWORD dwSize;
    HANDLE hDevice;
    WPARAM wParam;
} RAWINPUTHEADER, *PRAWINPUTHEADER, *LPRAWINPUTHEADER;

typedef struct tagRAWMOUSE {
    USHORT usFlags;

    union {
        ULONG ulButtons;
        struct  {
            USHORT  usButtonFlags;
            USHORT  usButtonData;
        };
    };

    ULONG ulRawButtons;
    LONG lLastX;
    LONG lLastY;
    ULONG ulExtraInformation;
} RAWMOUSE, *PRAWMOUSE, *LPRAWMOUSE;

typedef struct tagRAWKEYBOARD {
    USHORT MakeCode;
    USHORT Flags;
    USHORT Reserved;
    USHORT VKey;
    UINT   Message;
    ULONG ExtraInformation;
} RAWKEYBOARD, *PRAWKEYBOARD, *LPRAWKEYBOARD;

typedef struct tagRAWHID {
    DWORD dwSizeHid;
    DWORD dwCount;
    BYTE bRawData[1];
} RAWHID, *PRAWHID, *LPRAWHID;

typedef struct tagRAWINPUT {
    RAWINPUTHEADER header;
    union {
        RAWMOUSE    mouse;
        RAWKEYBOARD keyboard;
        RAWHID      hid;
    } data;
} RAWINPUT, *PRAWINPUT, *LPRAWINPUT;

BOOL WINAPI RegisterRawInputDevices(
        const RAWINPUTDEVICE* pRawInputDevices,
        UINT uiNumDevices,
        UINT cbSize);

UINT WINAPI GetRawInputData(
        HRAWINPUT hRawInput,
        UINT uiCommand,
        LPVOID pData,
        UINT* pcbSize,
        UINT cbSizeHeader);

#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif /* WINDOWS_ATOMIC_H */
#endif /* _WINDOWS_ */