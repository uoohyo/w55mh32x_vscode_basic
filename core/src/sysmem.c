/**
 * @file sysmem.c
 * @brief Newlib heap (_sbrk) implementation for bare-metal W55MH32.
 *
 * The heap grows upward from the end of .bss (_end) toward the bottom of
 * the stack region. The linker script w55mh32x_flash.ld defines:
 *   - _end / end       : first byte after .bss (PROVIDE)
 *   - _estack          : top of RAM (== ORIGIN(RAM) + LENGTH(RAM))
 *   - _Min_Heap_Size   : reserved heap (0x2000 = 8 KB by default)
 * A collision check prevents the heap from growing past
 * (_estack - _Min_Heap_Size), which is the lowest address the stack
 * may legitimately reach.
 */
#include <errno.h>
#include <stdint.h>
#include <stddef.h>

/* Symbols defined by the linker script. */
extern char _end;          /* first byte after .bss  */
extern char _estack;       /* top of the stack region */
extern uint32_t _Min_Heap_Size; /* minimum required heap */

__attribute__((weak)) void *_sbrk(ptrdiff_t incr)
{
    static char *heap_end = NULL;
    char *prev_heap_end;

    if (heap_end == NULL) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;

    /* Guard: stop if advancing heap would collide with reserved stack space. */
    if (heap_end + incr > (&_estack - (uint32_t)&_Min_Heap_Size)) {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_end += incr;
    return (void *)prev_heap_end;
}
