#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED1 5   // PA5 (Nucleo LED)

void led_init(void);
void led_on(void);
void led_off(void);
void delay(uint32_t count);

#endif