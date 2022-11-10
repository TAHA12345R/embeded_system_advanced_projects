/****************************************************
* [File Name]: gpio.c
* [Description]: Source File for AVR GPIO
* [Author]: taha Khaled
****************************************************/
#include "gpio.h"
#include "avr/io.h"
#include "../../Utilities/common_macros.h"

/************************************************************
*                   Function Definitions                    *
************************************************************/

/*
* Description:
* set Direction of any Pin in Passed Port_num (input or output)
* if Port_num or Pin_num are invalid, function will not handle the request
*/
void GPIO_setupPinDirection(uint8 Port_num , uint8 Pin_num , GPIO_PinDirectionType direction){
	if(Port_num >= NUM_OF_PORTS || Pin_num >= NUM_OF_PINS_PER_PORT)
	{
		/* Do Nothing */
	}
	else
	{
		switch(Port_num){
		case PORTA_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRA,Pin_num);
			}
			else
			{
				SET_BIT(DDRA,Pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRB,Pin_num);
			}
			else
			{
				SET_BIT(DDRB,Pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRC,Pin_num);
			}
			else
			{
				SET_BIT(DDRC,Pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRD,Pin_num);
			}
			else
			{
				SET_BIT(DDRD,Pin_num);
			}
			break;
		}
	}
}

/*
* Description:
* write Logic High or Low in a Specific Pin in PORT Passed to Function
* if Port_num or Pin_num are invalid, function will not handle the request
* if This Pin are defined as Input Pin, It will be activate or deactivate of Internal Pull-up Resistor
*/
void GPIO_writePin(uint8 Port_num , uint8 Pin_num , uint8 value){
	if(Port_num >= NUM_OF_PORTS || Pin_num >= NUM_OF_PINS_PER_PORT)
	{
		/* Do Nothing */
	}
	else
	{
		switch(Port_num){
		case PORTA_ID:
			if(value == LOGIC_High)
			{
				SET_BIT(PORTA,Pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,Pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_High){
				SET_BIT(PORTB,Pin_num);
			}
			else{
				CLEAR_BIT(PORTB,Pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_High)
			{
				SET_BIT(PORTC,Pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,Pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_High)
			{
				SET_BIT(PORTD,Pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,Pin_num);
			}
			break;
		}
	}
}

/*
* Description:
* Read value of Certain Pin in Port passed to Function (Logic High or LOW)
* if Port_num or Pin_num are invalid, function will return LOW
*/
uint8 GPIO_ReadPin(uint8 Port_num , uint8 Pin_num){
	if(Port_num >= NUM_OF_PORTS || Pin_num >= NUM_OF_PINS_PER_PORT){
		/* Return Logic LOW */
		return LOGIC_Low;
	}
	else
	{
		switch(Port_num){
		case PORTA_ID:
			if(BIT_IS_SET(PINA,Pin_num)){
				return LOGIC_High;
			}
			else{
				return LOGIC_Low;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,Pin_num)){
				return LOGIC_High;
			}
			else{
				return LOGIC_Low;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,Pin_num)){
				return LOGIC_High;
			}
			else{
				return LOGIC_Low;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,Pin_num)){
				return LOGIC_High;
			}
			else{
				return LOGIC_Low;
			}
			break;
		}
	}
}

/*
* Description:
* set Direction of any PORT Passed to Function (input or output)
* if direction value is PORT_INPUT --> All Pins will be Input Pins
* if direction value is PORT_OUTPUT --> All Pins will be output Pins
* if Port_num is invalid, function will not handle the request
*/
void GPIO_setupPortDirection(uint8 Port_num , GPIO_PortDirectionType direction){
	if(Port_num >= NUM_OF_PORTS){
		/* Do Nothing */
	}
	else{
		switch(Port_num){
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*
* Description:
* write Logic High or Low in a Specific PORT Passed to Function
* if Port_num is invalid, function will not handle the request
* if value of PORT is LOGIC HIGH or LOW and Pin is output ---> value will be written
* if value of PORT is LOGIC HIGH or LOW and PIN is input ---> activate or deactivate Pull-up Resistor
*/
void GPIO_writePort(uint8 Port_num , uint8 value){
	if(Port_num >= NUM_OF_PORTS){
		/* Do Nothing */
	}
	else{
		switch(Port_num){
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
* Description:
* Read value of Certain Port passed to Function (Logic High or LOW)
* if Port_num is invalid, function will return LOW
*/
uint8 GPIO_readPort(uint8 Port_num){
	uint8 value = LOGIC_Low ;
	if(Port_num >= NUM_OF_PORTS){
		/* Return Logic LOW */
	}
	else{
		switch(Port_num){
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}
	return value;
}

