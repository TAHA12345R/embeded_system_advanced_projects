/****************************************************
* [File Name:] gpio.h
* [Description]: Header File for AVR GPIO
* [Author]: taha Khaled
****************************************************/
#ifndef GPIO_H_
#define GPIO_H_

#include "../../Utilities/std_types.h"

/****************************************************
*                    Definitions                    *
****************************************************/
#define NUM_OF_PORTS 4
#define NUM_OF_PINS_PER_PORT 8

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/****************************************************
*               Type Declaration                    *
****************************************************/
typedef enum{
	PIN_INPUT , PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum {
	PORT_INPUT , PORT_OUTPUT = 0xFF
}GPIO_PortDirectionType;

/******************************************************
*               Functions Prototypes                  *
******************************************************/

/*
* Description:
* set Direction of any Pin in Passed Port_num (input or output)
* if Port_num or Pin_num are invalid, function will not handle the request
*/
void GPIO_setupPinDirection(uint8 Port_num , uint8 Pin_num , GPIO_PinDirectionType direction);

/*
* Description:
* write Logic High or Low in a Specific Pin in PORT Passed to Function
* if Port_num or Pin_num are invalid, function will not handle the request
* if This Pin are defined as Input Pin, It will be activate or deactivate of Internal Pull-up Resistor
*/
void GPIO_writePin(uint8 Port_num , uint8 Pin_num , uint8 value);

/*
* Description:
* Read value of Certain Pin in Port passed to Function (Logic High or LOW)
* if Port_num or Pin_num are invalid, function will return LOW
*/
uint8 GPIO_ReadPin(uint8 Port_num , uint8 Pin_num);

/*
* Description:
* set Direction of any PORT Passed to Function (input or output)
* if direction value is PORT_INPUT --> All Pins will be Input Pins
* if direction value is PORT_OUTPUT --> All Pins will be output Pins
* if Port_num is invalid, function will not handle the request
*/
void GPIO_setupPortDirection(uint8 Port_num , GPIO_PortDirectionType direction);

/*
* Description:
* write Logic High or Low in a Specific PORT Passed to Function
* if Port_num is invalid, function will not handle the request
* if value of PORT is LOGIC HIGH or LOW and Pin is output ---> value will be written
* if value of PORT is LOGIC HIGH or LOW and PIN is input ---> activate or deactivate Pull-up Resistor
*/
void GPIO_writePort(uint8 Port_num , uint8 value);

/*
* Description:
* Read value of Certain Port passed to Function (Logic High or LOW)
* if Port_num is invalid, function will return LOW
*/
uint8 GPIO_readPort(uint8 Port_num);

#endif

