################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configuration.cpp \
../src/LocalSearch.cpp \
../src/MonitorLayer.cpp \
../src/Problems.cpp \
../src/RandomRestartLocalSearch.cpp \
../src/Record.cpp \
../src/SolverCollection.cpp \
../src/Util.cpp \
../src/main.cpp 

OBJS += \
./src/Configuration.o \
./src/LocalSearch.o \
./src/MonitorLayer.o \
./src/Problems.o \
./src/RandomRestartLocalSearch.o \
./src/Record.o \
./src/SolverCollection.o \
./src/Util.o \
./src/main.o 

CPP_DEPS += \
./src/Configuration.d \
./src/LocalSearch.d \
./src/MonitorLayer.d \
./src/Problems.d \
./src/RandomRestartLocalSearch.d \
./src/Record.d \
./src/SolverCollection.d \
./src/Util.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


