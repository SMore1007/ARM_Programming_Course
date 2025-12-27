#include <stdint.h>

#ifndef HEADERTASK1_H_
#define HEADERTASK1_H_

#define __IO volatile

/* MODER Register (2 bits per pin) */
typedef struct
{
    uint32_t MODER0  : 2;
    uint32_t MODER1  : 2;
    uint32_t MODER2  : 2;
    uint32_t MODER3  : 2;
    uint32_t MODER4  : 2;
    uint32_t MODER5  : 2;
    uint32_t MODER6  : 2;
    uint32_t MODER7  : 2;
    uint32_t MODER8  : 2;
    uint32_t MODER9  : 2;
    uint32_t MODER10 : 2;
    uint32_t MODER11 : 2;
    uint32_t MODER12 : 2;
    uint32_t MODER13 : 2;
    uint32_t MODER14 : 2;
    uint32_t MODER15 : 2;
} GPIOx_MODER;

/* Input Data Register (1 bit per pin) */
typedef struct
{
    uint32_t IDR0  : 1;
    uint32_t IDR1  : 1;
    uint32_t IDR2  : 1;
    uint32_t IDR3  : 1;
    uint32_t IDR4  : 1;
    uint32_t IDR5  : 1;
    uint32_t IDR6  : 1;
    uint32_t IDR7  : 1;
    uint32_t IDR8  : 1;
    uint32_t IDR9  : 1;
    uint32_t IDR10 : 1;
    uint32_t IDR11 : 1;
    uint32_t IDR12 : 1;
    uint32_t IDR13 : 1;
    uint32_t IDR14 : 1;
    uint32_t IDR15 : 1;
    uint32_t RESERVED : 16;
} GPIOx_IDR;

/* Output Data Register (1 bit per pin) */
typedef struct
{
    uint32_t ODR0  : 1;
    uint32_t ODR1  : 1;
    uint32_t ODR2  : 1;
    uint32_t ODR3  : 1;
    uint32_t ODR4  : 1;
    uint32_t ODR5  : 1;
    uint32_t ODR6  : 1;
    uint32_t ODR7  : 1;
    uint32_t ODR8  : 1;
    uint32_t ODR9  : 1;
    uint32_t ODR10 : 1;
    uint32_t ODR11 : 1;
    uint32_t ODR12 : 1;
    uint32_t ODR13 : 1;
    uint32_t ODR14 : 1;
    uint32_t ODR15 : 1;
    uint32_t RESERVED : 16;
} GPIOx_ODR;

/* GPIO Registers */
typedef struct
{
    __IO GPIOx_MODER MODER;   /*!< GPIO port mode register,               Address offset: 0x00 */
    __IO uint32_t    OTYPER;  /*!< GPIO port output type register,        Address offset: 0x04 */
    __IO uint32_t    OSPEEDR; /*!< GPIO port output speed register,       Address offset: 0x08 */
    __IO uint32_t    PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C */
    __IO GPIOx_IDR   IDR;     /*!< GPIO port input data register,         Address offset: 0x10 */
    __IO GPIOx_ODR   ODR;     /*!< GPIO port output data register,        Address offset: 0x14 */
    __IO uint32_t    BSRR;    /*!< GPIO port bit set/reset register,      Address offset: 0x18 */
    __IO uint32_t    LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C */
    __IO uint32_t    AFR[2];  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

/* Base addresses */
#define GPIOA_BASE (0x40020000UL)
#define GPIOC_BASE (0x40020800UL)

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)

#endif /* HEADERTASK1_H_ */
