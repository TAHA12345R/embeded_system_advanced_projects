/************************************************
* [Description]: Source File of Application of HMI_ECU
* [Author]: taha Khaled
************************************************/
#include "HMI_Utilities.h"
#include "util/delay.h"
#include "avr/io.h"
int main(void)
{

	/* Enable Global interrupt Flag */
	SREG |= (1 << 7);

	/* Initialize LCD Driver */
	LCD_init();

	/* Set call back function that will be used in ISR */
	TIMER1_setCallback(Callback);

	/* Initialize Timer1 with set of Configurations
	 * - Start Time       : 0
	 * - Compare value    : 8000
	 * - Pre-scaler       : 1024
	 * - Timer1 Mode      : Compare Mode
	 * ********************************************/
	Timer1_ConfigType Timer_configuration = {0,8000,F_CPU_1024,Compare_Mode};
	TIMER1_init_Compare(&Timer_configuration);

	/* Initialize UART Driver with set of Configurations
	 * - Number of Bits per Frame     : 8
	 * - Number of Stop bits in Frame : 1
	 * - Parity-bit in the Frame      : Disabled
	 * - Baud Rate of UART            : 9600
	 * ********************************************/
	UART_ConfigType Uart_configuration = {Data_8_bit,Stop_1Bit,Disabled,9600};
	UART_init(&Uart_configuration);

	/* Call Function Create_Password that will Take Password From User
	 * and send it serially using UART to Control_ECU to check Matching
	 * of Two Passwords */
	Create_Password();

	/* Key_Pressed variable that will take an option from user after Entered two Passwrods
	 * and Control_ECU check the validity of Two Passwords */
	uint8 Key_Pressed = 0;

	/* Status Variable That will store the state of Passwords entered by user */
	uint8 Status = 0;

	/* Password that will passed to Function get_Password to Take Passwrod From user  */
	uint8 Password[Length_of_Password];

	while(1)
	{
		/* Options always should be displayed on the screen after pass the Correction f two passwords */
		User_Options();

		/* Key Variable that will take an option from user + to Open Door or - to change Password */
		Key_Pressed = KEYPAD_getPressedKey();

		/* Clear Screen after Take an option from user */
		LCD_clearScreen();

		/* If Key_Pressed by the user is Open Door action */
		if(Key_Pressed == Open_Door)
		{
			/* clear screen */
			LCD_clearScreen();

			/* Ask User to enter a Password */
			LCD_displayString("PLZ ENTER PASS:");

			/* This delay made to avoid override occurs on LCD Screen */
			_delay_ms(1000);

			/* Take Password From user */
			Get_Password(Password);

			/* Send Ready state to indicate that HMI_ECU will send Message */
			UART_sendByte(Ready);

			/* Send a Password Serially to Control_ECU */
			Send_Password(Password);

			/* User Should Tell Control_ECU what the action done */
			UART_sendByte(Open_Door);

			/* Control_ECU will send a byte that show status of Password Entered by user and if Password match
			 * Password Exist in EEPROM, Control_ECU will send Open_Door_Action Byte to tell User the door will
			 * be opened  */
			Status = UART_recieveByte();

			if(Status == Opening_Door_Action)
			{
				/* Display Door Unlocking on LCD For 15 seconds and after that display Hold Motor for
				 * 3 second and after that display Door is Locking for 15 seconds */
				Open_Hold_Close();
			}
			else if(Status == 0)
			{
				/* If Control_ECU send to HMI_ECU status byte of 0 this means that password entered by user
				 * doesn't match password exist in EEPROM Driver */
				LCD_clearScreen();

				/* Display That will show to user that Password Entered is wrong and ask to Enter it again */
				LCD_displayString("PLZ ENTER PASS:");

				/* Take another Password From user */
				Get_Password(Password);

				/* Send it serially to Control_ECU */
				Send_Password(Password);

				/* Receive status from Control_ECU that indicated the status of Password Entered */
				Status = UART_recieveByte();

				/* If Status is True */
				if(Status == 1)
				{
					/* Display Door Unlocking on LCD For 15 seconds and after that display Hold Motor for
					 * 3 second and after that display Door is Locking for 15 seconds */
					Open_Hold_Close();
				}
				else if(Status == 0)
				{
					LCD_clearScreen();

					/* Display That will show to user that Password Entered is wrong and ask to Enter it again */
					LCD_displayString("PLZ ENTER PASS:");

					/* Take another Password From user */
					Get_Password(Password);

					/* Send it serially to Control_ECU */
					Send_Password(Password);

					/* Receive status from Control_ECU that indicated the status of Password Entered */
					Status = UART_recieveByte();

					/* If Status is True */
					if(Status == 1)
					{
						/* Display Door Unlocking on LCD For 15 seconds and after that display Hold Motor for
				         * 3 second and after that display Door is Locking for 15 seconds */
						Open_Hold_Close();
					}
					else if(Status == 0)
					{
						/* Danger_Message Function will be called because Password Entered wrong for 3 times repeatedly*/
						Danger_Message();
					}
				}
			}

			else if(Status == Danger)
			{
				Danger_Message();
			}

		}
		/* If Key_Pressed by the user is Change Password action */
		else if(Key_Pressed == ChangePass)
		{
			LCD_clearScreen();

			/* Ask User to enter a Password */
			LCD_displayString("PLZ ENTER PASS:");

			/* This delay made to avoid override occurs on LCD Screen */
			_delay_ms(1000);

			/* Take Password From user */
			Get_Password(Password);

			/* Send Ready state to indicate that HMI_ECU will send Message */
			UART_sendByte(Ready);

			/* Send a Password Serially to Control_ECU */
			Send_Password(Password);

			/* User Should Tell Control_ECU what the action done */
			UART_sendByte(ChangePass);

			/* Control_ECU will send a byte that show status of Password Entered by user and if Password match
			 * Password Exist in EEPROM, Control_ECU will send Change_Password_Action Byte to tell to repeat
			 * step1 again */
			Status = UART_recieveByte();

			/* If Status received is Changing_Password_Action ---> Password is correct */
			if(Status == Changing_Password_Action)
			{
				/* Repeat step1 again */
				Create_Password();
			}

			else if(Status == Danger)
			{
				/* if Entered 3 wrong repeated passwords */
				Danger_Message();
			}
			else if(Status == 0)
			{

				LCD_clearScreen();

				/* Ask user to enter Password again in case of the first time is wrong */
				LCD_displayString("PLZ ENTER PASS:");

				/* take the second Password from user*/
				Get_Password(Password);

				/* Send a Password taken from user serially using UART */
				Send_Password(Password);

				/* Receive the status of Password entered by user */
				Status = UART_recieveByte();

				/* If two password are true */
				if(Status == 1)
				{
					/* Repeat step 1 */
					Create_Password();
				}
				else if(Status == 0)
				{

					LCD_clearScreen();

					/* Ask user to enter Password again in case of the first time is wrong */
					LCD_displayString("PLZ ENTER PASS:");

					/* take the second Password from user*/
					Get_Password(Password);

					/* Send a Password taken from user serially using UART */
					Send_Password(Password);

					/* Receive the status of Password entered by user */
					Status = UART_recieveByte();

					/* if status true*/
					if(Status == 1)
					{
						/* Repeat step 1 */
						Create_Password();
					}
					else if(Status == 0)
					{
						/* After entering 3 wrong repeated passwords Danger Message will be shown on LCD*/
						Danger_Message();
					}
				}
			}
		}
	}
	return 0;
}
















