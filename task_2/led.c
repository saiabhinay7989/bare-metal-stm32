#include <stdint.h>
#include "led.h"

#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR   (*(volatile uint32_t*)0x40020014)

#define LED_PIN 5

void led_init(void)
{
    RCC_AHB1ENR |= (1 << 0); // Enable GPIOA

    GPIOA_MODER |= (1 << (2 * LED_PIN));
    GPIOA_MODER &= ~(1 << (2 * LED_PIN + 1));
}

void led_toggle(void)
{
    GPIOA_ODR ^= (1 << LED_PIN);
}