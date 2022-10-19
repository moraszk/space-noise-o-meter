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

CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
SIZE = arm-none-eabi-size

CPPFLAGS = -mcpu=cortex-m0plus -g3 -O0 -ffunction-sections -fdata-sections -Wall -Wextra --specs=nano.specs -mfloat-abi=soft -mthumb -I sw/Inc -fstack-usage
CFLAGS = -std=gnu11
CXXFLAGS = -std=c++2a -fno-exceptions -fno-rtti -fno-use-cxa-atexit

AS = arm-none-eabi-gcc
ASFLAGS = -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb

OBJECTS = $(addsuffix .o,$(basename $(wildcard sw/Src/*.cpp sw/Src/*.c sw/Src/*.s)))

sw/main.elf: $(OBJECTS)
	arm-none-eabi-g++ -o $@ $^ -mcpu=cortex-m0plus -T sw/stm32l010f4.ld --specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group

clean:
	find sw -name "*o" -delete
	find sw -executable -type f -delete
	find sw -name "*su" -delete

####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####

stackusage: $(OBJECTS)
	cat $(addsuffix .su, $(basename $(wildcard sw/Src/*cpp))) | awk 'BEGIN{FS="\t"} {print $$2 " " $$1 " " $$3;}' | sort -n -r | less

memoryusage: $(OBJECTS)
	$(SIZE) $^


####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####----####

sw/Tests/%: sw/Tests/%.cpp
	@echo "[CXX]    $(notdir $<)"
	@g++ -std=c++20 -fsanitize=address -fno-omit-frame-pointer $^ -o $@ -I sw/Tests -I sw/Inc -I sw/Src -g3

tests = $(basename $(wildcard sw/Tests/*cpp))

tests: $(tests)
	@for i in $^ ; do \
                echo -n "Running test" $$i; \
                ./$$i || echo -n "         FAIL                     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"; echo "";\
        done

sw/FuzzTests/%: sw/FuzzTests/%.cpp
	@echo "[CLANG]    $(notdir $<)"
	@clang++ -g -std=c++20 -fsanitize=fuzzer,signed-integer-overflow,memory $^ -o $@ -I sw/FuzzTests -I sw/Inc -I sw/Src

fuzztests = $(basename $(wildcard sw/FuzzTests/*cpp))

fuzztests: $(fuzztests)
	@for i in $^ ; do \
                echo -n "Running fuzztest" $$i; \
                ./$$i CORPUS -max_total_time=30;\
        done

.PHONY: tests clean fuzztests stackusage memoryusage
