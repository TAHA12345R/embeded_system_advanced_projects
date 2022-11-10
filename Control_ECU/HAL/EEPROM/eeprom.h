/************************************************
* [File Name] : eeprom.h
* [Description]: Header File of external eeprom
* [Author]: taha Khaled
************************************************/
#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../Utilities/std_types.h"
/*******************************************************************************
*                       Definitions                                            *
*******************************************************************************/
#define ERROR 0
#define SUCCESS 1
/*******************************************************************************
*                      Functions Prototypes                                    *
*******************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
#endif /* EEPROM_H_ */
