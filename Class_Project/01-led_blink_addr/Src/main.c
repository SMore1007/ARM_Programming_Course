/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Blink Led on STM32F446RE
 * 					 Where is the On-board LED?
 * 					 PORTA - Pin 5, it uses the AHB1 bus
 ******************************************************************************
 */
/*
AHB Bus :- Advanced High Performance bus
APB Bus :- Advanced Peripherals Bus
-------------------------------------------
RCC_BASE        :- 0x40023800

RCC_AHB1ENR_OFFSET    :- 0x30
RCC_AHB1ENR     :- 0x40023830
-------------------------------------------

GPIOA_BASE     :- 0x40020000

GPIOA_MODER_OFFSET   :- 0x00
GPIOA_MODER    :- 0x40020000

GPIOA_ODR_OFFSET    :-  0x14
GPIOA_ODR     :-  0x40020014
-------------------------------------------
*/

#include <stdint.h>

#define RCC_AHB1ENR (*(uint32_t *)0x40023830)

#define GPIOA_MODER (*(uint32_t *)0x40020000)

#define GPIOA_ODR (*(uint32_t *)0x40020014)

int main(void)
{
    RCC_AHB1ENR |= (0x1 << 0); // Enable clock for GPIOA

    // Set pin5 to output (On-board LED)
    GPIOA_MODER |= (0x1 << 10);
    GPIOA_MODER &= ~(0x1 << 11);

    while (1)
    {
        GPIOA_ODR |= (0x1 << 5);
        for (int i = 0; i < 1000000; i++)
        {
        }
        GPIOA_ODR &= ~(0x1 << 5);
        for (int i = 0; i < 1000000; i++)
        {
        }
    }
}
