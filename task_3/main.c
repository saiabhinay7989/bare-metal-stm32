#include <stdint.h>
#include "led.h"
#include "button.h"

/* SysTick */
#define SYST_CSR (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)

/* EXTI */
#define EXTI_PR (*(volatile uint32_t*)0x40013C14)

volatile uint8_t mode = 0;
volatile uint32_t tick = 0;
volatile uint32_t last_tick = 0;   // debounce

void systick_init(void)
{
    SYST_RVR = 16000000/10 - 1; // 100ms
    SYST_CVR = 0;

    SYST_CSR |= (1 << 1);
    SYST_CSR |= (1 << 2);
    SYST_CSR |= (1 << 0);
}

/* Timer ISR */
void SysTick_Handler(void)
{
    tick++;

    if(mode == 0)
    {
        if(tick >= 10) // 1 sec
        {
            led_toggle();
            tick = 0;
        }
    }
    else
    {
        if(tick >= 2) // 200 ms
        {
            led_toggle();
            tick = 0;
        }
    }
}

/* Button ISR with debounce */
void EXTI15_10_IRQHandler(void)
{
    EXTI_PR |= (1 << 13); // clear interrupt

    if((tick - last_tick) > 5) // debounce (~500ms)
    {
        mode ^= 1;
        last_tick = tick;
    }
}

int main(void)
{
    led_init();
    button_init();
    systick_init();

    while(1);
}