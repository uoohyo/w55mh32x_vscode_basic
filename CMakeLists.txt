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
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32_it.c
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32_msp.c
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
    --specs=nosys.specs
)

# Post-build: emit hex + bin and print a size summary so each build
# surfaces flash / SRAM usage immediately.
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${TARGET}>
    VERBATIM
)
