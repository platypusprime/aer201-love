################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Arduino/hardware/arduino/cores/arduino/avr-libc/malloc.c \
C:/Arduino/hardware/arduino/cores/arduino/avr-libc/realloc.c 

C_DEPS += \
./arduino/avr-libc/malloc.d \
./arduino/avr-libc/realloc.d 

OBJS += \
./arduino/avr-libc/malloc.o \
./arduino/avr-libc/realloc.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/avr-libc/malloc.o: C:/Arduino/hardware/arduino/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Arduino\hardware\arduino\cores\arduino" -I"C:\Arduino\hardware\arduino\variants\standard" -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -g  -ffunction-sections  -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/avr-libc/realloc.o: C:/Arduino/hardware/arduino/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Arduino\hardware\arduino\cores\arduino" -I"C:\Arduino\hardware\arduino\variants\standard" -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -g  -ffunction-sections  -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


