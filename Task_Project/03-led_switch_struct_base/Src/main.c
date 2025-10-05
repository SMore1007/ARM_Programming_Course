/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Class 3 - Task Led and Button using structure
 * @board          : STM32F446RE
 *
 * ******************************************************************************
*/

#include <stdint.h>
#include <stdbool.h>
#include "struct_header.h"

void ledHigh(void);
void ledLow(void);

int main(void)
{
    /* -------------------------------
     *  Enable Clock for GPIOA & GPIOC
     * -------------------------------
     * RCC_AHB1ENR:
     * Bit 0 -> GPIOAEN
     * Bit 2 -> GPIOCEN
     * 0x5 = (1 << 0) | (1 << 2)
     */
	RCC->AHB1ENR |= (0x5U << 0);

    /* -------------------------------
     * Configure GPIOA PIN5 as Output
     * -------------------------------
     * MODER[11:10] = 01 (Output Mode)
     */
    GPIOA->MODER |=  (1U << 10);  // Set MODER10 = 1
    GPIOA->MODER &= ~(1U << 11);  // Set MODER11 = 0

    /* -------------------------------
     * Configure GPIOC PIN13 as Input
     * -------------------------------
     * MODER[27:26] = 00 (Input Mode)
     */
    GPIOC->MODER &= ~(1U << 26);  // Clear MODER26
    GPIOC->MODER &= ~(1U << 27);  // Clear MODER27

    // Flag to track LED state
    volatile bool ledFlag = false;


    while (1)
    {
    	 if ((GPIOC->IDR & (1U << 13)) == 0)
    	        {
    	            ledFlag = true;   // Button pressed
    	        }
    	        else
    	        {
    	            ledFlag = false;  // Button released
    	        }

    	        /* -------------------------------
    	         * Control LED based on Flag
    	         * -------------------------------*/
    	        if (ledFlag)
    	        {
    	            ledHigh();  // Turn LED on
    	        }
    	        else
    	        {
    	            ledLow();   // Turn LED off
    	        }
    }
}



/* Turn LED ON (PA5 = 1) */
void ledHigh(void)
{
    GPIOA->ODR |= (1U << 5);
}

/* Turn LED OFF (PA5 = 0) */
void ledLow(void)
{
    GPIOA->ODR &= ~(1U << 5);
}

