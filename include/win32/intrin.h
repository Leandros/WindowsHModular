/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Copyright (c) Arvid Gerstmann. All rights reserved.
 */
#ifndef _WINDOWS_
#ifndef WINDOWS_INTRIN_H
#define WINDOWS_INTRIN_H

/* Disable all warnings */
#if defined(_MSC_VER)
    #pragma warning(push, 0)
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/* ========================================================================== */
/* Intrinsics                                                                 */
/* ========================================================================== */

extern void _mm_pause(void);
#pragma intrinsic(_mm_pause)

extern void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)



#if defined(__cplusplus)
}
#endif

/* Enable all warnings */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif

#endif /* WINDOWS_INTRIN_H */
#endif /* _WINDOWS_ */

