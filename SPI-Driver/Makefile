# path to CMSIS headers
CMSIS_PATH   := chip-headers/CMSIS

# include the project root (.) plus CMSIS
INCLUDES := \
    -Iinc \
    -Isrc \
    -Ichip-headers/CMSIS/Include \
    -Ichip-headers/CMSIS/Device/ST/STM32F4xx/Include

# toolchain & flags
CC      := arm-none-eabi-gcc
CFLAGS  := -DSTM32F446xx -c -mcpu=cortex-m4 -mthumb -std=gnu11 $(INCLUDES)
LDFLAGS := \
    -T stm32_ls.ld \
    --specs=nosys.specs \
    -lc -lm -lgcc \
    -Wl,-Map=stm32_blink.map
# source files and object files
SRCS := src/main.c \
        src/print.c \
        src/uart.c \
        src/adc.c \
        src/spi.c \
        src/adxl345.c \
        startup/stm32f446_startup.c

OBJS := $(SRCS:.c=.o)

# default target
all: stm32_blink.elf

# generic compile rule: .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# link everything into the final ELF
stm32_blink.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# flashing / debug helper
load:
	openocd -f board/st_nucleo_f4.cfg

# clean up all build artifacts
clean:
	rm -f $(OBJS) *.elf *.map
