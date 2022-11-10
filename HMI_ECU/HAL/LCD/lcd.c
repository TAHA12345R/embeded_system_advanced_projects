/************************************************
* [File Name] : lcd.c
* [Description]: Source File of LCD Driver
* [Author]: taha Khaled
************************************************/
#include "lcd.h"
#include "../../MCAL/gpio/gpio.h"
#include <util/delay.h>
#include "../../Utilities/common_macros.h"

/**********************************************************************
*                        Functions Definitions                        *
**********************************************************************/

/*****************************************************************************
* [Function_Name] : LCD_init
* [Description] : Initialization of LCD:
*                 1- Setup LCD Pins Direction using GPIO_Driver
*                 2- Setup LCD Data Mode 4-bits or 8-bits
* [Argument] : No arguments
* [Returns] : No return data type
*****************************************************************************/
void LCD_init(void){
	/* configure the direction of RS/Enable pins as output Pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID , LCD_RS_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID , LCD_E_PIN_ID , PIN_OUTPUT);

	_delay_ms(20); /* LCD Power ON delay always > 15ms */
#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);
	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INT2);
	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/* configure the direction of Port of Data as output Port*/
	GPIO_setupPortDirection(LCD_DATA_PORT_ID , PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* 2-lines LCD + 8-bit data mode */
#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor OFF */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear screen at the beginning */
}

/************************************************************************************
* [Function_Name] : LCD_sendCommand
* [Description] : Send The Required Command to screen
* [Argument] : uint8 Command --> 8-bits Command
* [Returns] : No return data type
************************************************************************************/
void LCD_sendCommand(uint8 Command){
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_Low); /* Command Mode RS=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_High); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)

	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB4_PIN_ID , GET_BIT(Command,4));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB5_PIN_ID , GET_BIT(Command,5));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB6_PIN_ID , GET_BIT(Command,6));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB7_PIN_ID , GET_BIT(Command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_Low); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_High); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(Command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(Command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(Command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(Command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_Low); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID , Command); /* Send Command to PORTC */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_Low); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif

}

/***********************************************************************************
* [Function_Name] : LCD_displayCharacter
* [Description] : Display the required character or screen
* [Argument] : uint8 Character --> 8-bits Character
* [Returns] : No return data type
***********************************************************************************/
void LCD_displayCharacter(uint8 character){
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_High); /* Data Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_High); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)

	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB4_PIN_ID , GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB5_PIN_ID , GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB6_PIN_ID , GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID , LCD_DB7_PIN_ID , GET_BIT(character,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_Low); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_High); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_Low); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID , character); /* Send Command to PORTC */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_Low); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif

}

/**************************************************************************************
* [Function_Name] : LCD_displayString
* [Description] : Display the required String or screen
* [Argument] : char* string ----> Pointer to character, Points to first character in string
* [Returns] : No return data type
**************************************************************************************/
void LCD_displayString(const char* string){
	uint8 i = 0;
	while(string[i] != '\0')
	{
		LCD_displayCharacter(string[i]);
		i++;
	}
}

/***************************************************************************************
* [Function_Name] : LCD_clearScreen
* [Description] : clear the screen
* [Argument] : No arguments
* [Returns] : No return data type
***************************************************************************************/
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/***************************************************************************************
* [Function_Name] : LCD_integerToString
* [Description] : Convert the required integer to string
* [Argument] : int data ---> Passed data that needed to be converted
* [Returns] : No return data type
***************************************************************************************/
void LCD_integerToString(int data){
	char buffer[16]; /* Contains ASCII Codes of Numbers, Declared as 16 location---> NUM of COL 16 */
	itoa(data,buffer,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buffer); /* Display the string */
}

/***************************************************************************************
* [Function_Name] : LCD_moveCursor
* [Description] : Move cursor in specified col number and row number
* [Argument] : uint8 row---> The required row to move cursor
*              uint8 col---> The required col to move cursor
* [Returns] : No return data type
***************************************************************************************/
void LCD_moveCursor(uint8 row , uint8 col){
	uint8 LCD_adress ;
	switch(row){
	case 0:
		LCD_adress = col;
		break;
	case 1:
		LCD_adress = col + 0x40;
		break;
	case 2:
		LCD_adress = col + 0x10;
		break;
	case 3:
		LCD_adress = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(LCD_adress | LCD_SET_CURSOR_LOCATION);
}
/************************************************************************************
* [Function_Name] : LCD_displayStringRowCol
* [Description] : Move cursor in specified col number and row number and display string in this location
* [Argument] : uint8 row---> The required row to move cursor
*              uint8 col---> The required col to move cursor
*              const char* ptr ---> Pointer to character, Points to first character in string
* [Returns] : No return data type
************************************************************************************/
void LCD_displayStringRowCol(uint8 row, uint8 col , const char* string){
	LCD_moveCursor(row,col);
	LCD_displayString(string);
}





