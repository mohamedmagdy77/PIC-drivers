/* 
 * File:   i2c.h
 * Author: futurecomp
 *
 * Created on 16 ?????, 2019, 10:44 ?
 */

#ifndef I2C_H
#define I2C_H

#include "sys.h"

void i2c_init_master(unsigned long int rate);
void i2c_start(void);
void i2c_send(unsigned char write);
void i2c_stop(void);
void i2c_repeated_start(void);
void mssp_idle(void);
void i2c_idle(void);
unsigned char i2c_recieve(char _compare);
void i2c_akn(void);
void i2c_nakn(void);

char _data=0;

#endif