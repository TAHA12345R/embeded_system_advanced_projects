/************************************************
* [Description]: Source File of Utilities Functions
* [Author]: taha Khaled
************************************************/
#include "HMI_Utilities.h"
#include "util/delay.h"

/*******************************************************************************
*                      Global Variables                                         *
*******************************************************************************/
uint32 g_ticks = 0;

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*****************************************************************************
* [Function_Name]: Get_Password()
* [Description]: This Function Take a Password entered from user through Keypad
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Get_Password(uint8* Password)
{
	uint8 Key_Pressed;

	/*Move a cursor of LCD to second Row to Print Password Entered by user */
	LCD_moveCursor(1, 0);

	/* Take Pressed key from user until */
	for(uint8 i = 0 ; i < Length_of_Password ; i++)
	{
		/* Get Key_Pressed by user */
		Key_Pressed = KEYPAD_getPressedKey();

		/* Store Password */
		Password[i] = Key_Pressed;

		/* Display on LCD Encrypted PAssword (*) */
		LCD_displayCharacter('*');

		_delay_ms(500);
	}

	/* Don't Exit From this Fucntion Until user entered Enter Key */
	while(KEYPAD_getPressedKey() != Enter_Key){}
}

/*****************************************************************************
* [Function_Name]: Send_Password()
* [Description]: This Function Send Password Taken from user and send it Serially using UART
*                Driver to another Micro-controller
* [Arguments]: uint8* Password that Password save on it
* [Returns]: No Returns Type
*****************************************************************************/
void Send_Password(uint8* Password)
{
	/* Loop until Reach the length of Password */
	for(uint8 i = 0 ; i < Length_of_Password ; i++)
	{
		/*Send a Password Serially to another MCU*/

		UART_sendByte(Password[i]);

		/*Simple delay between operations*/
		_delay_ms(50);
	}
}

/*****************************************************************************
* [Function_Name]: Create_Password()
* [Description]: This Function Take a Password From user and Ask him for re-enter a password and
*                Send Two Password serially using UART to another MCU to check if the two Passwords
*                are matched or not, if two Password Matched Save it into EEPROM Driver and if not
*                LCD Should Display Un-matched Two Passwords and ask again to enter Two Passwords
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Create_Password(void)
{
	/* Create Two arrays of Length of Password to send them to another MCU */
	uint8 First_Password[Length_of_Password];
	uint8 Second_Password[Length_of_Password];

	uint8 status = 0;

	/* When The state of Two password Unmatched, Again ask user to enter Two Matched Passwords to exit Loop*/
	while(status == 0)
	{
		LCD_clearScreen();

		/* Display on Screen to tell user what should him do */
		LCD_displayString("PLZ ENTER PASS:");

		/* Get First Password From User and store it in First_Password array */
		Get_Password(First_Password);

		/* Tell another MCU I will send a byte */
		UART_sendByte(Ready);

		/* If Control_ECU send HMI_ECU Ready byte so, HMI_ECU will start sending password to Control_ECU*/
		while(UART_recieveByte()!= Ready);

		/* Send Password After receiving Ready byte */
		Send_Password(First_Password);

		/* Clear Screen */
		LCD_clearScreen();

		/* ask user to Enter another Password to check Two matched Passwords */
		LCD_displayString("PLZ REENTER PASS:");

		/* Get Second Password From User and store it in Second_Password array */
		Get_Password(Second_Password);

		/* Tell another MCU I will send a byte */
		UART_sendByte(Ready);

		/* If Control_ECU send HMI_ECU Ready byte so, HMI_ECU will start sending password to Control_ECU*/
		while(UART_recieveByte()!=Ready);

		/* Send Password After receiving Ready byte */
		Send_Password(Second_Password);

		/* If Control_ECU send HMI_ECU Ready byte so, HMI_ECU will start receiving state from Control_ECU*/
		while(UART_recieveByte() != Ready){}

		/*HMI_ECU Receive status of Two Password (Matched , unmatched)*/
		status = UART_recieveByte();

		/* If status not matched */
		if(status == 0)
		{
			LCD_clearScreen();

			/* display on screen Not matched to tell user about wrong action done */
			LCD_displayString("NOT MATCHED");

			/* Delay of showing this message */
			_delay_ms(1000);

			LCD_clearScreen();
		}
	}
	LCD_clearScreen();
}

/*****************************************************************************
* [Function_Name]: User_Options()
* [Description]: This Function always display Options that available to user
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void User_Options(void)
{
	LCD_clearScreen();

	/* Display Open Door Option on LCD */
	LCD_displayStringRowCol(0, 0, "+ : Open Door");

	/* Display change Password Option on LCD */
	LCD_displayStringRowCol(1, 0, "- : Change Pass");
}

/*****************************************************************************
* [Function_Name]: Callback()
* [Description]: This Function is only increment the variable used when an interrupt occurs by
*                Timer1 Driver
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Callback(void)
{
	g_ticks ++;
}

/*****************************************************************************
* [Function_Name]: Open_Hold_Close()
* [Description]: This Function display Status that should be displayed after entering
*                correct password. Status such as (Door is Unlocking, Door is Locking , Door is hold)
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Open_Hold_Close(void)
{
	g_ticks = 0;

	LCD_clearScreen();

	/* Display Door Unlocking when user entered a correct Password */
	LCD_displayString("DOOR UNLOCKING");

	/* time of Message will be shown on the screen */
	while(g_ticks < Open_Time){}

	LCD_clearScreen();

	/* Display Hold motor after door is completely opened  */
	LCD_displayString("HOLD MOTOR");

	/* time of Message will be shown on the screen */
	while(g_ticks < Open_Time + Hold_Time){}

	LCD_clearScreen();

	/* Display unlocking door when door wait for some second  */
	LCD_displayString("DOOR IS LOCKING");

	/* time of Message will be shown on the screen */
	while(g_ticks < Open_Time + Hold_Time + Close_Time){}

	LCD_clearScreen();
}

/*****************************************************************************
* [Function_Name]: Danger_Message()
* [Description]: This Function display Warning message after entering 3-times Wrong Password
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Danger_Message(void)
{
	g_ticks = 0;

	LCD_clearScreen();

	/* Display Wrong Message on Screen To tell user about his wrong action */
	LCD_displayString("REPEATED WRONG!");

	/* time of Message will be shown on the screen */
	while(g_ticks < Danger_Time){}
}









