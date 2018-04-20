
#STM32F4 Project Template

## Переменные среды 

* ARM_TOOLCHAIN_PATH - путь к установленному тулчейну 
* STM32_HAL_DIR - путь к  STM32Cube_FW

## Flashing

### st-link tools
     st-flash --reset write firmware.bin 0x8000000


## OpenOCD

	openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/share/openocd/scripts/target/stm32f4x.cfg

