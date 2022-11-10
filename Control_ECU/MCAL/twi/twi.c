/************************************************
* [File Name] : twi.c
* [Description]: Source File of I2C Driver
* [Author]: taha Khaled
************************************************/
#include "twi.h"
#include "../../Utilities/common_macros.h"
#include "avr/io.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************************************
* [Function_Name] : TWI_init
* [Description] : Initialization of TWI Module:
*                 1- Specify the bit rate that devices will be operated with
*                 2- Specify the Pre-scaler that will be Appropriate with Bit rate specified
*                 3- Define my address if my device converted into slave device under any circumstance
*                 4- Enable TWI module
* [Argument] : No arguments
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_init(const TWI_ConfigType* Config)
{
	/* 400.000 KB/s using Pre-scaler 00 with F_CPU = 8Mhz */
	TWBR = Config->Factor;
	/* Set Pre-scaler with 0x00 to get bit rate 400.000 KB/s */
	TWSR = Config->Prescaler;
	/* my address if device converted into slave under any Circumstance to be able to interact with new master*/
	TWAR = Config->slaveAddress << 1;
	/* Enable I2C Module */
	TWCR = (1 << TWEN);
}

/*******************************************************************************************************
* [Function_Name] : TWI_start
* [Description] : Master device send a start bit:
*                 1- Clear interrupt Flag
*                 2- Send a Start bit
*                 3- Enable TWI Module
* [Argument] : No arguments
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_start(void)
{
	/* -Before sending any thing by master we must firstly clear the flag because any action done by master
	 * such as (Send start bit , Send stop bit , send Data Block , Device address) the flag will be enabled
	 * so, to able to detect which action make the flag is enabled we must clear the flag before any action
	 * -we also need to enable the TWI in each action because if we write this TWCR = (1 << TWSTA) it will
	 * clear the TWI enable bit so, we must enable this bit when make any action */
	/*********************************
	 * TWINT : Clear interrupt Flag
	 * TWSTA : Send a Start bit
	 * TWEN  : Enable TWI Module
	 ********************************/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* wait until start bit is send then terminate the function */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*******************************************************************************************************
* [Function_Name] : TWI_stop
* [Description] : Master device send a stop bit:
*                 1- Clear interrupt Flag
*                 2- Send a Stop bit
*                 3- Enable TWI Module
* [Argument] : No arguments
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_stop(void)
{
	/* -Before sending any thing by master we must firstly clear the flag because any action done by master
	 * such as (Send start bit , Send stop bit , send Data Block , Device address) the flag will be enabled
	 * so, to able to detect which action make the flag is enabled we must clear the flag before any action
	 * -we also need to enable the TWI in each action because if we write this TWCR = (1 << TWSTA) it will
	 * clear the TWI enable bit so, we must enable this bit when make any action */
	/*********************************
	 * TWINT : Clear interrupt Flag
	 * TWSTO : Send a Stop bit
	 * TWEN  : Enable TWI Module
	 ********************************/
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	/* No need to wait until stop bit is send because i will leave the bus anyway */
}
/*******************************************************************************************************
* [Function_Name] : TWI_writebyte
* [Description] : This Function used to send a data byte:
*                 1- Put data into Register
*                 2- clear Flag & Enable TWI
*                 3- wait until data send successfully
* [Argument] : uint8 ----> 8-bit Data
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_writebyte(uint8 data)
{
	/* Put the data on TWI Register */
	TWDR = data;
	/********************************
		 * TWINT : Clear interrupt Flag
		 * TWEN  : Enable TWI Module
    ********************************/
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* wait until the data is send successfully */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
/*******************************************************************************************************
* [Function_Name] : TWI_readByteWithACK
* [Description] : This Function used to read a data byte:
*                 1- clear Flag & Enable TWI
*                 2- wait until data received successfully
* [Argument] :No Arguments
* [Returns] : Return Data Received
*******************************************************************************************************/
uint8 TWI_readByteWithACK(void)
{
	/*********************************
		 * TWINT : Clear interrupt Flag
		 * TWSTO : Send a signal acknowledge to sender to make it know data is received successfully
		 * TWEN  : Enable TWI Module
	********************************/
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait until Data received successfully */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}
/*******************************************************************************************************
* [Function_Name] : TWI_readByteWithNACK
* [Description] : This Function used to read a data byte:
*                 1- clear Flag & Enable TWI
*                 2- No acknowledge will be send
*                 3- wait until data received successfully
* [Argument] :No Arguments
* [Returns] : Return Data Received
*******************************************************************************************************/
uint8 TWI_readByteWithNACK(void)
{
	/*********************************
		 * TWINT : Clear interrupt Flag
		 * TWEN  : Enable TWI Module
	********************************/
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait until Data received successfully */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}
/*******************************************************************************************************
* [Function_Name] : TWI_getStatus
* [Description] : This Function used to get status of TWI:
*                 -Get the status of the action done by sender to check which action the flag was enabled by which?
* [Argument] :No Arguments
* [Returns] : Return Status Data
*******************************************************************************************************/
uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}













