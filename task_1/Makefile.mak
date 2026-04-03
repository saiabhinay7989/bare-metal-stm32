CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb -std=gnu11 -Wall -O0

all: final.elf

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

led.o: led.c
	$(CC) $(CFLAGS) -c led.c

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -c stm32_startup.c

final.elf: main.o led.o stm32_startup.o
	$(CC) -nostdlib -T stm32_ls.ld *.o -o final.elf

clean:
	rm -f *.o *.elf