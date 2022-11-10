/****************************************************
* [File Name] : dc_motor.h
* [Description] : Header file of DC Motor Driver
* [Author] : taha Khaled
****************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../Utilities/std_types.h"

/**********************************************************
*                Functions Prototypes                     *
**********************************************************/

/***************************************************
* [Function Name]: DCMotor_init
* [Description]: Initialize the direction of Motor
* [Argument]: No Arguments
* [Returns]: No Return Type
***************************************************/
void DCMotor_init(void);

/***************************************************
* [Function Name]: DCMotor_rotate
* [Description]: 1- set state of Dc-Motor, it must be CW , A-/CW or Stop based on input state
*                2- send Duty cycle to PWM Driver based on value of Argument speed
* [Argument]: uint8 state ---> specify state of DcMotor (CW / A-CW / Stop)
*             uint8 speed ---> specify Speed of Motor(Send Duty cycle to PWM Driver)
* [Returns]: No Return Type
***************************************************/
void DCMotor_rotate(uint8 state, uint8 speed);

#endif /* DC_MOTOR_H_ */






