################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ModelChecking/InvokePrism.cpp 

OBJS += \
./src/ModelChecking/InvokePrism.o 

CPP_DEPS += \
./src/ModelChecking/InvokePrism.d 


# Each subdirectory must supply rules for building sources it contributes
src/ModelChecking/%.o: ../src/ModelChecking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Utils" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Adaptor" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/Controller" -I"/home/ashutosp/workspace/Profiling/ProfileInfra/src/ModelChecking" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


