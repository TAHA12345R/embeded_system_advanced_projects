/************************************************
* [File Name] : utilities2.h
* [Description]: Header File of Utilities2 Functions
* [Author]: taha Khaled
************************************************/
#ifndef UTILITIES2_H_
#define UTILITIES2_H_

#include "MCAL/uart/uart.h"
#include "HAL/DC_Motor/dc_motor.h"
#include "HAL/EEPROM/eeprom.h"
#include "MCAL/timer1/timer1.h"
#include "HAL/Buzeer/buzzer.h"
#include "Utilities/std_types.h"
#include "util/delay.h"

/****************************************************************
*                        Definitions                            *
****************************************************************/
#define Enter_Key 13                // Entered Key to move to next state //
#define Length_of_Password 5        // Length of Password user should entered //
#define Ready 0x10                  // Indication for MCU to let other MCU Ready to Receive //
#define Open_Time 10                // Used by Timer1 Driver to Open Door until reach approx 15s //
#define Close_Time 10               // Used by Timer1 Driver to close Door until reach approx 15s //
#define Hold_Time 3                 // Used by Timer1 Driver to hold Door until reach approx 3s //
#define Danger_Time 60              // Used by Timer1 Driver to Display Danger message until reach approx 60s //
#define EEPROM_Address 0x0311       // Address that will be stored in it tha password entered by user //
#define Open_Door '+'               // Option 1 that available to user //
#define ChangePass '-'              // Option 2 that available to user //
#define Opening_Door_Action 88      // Open Door action byte that send to MCU to Know the action that user want to do //
#define Changing_Password_Action 44 // change Pass action byte that send to MCU to Know the action that user want to do //
#define Danger 0x33                 // Control MCU shold Send a byte to HMI MCU to Know that user entered a wrong password 3 times //
#define Max_Number_of_Wrong_Password 3 // Maximum Number of Wrong Password befor warning //

/*******************************************************************************
*                      Global Variables                                        *
*******************************************************************************/
extern uint32 g_ticks;
extern uint8 App_Password[Length_of_Password];

/*******************************************************************************
*                      Functions Prototypes                                    *
*******************************************************************************/

/*****************************************************************************
* [Function_Name]: Compare_Password()
* [Description]: This Function Take Two Passwords and Compare them and check if Two
*                Passwords are true
* [Arguments]: - uint8* Password1 ---> First Password Entered
*              - uint8* Password2 ---> Second Password Entered
* [Returns]: Return state of Two Passwords
*****************************************************************************/
uint8 Compare_Password(uint8* Password1 , uint8* Password2);

/*****************************************************************************
* [Function_Name]: Receive_From_User()
* [Description]: This Function Receive Password Entered by user serially using UART
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Receive_From_User(uint8* Password);

/*****************************************************************************
* [Function_Name]: Store_Password_EEPROM()
* [Description]: This Function store password in EEPROM Module after make a check that two
*                Password entered by user are matched
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this global variable
* [Returns]: No Returns Type
*****************************************************************************/
void Store_Password_EEPROM(uint8* Password);

/*****************************************************************************
* [Function_Name]: Callback()
* [Description]: This Function increase only global variable that used by ISR in Timer1 Module
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Callback(void);

/*****************************************************************************
* [Function_Name]: Check_Password()
* [Description]: This Function is general function that call Receive_From_User and
*                Compare_Password function and Store_Password_EEPROM and make an action
*                based on Password correct or Not
* [Arguments]: uint8* Password that take Key Pressed by user and save it on this variable
* [Returns]: No Returns Type
*****************************************************************************/
void Check_Password(void);

/*****************************************************************************
* [Function_Name]: Danger_Action()
* [Description]: This Function Turn on Buzzer after entering 3 wrong Password Repeatedly
* [Arguments]: No Arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Danger_Action(void);

/*****************************************************************************
* [Function_Name]: Rotate_hold_motor()
* [Description]: This Function will rotate motor after entering a correct password and
*                wait when the door completely opened for 3 seconds after that Door will be closed
*                again
* [Arguments]: No arguments
* [Returns]: No Returns Type
*****************************************************************************/
void Rotate_hold_motor(void);

#endif /* UTILITIES2_H_ */
