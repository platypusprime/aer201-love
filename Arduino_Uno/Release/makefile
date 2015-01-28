################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include arduino/avr-libc/subdir.mk
-include arduino/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
libArduino_Uno.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libArduino_Uno.a secondary-outputs

# Tool invocations
libArduino_Uno.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libArduino_Uno.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libArduino_Uno.lss: libArduino_Uno.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libArduino_Uno.a  >"libArduino_Uno.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libArduino_Uno.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p libArduino_Uno.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(ARCHIVES)$(S_DEPS)$(PDE_DEPS)$(LSS)$(C_DEPS)$(CC_DEPS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) libArduino_Uno.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
