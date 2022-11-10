/****************************************************
* [File Name] : dc_motor.c
* [Description] : Source file of DC Motor Driver
* [Author] : taha Khaled
****************************************************/
#include "dc_motor.h"
#include "../../MCAL/gpio/gpio.h"
#include "avr/io.h"
#include "../../MCAL/PWM/pwm.h"
/***********************************************************
*                Functions Definitions                     *
***********************************************************/

/***************************************************
* [Function Name]: DCMotor_init
* [Description]: Initialize the direction of Motor
* [Argument]: No Arguments
* [Returns]: No Return Type
***************************************************/
void DCMotor_init(void){
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT); /* set PB0 as Output PIN */
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT); /* set PB1 as Output PIN*/

	/* initialize Direction of Motor to be Stopped */
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_Low);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_Low);
}

/***************************************************
* [Function Name]: DCMotor_rotate
* [Description]: 1- set state of Dc-Motor, it must be CW , A-/CW or Stop based on input state
*                2- send Duty cycle to PWM Driver based on value of Argument speed
* [Argument]: uint8 state ---> specify state of DcMotor (CW / A-CW / Stop)
*             uint8 speed ---> specify Speed of Motor(Send Duty cycle to PWM Driver)
* [Returns]: No Return Type
***************************************************/
void DCMotor_rotate(uint8 state, uint8 speed){
	PORTB = (PORTB & 0xFC) | (state & 0x03); // Set Direction of DCMotor (CW / A-CW / Stop) based on state argument //
	PWM_Timer0_Start(speed); // Set Duty cycle to PWM Driver Based on Speed Argument //
}




