/* 
 * File:   eeprom.h
 * Author: futurecomp
 *
 * Created on 08 ?????, 2019, 09:30 ?
 */
#ifndef EEPROM_H
#define EEPROM_H

#include "sys.h"

char _eeprom_read(int address);
void _eeprom_write(int address , char write);
void _eeprom_write_string(int address , char *write);

#define FREQ 8000000

#endif