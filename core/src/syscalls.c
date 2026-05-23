/**
 * @file syscalls.c
 * @brief Newlib syscall stubs for bare-metal W55MH32 (Cortex-M3).
 *
 * These are minimal stub implementations that satisfy the newlib linker
 * without pulling in OS-specific code. All I/O stubs return ENOSYS; only
 * the stubs required to silence newlib-nano link warnings are provided.
 * Override any stub by providing a non-weak definition in your application.
 */
#include <errno.h>
#include <sys/stat.h>

/* newlib declares errno as an extern; we must expose it here. */
#undef errno
extern int errno;

__attribute__((weak)) int _close(int fd)
{
    (void)fd;
    errno = ENOSYS;
    return -1;
}

__attribute__((weak)) int _lseek(int fd, int offset, int whence)
{
    (void)fd;
    (void)offset;
    (void)whence;
    errno = ENOSYS;
    return -1;
}

__attribute__((weak)) int _read(int fd, char *buf, int len)
{
    (void)fd;
    (void)buf;
    (void)len;
    errno = ENOSYS;
    return -1;
}

__attribute__((weak)) int _write(int fd, const char *buf, int len)
{
    (void)fd;
    (void)buf;
    (void)len;
    errno = ENOSYS;
    return -1;
}

__attribute__((weak)) int _isatty(int fd)
{
    (void)fd;
    return 1; /* treat all fds as terminal — harmless for bare-metal */
}

__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
    (void)fd;
    st->st_mode = S_IFCHR;
    return 0;
}

__attribute__((weak)) int _getpid(void)
{
    return 1;
}

__attribute__((weak)) int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

__attribute__((weak)) void _exit(int status)
{
    (void)status;
    /* Spin forever — no OS to return to. */
    for (;;) {}
}
