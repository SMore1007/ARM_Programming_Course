/******************************************************************************
 * File    : main.c
 * Target  : STM32F446RE (Cortex-M4)
 * Purpose : TASK-3 - Same sub-priority, check execution by IRQ number
 * Author  : Bare-metal NVIC demo
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>

/* ---------------- IRQ NUMBERS ---------------- */
#define IRQNO_TIM6      54
#define IRQNO_OTG_FS    77

/* ---------------- NVIC REGISTERS ---------------- */
#define NVIC_ISER_BASE   ((uint32_t*)0xE000E100)
#define NVIC_ISPR_BASE   ((uint32_t*)0xE000E200)
#define NVIC_IPR_BASE    ((uint32_t*)0xE000E400)

/* ---------------- SCB AIRCR ---------------- */
#define SCB_AIRCR        (*(volatile uint32_t*)0xE000ED0C)
#define VECTKEY          0x5FA

/* ---------------- FUNCTION PROTOTYPES ---------------- */
void nvic_set_priority_grouping(uint8_t prigroup);
void configure_priority_for_irq(uint8_t irq_no, uint8_t priority);
void enable_irq(uint8_t irq_no);
void set_pending_irq(uint8_t irq_no);
uint8_t encode_priority(uint8_t preempt_prio, uint8_t sub_prio);

/* ---------------- PRIORITY GROUPING ---------------- */
/*
 * PRIGROUP = 5
 * Preempt Priority : 2 bits
 * Sub Priority     : 2 bits
 */
void nvic_set_priority_grouping(uint8_t prigroup)
{
    SCB_AIRCR = (VECTKEY << 16) | (prigroup << 8);
}

/* ---------------- PRIORITY ENCODING ---------------- */
uint8_t encode_priority(uint8_t preempt_prio, uint8_t sub_prio)
{
    /*
     * Bits [7:6] = Preempt priority
     * Bits [5:4] = Sub priority
     * Bits [3:0] = Not implemented
     */
    return ((preempt_prio << 6) | (sub_prio << 4));
}

/* ---------------- NVIC CONFIG HELPERS ---------------- */
void configure_priority_for_irq(uint8_t irq_no, uint8_t priority)
{
    uint8_t iprx = irq_no / 4;
    uint8_t pos  = (irq_no % 4) * 8;

    NVIC_IPR_BASE[iprx] &= ~(0xFF << pos);
    NVIC_IPR_BASE[iprx] |= (priority << pos);
}

void enable_irq(uint8_t irq_no)
{
    NVIC_ISER_BASE[irq_no / 32] |= (1 << (irq_no % 32));
}

void set_pending_irq(uint8_t irq_no)
{
    NVIC_ISPR_BASE[irq_no / 32] |= (1 << (irq_no % 32));
}

/* ---------------- ISR DEFINITIONS ---------------- */
void TIM6_DAC_IRQHandler(void)
{
    printf("TIM6 ISR executed (IRQ 54)\n");
}

void OTG_FS_IRQHandler(void)
{
    printf("OTG FS ISR executed (IRQ 77)\n");
}

/* ---------------- MAIN ---------------- */
int main(void)
{
    printf("TASK-3: Same sub-priority test started\n");

    /* Step 1: Configure priority grouping */
    nvic_set_priority_grouping(5);

    /* Step 2: Same preempt + same sub priority */
    uint8_t same_priority = encode_priority(1, 1);

    configure_priority_for_irq(IRQNO_TIM6,   same_priority);
    configure_priority_for_irq(IRQNO_OTG_FS, same_priority);

    /* Step 3: Enable IRQs */
    enable_irq(IRQNO_TIM6);
    enable_irq(IRQNO_OTG_FS);

    /* Step 4: Trigger both interrupts */
    set_pending_irq(IRQNO_OTG_FS);
    set_pending_irq(IRQNO_TIM6);

    while (1);
}
