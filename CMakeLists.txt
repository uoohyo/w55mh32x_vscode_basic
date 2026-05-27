cmake_minimum_required(VERSION 3.22)

# Toolchain selection must precede project().
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

project(w55mh32x_vscode_basic
    LANGUAGES C CXX ASM
    VERSION   0.1.0
)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# MCU / SPL bundle exposed as an INTERFACE library.
add_subdirectory(cmake/w55mh32)

# Application target — .elf is the canonical product, .hex/.bin produced post-build.
set(TARGET ${PROJECT_NAME}.elf)

# Application sources are listed explicitly so adding/removing a file
# always triggers a CMake reconfigure and nothing unintended sneaks in.
set(CORE_SRC
    ${CMAKE_SOURCE_DIR}/core/src/main.c
    ${CMAKE_SOURCE_DIR}/core/src/interrupt_vector_table.c  # C vector table + weak IRQ handlers
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32_it.c
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32_msp.c
    ${CMAKE_SOURCE_DIR}/core/src/syscalls.c   # newlib syscall stubs
    ${CMAKE_SOURCE_DIR}/core/src/sysmem.c     # newlib heap (_sbrk)
)

add_executable(${TARGET}
    ${CORE_SRC}
    ${CMAKE_SOURCE_DIR}/startup_w55mh32.s
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/core/inc
)

target_link_libraries(${TARGET} PRIVATE w55mh32x_hal)

target_link_options(${TARGET} PRIVATE
    -T${CMAKE_SOURCE_DIR}/w55mh32x_flash.ld
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--gc-sections
    --specs=nano.specs
    # --specs=nosys.specs intentionally omitted: syscalls.c + sysmem.c
    # provide explicit weak stubs for _close/_lseek/_read/_write/_isatty/
    # _fstat/_getpid/_kill/_exit/_sbrk. Pulling in libnosys here would
    # supply strong duplicates that override _sbrk's heap/stack
    # collision guard.
    # Cortex-M3 is bare-metal without an MMU, so the RAM LOAD segment is
    # legitimately RWX. GCC 12+ flags this even though the .data copy
    # pattern in startup_w55mh32.s makes it intentional — silence the
    # spurious warning.
    -Wl,--no-warn-rwx-segments
)

# Post-build: emit hex + bin and print a size summary so each build
# surfaces flash / SRAM usage immediately.
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${TARGET}>
    VERBATIM
)
