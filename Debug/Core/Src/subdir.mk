################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/auto_mode.c \
../Core/Src/button.c \
../Core/Src/config_mode.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/i2c-lcd.c \
../Core/Src/i2c.c \
../Core/Src/led_7_seg.c \
../Core/Src/main.c \
../Core/Src/manual_mode.c \
../Core/Src/scheduler.c \
../Core/Src/spi.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tasks.c \
../Core/Src/tim.c \
../Core/Src/traffic_light.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/auto_mode.o \
./Core/Src/button.o \
./Core/Src/config_mode.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/i2c-lcd.o \
./Core/Src/i2c.o \
./Core/Src/led_7_seg.o \
./Core/Src/main.o \
./Core/Src/manual_mode.o \
./Core/Src/scheduler.o \
./Core/Src/spi.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tasks.o \
./Core/Src/tim.o \
./Core/Src/traffic_light.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/auto_mode.d \
./Core/Src/button.d \
./Core/Src/config_mode.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/i2c-lcd.d \
./Core/Src/i2c.d \
./Core/Src/led_7_seg.d \
./Core/Src/main.d \
./Core/Src/manual_mode.d \
./Core/Src/scheduler.d \
./Core/Src/spi.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tasks.d \
./Core/Src/tim.d \
./Core/Src/traffic_light.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/auto_mode.cyclo ./Core/Src/auto_mode.d ./Core/Src/auto_mode.o ./Core/Src/auto_mode.su ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/config_mode.cyclo ./Core/Src/config_mode.d ./Core/Src/config_mode.o ./Core/Src/config_mode.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c-lcd.cyclo ./Core/Src/i2c-lcd.d ./Core/Src/i2c-lcd.o ./Core/Src/i2c-lcd.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/led_7_seg.cyclo ./Core/Src/led_7_seg.d ./Core/Src/led_7_seg.o ./Core/Src/led_7_seg.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/manual_mode.cyclo ./Core/Src/manual_mode.d ./Core/Src/manual_mode.o ./Core/Src/manual_mode.su ./Core/Src/scheduler.cyclo ./Core/Src/scheduler.d ./Core/Src/scheduler.o ./Core/Src/scheduler.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tasks.cyclo ./Core/Src/tasks.d ./Core/Src/tasks.o ./Core/Src/tasks.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/traffic_light.cyclo ./Core/Src/traffic_light.d ./Core/Src/traffic_light.o ./Core/Src/traffic_light.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

