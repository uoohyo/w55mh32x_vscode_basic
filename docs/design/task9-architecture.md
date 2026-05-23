# Task #9 — W55MH32 VS Code Template Architecture Design

> Architect: 기로로 하사
> Target task: #9 (전체 구조 설계)
> Consumer: 쿠루루 상사 (task #10 implementation input)

## 1. Critical Clarification (Read First)

W55MH32X_Driver 헤더(`drivers/W55MH32X_Driver/inc/w55mh32.h`)는 매크로 `USE_STDPERIPH_DRIVER`를 사용하는 **STM32 SPL (Standard Peripheral Library) 스타일**이지 STM32 Cube **HAL** 스타일이 아니다.

| 요소 | STM32 HAL (Cube) | W55MH32 (실제 사용 스타일) |
|------|------------------|--------------------------|
| init 진입점 | `HAL_Init()` | `SystemInit()` (startup이 호출, `core/src/system_w55mh32.c` 제공) |
| 모듈 enable | `#define USE_HAL_GPIO_MODULE` | `w55mh32x_conf.h` 안에서 `#include "w55mh32_gpio.h"` 주석 토글 |
| board init | `HAL_MspInit()` | 사용자 정의 `BSP_*` 함수 (weak default) |
| main 헤더 | `stm32xx_hal.h` | `w55mh32.h` |

→ 케로로 지시의 `HAL_Init/HAL_MspInit/USE_HAL_GPIO_MODULE` 표현은 **SPL 스타일로 치환**해 설계함. (사용자가 명시한 `stm32g0xx_msp.c`도 `w55mh32x_msp.c`로 치환했음 — 케로로 지시 확인 완료.)

## 2. .gitignore 설계

### 2.1 정책 결정 (권장)

| 대상 | 추적 여부 | 근거 |
|------|---------|------|
| `.vscode/` | **추적 O** | 본 프로젝트는 팀 공유 VS Code 템플릿이 목적. 4개 핵심 파일(tasks/launch/c_cpp_properties/extensions)이 템플릿 가치의 핵심. |
| `.vscode/*.local.json` | 추적 X | 개인 설정 격리 통로 제공 |
| `.claude/` | 추적 X | 사용자별 Claude Code 워크스페이스 |
| `c_cpp_properties.json` | 추적 O | 위와 동일 이유 — 기존 .gitignore에 있던 항목 **제거** |
| `drivers/**/*.lib`, `drivers/**/*.a` | 추적 O | 벤더 제공 toolchain 산출물, 빌드 산출물 아님 → ignore 패턴에 `**/*.lib`/`**/*.a` 넣지 않음 |
| `*.elf`/`*.hex`/`*.bin`/`*.map` | 추적 X | 빌드 산출물 |

### 2.2 최종 .gitignore 내용

```gitignore
# Build outputs
/build/
/Debug/
/Release/
*.o
*.d
*.elf
*.hex
*.bin
*.axf
*.map
*.lst
*.list

# CMake (ignored in any directory)
**/CMakeCache.txt
**/CMakeFiles/
**/CMakeScripts/
**/Makefile
**/cmake_install.cmake
**/install_manifest.txt
**/compile_commands.json
**/CTestTestfile.cmake
**/_deps/

# Ninja build files
.ninja_log
.ninja_deps
build.ninja
rules.ninja

# Editor / tool caches
.cursor
.clangd
.history/
.metadata/
*.swp
*~
*.bak
*.tmp
*.orig

# Claude Code workspace (user-local)
.claude/

# Local VS Code overrides (team-shared .vscode/ files are tracked)
.vscode/*.local.json
.vscode/settings.local.json

# Debugger / probe logs
JLinkLog.txt
JLinkSettings.ini

# OS-generated files (macOS / Windows)
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
.AppleDouble
.AppleDB
.AppleDesktop
.LSOverride
.apdisk
ehthumbs.db
Thumbs.db
Network Trash Folder
Temporary Items
nul
```

### 2.3 변경 차이 (기존 → 신규)

**제거**
- Eclipse/SW4STM32/Atollic: `.cproject`, `.project`, `.atollic`, `*.launch`, `.dep/`
- IAR 섹션 전체: `*.ewp`, `*.ewd`, `*.eww`, `*.ewt`, `*.wsdt`, `*.dbgdt`, `*.dep`
- Keil MDK 섹션 전체: `*.uvprojx`, `*.uvoptx`, `*.uvguix.*`, `*.uvopt`, `*.scvd`, `.axf` (오타 — `*.axf`로 정정), `.lnp`, `.htm`
- STM32CubeIDE 섹션 (`.settings/bundles*.json`)
- 중복: 두 번째 `.metadata/`, `*.ewd`, `*.eww`, `*.lst`, `*.uvguix.*`, `*.uvoptx`
- `c_cpp_properties.json` — `.vscode/` 추적 정책에 따라 추적 대상으로 전환

**추가**
- `.claude/`
- `.vscode/*.local.json`, `.vscode/settings.local.json`
- `*.axf` (정상 ignore 항목으로 재추가)

**변환**
- 모든 한국어 주석 → 영어
- 섹션 헤더 통합/단순화

## 3. core/ 파일 인터페이스 설계

### 3.1 파일 매트릭스

| 파일 | 역할 | 의존 |
|------|------|------|
| `core/inc/main.h` | 앱 진입 헤더, `Error_Handler` 선언 | `w55mh32.h` |
| `core/inc/w55mh32x_conf.h` | SPL 모듈 selector, `assert_param` | 각 페리페럴 헤더 |
| `core/inc/w55mh32x_it.h` | Cortex-M3 system handler + IRQ prototype | `w55mh32.h` |
| `core/src/main.c` | `main()`, `SystemClock_Config`, `Error_Handler` | main.h, w55mh32x_it.h |
| `core/src/w55mh32x_msp.c` | 보드/페리페럴 초기화 weak default | w55mh32.h |
| `core/src/w55mh32x_it.c` | 시스템 예외 핸들러 기본 구현 | w55mh32x_it.h, main.h |

기존 존재(수정 금지): `core/inc/core_cm3.h`, `core/inc/system_w55mh32.h`, `core/src/core_cm3.c`, `core/src/system_w55mh32.c`.

### 3.2 `core/inc/main.h`

```c
/**
 * @file    main.h
 * @brief   Application entry header for W55MH32 firmware template.
 */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "w55mh32.h"

/* Application-wide error trap. */
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
```

### 3.3 `core/inc/w55mh32x_conf.h`

```c
/**
 * @file    w55mh32x_conf.h
 * @brief   Module selector for W55MH32 Standard Peripheral Library.
 *          Uncomment a header to pull the matching driver in.
 *          (Triggered when w55mh32.h sees USE_STDPERIPH_DRIVER defined.)
 */
#ifndef __W55MH32X_CONF_H
#define __W55MH32X_CONF_H

/* Always-on core peripherals */
#include "w55mh32_rcc.h"
#include "w55mh32_gpio.h"
#include "misc.h"

/* Optional peripherals — uncomment as needed */
/* #include "w55mh32_adc.h"      */
/* #include "w55mh32_bkp.h"      */
/* #include "w55mh32_can.h"      */
/* #include "w55mh32_crc.h"      */
/* #include "w55mh32_dac.h"      */
/* #include "w55mh32_dbgmcu.h"   */
/* #include "w55mh32_dma.h"      */
/* #include "w55mh32_exti.h"     */
/* #include "w55mh32_flash.h"    */
/* #include "w55mh32_i2c.h"      */
/* #include "w55mh32_iwdg.h"     */
/* #include "w55mh32_otp.h"      */
/* #include "w55mh32_pwr.h"      */
/* #include "w55mh32_rtc.h"      */
/* #include "w55mh32_sdio.h"     */
/* #include "w55mh32_spi.h"      */
/* #include "w55mh32_tim.h"      */
/* #include "w55mh32_trng.h"     */
/* #include "w55mh32_usart.h"    */
/* #include "w55mh32_wwdg.h"     */
/* #include "w55mh32_wztoe.h"    */

#ifdef USE_FULL_ASSERT
  #define assert_param(expr) \
      ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t *file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif

#endif /* __W55MH32X_CONF_H */
```

### 3.4 `core/inc/w55mh32x_it.h`

```c
/**
 * @file    w55mh32x_it.h
 * @brief   Cortex-M3 system exception and peripheral IRQ handler prototypes.
 *          Names must match the vector table in startup_w55mh32.s.
 */
#ifndef __W55MH32X_IT_H
#define __W55MH32X_IT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "w55mh32.h"

/* Cortex-M3 system exception handlers */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* Peripheral IRQ handler prototypes are added here when peripherals are enabled. */

#ifdef __cplusplus
}
#endif

#endif /* __W55MH32X_IT_H */
```

### 3.5 `core/src/main.c`

```c
/**
 * @file    main.c
 * @brief   Firmware entry point for the W55MH32 VS Code template.
 */
#include "main.h"
#include "w55mh32x_it.h"

static void SystemClock_Config(void);

int main(void)
{
    /* SystemInit() ran from startup_w55mh32.s before main() — clocks are
     * already at the default configured in core/src/system_w55mh32.c.
     * Override below if a different PLL/HSE setup is required.
     */
    SystemClock_Config();

    /* TODO: board / peripheral initialization. */

    while (1)
    {
        /* TODO: application logic. */
    }
}

static void SystemClock_Config(void)
{
    /* Default: no override — rely on SystemInit() in system_w55mh32.c.
     * Replace with custom RCC configuration when needed.
     */
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        /* Halt for debugger inspection. */
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    (void)file;
    (void)line;
    /* User can route this to a UART logger. */
}
#endif
```

### 3.6 `core/src/w55mh32x_msp.c`

```c
/**
 * @file    w55mh32x_msp.c
 * @brief   Board-Support / MSP layer: clock gating and GPIO AF wiring.
 *          All functions are weak defaults so the application can override
 *          them without touching template code.
 */
#include "w55mh32.h"

__attribute__((weak)) void BSP_Init(void)
{
    /* Default: nothing. Application overrides to enable peripherals. */
}

__attribute__((weak)) void BSP_GPIO_Init(void)
{
}

__attribute__((weak)) void BSP_USART_MspInit(USART_TypeDef *USARTx)
{
    (void)USARTx;
}

__attribute__((weak)) void BSP_SPI_MspInit(SPI_TypeDef *SPIx)
{
    (void)SPIx;
}

__attribute__((weak)) void BSP_I2C_MspInit(I2C_TypeDef *I2Cx)
{
    (void)I2Cx;
}
```

### 3.7 `core/src/w55mh32x_it.c`

```c
/**
 * @file    w55mh32x_it.c
 * @brief   Default Cortex-M3 system exception handlers.
 *          Fault handlers spin to keep the failing state visible to the debugger.
 */
#include "w55mh32x_it.h"
#include "main.h"

void NMI_Handler(void)         { }
void HardFault_Handler(void)   { while (1) { } }
void MemManage_Handler(void)   { while (1) { } }
void BusFault_Handler(void)    { while (1) { } }
void UsageFault_Handler(void)  { while (1) { } }
void SVC_Handler(void)         { }
void DebugMon_Handler(void)    { }
void PendSV_Handler(void)      { }

void SysTick_Handler(void)
{
    /* Increment a tick base here if one is added. */
}
```

## 4. CMake 프로젝트 구조 설계

### 4.1 디렉토리 트리

```
/
├── CMakeLists.txt              ← root (project, target, link options)
├── CMakePresets.json           ← debug / release presets, Ninja
├── cmake/
│   ├── gcc-arm-none-eabi.cmake ← toolchain (cortex-m3, soft FP)
│   └── w55mh32x/
│       └── CMakeLists.txt      ← INTERFACE lib bundling SPL + CMSIS sources
├── startup_w55mh32.s           ← root (referenced from root CMakeLists)
└── w55mh32x_flash.ld           ← root (linker script)
```

### 4.2 root `CMakeLists.txt`

```cmake
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

# MCU/HAL bundle as INTERFACE library
add_subdirectory(cmake/w55mh32x)

# Application target
set(TARGET ${PROJECT_NAME}.elf)

file(GLOB CORE_SRC CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/core/src/main.c
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32x_it.c
    ${CMAKE_SOURCE_DIR}/core/src/w55mh32x_msp.c
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

# POST_BUILD: hex + bin + size summary
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${TARGET}>
    VERBATIM
)
```

설계 메모:
- `system_w55mh32.c`와 `core_cm3.c`는 SPL 측면에서 HAL 구성요소로 분류 → `cmake/w55mh32x/CMakeLists.txt`로 이동. `core/src/main.c`, `w55mh32x_it.c`, `w55mh32x_msp.c`만 애플리케이션 소스.
- `file(GLOB ...)` 대신 명시 나열한 이유: 신규/삭제 시 cmake 재실행 보장 + 의도하지 않은 파일 포함 방지.

### 4.3 `CMakePresets.json`

```json
{
  "version": 6,
  "cmakeMinimumRequired": { "major": 3, "minor": 22, "patch": 0 },
  "configurePresets": [
    {
      "name": "base",
      "hidden": true,
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build/${presetName}",
      "cacheVariables": {
        "CMAKE_EXPORT_COMPILE_COMMANDS": "TRUE"
      }
    },
    {
      "name": "debug",
      "inherits": "base",
      "cacheVariables": { "CMAKE_BUILD_TYPE": "Debug" }
    },
    {
      "name": "release",
      "inherits": "base",
      "cacheVariables": { "CMAKE_BUILD_TYPE": "Release" }
    }
  ],
  "buildPresets": [
    { "name": "debug",   "configurePreset": "debug" },
    { "name": "release", "configurePreset": "release" }
  ]
}
```

### 4.4 `cmake/gcc-arm-none-eabi.cmake`

```cmake
# Toolchain: arm-none-eabi-gcc, targeting W55MH32 (Cortex-M3, soft FP).

set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  arm)

# Avoid host-link test on a bare-metal compiler.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX arm-none-eabi-)
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
```

### 4.5 `cmake/w55mh32x/CMakeLists.txt`

```cmake
# INTERFACE library bundling W55MH32 CMSIS device + Standard Peripheral Library.
# Application targets pull this in via target_link_libraries(<app> PRIVATE w55mh32x_hal).

add_library(w55mh32x_hal INTERFACE)

target_sources(w55mh32x_hal INTERFACE
    # CMSIS / system
    ${CMAKE_SOURCE_DIR}/core/src/system_w55mh32.c
    ${CMAKE_SOURCE_DIR}/core/src/core_cm3.c

    # SPL — always-on core peripherals
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/misc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_rcc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_gpio.c

    # SPL — optional peripherals (uncomment per project needs)
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_adc.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_usart.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_spi.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_i2c.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_tim.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_dma.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_exti.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_flash.c
)

target_include_directories(w55mh32x_hal INTERFACE
    ${CMAKE_SOURCE_DIR}/core/inc
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Device/WIZnet/W55MH32X/inc
)

target_compile_definitions(w55mh32x_hal INTERFACE
    USE_STDPERIPH_DRIVER
    W55MH32
)
```

### 4.6 MCU 플래그 트레이드오프

| 항목 | 선택 | 대안 | 이유 |
|------|------|------|------|
| `-mcpu` | `cortex-m3` | `cortex-m0plus` (참조 프로젝트의 STM32G0) | W55MH32 = Cortex-M3 |
| `-mfloat-abi` | `soft` | `softfp`/`hard` | M3에는 FPU 없음 |
| libc spec | `nano.specs` + `nosys.specs` | full newlib | 임베디드 표준, syscall stub 회피 |
| 섹션 분리 | `-ffunction-sections -fdata-sections` + `--gc-sections` | 없음 | 미사용 심볼 제거로 코드 크기 절감 |
| 최적화 (Debug) | `-Og -g3` | `-O0` | 디버깅 가능성 유지 + 적정 최적화 |
| 빌드 디렉토리 | `build/${presetName}` | `build/` 평면 | preset별 격리 → debug/release 병행 가능 |

## 5. `.vscode/` 구성 설계

### 5.1 `.vscode/tasks.json`

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "CMake: configure (debug)",
            "type": "shell",
            "command": "cmake",
            "args": ["--preset", "debug"],
            "options": { "cwd": "${workspaceFolder}" },
            "problemMatcher": []
        },
        {
            "label": "CMake: configure (release)",
            "type": "shell",
            "command": "cmake",
            "args": ["--preset", "release"],
            "options": { "cwd": "${workspaceFolder}" },
            "problemMatcher": []
        },
        {
            "label": "Build (debug)",
            "type": "shell",
            "command": "cmake",
            "args": ["--build", "--preset", "debug"],
            "options": { "cwd": "${workspaceFolder}" },
            "group": { "kind": "build", "isDefault": true },
            "dependsOn": ["CMake: configure (debug)"],
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "Build (release)",
            "type": "shell",
            "command": "cmake",
            "args": ["--build", "--preset", "release"],
            "options": { "cwd": "${workspaceFolder}" },
            "group": "build",
            "dependsOn": ["CMake: configure (release)"],
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "Clean (debug)",
            "type": "shell",
            "command": "cmake",
            "args": ["--build", "--preset", "debug", "--target", "clean"],
            "options": { "cwd": "${workspaceFolder}" },
            "problemMatcher": []
        }
    ]
}
```

### 5.2 `.vscode/launch.json`

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug (J-Link)",
            "type": "cortex-debug",
            "request": "launch",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/debug/w55mh32x_vscode_basic.elf",
            "servertype": "jlink",
            "device": "W55MH32",
            "interface": "swd",
            "runToEntryPoint": "main",
            "preLaunchTask": "Build (debug)"
        },
        {
            "name": "Debug (OpenOCD + CMSIS-DAP)",
            "type": "cortex-debug",
            "request": "launch",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/debug/w55mh32x_vscode_basic.elf",
            "servertype": "openocd",
            "configFiles": [
                "interface/cmsis-dap.cfg",
                "target/w55mh32.cfg"
            ],
            "runToEntryPoint": "main",
            "preLaunchTask": "Build (debug)"
        }
    ]
}
```

디버거 선택 근거:
- **J-Link**: WIZnet `WIZnet.W55MH32_DFP.1.0.0.pack` 존재 → SEGGER J-Link Device 목록에 W55MH32 추가될 가능성 높음 (쿠루루가 실기로 device 명 검증 필요. fallback: `device: "Cortex-M3"`).
- **OpenOCD**: `target/w55mh32.cfg` 미존재 시 사용자가 cfg 작성. 일단 자리는 잡아둠.

### 5.3 `.vscode/c_cpp_properties.json`

```json
{
    "version": 4,
    "configurations": [
        {
            "name": "W55MH32",
            "intelliSenseMode": "linux-gcc-arm",
            "compileCommands": "${workspaceFolder}/build/debug/compile_commands.json",
            "compilerPath": "arm-none-eabi-gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "includePath": [
                "${workspaceFolder}/core/inc",
                "${workspaceFolder}/drivers/W55MH32X_Driver/inc",
                "${workspaceFolder}/drivers/CMSIS/Device/WIZnet/W55MH32X/inc"
            ],
            "defines": [
                "USE_STDPERIPH_DRIVER",
                "W55MH32"
            ]
        }
    ]
}
```

설계 원칙: `compileCommands`가 우선 소스, `includePath`/`defines`는 빌드 전 IntelliSense 부트스트랩용. **절대 경로 금지**.

### 5.4 `.vscode/extensions.json`

```json
{
    "recommendations": [
        "ms-vscode.cpptools",
        "ms-vscode.cmake-tools",
        "twxs.cmake",
        "marus25.cortex-debug",
        "dan-c-underwood.arm",
        "zixuanwang.linkerscript"
    ]
}
```

| 확장 | 용도 |
|------|------|
| ms-vscode.cpptools | C/C++ IntelliSense |
| ms-vscode.cmake-tools | CMake 통합 |
| twxs.cmake | CMakeLists 구문 강조 |
| marus25.cortex-debug | Cortex-M 디버깅 |
| dan-c-underwood.arm | ARM 어셈블리 강조 (startup_w55mh32.s) |
| zixuanwang.linkerscript | `.ld` 강조 |

## 6. 영향 범위 (쿠루루용)

### 신규 생성
- `core/inc/main.h`, `core/inc/w55mh32x_conf.h`, `core/inc/w55mh32x_it.h`
- `core/src/main.c`, `core/src/w55mh32x_msp.c`, `core/src/w55mh32x_it.c`
- `CMakeLists.txt` (root)
- `CMakePresets.json`
- `cmake/gcc-arm-none-eabi.cmake`
- `cmake/w55mh32x/CMakeLists.txt`
- `.vscode/tasks.json`, `.vscode/launch.json`, `.vscode/c_cpp_properties.json`, `.vscode/extensions.json`

### 수정
- `.gitignore` (위 §2.2 내용으로 전체 치환)

### 손대지 말 것
- `startup_w55mh32.s`, `w55mh32x_flash.ld` (벤더 제공, 그대로 사용)
- `core/inc/core_cm3.h`, `core/inc/system_w55mh32.h`
- `core/src/core_cm3.c`, `core/src/system_w55mh32.c`
- `drivers/**` (전체)
- `LICENSE`, `docs/**/*.pdf`

## 7. 리스크 / 가정

| 항목 | 가정 | 검증 책임 |
|------|------|---------|
| J-Link `device` 이름 | "W55MH32" 또는 "Cortex-M3" | 쿠루루 (J-Link 실기 또는 SEGGER device list) |
| OpenOCD target cfg | `target/w55mh32.cfg` 미제공 가능성 | 쿠루루 — 미존재 시 launch.json에서 OpenOCD 구성 주석 처리 권장 |
| `w55mh32_rcc.c`/`gpio.c` source 존재 | drivers/W55MH32X_Driver/src에 존재 확인됨 | — |
| 링크 시 `crypt_lib_ac6.lib`, `w55mh32.lib` 등 정적 라이브러리 필요 여부 | 본 템플릿(범용 펌웨어, 네트워크 미사용)에는 불필요 가정 | 필요 시 `cmake/w55mh32x/CMakeLists.txt`에 `target_link_libraries(... INTERFACE <lib>)` 추가 |
| Windows/WSL 경로 호환 | 모든 경로는 `${workspaceFolder}`/`${CMAKE_SOURCE_DIR}` 기반 | — |

## 8. 구현 시 주의 (쿠루루용 체크리스트)

1. `.gitignore`는 **전체 치환** (덧붙이기 금지) — §2.2 내용 그대로.
2. 신규 `.c`/`.h` 파일은 위 §3 코드 블록을 **있는 그대로** 작성. 추가 로직 넣지 말 것 (템플릿이라 의도적으로 비어있음).
3. CMake configure 첫 빌드는 `cmake --preset debug && cmake --build --preset debug` 로 검증. `.elf`/`.hex`/`.bin` 생성과 `arm-none-eabi-size` 출력 확인.
4. 커밋 단위(task #10의 7개): .gitignore → core/inc → core/src → cmake toolchain → cmake/w55mh32x → root CMakeLists+Presets → .vscode 4종, 순으로 분리 권장. 각 커밋이 단독으로 의미를 가지도록.
5. `c_cpp_properties.json`은 빌드 1회 후 IntelliSense가 `compile_commands.json`을 읽어야 정확해짐. 첫 빌드 전에는 일부 헤더가 회색 표시될 수 있음 (정상).
6. J-Link device 명 확정 어려우면 `"device": "Cortex-M3"`로 둘 것.

## 9. Addendum — 추가 발견 및 보완 (2026-05-23 후속)

### 9.1 케로로/타마마 추가 조사 검증 결과

| 추가 발견사항 | 본 설계 반영 여부 | 위치 |
|--------------|----------------|------|
| `USE_HAL_GPIO_MODULE` 패턴 → `USE_STDPERIPH_DRIVER` 패턴 | ✅ 반영 완료 | §1, §3.3, §4.5 |
| `HAL_Init()` → SPL init 패턴 | ✅ 반영 완료 | §3.5 (SystemInit + SystemClock_Config) |
| HAL MSP 패턴 → SPL BSP 패턴 | ✅ 반영 완료 | §3.6 (`BSP_*` weak) |
| launch.json `device` STM32G071RBTx → W55MH32 | ✅ 반영 완료 | §5.2 |
| `tasks.json` STM32_Programmer_CLI 회피 | ✅ 반영 완료 (flash 태스크 자체를 §9.3에서 추가) | §9.3 |
| `c_cpp_properties.json` `compileCommands` 기반 | ✅ 반영 완료 | §5.3 |

### 9.2 W55MH32.svd / W55MH32.FLM 확인 결과

`drivers/CMSIS/Device/WIZnet/W55MH32X/pack/WIZnet.W55MH32_DFP.1.0.0.pack` 안에 다음 파일 존재 (zipfile 검증):

```
WIZnet.W55MH32_DFP.1.0.0/CMSIS/SVD/W55MH32.svd
WIZnet.W55MH32_DFP.1.0.0/CMSIS/Flash/W55MH32.FLM
WIZnet.W55MH32_DFP.1.0.0/WIZnet.W55MH32_DFP.pdsc
```

**권장 처리** (쿠루루 작업):
1. pack 파일을 zip으로 추출하여 SVD/FLM 별도 배치:
   - `drivers/CMSIS/Device/WIZnet/W55MH32X/svd/W55MH32.svd`
   - `drivers/CMSIS/Device/WIZnet/W55MH32X/flash/W55MH32.FLM`
2. launch.json `svdFile` 항목에 경로 추가 (§9.4 참조).
3. pack 파일 자체는 그대로 유지 (Keil μVision 사용자 호환).

WSL에 unzip 미설치 시 `python3 -m zipfile -e <pack> <dest>` 사용 가능.

### 9.3 tasks.json 보강 — Flash 태스크 추가

§5.1의 `tasks.json`에 다음 두 태스크를 추가:

```json
{
    "label": "Flash (J-Link)",
    "type": "shell",
    "command": "JLinkExe",
    "args": [
        "-device", "W55MH32",
        "-if", "SWD",
        "-speed", "4000",
        "-autoconnect", "1",
        "-CommanderScript", "${workspaceFolder}/.vscode/jlink-flash.jlink"
    ],
    "options": { "cwd": "${workspaceFolder}" },
    "dependsOn": ["Build (debug)"],
    "problemMatcher": []
},
{
    "label": "Flash (OpenOCD)",
    "type": "shell",
    "command": "openocd",
    "args": [
        "-f", "interface/cmsis-dap.cfg",
        "-f", "target/w55mh32.cfg",
        "-c", "program build/debug/w55mh32x_vscode_basic.elf verify reset exit"
    ],
    "options": { "cwd": "${workspaceFolder}" },
    "dependsOn": ["Build (debug)"],
    "problemMatcher": []
}
```

`.vscode/jlink-flash.jlink` 보조 스크립트 (J-Link CommanderScript):

```
loadfile build/debug/w55mh32x_vscode_basic.hex
r
g
qc
```

**중요**: STM32_Programmer_CLI는 STM32 전용 → **사용 금지**. WIZnet은 자체 ISP 도구를 별도로 제공할 수 있으나 본 템플릿에서는 J-Link/OpenOCD 표준 경로만 다룬다.

### 9.4 launch.json 보강 — SVD 경로

§5.2의 두 디버그 구성에 `svdFile` 경로 추가:

```json
"svdFile": "${workspaceFolder}/drivers/CMSIS/Device/WIZnet/W55MH32X/svd/W55MH32.svd"
```

→ Cortex-Debug 확장에서 페리페럴 레지스터 보기(Peripheral View) 지원.
SVD 파일 추출 전에는 해당 라인을 주석 또는 빈 문자열로 둘 것.

### 9.5 MCU define 명확화

`w55mh32.h`(7,150줄 헤더 전체)는 device-discriminating macro로 `W55MH32`를 **체크하지 않음**. SPL 활성화 조건은 오직 `USE_STDPERIPH_DRIVER`이며, 헤더 자체가 W55MH32 전용이라 분기 필요 없음.

→ 본 설계의 `target_compile_definitions(... W55MH32)`는 **IntelliSense/외부 도구 식별용**으로 유지 (제거해도 빌드는 동일). 변경 없음.

### 9.6 SPL 모듈 활성화 동작 명세

`w55mh32.h` 라인 17~25 기준:
```c
#if !defined  USE_STDPERIPH_DRIVER
  /*#define USE_STDPERIPH_DRIVER*/
#endif
...
#ifdef USE_STDPERIPH_DRIVER
  #include "w55mh32_conf.h"
#endif
```

즉 흐름은:
1. 빌드 시 `-D USE_STDPERIPH_DRIVER` 전달 (cmake `target_compile_definitions`)
2. `w55mh32.h`가 `w55mh32_conf.h` include
3. `w55mh32_conf.h`(§3.3)가 사용할 페리페럴 헤더 선택적 include

→ 본 설계의 `cmake/w55mh32x/CMakeLists.txt`에 `USE_STDPERIPH_DRIVER` 추가는 **필수** (§4.5 반영됨).

### 9.7 보완된 체크리스트 (§8 보강)

쿠루루 추가 작업:
- [ ] pack 파일에서 SVD/FLM 추출 (§9.2)
- [ ] tasks.json에 Flash (J-Link) + Flash (OpenOCD) 태스크 추가 (§9.3)
- [ ] `.vscode/jlink-flash.jlink` 보조 스크립트 생성 (§9.3)
- [ ] launch.json 두 구성에 `svdFile` 추가 (§9.4)
- [ ] STM32_Programmer_CLI 관련 참조는 어디에도 두지 말 것

## 10. Errata — 파일명 정정 (벤더 호환 강제)

### 10.1 문제 (쿠루루 발견, 2026-05-23)

`drivers/W55MH32X_Driver/inc/w55mh32.h:7121`이 다음과 같이 고정 include:
```c
#include "w55mh32_conf.h"
```

본 설계 §3.3은 파일명을 `w55mh32x_conf.h` (x 포함)로 명시했으나, **벤더 헤더가 x 없는 이름으로 참조**하므로 그대로 만들면 빌드 실패.

또한 벤더 페리페럴 헤더 전체가 `w55mh32_<periph>.h` 컨벤션 (x 없음)이라, 사용자 측 파일도 x를 빼는 것이 일관성 측면에서 옳음.

### 10.2 정정 결정 (확정)

| 원본 (§3, §4, §5) | 정정 | 근거 |
|------|------|------|
| `core/inc/w55mh32x_conf.h` | **`core/inc/w55mh32_conf.h`** | 벤더 헤더 강제 include 이름 |
| `core/inc/w55mh32x_it.h` | **`core/inc/w55mh32_it.h`** | 벤더 페리페럴 컨벤션 일관성 |
| `core/src/w55mh32x_it.c` | **`core/src/w55mh32_it.c`** | 동일 |
| `core/src/w55mh32x_msp.c` | **`core/src/w55mh32_msp.c`** | 동일 (케로로 지시의 `w55mh32x_msp.c`는 STM32 패밀리 placeholder `x`를 그대로 답습한 것으로 판단 — 케로로 승인 사항) |
| include guard `__W55MH32X_CONF_H` | **`__W55MH32_CONF_H`** | 파일명 일치 |
| include guard `__W55MH32X_IT_H` | **`__W55MH32_IT_H`** | 동일 |
| cmake 디렉토리 `cmake/w55mh32x/` | **`cmake/w55mh32/`** | 내부 명명, 일관성 통일 (선택적, but 권장) |

### 10.3 설계 메모 — "x" 의 의미 재검토

STM32 SPL의 `stm32f10x_conf.h`, `stm32g0xx_msp.c` 등에서 마지막 `x`는 **family 끝자리 placeholder** (e.g. STM32F10**3**, STM32G0**71**). W55MH32는 family명이 단일하게 확정된 MCU이므로 placeholder가 불필요. 벤더도 헤더에서 `x`를 쓰지 않음.

→ 케로로 지시의 `w55mh32x_msp.c`는 STM32 명명 패턴을 기계적으로 옮긴 것으로 판단되며, 벤더 컨벤션 우선 적용.

### 10.4 영향 받는 §의 정정 (§3, §4, §5 모두 적용)

**적용 규칙**: 본 설계 문서 §3 ~ §5 전체에서 `w55mh32x_` 토큰은 다음 매핑으로 일괄 치환하여 읽어야 함.

| 발생 위치 | 치환 |
|---------|------|
| `w55mh32x_conf.h` | `w55mh32_conf.h` |
| `w55mh32x_it.h` | `w55mh32_it.h` |
| `w55mh32x_it.c` | `w55mh32_it.c` |
| `w55mh32x_msp.c` | `w55mh32_msp.c` |
| `__W55MH32X_CONF_H` | `__W55MH32_CONF_H` |
| `__W55MH32X_IT_H` | `__W55MH32_IT_H` |
| `cmake/w55mh32x/` | `cmake/w55mh32/` |

§3.2 매트릭스, §3.3~§3.7 코드, §4.2 root CMakeLists의 `file(GLOB ...)` 명시 리스트, §4.5 cmake/w55mh32/CMakeLists.txt 모두 본 규칙 적용 후 사용할 것.

`USE_STDPERIPH_DRIVER` define, `W55MH32` compile def, `w55mh32x_flash.ld` 링커 스크립트 파일명, `startup_w55mh32.s` 어셈블리 파일명, `w55mh32x_vscode_basic` 프로젝트명은 **변경 없음** (이들은 기존 파일/외부 식별자).

### 10.5 명령형 체크리스트 (쿠루루 즉시 반영)

- [ ] `core/inc/w55mh32_conf.h` 로 생성 (§3.3 본문 그대로, guard만 `__W55MH32_CONF_H`)
- [ ] `core/inc/w55mh32_it.h` (§3.4 본문 그대로, guard `__W55MH32_IT_H`)
- [ ] `core/src/w55mh32_it.c` (§3.7 본문 그대로, include `"w55mh32_it.h"`)
- [ ] `core/src/w55mh32_msp.c` (§3.6 본문 그대로)
- [ ] `cmake/w55mh32/CMakeLists.txt` (§4.5 본문 그대로)
- [ ] root `CMakeLists.txt`의 `add_subdirectory(cmake/w55mh32)`, `file(GLOB ... w55mh32_it.c w55mh32_msp.c)` 경로 정정 (§4.2)

### 10.6 권장 커밋 순서 재갱신 (§8 → §9.7 → §10.6)

총 8개 커밋. 변경된 파일명만 반영:

1. `.gitignore` 전체 치환 (§2.2)
2. `core/inc/` 헤더 3종 (`main.h`, `w55mh32_conf.h`, `w55mh32_it.h`)
3. `core/src/` 소스 3종 (`main.c`, `w55mh32_msp.c`, `w55mh32_it.c`)
4. `cmake/gcc-arm-none-eabi.cmake` (§4.4)
5. `cmake/w55mh32/CMakeLists.txt` (§4.5)
6. root `CMakeLists.txt` + `CMakePresets.json` (§4.2, §4.3)
7. SVD/FLM 추출 + 배치 (§9.2)
8. `.vscode/` 4개 파일 + `.vscode/jlink-flash.jlink` (§5.1~§5.4, §9.3~§9.4)

## 11. Errata — CMSIS 버전 불일치 (task #13 관련)

### 11.1 발견 (2026-05-23, 빌드 실패 분석)

`core/inc/` 와 `core/src/` 에 동봉된 ARM CMSIS Cortex-M3 core 파일들의 버전이 일치하지 않음.

| 파일 | 버전 | 날짜 |
|------|------|------|
| `core/inc/core_cm3.h` | **V3.20** | 2013-02-25 |
| `core/src/core_cm3.c` | **V1.30** | 2009-10-30 |

4년 차이 + CMSIS major version 차이로 인한 충돌 발생.

### 11.2 핵심 충돌

CMSIS V3.x 표준 변경:
- V3.x 이상부터 모든 core intrinsic 함수(`NVIC_*`, `__set_PRIMASK`, `__enable_irq` 등)를 헤더에서 `__STATIC_INLINE`으로 제공.
- → `core_cm*.c` 파일은 **표준 배포에서 제거됨**. CMSIS V3.x 이후 GitHub의 ARM-software/CMSIS 저장소에 core_cm3.c는 존재하지 않음.

실측 충돌 사례:
```
core_cm3.h:1291  __STATIC_INLINE void NVIC_SetPriorityGrouping(...)   ← V3.20 inline
core_cm3.h:1323  __STATIC_INLINE void NVIC_EnableIRQ(...)             ← V3.20 inline
core_cm3.h:1405  __STATIC_INLINE void NVIC_SetPriority(...)           ← V3.20 inline

core_cm3.c:193   __ASM void __set_PRIMASK(uint32_t priMask)           ← V1.30 외부 함수
core_cm3.c:551   void __set_PRIMASK(uint32_t priMask)                 ← V1.30 일반 함수
```

→ V3.20 헤더가 `__STATIC_INLINE`으로 정의한 함수와 V1.30 `.c`의 동명 함수가 링크 시점에 충돌, 또는 컴파일러가 함수 정의를 두 번 보면서 redefinition 에러.

### 11.3 해결 결정 (확정, 권장)

**`core/src/core_cm3.c` 를 빌드 대상에서 제외**.

근거:
1. CMSIS V3.x 이상의 표준: 헤더 only. `.c` 빌드 불필요.
2. V3.20 헤더가 모든 필요 함수를 `__STATIC_INLINE`으로 제공 → 별도 소스 빌드 없이도 전 페리페럴 정상 동작.
3. 벤더 코드 패치 회피 → 향후 벤더 업데이트 머지 부담 제거.
4. 파일 삭제가 아닌 빌드 제외 (`.c` 파일은 디스크에 남겨두되 `target_sources`에서 빠짐).

### 11.4 §4.5 `cmake/w55mh32/CMakeLists.txt` 정정

§4.5의 INTERFACE library 소스 목록에서 `core_cm3.c` 줄 제거:

```cmake
# 정정 전 (§4.5)
target_sources(w55mh32x_hal INTERFACE
    ${CMAKE_SOURCE_DIR}/core/src/system_w55mh32.c
    ${CMAKE_SOURCE_DIR}/core/src/core_cm3.c                  # ← 삭제
    ...
)

# 정정 후
target_sources(w55mh32x_hal INTERFACE
    ${CMAKE_SOURCE_DIR}/core/src/system_w55mh32.c

    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/misc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_rcc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_gpio.c
    # ...
)
```

`core/inc/core_cm3.h` 는 그대로 사용 (헤더는 V3.20이 표준이며 정상 동작).
`core/src/core_cm3.c` 파일은 **디스크에 유지**하되 빌드 대상에서만 제외 (벤더 제공 파일 보존 원칙).

### 11.5 대안 검토

| 대안 | 채택 여부 | 사유 |
|------|---------|------|
| A. core_cm3.c 빌드 제외 | ✅ 채택 | 표준 CMSIS V3.x 패턴, 벤더 코드 무수정 |
| B. core_cm3.c, core_cm3.h 모두 V5 최신으로 교체 | ❌ | 벤더 SPL이 V3.20 API에 의존할 가능성, 회귀 위험 |
| C. core_cm3.c 패치 (충돌 함수 제거) | ❌ | 벤더 코드 수정 → 업데이트 머지 부담 |
| D. core_cm3.h를 V1.30 헤더로 교체 | ❌ | V1.30 헤더는 V3.x 대비 누락 API 많음 (DWT, ITM 등) |

### 11.6 검증 절차 (쿠루루)

1. `cmake/w55mh32/CMakeLists.txt`에서 `core_cm3.c` 라인 제거 후 `cmake --build --preset debug` 재실행.
2. 링크 에러 (`__set_PRIMASK` 등 undefined reference) 발생 시 → V3.20 헤더가 inline으로 제공 중이므로 발생 안 함이 정상.
3. 만약 헤더 측 `__STATIC_INLINE` 매크로 정의가 누락된 컴파일러라면 `__STATIC_INLINE` 매크로 fallback을 `static __inline`으로 정의 필요. arm-none-eabi-gcc는 표준 매크로 인식하므로 추가 작업 불필요.

### 11.7 force-push 묶음 권장

쿠루루 force-push 시점에 §10 파일명 정정과 §11 core_cm3.c 빌드 제외를 **단일 force-push로 묶어** 처리 권장. 별도 PR/커밋 분리 불필요. 정정 커밋은 §10.6의 5번 커밋 (`cmake/w55mh32/CMakeLists.txt`) 안에서 동시 반영.

### 11.8 task #13 관계

방금 등록된 task #13 ("core_cm3.c CMSIS V1.30 빌드 오류 수정")의 본질은 본 §11 결정으로 해결 가능. 별도 task로 분리하지 않고 task #10 force-push 묶음으로 통합 처리 권장. 케로로 결정 사항.
