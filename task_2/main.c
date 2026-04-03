#include <stdint.h>
#include "led.h"

/* SysTick Registers */
#define SYST_CSR (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)

/* Initialize SysTick (500ms interrupt) */
void systick_init(void)
{
    SYST_RVR = 16000000/2 - 1; // 500 ms
    SYST_CVR = 0;

    SYST_CSR |= (1 << 1); // interrupt enable
    SYST_CSR |= (1 << 2); // processor clock
    SYST_CSR |= (1 << 0); // enable
}

/* ISR */
void SysTick_Handler(void)
{
    led_toggle();
}

int main(void)
{
    led_init();
    systick_init();

    while(1);
}