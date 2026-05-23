# Toolchain: arm-none-eabi-gcc, targeting W55MH32 (Cortex-M3, soft FP).

set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  arm)

# Avoid host-link test on a bare-metal compiler.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Toolchain binary directory.
# When arm-none-eabi-gcc is not on PATH, point ARM_TOOLCHAIN_DIR at the
# directory that contains the compiler executables.
#   * CMake variable:  -DARM_TOOLCHAIN_DIR="C:/path/to/bin"
#   * Env variable:    ARM_TOOLCHAIN_DIR=C:/path/to/bin
#   * CMakeUserPresets.json cacheVariables (recommended on Windows so the
#     setting is checked into a developer-local file, not the shared repo)
if(DEFINED ARM_TOOLCHAIN_DIR)
    set(TOOLCHAIN_PREFIX "${ARM_TOOLCHAIN_DIR}/arm-none-eabi-")
elseif(DEFINED ENV{ARM_TOOLCHAIN_DIR})
    set(TOOLCHAIN_PREFIX "$ENV{ARM_TOOLCHAIN_DIR}/arm-none-eabi-")
else()
    set(TOOLCHAIN_PREFIX "arm-none-eabi-")
endif()

if(WIN32)
    set(TOOLCHAIN_EXT ".exe")
else()
    set(TOOLCHAIN_EXT "")
endif()

set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXT})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++${TOOLCHAIN_EXT})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXT})
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PREFIX}objcopy${TOOLCHAIN_EXT} CACHE INTERNAL "objcopy")
set(CMAKE_SIZE         ${TOOLCHAIN_PREFIX}size${TOOLCHAIN_EXT}    CACHE INTERNAL "size")

set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb -mfloat-abi=soft")

set(CMAKE_C_FLAGS_INIT             "${MCU_FLAGS} -Wall -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_INIT           "${MCU_FLAGS} -Wall -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions")
set(CMAKE_ASM_FLAGS_INIT           "${MCU_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS_INIT    "${MCU_FLAGS}")

set(CMAKE_C_FLAGS_DEBUG_INIT       "-Og -g3 -gdwarf-2")
set(CMAKE_CXX_FLAGS_DEBUG_INIT     "-Og -g3 -gdwarf-2")
set(CMAKE_ASM_FLAGS_DEBUG_INIT     "-g3 -gdwarf-2")

set(CMAKE_C_FLAGS_RELEASE_INIT     "-Os -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT   "-Os -g")
