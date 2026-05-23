# w55mh32x_vscode_basic

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![MCU: W55MH32 (Cortex-M3)](https://img.shields.io/badge/MCU-W55MH32%20Cortex--M3-green.svg)
![Toolchain: arm-none-eabi-gcc](https://img.shields.io/badge/toolchain-arm--none--eabi--gcc-orange.svg)

## Overview

A minimal Visual Studio Code + CMake template for **WIZnet W55MH32**
firmware development on a Cortex-M3 core. The project pairs the vendor
Standard Peripheral Library (SPL) with `arm-none-eabi-gcc`, Ninja, and
cortex-debug so that a fresh clone can configure, build, flash, and
debug without further setup.

The repository is organized to keep vendor code (CMSIS, SPL drivers,
DSP libraries) untouched while application code lives under `core/`.

## Requirements

| Tool | Version | Notes |
|------|---------|-------|
| `arm-none-eabi-gcc` | 10.3+ | C11 / C++17 capable |
| CMake | 3.22+ | Required for `CMakePresets.json` v6 |
| Ninja | any recent | Used by all presets |
| Visual Studio Code | latest | Workspace ships recommended extensions |
| J-Link or OpenOCD + CMSIS-DAP | optional | For flashing/debugging |

Recommended VS Code extensions are pulled in automatically from
`.vscode/extensions.json` (Cortex-Debug, CMake Tools, C/C++ IntelliSense,
ARM syntax, linker script highlighting).

## Project Structure

```
.
├── CMakeLists.txt              Root project + executable target
├── CMakePresets.json           Debug / Release presets (Ninja)
├── cmake/
│   ├── gcc-arm-none-eabi.cmake Toolchain (cortex-m3, soft FP)
│   └── w55mh32/
│       └── CMakeLists.txt      INTERFACE library bundling SPL + CMSIS
├── core/
│   ├── inc/                    Application headers (main.h, *_it.h, conf)
│   └── src/                    main.c, w55mh32_it.c, w55mh32_msp.c,
│                               and the CMSIS system/core sources
├── drivers/
│   ├── CMSIS/Device/WIZnet/W55MH32X/   CMSIS device pack (inc/lib/pack)
│   └── W55MH32X_Driver/                Vendor SPL (inc/src/lib/cryptlib)
├── docs/                       Reference manuals, datasheet, design docs
├── startup_w55mh32.s           Cortex-M3 startup (vector table, SystemInit)
├── w55mh32x_flash.ld           GNU LD linker script (flash + SRAM layout)
└── .vscode/                    Team-shared tasks, launch, IntelliSense
```

## Getting Started

```bash
# 1. Clone
git clone https://github.com/uoohyo/w55mh32x_vscode_basic.git
cd w55mh32x_vscode_basic

# 2. Configure (Debug)
cmake --preset debug

# 3. Build
cmake --build --preset debug

# 4. Output
#    build/debug/w55mh32x_vscode_basic.elf
#    build/debug/w55mh32x_vscode_basic.hex
#    build/debug/w55mh32x_vscode_basic.bin
```

Swap `debug` for `release` to get an optimized build.

Inside VS Code, hit `Ctrl+Shift+B` to run the default **Build (debug)**
task, or pick **Flash (J-Link)** / **Flash (OpenOCD)** from the task
list to program the target.

## MCU Info

| Item | Value |
|------|-------|
| Vendor | WIZnet |
| Family | W55MH32 |
| Core | ARM Cortex-M3 |
| FPU | None (soft float) |
| Toolchain | arm-none-eabi-gcc, `nano.specs` + `nosys.specs` |
| Build flags | `-mcpu=cortex-m3 -mthumb -mfloat-abi=soft` |

Flash and SRAM addresses, sizes, and section layout are defined in
`w55mh32x_flash.ld`. Reference manuals and the datasheet are shipped
under `docs/`.

## License

This project's template code is released under the MIT License — see
[`LICENSE`](LICENSE). Vendor sources under `drivers/` retain their
original WIZnet / ARM CMSIS licenses (see the `LICENSE` files inside
each vendor directory).
