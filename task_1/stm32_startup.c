#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (128 * 1024)
#define SRAM_END   (SRAM_START + SRAM_SIZE)

#define STACK_START SRAM_END

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

int main(void);

void Reset_Handler(void);
void Default_Handler(void);

/* Vector table */
uint32_t vectors[] __attribute__((section(".isr_vector"))) =
{
    STACK_START,
    (uint32_t)&Reset_Handler
};

void Reset_Handler(void)
{
    /* Copy .data */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *src = (uint8_t*)&_etext;
    uint8_t *dst = (uint8_t*)&_sdata;

    for(uint32_t i=0;i<size;i++)
        dst[i] = src[i];

    /* Zero .bss */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    dst = (uint8_t*)&_sbss;

    for(uint32_t i=0;i<size;i++)
        dst[i] = 0;

    main();
}

void Default_Handler(void)
{
    while(1);
}