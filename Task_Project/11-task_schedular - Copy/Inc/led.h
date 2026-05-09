/*
 * led.h
 *
 *  Created on: Jan 30, 2026
 *      Author: Lenovo
 */



#ifndef LED_H_
#define LED_H_

#include <stdint.h>

/* RCC and GPIOD Registers (STM32F4) */

#define RCC_AHB1_ENR  (*(volatile uint32_t*)0x40023830)
#define GPIO_MODE_REG (*(volatile uint32_t*)0x40020C00)
#define GPIO_DATA_REG (*(volatile uint32_t*)0x40020C14)

/* LED Pins (GPIOD) */

#define LED_GREEN   12
#define LED_ORANGE  13
#define LED_RED     14
#define LED_BLUE    15

void led_init_all(void);
void led_on(uint8_t led_no);
void led_off(uint8_t led_no);

#endif

