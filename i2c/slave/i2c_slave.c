/* 
 * File:   i2c_slave.c
 * Author: futurecomp
 *
 * Created on 18 ?????, 2019, 09:31 ?
 */


#include "i2c_slave.h"
#include <pic18f4550.h>



//slave-----------------------------------------------------------------------
void i2c_init_slave(unsigned char address){
    TRISB |= (1<<0);
    TRISB |= (1<<1);
    SSPSTAT |= (1<<7);      //Slew rate control disabled for Standard Speed mode (100 kHz and 1 MHz)
    SSPSTAT &= ~(1<<6);     //Disable SMBus specific inputs
    SSPCON1 = 0x36;         //Release clock & I2C Slave mode, 7-bit address(2)
                     //No collision & No overflow & Enables the serial port and configures the SDA and SCL
    SSPCON2 &= ~(1<<7);      //General call address disabled
    SSPCON2 |= (1<<0);      //Clock stretching is enabled
     
    SSPADD = address;
    PIE1 |= (1<<3);          //enable interrupt
    PIR1 &= ~(1<<3);         //mssp flag cleared
    INTCON |=(1<<7);          //enable general interrupt
    INTCON |=(1<<6);          //enable peripheral interrupt
}
//------------------------------------------------------------------------------
void __interrupt() ISR(void){
    if((PIR1&(1<<3)) == 8){
        SSPCON1 &= ~(1<<4);         //hold clock
        if((SSPCON1&(1<<7)) || (SSPCON1&(1<<6))){
            data_buffer = SSPBUF;
            SSPCON1 &= ~(1<<7);
            SSPCON1 &= ~(1<<6);
            SSPCON1 |= (1<<4);      //release clock
        }
        if((SSPSTAT&(1<<5))==0 && (SSPSTAT&(1<<2))==0){//writing to slave
            data_buffer = SSPBUF;
            while((SSPSTAT&(1<<0))==0){}
            data_buffer = SSPBUF;
            LATD = data_buffer;
            SSPCON1 |= (1<<4);      //release clock
        }
        else if((SSPSTAT&(1<<5))==0 && (SSPSTAT&(1<<2))==4){//reading from slave
            data_buffer = SSPBUF;
            SSPBUF = data_sended;
            SSPCON1 |= (1<<4);      //release clock
            while((SSPSTAT&(1<<0))==1){}
        }
        PIR1 &= ~(1<<3);
    }
}