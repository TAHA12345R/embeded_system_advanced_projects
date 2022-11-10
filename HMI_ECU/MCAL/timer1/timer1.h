/************************************************
* [File Name] : timer1.h
* [Description]: Header File of Timer1 Driver
* [Author]: taha Khaled
************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_
#include "../../Utilities/std_types.h"
/****************************************************************
*                        Definitions                            *
****************************************************************/
#define TIMER1_Compare_Mode
/****************************************************************
*                        Type Declaration                       *
****************************************************************/
// 1- Pre-scaler enum that will specify which clock Timer1 Will Operate
typedef enum{
	No_Clock, F_CPU_CLOCK ,F_CPU_8 , F_CPU_64 , F_CPU_256 , F_CPU_1024
}TIMER1_Prescaler;
/**********************************************************************/
// 2- Mode enum that will specify which Mode Timer1 Will Operate
typedef enum{
	Normal_Mode , Compare_Mode = 4
}TIMER1_MODE;
/**********************************************************************/
#ifndef TIMER1_Compare_Mode
typedef struct{
	uint16 Initial_value; // This member will put initial value for Timer1 to start count
	TIMER1_Prescaler Prescaler; // This member will specify Pre-scaler which Timer1 will Operate
	TIMER1_MODE Mode; // This member used to specify Mode of Operation
}Timer1_ConfigType;
#else
typedef struct{
	uint16 Initial_value; // This member will put initial value for Timer1 to start count
	uint16 Compare_value; // This member Put value in Compare Register that will make Timer1 Stop and re-timing when reach to it
	TIMER1_Prescaler Prescaler; // This member will specify Pre-scaler which Timer1 will Operate
	TIMER1_MODE Mode; // This member used to specify Mode of Operation
}Timer1_ConfigType;
#endif
/*******************************************************************************
*                      Functions Prototypes                                    *
*******************************************************************************/
#ifndef TIMER1_Compare_Mode
/********************************************************************************
* [Function Name]: TIMER1_init_Compare
* [Description]: 1- Initialize Value that Timer1 will start from it
*                2- Set Mode of timer1 that will be operate on it
*                3- Specify Pre-scaler which decide the frequency that Timer1 Will operate on it
* [Arguments]: Pointer to struct of type Timer1_ConfigType to set configuration that
*              Timer1 will operate on it
* [Returns]: No Return type
********************************************************************************/
void TIMER1_init_Normal(Timer1_ConfigType* Config_ptr);
#else
/********************************************************************************
* [Function Name]: TIMER1_init_Compare
* [Description]: 1- Initialize Value that Timer1 will start from it
*                2- Set Compare Value that when Timer1 reach to it then, back to 0
*                3- Set Mode of timer1 that will be operate on it
*                4- Specify Pre-scaler which decide the frequency that Timer1 Will operate on it
* [Arguments]: Pointer to struct of type Timer1_ConfigType to set configuration that
*              Timer1 will operate on it
* [Returns]: No Return type
********************************************************************************/
void TIMER1_init_Compare(Timer1_ConfigType* Config_ptr);
#endif

/********************************************************************************
* [Function Name]: TIMER1_deInit
* [Description]: Function disable and stop Timer1 driver
* [Arguments]: No arguments
* [Returns]: No Returns
********************************************************************************/
void TIMER1_deInit(void);
/********************************************************************************
* [Function Name]: TIMER1_setCallback
* [Description]: Function set Pointer argument to Point to Function that will be executed
*                at ISR
* [Arguments]: Pointer that will point to passed Function that will be executed when
*              The interrupt(detection) occurs
* [Returns]: No Return type
********************************************************************************/
void TIMER1_setCallback(void(*a_ptr)(void));
#endif /* TIMER1_H_ */





















