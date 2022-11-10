/************************************************
* [File Name] : eeprom.h
* [Description]: Header File of external eeprom
* [Author]: taha Khaled
************************************************/
#include "eeprom.h"
#include "../../MCAL/twi/twi.h"
/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	/* TWI send a start bit */
	TWI_start();

	/* Check the action that make the flag is enabled is Sending a start bit*/
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	/* Sending the address device of EEPROM 1010 is Fixed and first three bit is last three bits in 11-bit
	 * of the location that want to write a value on it in the EEPROM
	 * and specify R/W, In this case Write */
	TWI_writebyte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));

	/* Check the action that make the flag is enabled is Sending device address with R/W bit*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	    return ERROR;

	/* Send the rest of Address that want to write on it in the EEPROM */
	TWI_writebyte((uint8)(u16addr));

	/* Check the action that make the flag is enabled is Sending address of location in memory*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* write byte to EEPROM */
	TWI_writebyte(u8data);

	/* Check the action that make the flag is enabled is Sending The data that want to store in EEPROM */
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	/* TWI send a start bit */
	TWI_start();

	/* Check the action that make the flag is enabled is Sending a start bit*/
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	/* Sending the address device of EEPROM 1010 is Fixed and first three bit is last three bits in 11-bit
	 * of the location that want to write a value on it in the EEPROM
	 * and specify R/W, In this case Write */
	TWI_writebyte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));

	/* Check the action that make the flag is enabled is Sending device address with R/W bit*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	    return ERROR;

	/* Send the rest of Address that want to write on it in the EEPROM */
	TWI_writebyte((uint8)(u16addr));

	/* Check the action that make the flag is enabled is Sending device address of location in memory*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the Repeated Start bit */
	TWI_start();

	/* Check the action that make the flag is enabled is Sending repeated start bit */
	if(TWI_getStatus() != TWI_REP_START)
	    return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
	TWI_writebyte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));

	/* Check the action that make the flag is enabled is reading acknowledge */
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
        TWI_stop();
    return SUCCESS;
}







