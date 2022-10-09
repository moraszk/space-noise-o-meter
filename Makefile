# ____________________________
#/ University of Szeged       \
#|                            |
#| Student card 4 BME MRC-100 |
#|                            |
#\ Makefile                   /
# ----------------------------
#        \   ^__^
#         \  (oo)\_______
#            (__)\       )\/\
#                ||----w |
#                ||     ||
#######################################

#Implicit c++ rule
#$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c

#Implicit c rule
#$(CC) $(CPPFLAGS) $(CFLAGS) -c

CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++

CPPFLAGS = -mcpu=cortex-m0plus -g3 -O0 -ffunction-sections -fdata-sections -Wall --specs=nano.specs -mfloat-abi=soft -mthumb -I sw/Inc
#-DSTM32L010x4
CFLAGS = -std=gnu11
CXXFLAGS = -std=c++2a -fno-exceptions -fno-rtti -fno-use-cxa-atexit

AS = arm-none-eabi-gcc
ASFLAGS = -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb

OBJECTS = $(addsuffix .o,$(basename $(wildcard sw/Src/*.cpp sw/Src/*.c sw/Src/*.S)))

sw/main.elf: $(OBJECTS)
	arm-none-eabi-g++ -o $@ $^ -mcpu=cortex-m0plus -T"stm32l010f4.ld" --specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
