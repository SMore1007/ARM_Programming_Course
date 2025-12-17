/********************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Class 3 - Task Led and Button using structure
 * @board          : STM32F446RE
 * ******************************************************************************/

#include "HeaderTask2.h"

int main(void){
    /* Enable GPIOA clock */
	RCC->AHB1ENR.AHB1ENR0 = 0x01;

	/* Enable GPIOC Clock */
	RCC->AHB1ENR.AHB1ENR2 = 0x01;

    /* Set PA5 as Output (01) */
    GPIOA->MODER.MODER5 = 0x01;

    /* Set PC13 as Input (00) */
    GPIOC->MODER.MODER13 = 0x00;

    while(1){
        if (GPIOC->IDR.IDR13 == 0){
            GPIOA->ODR.ODR5 = 1;   // LED ON
        }
        else{
            GPIOA->ODR.ODR5 = 0;   // LED OFF
        }
    }
}
