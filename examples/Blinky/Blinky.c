/******************************************************************************
Copyright (c) 2026 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.

*****************************************************************************/

/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s):
 *----------------------------------------------------------------------------
 * All files for ADuCM355 provided by ADI, including this file, are
 * provided  as is without warranty of any kind, either expressed or implied.
 * The user assumes any and all risk from the use of this code.
 * It is the responsibility of the person integrating this code into an application
 * to ensure that the resulting application performs as required and is safe.
 *----------------------------------------------------------------------------*/

#include "LED.h"
#include "UrtLib.h"
#include "DioLib.h"
#include "ClkLib.h"

void UartInit(void);
void ClockInit(void);
int main()
{

	int count = 0;
    ClockInit();                                // Init system clocks
    UartInit();                                 // Init UART for 230400-8-N-1
	printf("Hello World!\n");
	LED_Init();

	while(1)
	{
		LED_On();			/* Turn on LED          */
		delay(100000);		/* Delay                */
		LED_Off();			/* Turn off LED         */
		delay(100000);		/* Delay                */

		printf ("count = %d\n", count++);
	}

}

void UartInit(void)
{
   DioCfgPin(pADI_GPIO0,PIN10|PIN11,1);        // Setup P0.10, P0.11 as UART pin
   UrtCfg(pADI_UART0,B230400,
          (BITM_UART_COMLCR_WLS|3),0);         // Configure UART for 230400 baud rate
   UrtFifoCfg(pADI_UART0, RX_FIFO_1BYTE,       // Configure the UART FIFOs for 8 bytes deep
              BITM_UART_COMFCR_FIFOEN);
   UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR// Clear the Rx/TX FIFOs
              |BITM_UART_COMFCR_TFCLR);

   UrtIntCfg(pADI_UART0,BITM_UART_COMIEN_ERBFI|BITM_UART_COMIEN_ELSI);
}


// Clock digital die with Internal 26MHz oscillator
void ClockInit(void)
{
   DigClkSel(DIGCLK_SOURCE_HFOSC);
   ClkDivCfg(1,1);
}

