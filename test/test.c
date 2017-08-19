#if defined(TEST_MODULAR)
    #include <win32/windows_modular.h>
#elif defined(TEST_ATOMIC)
    #include <win32/atomic.h>
#elif defined(TEST_DBGHELP)
    #include <win32/dbghelp.h>
#elif defined(TEST_DDS)
    #include <win32/dds.h>
#elif defined(TEST_FILE)
    #include <win32/file.h>
#elif defined(TEST_GDI)
    #include <win32/gdi.h>
#elif defined(TEST_IO)
    #include <win32/io.h>
#elif defined(TEST_MISC)
    #include <win32/misc.h>
#elif defined(TEST_PROCESS)
    #include <win32/process.h>
#elif defined(TEST_SYSINFO)
    #include <win32/sysinfo.h>
#elif defined(TEST_THREADS)
    #include <win32/threads.h>
#elif defined(TEST_WINDOW)
    #include <win32/window.h>
#endif


int
main(void)
{
    return 0;
}

