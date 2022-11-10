/************************************************
* [File Name] : buzzer.h
* [Description]: Header File of buzzer Driver
* [Author]: taha Khaled
************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../Utilities/std_types.h"
/*******************************************************************
*                        Definitions                               *
*******************************************************************/
#define Buzzer_PORT_ID PORTD_ID
#define Buzzer_PIN_ID PIN2_ID
/*******************************************************************
*                        Function Prototype                        *
*******************************************************************/

/**********************************************************************
* [Function_Name] : Buzzer_init
* [Description] : Initialization of Buzzer:
*                 1- Setup Direction of PIN Connected to Buzzer as OUTPUT PIN
*                 2- Turn OFF Buzzer Initially
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_init(void);
/**********************************************************************
* [Function_Name] : Buzzer_ON
* [Description] : Turn ON Buzzer
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_ON(void);
/**********************************************************************
* [Function_Name] : Buzzer_OFF
* [Description] : Turn OFF Buzzer
* [Argument] : No arguments
* [Returns] : No return data type
**********************************************************************/
void Buzzer_OFF(void);

#endif /* BUZZER_H_ */
