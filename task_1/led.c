#include <stdint.h>
#include "led.h"

#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)

void led_init(void)
{
    RCC_AHB1ENR |= (1 << 0);   // Enable GPIOA

    GPIOA_MODER |= (1 << (2 * LED1));
    GPIOA_MODER &= ~(1 << (2 * LED1 + 1));
}

void led_on(void)
{
    GPIOA_ODR |= (1 << LED1);
}

void led_off(void)
{
    GPIOA_ODR &= ~(1 << LED1);
}

void delay(uint32_t count)
{
    for(uint32_t i=0;i<count;i++);
}