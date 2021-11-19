/* 
 * File:   adc.c
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 01:51 ?
 */


#include <pic18f4550.h>
#include "adc.h"


//-------------------------------------------------------------------------
void adc_init(void){
    TRISA = 0xFF;       //as input
    ADCON1 = 0x0E;      //VSS & VDD & AN0
    ADCON2 = 0x92;      //Right justified & 4 TAD & FOSC/32
    ADRESH=0;  			/*Flush ADC output Register*/
    ADRESL=0;
}
//-----------------------------------------------------------------------------
int adc_read(int adc){
    int digital;
    ADCON0 = (ADCON0 & (0b11000011)) | (adc<<2);
    ADCON0 |= (1<<0);      //A/D converter module is enabled
    ADCON0 |= (1<<1);      //start conversion

    while((ADCON0&(1<<1))==2){}
    digital = (ADRESH<<8) + ADRESL;
    return (digital);
}