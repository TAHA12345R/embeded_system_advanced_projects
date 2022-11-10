/************************************************
* [File Name] : twi.h
* [Description]: Header File of I2C Driver
* [Author]: taha Khaled
************************************************/
#ifndef TWI_H_
#define TWI_H_

#include "../../Utilities/std_types.h"

/*******************************************************************************
*                       Definitions                                            *
*******************************************************************************/
/* Action done by I2C is saved in register TWCR (Read only bits) */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
*                      Type Definition                                         *
*******************************************************************************/
typedef enum
{
	TWI_F_CPU , TWI_F_CPU_4 , TWI_F_CPU_16 , TWI_F_CPU_64
}TWI_Prescaler;
typedef struct
{
	TWI_Prescaler Prescaler;
	uint8 slaveAddress;
	uint8 Factor;
}TWI_ConfigType;
/*******************************************************************************
*                      Functions Prototypes                                    *
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
void TWI_init(const TWI_ConfigType* Config);
/*******************************************************************************************************
* [Function_Name] : TWI_start
* [Description] : Master device send a start bit:
*                 1- Clear interrupt Flag
*                 2- Send a Start bit
*                 3- Enable TWI Module
* [Argument] : No arguments
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_start(void);
/*******************************************************************************************************
* [Function_Name] : TWI_stop
* [Description] : Master device send a stop bit:
*                 1- Clear interrupt Flag
*                 2- Send a Stop bit
*                 3- Enable TWI Module
* [Argument] : No arguments
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_stop(void);
/*******************************************************************************************************
* [Function_Name] : TWI_writebyte
* [Description] : This Function sued to send a data byte:
*                 1- Put data into Register
*                 2- clear Flag
*                 3- wait until data send successfully
* [Argument] : uint8 ----> 8-bit Data
* [Returns] : No return data type
*******************************************************************************************************/
void TWI_writebyte(uint8 data);
/*******************************************************************************************************
* [Function_Name] : TWI_readByteWithACK
* [Description] : This Function used to read a data byte:
*                 1- clear Flag & Enable TWI
*                 2- Send acknowledge signal to sender
*                 3- wait until data received successfully
* [Argument] :No Arguments
* [Returns] : Return Data Received
*******************************************************************************************************/
uint8 TWI_readByteWithACK(void);
/*******************************************************************************************************
* [Function_Name] : TWI_readByteWithACK
* [Description] : This Function used to read a data byte:
*                 1- clear Flag & Enable TWI
*                 2- No acknowledge will be send
*                 3- wait until data received successfully
* [Argument] :No Arguments
* [Returns] : Return Data Received
*******************************************************************************************************/
uint8 TWI_readByteWithNACK(void);
/*******************************************************************************************************
* [Function_Name] : TWI_getStatus
* [Description] : This Function used to get status of TWI:
*                 -Get the status of the action done by sender to check which action the flag was enabled by which?
* [Argument] :No Arguments
* [Returns] : Return Status Data
*******************************************************************************************************/
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */


















