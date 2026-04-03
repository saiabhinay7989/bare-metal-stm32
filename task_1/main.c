#include "led.h"

int main(void)
{
    led_init();

    while(1)
    {
        led_on();
        delay(500000);
        led_off();
        delay(500000);
    }
}