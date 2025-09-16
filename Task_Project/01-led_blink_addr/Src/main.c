/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Class 1 Task Program
 *                   Blink Led on POARTB PIN3 AND PIN8 STM32F446RE
 * 					 Where TO Connect LED?
 * 					 PORTB - PIN3 and PIN8, POARTB uses the AHB1 bus
 ******************************************************************************
 */

/*
RCC_BASE        :- 0x40023800

RCC_AHB1ENR_OFFSET    :- 0x30
RCC_AHB1ENR     :- 0x40023830
-------------------------------------------

GPIOB_BASE     :- 0x40020400

GPIOB_MODER_OFFSET   :- 0x00
GPIOB_MODER    :- 0x40020400

GPIOB_ODR_OFFSET    :-  0x14
GPIOB_ODR     :-  0x40020414
-------------------------------------------
 */

#include <stdint.h>

#define RCC_AHB1ENR (*(uint32_t *)0x40023830)
#define GPIOB_MODER (*(uint32_t *)0x40020400)
#define GPIOB_ODR   (*(uint32_t *)0x40020414)

void delay(void) {
    for (int i = 0; i < 1000000; i++) {
    }
}


int main(void){
    // Enable clock for GPIOB
    RCC_AHB1ENR |= (1 << 1);

    // Set PB3 as output
    GPIOB_MODER |=  (1 << 6);
    GPIOB_MODER &= ~(1 << 7);

    // Set PB8 as output
    GPIOB_MODER |=  (1 << 16);
    GPIOB_MODER &= ~(1 << 17);

    while (1)
    {
        GPIOB_ODR |=  (1 << 3);   // PB3 ON
        GPIOB_ODR &= ~(1 << 8);   // PB8 OFF
        delay();

        GPIOB_ODR |=  (1 << 3);   // PB3 ON
        GPIOB_ODR |=  (1 << 8);   // PB8 ON
        delay();

        GPIOB_ODR &= ~(1 << 3);   // PB3 OFF
        GPIOB_ODR |=  (1 << 8);   // PB8 ON
        delay();

        GPIOB_ODR &= ~(1 << 3);   // PB3 OFF
        GPIOB_ODR &= ~(1 << 8);   // PB8 OFF
        delay();
    }
}
