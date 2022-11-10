/************************************************
* [File Name] : uart.h
* [Description]: Source File of UART Driver
* [Author]: taha Khaled
************************************************/
#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "../../Utilities/common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
*                      Functions Definitions                                   *
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
void UART_init(const UART_ConfigType* Config_ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/

	/* Set Bits number 3 in The Data size number in The bit UCSZ2 in Register UCSRB */
	UCSRB = (UCSRB & 0xFB) | (Config_ptr->Data_size & 0x04);

	/* To Write in Register UCSRC, Firstly we need to make URSEL with LOGIC HIGH */
	/* But the first 2 bits in Data size in the bits UCSZ1 and UCSZ0 to Specify the size of Data */
	UCSRC = (1 << URSEL) | (Config_ptr->Data_size << 1);

	/* Specify Parity bit Mode(Even/ Odd / Disabled) in Data frame */
	UCSRC = (UCSRC & 0xCF) | (Config_ptr->Parity_bit << 4);

	/* Specify number of stop bits in the Data frame */
	UCSRC = (UCSRC & 0xF7) | (Config_ptr->Stop_bit << 3);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (Config_ptr->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*******************************************************************************
* [Function Name]: UART_sendByte
* [Description]: This Function Responsible for send byte to another UART Device
* [Arguments]: uint8 ---> Data that will be send
* [Returns]: No Return Types
*******************************************************************************/
void UART_sendByte(const uint8 data)
{
	/* Here This check if Transmitter Register is Empty or Not */
	/* If empty --> it can receive another byte and will exit from while loop and send data to UDR Register*/
	/* If not empty --> it will wait until Transmit Register to be empty to be able to send another byte without
	   Data overrun */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*Send The Required data to UART Register */
	UDR = data;
}

/*******************************************************************************
* [Function Name]: UART_receiveByte
* [Description]: This Function Responsible for receive byte to another UART Device
* [Arguments]: No Arguments
* [Returns]: No Return Types
*******************************************************************************/
uint8 UART_recieveByte(void)
{
	/* this while loop will stop when The reading of byte is completed ---> data already read */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	//---> This will clear RX Flag after reading the Register
    return UDR;
}

/*******************************************************************************
* [Function Name]: UART_sendString
* [Description]: This Function Responsible for send string to another UART Device
* [Arguments]: Pointer to First character in the string
* [Returns]: No Return Types
*******************************************************************************/
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Loop until reach to the end of the string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*******************************************************************************
* [Function Name]: UART_receiveString
* [Description]: This Function Responsible for receive string to another UART Device
* [Arguments]: Pointer to First character in the string
* [Returns]: No Return Types
*******************************************************************************/
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* First Receive the First byte to check this byte is the end of string or not */
	Str[i] = UART_recieveByte();

	/* Loop until string ends with the Special character that first user specified it */
	/* this character '#' is optional you can use any character instead of it*/
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* end the string received with null Terminator */
	Str[i] = '\0';
}











