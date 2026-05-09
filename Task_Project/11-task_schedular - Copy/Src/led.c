/*
 * led.c
 *
 *  Created on: Jan 30, 2026
 *      Author: Lenovo
 */

#include "led.h"

void led_init_all(void)
{
    /* Enable clock for GPIOD */
    RCC_AHB1_ENR |= (1 << 3);

    /* Set PD12–PD15 as output */
    GPIO_MODE_REG |= (1 << (2 * LED_GREEN));
    GPIO_MODE_REG |= (1 << (2 * LED_ORANGE));
    GPIO_MODE_REG |= (1 << (2 * LED_RED));
    GPIO_MODE_REG |= (1 << (2 * LED_BLUE));

    /* Turn off all LEDs */
    led_off(LED_GREEN);
    led_off(LED_ORANGE);
    led_off(LED_RED);
    led_off(LED_BLUE);
}

void led_on(uint8_t led_no)
{
    GPIO_DATA_REG |= (1 << led_no);
}

void led_off(uint8_t led_no)
{
    GPIO_DATA_REG &= ~(1 << led_no);
}
