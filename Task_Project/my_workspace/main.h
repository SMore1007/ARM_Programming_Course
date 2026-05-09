#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

/* ============================================================
   STACK CONFIGURATION
   ============================================================ */

#define SIZE_TASK_STACK        1024U
#define SIZE_SCHEDULER_STACK   1024U

/* ============================================================
   SRAM CONFIGURATION (STM32F4 example: 128KB SRAM)
   ============================================================ */

#define SRAM_START             0x20000000U // from meory map of processor
#define SRAM_SIZE              (128U * 1024U) // 128 kbyte total
#define SRAM_END               (SRAM_START + SRAM_SIZE)

/*
   Memory Layout (TOP -> DOWN)

   |---------------------|  SRAM_END
   |  Scheduler Stack    |
   |---------------------|
   |  Idle Task Stack    |
   |---------------------|
   |  Task1 Stack        |
   |---------------------|
   |  Task2 Stack        |
   |---------------------|
   |  Task3 Stack        |
   |---------------------|
   |  Task4 Stack        |
   |---------------------|
*/

#define SCHED_STACK_START      SRAM_END
#define IDEAL_STACK_START      (SRAM_END - 1U * SIZE_TASK_STACK)
#define T1_STACK_START         (SRAM_END - 2U * SIZE_TASK_STACK)
#define T2_STACK_START         (SRAM_END - 3U * SIZE_TASK_STACK)
#define T3_STACK_START         (SRAM_END - 4U * SIZE_TASK_STACK)
#define T4_STACK_START         (SRAM_END - 5U * SIZE_TASK_STACK)

/* ============================================================
   SYSTICK CONFIGURATION
   ============================================================ */

#define TICK_HZ                1000U
#define HSI_CLK                16000000U
#define SYSTICK_TIM_CLK        HSI_CLK

/* ============================================================
   TASK STATES
   ============================================================ */

#define MAX_TASKS              5U

#define TASK_READY_STATE       0x00
#define TASK_BLOCKED_STATE     0xFF

/* ============================================================
   CPU DEFINITIONS
   ============================================================ */

#define DUMMY_XPSR             0x01000000U   // Thumb bit set

/* ============================================================
   CORE REGISTERS
   ============================================================ */

#define ICSR                   (*(volatile uint32_t*)0xE000ED04)
#define NVIC_SHPR3             (*(volatile uint32_t*)0xE000ED20)

/* ============================================================
   INTERRUPT CONTROL
   ============================================================ */

#define INTERRUPT_DISABLE()    __asm volatile ("CPSID I")
#define INTERRUPT_ENABLE()     __asm volatile ("CPSIE I")

#endif /* MAIN_H_ */

