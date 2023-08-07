/*
 * I2C_slave_EEPROM.h
 *
 *  Created on: Jul 10, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_

#include "STM32F103C6_DRIVER_I2C.h"
#include "STM32F103C6_DRIVER_GPIO.h"

// E2PROM is an i2C SLAVE
// Idle Mode: device is in high-impedance state and waits for data.
// Master Transmitter Mode: the device transmits data to a slave receiver.
// Master Receiver Mode: the device receives data from a slave transmitter.

#define EEPROM_Slave_address	0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes,uint8_t Data_Length);
unsigned char eeprom_read_byte(unsigned int address , uint8_t* dataOut, uint8_t dataLen);




#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
