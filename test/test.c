#if defined(TEST_MODULAR)
#include <windows_modular.h>
#elif defined(TEST_ATOMIC)
#include <atomic.h>
#elif defined(TEST_DBGHELP)
#include "dbghelp.h"
#elif defined(TEST_DDS)
#include "dds.h"
#elif defined(TEST_FILE)
#include "file.h"
#elif defined(TEST_GDI)
#include "gdi.h"
#elif defined(TEST_IO)
#include "io.h"
#elif defined(TEST_MISC)
#include "misc.h"
#elif defined(TEST_PROCESS)
#include "process.h"
#elif defined(TEST_SYSINFO)
#include "sysinfo.h"
#elif defined(TEST_THREADS)
#include "threads.h"
#elif defined(TEST_WINDOW)
#include "window.h"
#endif


int
main(void)
{
    return 0;
}

