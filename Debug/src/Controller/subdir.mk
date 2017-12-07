################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Controller/GlobalSettings.cpp \
../src/Controller/ProfileInfra.cpp 

OBJS += \
./src/Controller/GlobalSettings.o \
./src/Controller/ProfileInfra.o 

CPP_DEPS += \
./src/Controller/GlobalSettings.d \
./src/Controller/ProfileInfra.d 


# Each subdirectory must supply rules for building sources it contributes
src/Controller/%.o: ../src/Controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Adaptor" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/ModelChecking" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Controller" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Utils" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


