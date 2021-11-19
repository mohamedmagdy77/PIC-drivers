/* 
 * File:   eeprom.c
 * Author: futurecomp
 *
 * Created on 08 ?????, 2019, 09:30 ?
 */
#include <pic18f4550.h>
#include "eeprom.h"




//----------------------------------------------------------------------------
char _eeprom_read(int address){
    EEADR = address;        //put address
    EECON1 = 0x01;          //Initiates an EEPROM read
    return EEDATA;          //return data on address
}
//-----------------------------------------------------------------------------
void _eeprom_write(int address , char write){
    INTCON &= ~(1<<7);      //disables all interrupts
    EEADR = address;        //put address
    EEDATA = write;         //put data
    EECON1 &= ~(1<<7);      //Access data EEPROM memory
    EECON1 &= ~(1<<6);      //Access Flash program or data EEPROM memory
    EECON1 |= (1<<2);       //Allows write cycles to Flash program/data EEPROM
    
    //sequence must be done
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1 |= (1<<1);       //cannot be set unless 2_bit is set first
    EECON1 |= (1<<2);
    
    //wait till data write complete
    while((PIR2&(1<<4))==0){}
    PIR2 &= ~(1<<4);
}
//-----------------------------------------------------------------------------
void _eeprom_write_string(int address , char *write){
    unsigned char i=0;
    while(write[i] != '\0'){
        _eeprom_write(address,write[i]);
        address++;
        i++;
    }
}
