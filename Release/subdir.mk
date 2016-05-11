################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ESP8266.cpp \
../can.cpp \
../led.cpp \
../main.cpp \
../queue.cpp \
../scheduler.cpp \
../systick.cpp \
../task.cpp \
../uart.cpp 

OBJS += \
./ESP8266.o \
./can.o \
./led.o \
./main.o \
./queue.o \
./scheduler.o \
./systick.o \
./task.o \
./uart.o 

CPP_DEPS += \
./ESP8266.d \
./can.d \
./led.d \
./main.d \
./queue.d \
./scheduler.d \
./systick.d \
./task.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=at90can128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


