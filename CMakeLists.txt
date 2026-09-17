cmake_minimum_required(VERSION 3.16)

# ─────────────────────────────────────────────────────────────────────────────
#  Toolchain MUST be set before project() — point this to your arm-none-eabi-gcc
#  e.g. C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.3 rel1/bin
# ─────────────────────────────────────────────────────────────────────────────
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/arm-none-eabi.cmake")

project(smart_shoe_stm32_phase1 C ASM)

# ─────────────────────────────────────────────────────────────────────────────
#  Target MCU flags  (STM32F103C8T6 = Cortex-M3)
# ─────────────────────────────────────────────────────────────────────────────
set(MCU_FLAGS
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
)

# ─────────────────────────────────────────────────────────────────────────────
#  Compiler definitions required by STM32 HAL
# ─────────────────────────────────────────────────────────────────────────────
add_compile_definitions(
    USE_HAL_DRIVER
    STM32F103xB
)

# ─────────────────────────────────────────────────────────────────────────────
#  Include paths  (local Drivers/ folder cloned from STMicroelectronics GitHub)
# ─────────────────────────────────────────────────────────────────────────────
set(DRIVERS_DIR "${CMAKE_SOURCE_DIR}/Drivers")

set(HAL_INC
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Inc
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Inc/Legacy
    ${DRIVERS_DIR}/CMSIS/Device/ST/STM32F1xx/Include
    ${DRIVERS_DIR}/CMSIS/Core/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/Inc                         # project-local main.h
)

# ─────────────────────────────────────────────────────────────────────────────
#  HAL source files  (only the peripherals this project actually uses)
# ─────────────────────────────────────────────────────────────────────────────
file(GLOB HAL_SRCS
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
)

# ─────────────────────────────────────────────────────────────────────────────
#  Project sources  (your firmware file + startup + clock stubs)
# ─────────────────────────────────────────────────────────────────────────────
set(PROJECT_SRCS
    ${CMAKE_SOURCE_DIR}/smart_shoe_stm32_phase1.c
    ${CMAKE_SOURCE_DIR}/Src/system_stm32f1xx.c
    ${CMAKE_SOURCE_DIR}/startup_stm32f103xb.s
)

# ─────────────────────────────────────────────────────────────────────────────
#  Linker script
# ─────────────────────────────────────────────────────────────────────────────
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)

# ─────────────────────────────────────────────────────────────────────────────
#  Executable
# ─────────────────────────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME}.elf
    ${PROJECT_SRCS}
    ${HAL_SRCS}
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${HAL_INC})

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
    -fno-exceptions
    -O2
    -g
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -T${LINKER_SCRIPT}
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    --specs=nano.specs
    --specs=nosys.specs
    -lc
    -lm
    -lnosys
)

# ─────────────────────────────────────────────────────────────────────────────
#  Post-build: generate .hex and print size
# ─────────────────────────────────────────────────────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Generating HEX and BIN files..."
)
