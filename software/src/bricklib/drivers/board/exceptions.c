/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \file
 * This file contains the default exception handlers.
 *
 * \note
 * The exception handler has __attribute__ ((weak)) aliases.
 * As they are __attribute__ ((weak)) aliases, any function with the same name will override
 * this definition.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "exceptions.h"
#include "config.h"
#include "bricklib/logging/logging.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Default interrupt handler for not used irq.
 */
void IrqHandlerNotUsed(void)
{
    while(1);
}

/**
 * \brief Default NMI interrupt handler.
 */
__attribute__ ((weak)) void NMI_Handler(void)
{
	logf("MNI\n\r");
    while(1);
}

#include "bricklib/drivers/cmsis/core_cm3.h"
/**
 * \brief Default HardFault interrupt handler.
 */
__attribute__ ((weak)) void HardFault_Handler(void)
{

	__asm("MOVS   R0, #4  \n"
	      "MOV    R1, LR  \n"
	      "TST    R0, R1  \n"
	      "BEQ    _MSP    \n"
	      "MRS    R0, PSP \n"
	      "B      HardFault_HandlerC      \n"
	      "_MSP:  \n"
	      "MRS    R0, MSP \n"
	      "B      HardFault_HandlerC      \n");
}

__attribute__ ((weak)) void HardFault_HandlerC(uint32_t * hardfault_args)
{
#if LOGGING_LEVEL != LOGGING_NONE
	uint32_t stacked_r0;
	uint32_t stacked_r1;
	uint32_t stacked_r2;
	uint32_t stacked_r3;
	uint32_t stacked_r12;
	uint32_t stacked_lr;
	uint32_t stacked_pc;
	uint32_t stacked_psr;

	stacked_r0 = ((uint32_t) hardfault_args[0]);
	stacked_r1 = ((uint32_t) hardfault_args[1]);
	stacked_r2 = ((uint32_t) hardfault_args[2]);
	stacked_r3 = ((uint32_t) hardfault_args[3]);

	stacked_r12 = ((uint32_t) hardfault_args[4]);
	stacked_lr = ((uint32_t) hardfault_args[5]);
	stacked_pc = ((uint32_t) hardfault_args[6]);
	stacked_psr = ((uint32_t) hardfault_args[7]);

	uint32_t *pc = (uint32_t*)stacked_pc;

	logf("\n\n[Hard fault handler]\n\r");
	logf("R0 = %lx\n\r", stacked_r0);
	logf("R1 = %lx\n\r", stacked_r1);
	logf("R2 = %lx\n\r", stacked_r2);
	logf("R3 = %lx\n\r", stacked_r3);
	logf("R12 = %lx\n\r", stacked_r12);
	logf("LR [R14] = %lx  subroutine call return address\n\r", stacked_lr);
	logf("PC [R15] = %lx (%lx)  program counter\n\r", stacked_pc, *pc);
	logf("PSR = %lx\n\r", stacked_psr);
	logf("BFAR = %lx\n\r", (*((volatile uint32_t *)(0xE000ED38))));
	logf("CFSR = %lx\n\r", (*((volatile uint32_t *)(0xE000ED28))));
	logf("HFSR = %lx\n\r", (*((volatile uint32_t *)(0xE000ED2C))));
	logf("DFSR = %lx\n\r", (*((volatile uint32_t *)(0xE000ED30))));
	logf("AFSR = %lx\n\r", (*((volatile uint32_t *)(0xE000ED3C))));
	logf("SCB_SHCSR = %lx\n\r", SCB->SHCSR);
#endif

    while(1);
}

/**
 * \brief Default MemManage interrupt handler.
 */
__attribute__ ((weak)) void MemManage_Handler(void)
{
	logf("MemManage\n\r");
    while(1);
}

/**
 * \brief Default BusFault interrupt handler.
 */
__attribute__ ((weak)) void BusFault_Handler(void)
{
	logf("BusFault\n\r");
    while(1);
}

/**
 * \brief Default UsageFault interrupt handler.
 */
__attribute__ ((weak)) void UsageFault_Handler(void)
{
	logf("UsageFault\n\r");
    while(1);
}

/**
 * \brief Default SVC interrupt handler.
 */
__attribute__ ((weak)) void SVC_Handler(void)
{
	logf("SVC\n\r");
    while(1);
}

/**
 * \brief Default DebugMon interrupt handler.
 */
__attribute__ ((weak)) void DebugMon_Handler(void)
{
	logf("DebugMon\n\r");
    while(1);
}

/**
 * \brief Default PendSV interrupt handler.
 */
__attribute__ ((weak)) void PendSV_Handler(void)
{
	logf("PendSV\n\r");
    while(1);
}

/**
 * \brief Default SysTick interrupt handler.
 */
__attribute__ ((weak)) void SysTick_Handler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for Supply Controller.
 */
__attribute__ ((weak)) void SUPC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for Reset Controller.
 */
__attribute__ ((weak)) void RSTC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for Real Time Clock.
 */
__attribute__ ((weak)) void RTC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for Real Time Timer.
 */
__attribute__ ((weak)) void RTT_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for Watchdog Timer.
 */
__attribute__ ((weak)) void WDT_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for PMC.
 */
__attribute__ ((weak)) void PMC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for EEFC.
 */
__attribute__ ((weak)) void EEFC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for UART0.
 */
__attribute__ ((weak)) void UART0_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for UART1.
 */
__attribute__ ((weak)) void UART1_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for SMC.
 */
__attribute__ ((weak)) void SMC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for PIOA Controller.
 */
__attribute__ ((weak)) void PIOA_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for PIOB Controller.
 */
__attribute__ ((weak)) void PIOB_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for PIOC Controller.
 */
__attribute__ ((weak)) void PIOC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for USART0.
 */
__attribute__ ((weak)) void USART0_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for USART1.
 */
__attribute__ ((weak)) void USART1_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for MCI.
 */
__attribute__ ((weak)) void MCI_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for TWI0.
 */
__attribute__ ((weak)) void TWI0_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for TWI1.
 */
__attribute__ ((weak)) void TWI1_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for SPI.
 */
__attribute__ ((weak)) void SPI_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for SSC.
 */
__attribute__ ((weak)) void SSC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for TC0.
 */
__attribute__ ((weak)) void TC0_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for TC1.
 */
__attribute__ ((weak)) void TC1_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default interrupt handler for TC2.
 */
__attribute__ ((weak)) void TC2_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for TC3.
 */
__attribute__ ((weak)) void TC3_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for TC4.
 */
__attribute__ ((weak)) void TC4_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for TC5.
 */
__attribute__ ((weak)) void TC5_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for ADC.
 */
__attribute__ ((weak)) void ADC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for DAC.
 */
__attribute__ ((weak)) void DAC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for PWM.
 */
__attribute__ ((weak)) void PWM_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for CRCCU.
 */
__attribute__ ((weak)) void CRCCU_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for ACC.
 */
__attribute__ ((weak)) void ACC_IrqHandler(void)
{
    while(1);
}

/**
 * \brief Default SUPC interrupt handler for USBD.
 */
__attribute__ ((weak)) void USBD_IrqHandler(void)
{
    while(1);
}
