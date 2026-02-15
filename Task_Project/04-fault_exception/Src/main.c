/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Write a progam to enable all configurable fault exceptions
 *                  implement the fault exception handlers and cause the fault by following method
 *
 *                  1. Execute an undefined instructions
 *                  2. Divide by zero
 *                  3. Try executing instruction from peripheral region
 *                  4. Executing SVC inside the SVC handler
 *                  5. Executing SVC instructions inside the interrupt handler whose priority
 *                     is same or lesser than SVC handler
 ******************************************************************************
*/

#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* 1. Enable configurable fault exceptions */
    uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

    *pSHCSR |= (1 << 16);  // MemManage enable
    *pSHCSR |= (1 << 17);  // BusFault enable
    *pSHCSR |= (1 << 18);  // UsageFault enable

    /* 2. Force UsageFault using undefined instruction */
    __asm volatile (".word 0xFFFFFFFF");

    /* Should never reach here */
    for(;;);
}

/* ================= Fault Handlers ================= */

void HardFault_Handler(void)
{
    printf("HardFault_Handler\r\n");
    while(1);
}

void MemManage_Handler(void)
{
    printf("MemManage_Handler\r\n");
    while(1);
}

void BusFault_Handler(void)
{
    printf("BusFault_Handler\r\n");
    while(1);
}

//void UsageFault_Handler(void)
//{
//    __asm volatile ("MRS r0, MSP");
//    register uint32_t msp_value __asm("r0");
//
//    uint32_t *pMSP = (uint32_t *)msp_value;
//    uint16_t *pUFSR = (uint16_t*)0xE000ED2A;
//
//    printf("UsageFault_Handler\r\n");
//    printf("UFSR = 0x%04X\r\n", *pUFSR);
//    printf("MSP = %p\r\n", pMSP);
//
//    while(1);
//}



void UsageFault_Handler(void)
{
    /* Read Main Stack Pointer (MSP) into R0 register
     * On exception entry, Cortex-M automatically uses MSP
     * MSP points to the stacked register frame */
    __asm volatile ("MRS r0, MSP");

    /* Bind C variable 'msp_value' to register R0
     * This avoids extra instructions and captures MSP value */
    register uint32_t msp_value __asm("r0");

    /* Cast MSP value to uint32_t pointer
     * This pointer now +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     *
     *
     *
     *
     *
     *
     *  to the stacked CPU registers:
     * [R0, R1, R2, R3, R12, LR, PC, xPSR] */
    uint32_t *pMSP = (uint32_t *)msp_value;

    /* Usage Fault Status Register (UFSR)
     * UFSR is the upper 16 bits of CFSR (0xE000ED28)
     * Address = 0xE000ED28 + 2 = 0xE000ED2A */
    uint16_t *pUFSR = (uint16_t *)0xE000ED2A;

    /* Print message indicating UsageFault handler execution */
    printf("UsageFault_Handler\r\n");

    /* Print Usage Fault Status Register value
     * This value helps identify the exact UsageFault reason
     * (DIVBYZERO, UNALIGNED, UNDEFINSTR, etc.) */
    printf("UFSR = 0x%04X\r\n", *pUFSR);

    /* Print MSP address
     * This stack pointer can be used to analyze stacked PC & LR
     * Useful for locating the faulting instruction */
    printf("MSP = %p\r\n", pMSP);

    /* Stay here forever
     * Prevents further execution and allows debugger inspection */
    while(1);
}

