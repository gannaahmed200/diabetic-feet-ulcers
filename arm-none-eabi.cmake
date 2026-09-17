# ─────────────────────────────────────────────────────────────────────────────
#  arm-none-eabi.cmake  —  CMake toolchain file for ARM Cortex-M bare-metal
#
#  HOW TO SET YOUR COMPILER PATH:
#    Edit the line below (TOOLCHAIN_PREFIX) to match where arm-none-eabi-gcc
#    is installed on your PC. Examples:
#
#    Windows (Arm GNU Toolchain):
#      C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.3 rel1/bin/arm-none-eabi-
#
#    Windows (STM32CubeIDE built-in GCC):
#      C:/ST/STM32CubeIDE_1.x.x/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.xx.x.xxx/tools/bin/arm-none-eabi-
#
#    If arm-none-eabi-gcc is already in your system PATH just use:
#      set(TOOLCHAIN_PREFIX "C:/Users/Dell/Downloads/arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin/arm-none-eabi-")
# ─────────────────────────────────────────────────────────────────────────────

# >>>  CHANGE THIS LINE to your actual compiler path  <<<
set(TOOLCHAIN_PREFIX "C:/Users/Dell/Downloads/arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin/arm-none-eabi-")

# ---------------------------------------------------------------------------
set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_OBJCOPY      "${TOOLCHAIN_PREFIX}objcopy.exe")
set(CMAKE_OBJDUMP      "${TOOLCHAIN_PREFIX}objdump.exe")
set(CMAKE_SIZE         "${TOOLCHAIN_PREFIX}size.exe")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Prevent CMake from testing the compiler with a dummy executable
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
