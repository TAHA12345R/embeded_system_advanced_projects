/************************************************
* [File Name] : buzzer.c
* [Description]: Source File of buzzer Driver
* [Author]: taha Khaled
************************************************/
#include "buzzer.h"
#include "../../MCAL/gpio/gpio.h"

/**********************************************************************
*                        Functions Definitions                        *
**********************************************************************/
/**********************************************************************
* [Function_Name] : Buzzer_init
* [Description] : Initialization of Buzzer:
*                 1- Setup Direction of PIN Connected to Buzzer as OUTPUT PIN
*                 2- Turn OFF Buzzer Initially
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_init(void)
{
	/* Set Direction of PIN Connected to Buzzer */
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_PIN_ID, PIN_OUTPUT);
	/*Turn OFF Buzzer initially*/
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID, LOGIC_Low);
}
/**********************************************************************
* [Function_Name] : Buzzer_ON
* [Description] : Turn ON Buzzer
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_ON(void)
{
	/* Turn ON Buzzer */
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID, LOGIC_High);
}
/**********************************************************************
* [Function_Name] : Buzzer_OFF
* [Description] : Turn OFF Buzzer
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_OFF(void)
{
	/*Turn OFF Buzzer*/
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID, LOGIC_Low);
}
