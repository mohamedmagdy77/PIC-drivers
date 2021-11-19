/* 
 * File:   i2c_slave.h
 * Author: futurecomp
 *
 * Created on 18 ?????, 2019, 09:33 ?
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "sys.h"

//slave mode
void i2c_init_slave(unsigned char address);
#define data_sended 0xff

volatile char data_buffer;

#endif