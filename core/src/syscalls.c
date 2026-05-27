/**
 ******************************************************************************
 * @file           : syscalls.c
 * @brief          : Newlib syscall stubs for bare-metal W55MH32 (Cortex-M3).
 *                   These are minimal stub implementations that satisfy the newlib linker
 *                   without pulling in OS-specific code. All I/O stubs return ENOSYS; only
 *                   the stubs required to silence newlib-nano link warnings are provided.
 *                   Override any stub by providing a non-weak definition in your application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 uoohyo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <errno.h>
#include <sys/stat.h>

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* newlib declares errno as an extern; we must expose it here. */
#undef errno
extern int errno;

/* Function -----------------------------------------------------------------*/
/**
 * @brief Stub for close(): there is no filesystem, so closing any
 *        descriptor always fails with ENOSYS.
 * @param fd File descriptor (ignored).
 * @return Always -1, with errno set to ENOSYS.
 */
__attribute__((weak)) int _close(int fd)
{
    (void)fd;
    errno = ENOSYS;
    return -1;
}

/**
 * @brief Stub for lseek(): no seekable streams exist on bare-metal.
 * @param fd     File descriptor (ignored).
 * @param offset Requested seek offset (ignored).
 * @param whence SEEK_SET / SEEK_CUR / SEEK_END (ignored).
 * @return Always -1, with errno set to ENOSYS.
 */
__attribute__((weak)) int _lseek(int fd, int offset, int whence)
{
    (void)fd;
    (void)offset;
    (void)whence;
    errno = ENOSYS;
    return -1;
}

/**
 * @brief Stub for read(): no input devices wired by default. Override
 *        in the application to route stdin to UART or similar.
 * @param fd  File descriptor (ignored).
 * @param buf Destination buffer (ignored).
 * @param len Number of bytes requested (ignored).
 * @return Always -1, with errno set to ENOSYS.
 */
__attribute__((weak)) int _read(int fd, char *buf, int len)
{
    (void)fd;
    (void)buf;
    (void)len;
    errno = ENOSYS;
    return -1;
}

/**
 * @brief Stub for write(): no output devices wired by default. Override
 *        in the application to route stdout/stderr to UART (printf
 *        retargeting) or similar.
 * @param fd  File descriptor (ignored).
 * @param buf Source buffer (ignored).
 * @param len Number of bytes to write (ignored).
 * @return Always -1, with errno set to ENOSYS.
 */
__attribute__((weak)) int _write(int fd, const char *buf, int len)
{
    (void)fd;
    (void)buf;
    (void)len;
    errno = ENOSYS;
    return -1;
}

/**
 * @brief Stub for isatty(): newlib's stdio uses this to decide whether
 *        to buffer line-by-line. Returning 1 (terminal) is the safe
 *        choice for bare-metal serial output.
 * @param fd File descriptor (ignored).
 * @return Always 1.
 */
__attribute__((weak)) int _isatty(int fd)
{
    (void)fd;
    return 1; /* treat all fds as terminal — harmless for bare-metal */
}

/**
 * @brief Stub for fstat(): reports every descriptor as a character
 *        device so newlib does not try to seek or stat-size it.
 * @param fd File descriptor (ignored).
 * @param st Caller-provided stat buffer; only st_mode is populated.
 * @return Always 0.
 */
__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
    (void)fd;
    st->st_mode = S_IFCHR;
    return 0;
}

/**
 * @brief Stub for getpid(): there is only one execution context.
 * @return Always 1.
 */
__attribute__((weak)) int _getpid(void)
{
    return 1;
}

/**
 * @brief Stub for kill(): no process model to signal.
 * @param pid Target pid (ignored).
 * @param sig Signal number (ignored).
 * @return Always -1, with errno set to EINVAL.
 */
__attribute__((weak)) int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

/**
 * @brief Stub for exit(): nowhere to return to on bare-metal. Spins
 *        forever so the debugger can inspect the final state.
 * @param status Exit status (ignored).
 */
__attribute__((weak)) void _exit(int status)
{
    (void)status;
    /* Spin forever — no OS to return to. */
    for (;;) {}
}
