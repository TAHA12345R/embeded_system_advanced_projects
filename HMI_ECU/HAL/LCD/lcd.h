/************************************************
* [File Name] : lcd.h
* [Description]: Header File of LCD Driver
* [Author]: taha Khaled
************************************************/

#ifndef LCD_H_
#define LCD_H_
#include "../../Utilities/std_types.h"
/************************************************************
*                        Definitions                        *
************************************************************/
/* Configure Data bit mode 4-bits or 8-bits */
#define LCD_DATA_BITS_MODE 8
#if ((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE !=8))
#error "Number of Data bits must be 4 or 8"
#endif

/* LCD HW PORTS and PINS */
#define LCD_RS_PORT_ID PORTD_ID
#define LCD_RS_PIN_ID PIN2_ID

#define LCD_E_PORT_ID PORTD_ID
#define LCD_E_PIN_ID PIN3_ID

#define LCD_DATA_PORT_ID PORTB_ID

#if(LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID PIN3_ID
#define LCD_DB5_PIN_ID PIN4_ID
#define LCD_DB6_PIN_ID PIN5_ID
#define LCD_DB7_PIN_ID PIN6_ID
#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND 0x01
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_TWO_LINES_EIGHT_BITS_MODE 0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE 0x28
#define LCD_SET_CURSOR_LOCATION 0x80
#define LCD_GO_TO_HOME 0x02
#define LCD_TWO_LINES_FOUR_BITS_MODE_INT1 0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INT2 0x32

/*******************************************************************
*                        Function Prototype                        *
*******************************************************************/
/*
* [Function_Name] : LCD_init
* [Description] : Initialization of LCD:
*                 1- Setup LCD Pins Direction using GPIO_Driver
*                 2- Setup LCD Data Mode 4-bits or 8-bits
* [Argument] : No arguments
* [Returns] : No return data type
*/
void LCD_init(void);

/*
* [Function_Name] : LCD_sendCommand
* [Description] : Send The Required Command to screen
* [Argument] : uint8 Command --> 8-bits Command
* [Returns] : No return data type
*/
void LCD_sendCommand(uint8 Command);

/*
* [Function_Name] : LCD_displayCharacter
* [Description] : Display the required character or screen
* [Argument] : uint8 Character --> 8-bits Character
* [Returns] : No return data type
*/
void LCD_displayCharacter(uint8 character);

/*
* [Function_Name] : LCD_displayString
* [Description] : Display the required String or screen
* [Argument] : char* string ----> Pointer to character, Points to first character in string
* [Returns] : No return data type
*/
void LCD_displayString(const char* string);

/*
* [Function_Name] : LCD_clearScreen
* [Description] : clear the screen
* [Argument] : No arguments
* [Returns] : No return data type
*/
void LCD_clearScreen(void);

/*
* [Function_Name] : LCD_integerToString
* [Description] : Convert the required integer to string
* [Argument] : int data ---> Passed data that needed to be converted
* [Returns] : No return data type
*/
void LCD_integerToString(int data);

/*
* [Function_Name] : LCD_moveCursor
* [Description] : Move cursor in specified col number and row number
* [Argument] : uint8 row---> The required row to move cursor
*              uint8 col---> The required col to move cursor
* [Returns] : No return data type
*/
void LCD_moveCursor(uint8 row , uint8 col);

/*
* [Function_Name] : LCD_displayStringRowCol
* [Description] : Move cursor in specified col number and row number and display string in this location
* [Argument] : uint8 row---> The required row to move cursor
*              uint8 col---> The required col to move cursor
*              const char* ptr ---> Pointer to character, Points to first character in string
* [Returns] : No return data type
*/
void LCD_displayStringRowCol(uint8 row, uint8 col , const char* ptr);
#endif /* LCD_H_ */
















