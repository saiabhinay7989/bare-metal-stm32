#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (128 * 1024)
#define STACK_START (SRAM_START + SRAM_SIZE)

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

int main(void);

void Reset_Handler(void);
void Default_Handler(void);
void SysTick_Handler(void);
void EXTI15_10_IRQHandler(void);

/* weak handlers */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) =
{
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0,0,0,0,
    (uint32_t)&SVC_Handler,
    (uint32_t)&DebugMon_Handler,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&SysTick_Handler,

    /* External interrupts (only needed index for EXTI15_10) */
    [40] = (uint32_t)&EXTI15_10_IRQHandler
};

void Reset_Handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *src = (uint8_t*)&_etext;
    uint8_t *dst = (uint8_t*)&_sdata;

    for(uint32_t i=0;i<size;i++)
        dst[i] = src[i];

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