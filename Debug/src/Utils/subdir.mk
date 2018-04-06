################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utils/Utils.cpp 

OBJS += \
./src/Utils/Utils.o 

CPP_DEPS += \
./src/Utils/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utils/%.o: ../src/Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I"/home/ashutosp/ProfileInfra/src/Utils" -I"/home/ashutosp/ProfileInfra/src/Adaptor" -I"/home/ashutosp/ProfileInfra/src/Controller" -I"/home/ashutosp/ProfileInfra/src/ModelChecking" -I"/home/ashutosp/ProfileInfra/src/ProblemDB" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


