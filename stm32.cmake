# Путь к тулчейну
if(DEFINED ENV{ARM_TOOLCHAIN_PATH})
	SET(TOOLCHAIN_DIR $ENV{ARM_TOOLCHAIN_PATH})
else()
	message(FATAL_ERROR "Please set ARM_TOOLCHAIN_PATH environment value")
endif()

# Путь к библиотеке стандартной переферии.
if(DEFINED ENV{STM32_HAL_DIR})
	SET(STM32_HAL_DIR $ENV{STM32_HAL_DIR})
else()
	message(FATAL_ERROR "Please set STM32_HAL_DIR environment value")
endif()


# Пути, где лежат заголовки
SET(STM32_HAL_INCLUDE_DIRS
    ${STM32_HAL_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${STM32_HAL_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32_HAL_DIR}/Drivers/CMSIS/Include
)

SET(STM32_PROCESSOR_OPT
    "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp"
)

# Другие полезные пути
SET(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_DIR}/bin)
SET(TOOLCHAIN_LIBC_DIR ${TOOLCHAIN_DIR}/arm-none-eabi/libc)
SET(TOOLCHAIN_INC_DIR ${TOOLCHAIN_LIBC_DIR}/include)
SET(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_DIR}/arm-none-eabi/lib/)
link_directories(${TOOLCHAIN_LIB_DIR})

SET(CMAKE_SYSTEM_NAME Linux CACHE INTERNAL "system name")
SET(CMAKE_SYSTEM_PROCESSOR arm CACHE INTERNAL "processor")

# Компиляторы
SET(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-gcc CACHE INTERNAL "")
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-g++ CACHE INTERNAL "")
SET(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-gcc CACHE INTERNAL "")

# Включаем ассемблер
ENABLE_LANGUAGE(ASM)

# objcopy и objdump для создания хексов и бинариков
SET(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-objcopy CACHE INTERNAL "")
SET(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-objdump CACHE INTERNAL "")
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CROSSCOMPILING 1)
#IF(SEMIHOSTING STREQUAL "enable")
#  message(STATUS "Arm semihosting: Enabled")
#  ADD_DEFINITIONS(-DSEMIHOSTING_ENABLE)
#  SET(EXTRA_FLAGS_SEMIHOSTING "--specs=rdimon.specs -lc -lrdimon")
#else()
#  message(STATUS "Arm semihosting: Disabled")

#ENDIF()

# Установка HSE_VALUE
if(NOT HSE_VALUE)
    message(STATUS "Setting HSE to default")
else()
    message(STATUS "Setting HSE to ${HSE_VALUE}")
    ADD_DEFINITIONS("-DHSE_VALUE=${HSE_VALUE}")

endif()

# Флаги компиляторов, тут можно подкрутить
SET(CMAKE_C_FLAGS "-isystem ${TOOLCHAIN_INC_DIR} ${STM32_PROCESSOR_OPT} -fno-builtin -Wall -std=gnu99 ${EXTRA_FLAGS_SEMIHOSTING}" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-isystem ${TOOLCHAIN_INC_DIR} ${STM32_PROCESSOR_OPT} -fno-builtin -Wall " CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,-Map -Wl,main.map ${STM32_PROCESSOR_OPT} -lc -lm -lnosys -specs=nano.specs" CACHE INTERNAL "exe link flags")
SET(CMAKE_MODULE_LINKER_FLAGS "-L${TOOLCHAIN_LIB_DIR}" CACHE INTERNAL "module link flags")
SET(CMAKE_SHARED_LINKER_FLAGS "-L${TOOLCHAIN_LIB_DIR}" CACHE INTERNAL "shared lnk flags")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

SET(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_LIBC_DIR} CACHE INTERNAL "cross root directory")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH CACHE INTERNAL "")
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY CACHE INTERNAL "")
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY CACHE INTERNAL "")

# Исходник CMSIS
SET(STM32_SYSTEM_SOURCE ${STM32_HAL_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c)
SET(STM32_SYSTEM_SOURCE ${STM32_SYSTEM_SOURCE} ${STM32_HAL_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c)
SET(STM32_SYSTEM_SOURCE ${STM32_SYSTEM_SOURCE} ${STM32_HAL_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c)
SET(STM32_HAL_SRC_PATH ${STM32_HAL_DIR}/Drivers/STM32F4xx_HAL_Driver/Src)



SET(STARTUP_PATH "${STM32_HAL_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc")

SET(STM32_STARTUP_401XC ${STARTUP_PATH}/startup_stm32f401xc.s)
SET(STM32_STARTUP_401XE ${STARTUP_PATH}/startup_stm32f401xe.s)
SET(STM32_STARTUP_405XX ${STARTUP_PATH}/startup_stm32f405xx.s)
SET(STM32_STARTUP_407XX ${STARTUP_PATH}/startup_stm32f407xx.s)
SET(STM32_STARTUP_410CX ${STARTUP_PATH}/startup_stm32f410cx.s)
SET(STM32_STARTUP_410RX ${STARTUP_PATH}/startup_stm32f410rx.s)
SET(STM32_STARTUP_410TX ${STARTUP_PATH}/startup_stm32f410tx.s)
SET(STM32_STARTUP_411XE ${STARTUP_PATH}/startup_stm32f411xe.s)
SET(STM32_STARTUP_412CX ${STARTUP_PATH}/startup_stm32f412cx.s)
SET(STM32_STARTUP_412RX ${STARTUP_PATH}/startup_stm32f412rx.s)
SET(STM32_STARTUP_412VX ${STARTUP_PATH}/startup_stm32f412vx.s)
SET(STM32_STARTUP_412ZX ${STARTUP_PATH}/startup_stm32f412zx.s)
SET(STM32_STARTUP_413XX ${STARTUP_PATH}/startup_stm32f413xx.s)
SET(STM32_STARTUP_415XX ${STARTUP_PATH}/startup_stm32f415xx.s)
SET(STM32_STARTUP_417XX ${STARTUP_PATH}/startup_stm32f417xx.s)
SET(STM32_STARTUP_423XX ${STARTUP_PATH}/startup_stm32f423xx.s)
SET(STM32_STARTUP_427XX ${STARTUP_PATH}/startup_stm32f427xx.s)
SET(STM32_STARTUP_429XX ${STARTUP_PATH}/startup_stm32f429xx.s)
SET(STM32_STARTUP_437XX ${STARTUP_PATH}/startup_stm32f437xx.s)
SET(STM32_STARTUP_439XX ${STARTUP_PATH}/startup_stm32f439xx.s)
SET(STM32_STARTUP_446XX ${STARTUP_PATH}/startup_stm32f446xx.s)
SET(STM32_STARTUP_469XX ${STARTUP_PATH}/startup_stm32f469xx.s)
SET(STM32_STARTUP_479XX ${STARTUP_PATH}/startup_stm32f479xx.s)

SET(STM32_ADC_SOURCE ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_adc.c)
SET(STM32_RCC_SOURCE ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_rcc.c ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_rcc_ex.c)
SET(STM32_GPIO_SOURCE ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_gpio.c)
SET(STM32_RTC_SOURCE ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_rtc.c ${STM32_HAL_SRC_PATH}/stm32f4xx_hal_rtc_ex.c)


#[[

# Модули библиотеки стандартной переферии

SET(STM32_BKP_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c)
SET(STM32_CAN_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c)
SET(STM32_CEC_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c)
SET(STM32_CRC_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c)
SET(STM32_DAC_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c)
SET(STM32_DBGMCU_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c)
SET(STM32_DMA_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c)
SET(STM32_EXTI_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c)
SET(STM32_FLASH_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c)
SET(STM32_FSMC_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c)
SET(STM32_GPIO_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c)
SET(STM32_I2C_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c)
SET(STM32_IWDG_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c)
SET(STM32_PWR_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c)
SET(STM32_RTC_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c)
SET(STM32_SDIO_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c)
SET(STM32_SPI_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c)
SET(STM32_TIM_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c)
SET(STM32_USART_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c)
SET(STM32_WWDG_SOURCE ${STM32_StdPeriphLib_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c)
SET(SMT32_CMSIS_CORE_CM3 ${STM32_StdPeriphLib_DIR}/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c)

]]
