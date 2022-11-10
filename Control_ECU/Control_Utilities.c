/************************************************
* [File Name] : utilities2.c
* [Description]: Source File of Utilities2 Functions
* [Author]: taha khaled
************************************************/
#include "Control_Utilities.h"

/*******************************************************************************
*                      Global Variables                                        *
*******************************************************************************/
uint32 g_ticks = 0;
uint8 App_Password[Length_of_Password];

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*****************************************************************************
* [Function_Name]: Compare_Password()
* [Description]: This Function Take Two Passwords and Compare them and check if Two
*                Passwords are true
* [Arguments]: - uint8* Password1 ---> First Password Entered
*              - uint8* Password2 ---> Second Password Entered
* [Returns]: Return state of Two Passwords
*****************************************************************************/
uint8 Compare_Password(uint8* Password1 , uint8* Password2)
{
	/* Loop until Length of Password to Compare Two Passwrods*/
	for(uint8 i = 0 ; i < Length_of_Password ; ++i)
	{
		/* Check if Two Password are equal */
		if(Password1[i] != Password2[i])
		{
			/* Return 0 if Not */
			return 0;
		}
	}
	/* Return 1 if Matched */
	return 1;
}

/*****************************************************************************
* [Function_Name]: Receive_From_User()
* [Description]: This Function Receive Password Entered by user serially using UART
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Receive_From_User(uint8* Password)
{
	/* Loop until Length of Password to store it in Variable Password */
	for(uint8 i = 0 ; i < Length_of_Password ; ++i)
	{
		/* Receive Serially using UART */
		Password[i] = UART_recieveByte();

		/* Simple Delay between operations */
		_delay_ms(50);
	}
}

/*****************************************************************************
* [Function_Name]: Store_Password_EEPROM()
* [Description]: This Function store password in EEPROM Module after make a check that two
*                Password entered by user are matched
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this global variable
* [Returns]: No Returns Type
*****************************************************************************/
void Store_Password_EEPROM(uint8* Password)
{
	/* Loop until Length of Password to store it in Variable App_Password */
	for(uint8 i = 0 ; i < Length_of_Password ; ++i)
	{
		/* Store Password in the specific location in EEPROM Memory */
		EEPROM_writeByte(EEPROM_Address + i, Password[i]);

		/* This is global variable that will be compared in Main.c File */
		App_Password[i] = Password[i];

		/* Simple Delay between operations */
		_delay_ms(50);
	}
}

/*****************************************************************************
* [Function_Name]: Callback()
* [Description]: This Function increase only global variable that used by ISR in Timer1 Module
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Callback(void)
{
	g_ticks ++;
}

/*****************************************************************************
* [Function_Name]: Check_Password()
* [Description]: This Function is general function that call Receive_From_User and
*                Compare_Password function and Store_Password_EEPROM and make an action
*                based on Password correct or Not
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Check_Password(void)
{

	/* Create Two arrays of Length of Password that will be received from HMI_ECU */
	uint8 Password1[Length_of_Password];
	uint8 Password2[Length_of_Password];

	/* variable that will save the state of Two passwords entered */
	uint8 status = 0;

	/* When The state of Two password Unmatched, wait until user Entered another two passwords */
	while(status == 0)
	{

		/* Wait until HMI_ECU Entered a Password, Before entered a Password HMI_ECU will send Ready byte */
		while(UART_recieveByte() != Ready){}

		/* Tell HMI_ECU that Ready to Receive Passwords */
		UART_sendByte(Ready);

		/* Receive Password Entered by user and store it in the First array */
		Receive_From_User(Password1);

		/* Wait until HMI_ECU Entered a Password, Before entered a Password HMI_ECU will send Ready byte */
		while(UART_recieveByte()!=Ready){}

		/* Tell HMI_ECU that Ready to Receive Passwords */
		UART_sendByte(Ready);

		/* Receive Password Entered by user and store it in the Second array */
		Receive_From_User(Password2);

		/* Compare between two Password using Compare_Passwords Fucntion */
		status = Compare_Password(Password1, Password2);

		/* Tell HMI_ECU that Control_ECU will send a byte */
		UART_sendByte(Ready);

		/* Send the state of Two passwords to HMI_ECU */
		UART_sendByte(status);

		/* If two Passwords Matched then save password into EEPROM */
		if(status == 1)
		{
			/*save password into EEPROM*/
			Store_Password_EEPROM(Password1);
		}
	}
}

/*****************************************************************************
* [Function_Name]: Danger_Action()
* [Description]: This Function Turn on Buzzer after entering 3 wrong Password Repeatedly
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Danger_Action(void)
{
	g_ticks = 0;

	/* Turn on Buzzer when user Entered 3 wrong password repeatedly in Open door or change Password options */
	Buzzer_ON();

	/* Buzzer will be operated until Timer count 60 seconds */
	while(g_ticks < Danger_Time){}

	/* After Timer1 Finishing counts, Buzzer will Turn off */
	Buzzer_OFF();
}

/*****************************************************************************
* [Function_Name]: Rotate_hold_motor()
* [Description]: This Function will rotate motor after entering a correct password and
*                wait when the door completely opened for 3 seconds after that Door will be closed
*                again
* [Arguments]: No arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Rotate_hold_motor(void)
{
	g_ticks = 0;

	/* Rotate Motor with clockwise when user Entered a correct Password */
	DCMotor_rotate(1, 95);

	/* Wait until 15 seconds when Door is Completely opened */
	while(g_ticks < Open_Time){};

	/* Hold the Door for 3 seconds */
	DCMotor_rotate(0, 0);

	/* Wait until 3 seconds */
	while(g_ticks < Open_Time + Hold_Time){};

	/* Rotate Motor with Anti-clockwise to Close Door Again */
	DCMotor_rotate(2, 95);

	/* Wait until 15 seconds when Door is Completely closed */
	while(g_ticks < Open_Time + Hold_Time + Close_Time){}

	/* Stop Motor */
	DCMotor_rotate(0, 0);
}


















