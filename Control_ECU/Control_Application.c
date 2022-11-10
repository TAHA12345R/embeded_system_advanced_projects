/************************************************
* [File Name] : Application2.c
* [Description]: Source File of Application of control_ECU
* [Author]: taha khaled
************************************************/
#include "Control_Utilities.h"
#include "avr/io.h"
#include "util/delay.h"

int main(void)
{

	/* Enable Global interrupt Flag */
	SREG |= (1 << 7);

	/* Initialize DC_Motor Driver */
	DCMotor_init();

	/* Initialize UART Driver with set of Configurations
	 * - Number of Bits per Frame     : 8
	 * - Number of Stop bits in Frame : 1
	 * - Parity-bit in the Frame      : Disabled
	 * - Baud Rate of UART            : 9600
	 * ********************************************/
	UART_ConfigType Uart_configuration = {Data_8_bit , Stop_1Bit , Disabled , 9600};
	UART_init(&Uart_configuration);

	/* Initialize Buzzer Driver */
	Buzzer_init();

	/* Initialize Timer1 with set of Configurations
	 * - Start Time       : 0
	 * - Compare value    : 8000
	 * - Pre-scaler       : 1024
	 * - Timer1 Mode      : Compare Mode
	 * ********************************************/
	TIMER1_setCallback(Callback);
	Timer1_ConfigType Timer1_configuration = {0,8000,F_CPU_1024,Compare_Mode};
	TIMER1_init_Compare(&Timer1_configuration);

	/* Receive Two Passwords Entered by user and check the matching of two passwords of two password are matched
	 * this function will be terminated*/
	Check_Password();

	/* Array of Length of password that will be used to store password entered by user */
	uint8 receiver_Password[Length_of_Password];

	/* Variable used to count number of wrong times that user entered a wrong passwords*/
	uint8 number_wrong_Password = 0;

	/* Options variable that will receive what option that user will want to do */
	uint8 Options = 0;

	/* state variable that store the state of two passwords entered by user*/
	uint8 state = 0;

	while(1)
	{
		/* control_ECU will be ready to receive message from HMI_ECU when HMI_ECU sends a Ready Message */
		if(UART_recieveByte() == Ready)
		{
			/* Receive Password entered by user */
			Receive_From_User(receiver_Password);

			/* Receive what option that user want to do */
			Options = UART_recieveByte();

			/* check if Option entered is Open door option */
			if(Options == Open_Door)
			{
				/* Compare password received with password stored in Application global variable */
				state = Compare_Password(receiver_Password,App_Password);

				/* If Two passwords are same */
				if(state == 1)
				{
					/* Control_ECU sends a Open door action to receive it and display actions followed by the chosen
					 * action */
					UART_sendByte(Opening_Door_Action);

					number_wrong_Password = 0;

					/* Rotate Motor for 15 seconds then hold motor for 3 second and then rotate A-CW for 15 seconds*/
					Rotate_hold_motor();
				}
				/* If password received doesn't equal password saved in EEPROM Module*/
				else if(state == 0)
				{
					number_wrong_Password++;

					/* check every wrong entered password if number of entered wrong password reach to max or not*/
					if(number_wrong_Password == Max_Number_of_Wrong_Password)
					{
						/* If user entered 3 times wrong password Buzzer will be turn on for 60 seconds*/
						UART_sendByte(Danger);

						Danger_Action();

						/* Make this variable to be 0 again */
						number_wrong_Password = 0;
					}
					else
					{
						/* send to HMI_ECU that two passwords are not the same to ask him to enter password again*/
						UART_sendByte(0);

						/* Receive the second entered password */
						Receive_From_User(receiver_Password);

						/* Compare again with Password save in EEPROM Driver */
						state = Compare_Password(receiver_Password, App_Password);

						/* Send state of Two Passwords after comparing them */
						UART_sendByte(state);

						/* if two Password are same this time */
						if(state == 1)
						{
							/* Rotate Motor for 15 seconds then hold motor for 3 second and then rotate A-CW for 15 seconds*/
							Rotate_hold_motor();
						}
						/* If two password again are not same */
						else if(state == 0)
						{

							/* Receive again the third Password from user */
							Receive_From_User(receiver_Password);

							/* compare the two passwords for the third time */
							state = Compare_Password(receiver_Password, App_Password);

							/* send to HIM_ECU the state of two Passwords */
							UART_sendByte(state);

							/* If two Passwords are matched */
							if(state == 1)
							{
								/* Rotate Motor for 15 seconds then hold motor for 3 second and then rotate A-CW for 15 seconds*/
								Rotate_hold_motor();
							}
							/* If Two passwords not matched for the third time */
							else if(state == 0)
							{
								/* Enable buzzer module for 60 seconds */
								Danger_Action();
							}
						}
					}
				}
			}
			/* If option send by HMI_ECU is chane_Password option */
			else if(Options == ChangePass)
			{
				/* Compare Password received by user with password save in EEPROM Module */
				state = Compare_Password(receiver_Password,App_Password);

				/* IF the Two Password are the same */
				if(state == 1)
				{

					/* send to HMI_ECU Changing_Passwrod_Action to show the following steps of this action */
					UART_sendByte(Changing_Password_Action);

					number_wrong_Password = 0;

					/* Return to the step 1 (Enter and Re-enter two Passwords)*/
					Check_Password();
				}
				/* if the two passwords are not the same */
				else if(state == 0)
				{
					/* Increase variable first */
					number_wrong_Password++;

					/* check every wrong entered password if number of entered wrong password reach to max or not*/
					if(number_wrong_Password == Max_Number_of_Wrong_Password)
					{
						/* Send a Danger message if two passwords are not same for third time */
						UART_sendByte(Danger);

						/* Enable Buzzer for 60 seconds */
						Danger_Action();

						/* Make variable equal 0 again to count again */
						number_wrong_Password = 0;
					}
					else
					{
						/* Send Not matched state to HMI_ECU */
						UART_sendByte(0);

						/* Receive from user for second time */
						Receive_From_User(receiver_Password);

						/* compare between two Passwords */
						state = Compare_Password(receiver_Password, App_Password);

						/* send the state between two password to HMI_ECU */
						UART_sendByte(state);

						if(state == 1)
						{
							/* send to HMI_ECU Changing_Passwrod_Action to show the following steps of this action */
							UART_sendByte(Changing_Password_Action);

							number_wrong_Password = 0;

							/* Return to the step 1 (Enter and Re-enter two Passwords)*/
							Check_Password();
						}
						else if(state == 0)
						{
							/* Receive password from user again */
							Receive_From_User(receiver_Password);

							/* Compare Two Passwords aagain */
							state = Compare_Password(receiver_Password, App_Password);

							/* send the state of two passwords to user*/
							UART_sendByte(state);
							if(state == 1)
							{
								/* send to HMI_ECU Changing_Passwrod_Action to show the following steps of this action */
								UART_sendByte(Changing_Password_Action);

								number_wrong_Password = 0;

								/* Return to the step 1 (Enter and Re-enter two Passwords)*/
								Check_Password();
							}
							else if(state == 0)
							{
								/* If password does't match for third time */
								Danger_Action();
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
