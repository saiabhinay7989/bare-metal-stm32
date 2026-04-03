#include <stdint.h>
#include "button.h"

/* RCC */
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define RCC_APB2ENR (*(volatile uint32_t*)0x40023844)

/* GPIOC */
#define GPIOC_MODER (*(volatile uint32_t*)0x40020800)
#define GPIOC_PUPDR (*(volatile uint32_t*)0x4002080C)

/* SYSCFG */
#define SYSCFG_EXTICR4 (*(volatile uint32_t*)0x40013814)

/* EXTI */
#define EXTI_IMR  (*(volatile uint32_t*)0x40013C00)
#define EXTI_FTSR (*(volatile uint32_t*)0x40013C0C)

/* NVIC */
#define NVIC_ISER1 (*(volatile uint32_t*)0xE000E104)

void button_init(void)
{
    RCC_AHB1ENR |= (1 << 2);   // GPIOC enable
    RCC_APB2ENR |= (1 << 14);  // SYSCFG enable

    GPIOC_MODER &= ~(3 << (2 * 13)); // input

    // Pull-up (important for stability)
    GPIOC_PUPDR |= (1 << (2 * 13));

    SYSCFG_EXTICR4 |= (2 << 4); // PC13 → EXTI13

    EXTI_IMR  |= (1 << 13);
    EXTI_FTSR |= (1 << 13);

    NVIC_ISER1 |= (1 << 8); // EXTI15_10
}