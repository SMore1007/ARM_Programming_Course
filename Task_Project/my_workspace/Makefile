# CC = arm-none-eabi-gcc

# MACH = cortex-m4

# CFLAGS = -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0 -g -ffreestanding
# #LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs --specs=nosys.specs -T stm32_ls.ld -Wl,-Map=final.map
# LDFLAGS_SH = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs --specs=nosys.specs -T stm32_ls.ld -Wl,-Map=final.map

# SRCS = main.c led.c stm32_startup.c 
# OBJS = main.o led.o stm32_startup.o

# all: final.elf
# all_sh: final_sh.elf

# # Compile step (IMPORTANT: -c added)
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Link step
# final.elf: $(OBJS)
# 	$(CC) $(LDFLAGS) $^ -o $@

# final_sh.elf: $(OBJS)
# 	$(CC) $(LDFLAGS_SH) $^ -o $@


# clean:
# 	rm -rf *.o *.elf *.map

# # Only starts OpenOCD (debug server)
# openocd:
# 	openocd -f "D:/Argyan Technology/STM32_Embedded_Course/ARM_Programming_Course/OpenOCD/0.10.0-12-20190422-2015/scripts/board/st_nucleo_f4.cfg"

# # Full debug shortcut (VERY USEFUL)
# debug:
# 	arm-none-eabi-gdb final.elf \
# 	-ex "target remote localhost:3333" \
# 	-ex "monitor reset init" \
# 	-ex "load" \
# 	-ex "break main" \
# 	-ex "continue"

# .PHONY: all clean openocd debug



# ================= TOOLCHAIN =================
CC = arm-none-eabi-gcc

# ================= CPU =================
MACH = cortex-m4

# ================= FLAGS =================
CFLAGS = -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0 -g -ffreestanding

# Normal build (no semihosting)
LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft \
          --specs=nano.specs --specs=nosys.specs \
          -T stm32_ls.ld -Wl,-Map=final.map

# Semihosting build (IMPORTANT: no nosys here)
LDFLAGS_SH = -mcpu=$(MACH) -mthumb -mfloat-abi=soft \
             --specs=rdimon.specs \
             -T stm32_ls.ld -Wl,-Map=final_sh.map
			 
# ================= SOURCES =================
SRCS = main.c led.c stm32_startup.c
OBJS = $(SRCS:.c=.o)

# ================= TARGETS =================
all: final.elf
all_sh: final_sh.elf

# ================= COMPILE =================
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ================= LINK =================
final.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


final_sh.elf: $(OBJS)
	$(CC) $(LDFLAGS_SH) $^ -lc -lrdimon -o $@

# ================= CLEAN =================
clean:
	rm -rf *.o *.elf *.map

# ================= OPENOCD =================
openocd:
	openocd -f "D:/Argyan Technology/STM32_Embedded_Course/ARM_Programming_Course/OpenOCD/0.10.0-12-20190422-2015/scripts/board/st_nucleo_f4.cfg"

# ================= DEBUG NORMAL =================
debug:
	arm-none-eabi-gdb final.elf \
	-ex "target remote localhost:3333" \
	-ex "monitor reset init" \
	-ex "load" \
	-ex "break main" \
	-ex "continue"

# ================= DEBUG SEMIHOSTING =================
debug_sh:
	arm-none-eabi-gdb final_sh.elf \
	-ex "target remote localhost:3333" \
	-ex "monitor arm semihosting enable" \
	-ex "monitor reset init" \
	-ex "load" \
	-ex "break main" \
	-ex "continue"

.PHONY: all all_sh clean openocd debug debug_sh