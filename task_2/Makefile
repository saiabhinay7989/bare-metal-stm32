CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -Wall

all: final.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $<

final.elf: main.o led.o stm32_startup.o
	$(CC) -nostdlib -T stm32_ls.ld *.o -o final.elf

clean:
	rm -f *.o *.elf