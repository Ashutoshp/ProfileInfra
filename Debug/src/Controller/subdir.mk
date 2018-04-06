################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Controller/DBWriter.cpp \
../src/Controller/GlobalSettings.cpp \
../src/Controller/Log.cpp \
../src/Controller/ProfileInfra.cpp 

OBJS += \
./src/Controller/DBWriter.o \
./src/Controller/GlobalSettings.o \
./src/Controller/Log.o \
./src/Controller/ProfileInfra.o 

CPP_DEPS += \
./src/Controller/DBWriter.d \
./src/Controller/GlobalSettings.d \
./src/Controller/Log.d \
./src/Controller/ProfileInfra.d 


# Each subdirectory must supply rules for building sources it contributes
src/Controller/%.o: ../src/Controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I"/home/ashutosp/ProfileInfra/src/Adaptor" -I"/home/ashutosp/ProfileInfra/src/ModelChecking" -I"/home/ashutosp/ProfileInfra/src/Controller" -I"/home/ashutosp/ProfileInfra/src/Utils" -I"/home/ashutosp/ProfileInfra/src/ProblemDB" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


