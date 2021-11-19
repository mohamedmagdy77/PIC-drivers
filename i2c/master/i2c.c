/* 
 * File:   i2c.c
 * Author: mohamed
 *
 * Created on 16 ?????, 2019, 10:44 ?
 */

#include "i2c.h"
#include <pic18f4550.h>


//---------------------------------------------------------------------------
void i2c_init_master(unsigned long int rate){
    TRISB |= (1<<0);
    TRISB |= (1<<1);
    SSPSTAT |= (1<<7);      //Slew rate control disabled for Standard Speed mode (100 kHz and 1 MHz)
    SSPSTAT &= ~(1<<6);     //Disable SMBus specific inputs
    SSPCON1 = 0x28;         //I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))(2)
                            //No collision & No overflow & Enables the serial port and configures the SDA and SCL
    SSPCON2 = 0x00;         //Acknowledge was not received from slave
                            //Enables Receive mode for I2C
    SSPADD = (8000000)/(rate*4)-1;
    PIE1 |= (1<<3);         //enable interrupt
    PIR1 &= ~(1<<3);        //mssp flag
}
//----------------------------------------------------------------------------
void mssp_idle(void){
    while((PIR1&(1<<3)) != 8){}
    PIR1 &= ~(1<<3);
}
//--------------------------------------------------------------------------
void i2c_idle(void){
     while (( SSPCON2 & 0x1F ) || ( SSPSTAT & 0x04 )){} //no operations happening
}
//-----------------------------------------------------------------------------
void i2c_start(void){
    i2c_idle();
    SSPCON2 |= (1<<0);      //start bit
    mssp_idle();            //wait tell sending
}
//------------------------------------------------------------------------
void i2c_send(unsigned char write){
    L1:
    SSPBUF = write;
    mssp_idle();
    if((SSPCON2&(1<<6))==64){
        i2c_repeated_start();
        goto L1;
    }
}
//-----------------------------------------------------------------------------
void i2c_stop(void){
    SSPCON2 |= (1<<2);      //stop bit
    mssp_idle();            //wait tell sending
}
//---------------------------------------------------------------------------
void i2c_repeated_start(void){
    SSPCON2 |= (1<<1);      //start bit
    mssp_idle();            //wait tell sending
}
//---------------------------------------------------------------------------
unsigned char i2c_recieve(char _compare){
    SSPCON2 |= (1<<3);           //enable receive mode
    while((SSPSTAT&(1<<0))==0){}  //wait tell SSPBUF is full of data
    SSPCON2 &= ~(1<<3);         //disable receive mode
    if(_compare==0){
        i2c_akn();
    }
    else{
        i2c_nakn();
    }
    return SSPBUF;
}
//--------------------------------------------------------------------------
void i2c_akn(void){
    SSPCON2 |= (1<<4);      //enable akn & nakn
    SSPCON2 &= ~(1<<5);     //send akn
    mssp_idle();            //wait tell sending
}
//--------------------------------------------------------------------------
void i2c_nakn(void){
    SSPCON2 |= (1<<4);      //enable akn & nakn
    SSPCON2 |= (1<<5);     //send nakn
    mssp_idle();           //wait tell sending
}