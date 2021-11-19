/* 
 * File:   spi_slave.c
 * Author: futurecomp
 *
 * Created on 22 ?????, 2019, 12:12 ?
 */
#include "spi_slave.h"
#include <pic18f4550.h>


//---------------------------------------------------------------------------
void spi_init(char mode,char sample,char select,char pol){
    if(mode==5 || mode==4){     //slave
        TRISC &= ~(1<<7);       //SDO output
        TRISB |= (1<<1);        //SK INPUT
        TRISA |= (1<<5);        //SS INPUT
    }
    else{                       //master
        TRISC &= ~(1<<7);       //SDO output
        TRISB &= ~(1<<1);       //SK output
    }
    SSPCON1 = (SSPCON1 & 0xF0) | (mode & 0x0F);  //mode
    if(sample==0){
        SMP = 0;
    }
    else if(sample==1){
        SMP = 1;
    }
    if(select==0){
        CKE = 0;
    }
    else if(select==1){
        CKE = 1;
    }
    if(pol==0){
        CKP = 0;
    }
    else if(pol==1){
        CKP = 1;
    }
    SSPCON1 |= (1<<5);  //Enables serial port and configures SCK, SDO, SDI and SS
    SSPCON1 &= ~(1<<7);
    SSPCON1 &= ~(1<<6);
    SSPIF = 0;
}
//---------------------------------------------------------------------------
void spi_send(char sending){
    SSPBUF = sending;
    while(SSPIF == 0){}
    SSPIF = 0;
}
//-----------------------------------------------------------------
char spi_recieve(void){
    while(SSPIF == 0){}
    SSPIF = 0;
    return (SSPBUF);
}

