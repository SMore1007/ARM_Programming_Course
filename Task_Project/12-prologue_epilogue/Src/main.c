/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sagar More
 * @brief          : Prologue and Epilogue
 ******************************************************************************
 */

#include <stdint.h>

/*
 * Dummy global variable so compiler does not optimize everything
 */
volatile uint32_t result;

/*
 * Function to demonstrate PROLOGUE and EPILOGUE
 */
void PrologueEpilogue_Demo(uint32_t a, uint32_t b)
{
    /*
     * ---------------- PROLOGUE ----------------
     * PUSH {r4, lr}
     *  - Save callee-saved register r4
     *  - Save return address (Link Register)
     */
    __asm volatile (
        "PUSH {r4, lr}    \n"
    );

    /*
     * Function body
     * Using r4 as a local variable
     */
    __asm volatile (
        "MOV r4, %0       \n"   // r4 = a
        "ADD r4, r4, %1   \n"   // r4 = a + b
        "STR r4, %2      \n"   // store result to memory
        :
        : "r"(a), "r"(b), "m"(result)
        : "r4"
    );

    /*
     * ---------------- EPILOGUE ----------------
     * POP {r4, pc}
     *  - Restore r4
     *  - Restore PC → return from function
     */
    __asm volatile (
        "POP {r4, pc}     \n"
    );
}

/*
 * Entry point
 */
int main(void)
{
    /*
     * Call function
     * Parameters passed via registers (AAPCS)
     */
    PrologueEpilogue_Demo(10, 20);

    while (1)
    {
        /* Infinite loop */
    }
}
