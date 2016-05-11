################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ATMEGA90CAN128_CUSTOM_RTCS.lss \

FLASH_IMAGE += \
ATMEGA90CAN128_CUSTOM_RTCS.hex \

EEPROM_IMAGE += \
ATMEGA90CAN128_CUSTOM_RTCS.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ATMEGA90CAN128_CUSTOM_RTCS.elf secondary-outputs

# Tool invocations
ATMEGA90CAN128_CUSTOM_RTCS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,ATMEGA90CAN128_CUSTOM_RTCS.map,--cref -mrelax -Wl,--gc-sections -mmcu=at90can128 -o "ATMEGA90CAN128_CUSTOM_RTCS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ATMEGA90CAN128_CUSTOM_RTCS.lss: ATMEGA90CAN128_CUSTOM_RTCS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ATMEGA90CAN128_CUSTOM_RTCS.elf  >"ATMEGA90CAN128_CUSTOM_RTCS.lss"
	@echo 'Finished building: $@'
	@echo ' '

ATMEGA90CAN128_CUSTOM_RTCS.hex: ATMEGA90CAN128_CUSTOM_RTCS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ATMEGA90CAN128_CUSTOM_RTCS.elf  "ATMEGA90CAN128_CUSTOM_RTCS.hex"
	@echo 'Finished building: $@'
	@echo ' '

ATMEGA90CAN128_CUSTOM_RTCS.eep: ATMEGA90CAN128_CUSTOM_RTCS.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ATMEGA90CAN128_CUSTOM_RTCS.elf  "ATMEGA90CAN128_CUSTOM_RTCS.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ATMEGA90CAN128_CUSTOM_RTCS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=at90can128 ATMEGA90CAN128_CUSTOM_RTCS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) ATMEGA90CAN128_CUSTOM_RTCS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
