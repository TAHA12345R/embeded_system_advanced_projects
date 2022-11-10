/************************************************
* [File Name] : utilities.h
* [Description]: Header File of Utilities Functions
* [Author]: taha Khaled
************************************************/
#ifndef HMI_UTILITIES_H_
#define HMI_UTILITIES_H_

#include "MCAL/uart/uart.h"
#include "HAL/Keypad/keypad.h"
#include "HAL/LCD/lcd.h"
#include "MCAL/timer1/timer1.h"
#include "Utilities/std_types.h"
/****************************************************************
*                        Definitions                            *
****************************************************************/
#define Enter_Key 13           // Entered Key to move to next state //
#define Length_of_Password 5   // Length of Password user should entered //
#define Ready 0x10             // Indication for MCU to let other MCU Ready to Receive //
#define Open_Time 10           // Used by Timer1 Driver to Open Door until reach approx 15s //
#define Close_Time 10          // Used by Timer1 Driver to close Door until reach approx 15s //
#define Hold_Time 3            // Used by Timer1 Driver to hold Door until reach approx 3s //
#define Danger_Time 60         // Used by Timer1 Driver to Display Danger message until reach approx 60s //
#define Open_Door '+'          // Option 1 that available to user //
#define ChangePass '-'         // Option 2 that available to user //
#define Opening_Door_Action 88 // Open Door action byte that send to MCU to Know the action that user want to do //
#define Changing_Password_Action 44 // change Pass action byte that send to MCU to Know the action that user want to do //
#define Danger 0x33 // Control MCU shold Send a byte to HMI MCU to Know that user entered a wrong password 3 times //

/*******************************************************************************
*                      Global Variables                                        *
*******************************************************************************/
extern uint32 g_ticks;

/*******************************************************************************
*                      Functions Prototypes                                    *
*******************************************************************************/

/*****************************************************************************
* [Function_Name]: Get_Password()
* [Description]: This Function Take a Password entered from user through Keypad
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Get_Password(uint8* Password);
/*****************************************************************************
* [Function_Name]: Send_Password()
* [Description]: This Function Send Password Taken from user and send it Serially using UART
*                Driver to another Micro-controller
* [Arguments]: uint8* Password that Password save on it
* [Returns]: No Returns Type
*****************************************************************************/
void Send_Password(uint8* Password);
/*****************************************************************************
* [Function_Name]: Create_Password()
* [Description]: This Function Take a Password From user and Ask him for re-enter a password and
*                Send Two Password serially using UART to another MCU to check if the two Passwords
*                are matched or not, if two Password Matched Save it into EEPROM Driver and if not
*                LCD Should Display Un-matched Two Passwords and ask again to enter Two Passwords
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Create_Password(void);
/*****************************************************************************
* [Function_Name]: User_Options()
* [Description]: This Function always display Options that available to user
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void User_Options(void);
/*****************************************************************************
* [Function_Name]: Open_Hold_Close()
* [Description]: This Function display Status that should be displayed after entering
*                correct password. Status such as (Door is Unlocking, Door is Locking , Door is hold)
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Open_Hold_Close(void);
/*****************************************************************************
* [Function_Name]: Callback()
* [Description]: This Function is only increment the variable used when an interrupt occurs by
*                Timer1 Driver
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Callback(void);
/*****************************************************************************
* [Function_Name]: Danger_Message()
* [Description]: This Function display Warning message after entering 3-times Wrong Password
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Danger_Message(void);

#endif /* UTILITIES_H_ */







