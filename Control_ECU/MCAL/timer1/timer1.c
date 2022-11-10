/************************************************
* [File Name] : timer1.c
* [Description]: Source File of Timer1 Driver
* [Author]: taha Khaled
************************************************/
#include "timer1.h"
#include "avr/io.h"
#include <avr/interrupt.h>
/********************************************************************************
 *                       Global variables                                       *
* ******************************************************************************/
/* Global variable to Point to address of callBack function in Application*/
static volatile void(*callBack_ptr)(void) = NULL;

/********************************************************************************
 *                       Interrupt Service Routines                             *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect){
	if(callBack_ptr != NULL){
		(*callBack_ptr)();
	}
}
/********************************************************************************/

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
#ifndef TIMER1_Compare_Mode
/********************************************************************************
* [Function Name]: TIMER1_init_Compare
* [Description]: 1- Initialize Value that Timer1 will start from it
*                2- Set Mode of timer1 that will be operate on it
*                3- Specify Pre-scaler which decide the frequency that Timer1 Will operate on it
* [Arguments]: Pointer to struct of type Timer1_ConfigType to set configuration that
*              Timer1 will operate on it
* [Returns]: No Return type
********************************************************************************/
void TIMER1_init_Normal(Timer1_ConfigType* Config_ptr)
{
	/* Initialize Timer1 With value that will start count according to this value*/
	TCNT1 = Config_ptr->Initial_value;

	/* Enable Timer1 Interrupt*/
	TIMSK |= (1 << OCIE1A);

	/****************************************************************************
	 * FOC1A : It will be set when Timer1 Operate in non PWM Mode
	 * Set First 2-bits From Mode Member to Specify which Mode Timer1 Will Operate
	****************************************************************************/
	TCCR1A = (1 << FOC1A) | ((TCCR1A & 0xFC) | (Config_ptr->Mode & 0x03));

	/****************************************************************************
	 * Set Pre-scaler value in the first 3-bits in TCCR1B Register that will specify which frequency Timer1 will Operate
	 * Set Last 2-bits From Mode Member to Specify Which Mode Timer1 Will Operate
	****************************************************************************/
	TCCR1B = ((TCCR1B & 0xF8) | (Config_ptr->Prescaler & 0x07)) | ((TCCR1B & 0xE7) | ((Config_ptr->Mode & 0x0C)<<1));
}
#else
/********************************************************************************
* [Function Name]: TIMER1_init_Compare
* [Description]: 1- Initialize Value that Timer1 will start from it
*                2- Set Compare Value that when Timer1 reach to it then, back to 0
*                3- Set Mode of timer1 that will be operate on it
*                4- Specify Pre-scaler which decide the frequency that Timer1 Will operate on it
* [Arguments]: Pointer to struct of type Timer1_ConfigType to set configuration that
*              Timer1 will operate on it
* [Returns]: No Return type
********************************************************************************/
void TIMER1_init_Compare(Timer1_ConfigType* Config_ptr)
{
	/* Initialize Timer1 With value that will start count according to this value*/
	TCNT1 = Config_ptr->Initial_value;

	/* Set Compare value that Timer will reach to it then, it backs count from 0*/
	OCR1A = Config_ptr->Compare_value;

	/* Enable Timer1 Interrupt*/
	TIMSK |= (1 << OCIE1A);

	/****************************************************************************
	 * FOC1A : It will be set when Timer1 Operate in non PWM Mode
	 * Set First 2-bits From Mode Member to Specify which Mode Timer1 Will Operate
	****************************************************************************/
	TCCR1A = (1 << FOC1A) | ((TCCR1A & 0xFC) | (Config_ptr->Mode & 0x03));

	/****************************************************************************
	 * Set Pre-scaler value in the first 3-bits in TCCR1B Register that will specify which frequency Timer1 will Operate
	 * Set Last 2-bits From Mode Member to Specify Which Mode Timer1 Will Operate
	****************************************************************************/
	TCCR1B = ((TCCR1B & 0xF8) | (Config_ptr->Prescaler & 0x07)) | ((TCCR1B & 0xE7) | ((Config_ptr->Mode & 0x0C)<<1));
}
#endif
/********************************************************************************
* [Function Name]: TIMER1_deInit
* [Description]: Function disable and stop Timer1 driver
* [Arguments]: No arguments
* [Returns]: No Returns
********************************************************************************/
void TIMER1_deInit(void)
{
	/* Clear Timer Register */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	/* Disable Interrupt */
	TIMSK &= ~(1 << OCIE1A);
}
/********************************************************************************
* [Function Name]: TIMER1_setCallback
* [Description]: Function set Pointer argument to Point to Function that will be executed
*                at ISR
* [Arguments]: Pointer that will point to passed Function that will be executed when
*              The interrupt(detection) occurs
* [Returns]: No Return type
********************************************************************************/
void TIMER1_setCallback(void(*a_ptr)(void))
{
	/* Make global variable points to same function to be called in ISR when an detection occur*/
	callBack_ptr = a_ptr;
}









