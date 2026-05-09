# Bare-Metal STM32 Task Scheduler

This project implements a minimal, preemptive, bare-metal Real-Time Operating System (RTOS) task scheduler for an ARM Cortex-M4 microcontroller (specifically the STM32F446RE). It utilizes the intrinsic features of the ARM architecture such as **SysTick** and **PendSV** to perform seamless context switching between multiple tasks.

## 📂 Project Structure and Source Files

Here is a detailed breakdown of each file and its role in the scheduler:

### 1. `Src/main.c` (Core Scheduler Implementation)
This is the heart of the project. It contains the RTOS core, task functions, and context-switching assembly logic.
- **Task TCBs (Task Control Blocks):** Manages the `PSP` (Process Stack Pointer) values, blocking tick counts, and execution states for each task.
- **Naked Functions (`PendSV_Handler`, `switch_sp_to_psp`):** Written in inline ARM assembly to directly manipulate CPU registers. These functions carefully preserve the Link Register (`LR`) onto the Main Stack (`MSP`) while safely handling `PSP` context swapping.
- **`SysTick_Handler`:** Triggers every 1ms to increment the global tick count, unblock waiting tasks, and trigger the `schedule()` function to queue a context switch. 
- **User Tasks (`task1_handler` to `task4_handler`):** Simple applications that toggle LEDs at different rates and yield control back to the scheduler via `task_delay()`.
- **Idle Task:** Runs a Wait-For-Interrupt (`WFI`) loop to save power when no other tasks are ready to run.

### 2. `Inc/main.h` (Scheduler Definitions)
Contains all the macro definitions and memory map settings required by the RTOS.
- **Stack Memory Map:** Defines top-down allocations for the `MSP` (Main Stack Pointer for the scheduler/exceptions) and the individual `PSP`s (Process Stack Pointers) for the Idle task and tasks 1 through 4.
- **System Clocks:** Base configuration for the `SYSTICK_TIM_CLK` and timing calculations.
- **Hardware Register Macros:** Memory-mapped register definitions for `ICSR` (Interrupt Control and State Register), `SHCSR`, and `NVIC_SHPR3` to safely trigger and prioritize the PendSV exception.

### 3. `Src/led.c` & `Inc/led.h` (Hardware Abstraction Layer)
- Simple drivers to initialize the GPIO ports and provide `led_on()` and `led_off()` functions. 
- These are used inside the individual user tasks to provide visual evidence that the context-switcher is correctly preempting and resuming parallel routines.

### 4. `Src/syscalls.c` & `Src/sysmem.c`
- **`syscalls.c`:** Standard newlib low-level implementation. Used if standard C library functions like `printf` are invoked via UART/ITM.
- **`sysmem.c`:** Implements `_sbrk` for dynamic memory allocation. (Note: The core task scheduler statically allocates TCBs, so `malloc` is generally unused).

### 5. `STM32F446RETX_FLASH.ld` & `STM32F446RETX_RAM.ld`
- **Linker Scripts:** Tell the GCC linker exactly where the Flash (ROM) and SRAM exist in the STM32's memory space, configuring where `.text`, `.data`, and `.bss` sections are loaded during compilation.

### 6. `Startup` Code (Assembly)
- Automatically generated startup code providing Reset handler logic.
- Contains the crucial **Vector Table**, ensuring that hardware exceptions for `SysTick_Handler` and `PendSV_Handler` are mapped to the correct C functions in `main.c`.

## 🛠️ How it Works

1. **Initialization:** The `main()` routine manually builds a "dummy" hardware exception stack frame inside the SRAM allocated for each task's Process Stack.
2. **Context Switching:** The `switch_sp_to_psp()` function seamlessly alters the CPU's `CONTROL` register so that Thread Mode operates on the `PSP` instead of the `MSP`.
3. **Execution:** `main()` natively jumps to the first task.
4. **Preemption:** The `SysTick` timer interrupts execution every millisecond. The handler unblocks any delayed tasks and manually pends the `PendSV` exception by writing to the `ICSR` register. 
5. **Context Restoring:** Because `PendSV` is configured as the lowest priority interrupt, it runs safely after all other IRQs. It pushes the current task's registers into its private `PSP`, retrieves the `PSP` for the next ready task, and returns from the exception, allowing the Cortex-M processor to automatically pop the next task's state.
