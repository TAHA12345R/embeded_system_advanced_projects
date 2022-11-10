/************************************************
* [File Name] : uart.h
* [Description]: Source File of UART Driver
* [Author]: tahas Khaled
************************************************/
#ifndef UART_H_
#define UART_H_

#include "../../Utilities/std_types.h"

/*******************************************************************************
*                          Type Declaration                                    *
*******************************************************************************/
/* This Enumeration Specify The Situation of Parity bit in The Frame*/
typedef enum{
	Disabled , Reserved , Enabled_Even , Enabled_Odd
}UART_Parity_Mode;
/* This Enumeration Specify number of stop bits */
typedef enum{
	Stop_1Bit , Stop_2Bit
}UART_Stop_bit;
/* This Enumeration Specify The size of data in the frame */
typedef enum{
	Data_5_bit , Data_6_bit , Data_7_bit , Data_8_bit
}UART_Character_size;

typedef struct{
	UART_Character_size Data_size; // This Member specify the size of Data in the frame //
	UART_Stop_bit Stop_bit;        // This Member specify number of stop bits //
	UART_Parity_Mode Parity_bit;   // This Member specify Parity bit Mode //
	uint32 baud_rate;              // This Member Specify Baud rate of UART //
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
* [Function Name]: UART_init
* [Description]: This Function used to set configuration to UART Driver
*                1- Set Data sized that will be send and receive in the Frame
*                2- Set Baud rate of UART Driver
*                3- Set Parity bit Mode (Even / Odd / Disabled)
*                4- Specify Number of Stop bits (1-bit / 2-bits)
* [Arguments]: Pointer to structure of type UART_ConfigType To Specify Configuration
*              of UART Driver
* [Returns]: No Return Types
*******************************************************************************/
void UART_init(const UART_ConfigType* Config_ptr);

/*******************************************************************************
* [Function Name]: UART_sendByte
* [Description]: This Function Responsible for send byte to another UART Device
* [Arguments]: uint8 ---> Data that will be send
* [Returns]: No Return Types
*******************************************************************************/
void UART_sendByte(const uint8 data);

/*******************************************************************************
* [Function Name]: UART_receiveByte
* [Description]: This Function Responsible for receive byte to another UART Device
* [Arguments]: No Arguments
* [Returns]: No Return Types
*******************************************************************************/
uint8 UART_recieveByte(void);

/*******************************************************************************
* [Function Name]: UART_sendString
* [Description]: This Function Responsible for send string to another UART Device
* [Arguments]: Pointer to First character in the string
* [Returns]: No Return Types
*******************************************************************************/
void UART_sendString(const uint8 *Str);

/*******************************************************************************
* [Function Name]: UART_receiveString
* [Description]: This Function Responsible for receive string to another UART Device
* [Arguments]: Pointer to First character in the string
* [Returns]: No Return Types
*******************************************************************************/
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */

