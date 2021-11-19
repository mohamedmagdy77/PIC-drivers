/* 
 * File:   uart.c
 * Author: futurecomp
 *
 * Created on 07 ?????, 2019, 10:56 ?
 */


#include "uart.h"

//--------------------------------------------------------------
void uart_init(unsigned int rate){
    TRISC &= ~(1<<6);   //tx output
    TRISC |= (1<<7);    //rx input
    BAUDCON = 0;
    SPBRG = (int)((float)(FREQ/64)/(float)(rate)-1);
    TXSTA = 0x20;        //Selects 8-bit transmission & Transmit disabled & Asynchronous mode
    //Low speed & Sync Break transmission completed
    RCSTA = 0x90;       //Serial port enabled & Enables receiver & No framing error
    
    
}
//-----------------------------------------------------------------------
void uart_send_char(char out){
    TXREG = out;
    MSdelay(5);
}
//----------------------------------------------------------------------
unsigned char send_idle(void){
    unsigned char temp = ((PIR1&(1<<4))>>4); 
    return temp;
}
//-------------------------------------------------------------
unsigned char recieve_idle(void){
    unsigned char temp = ((PIR1&(1<<5))>>5); 
    return temp;
}
//------------------------------------------------------------------
#if(SEND_STR_API == TRUE)
void uart_send_string(char *out){
    unsigned int i=0;
    while(out[i] != '\0'){
        while(send_idle()==0){}
        uart_send_char(out[i]);
        i++;
    }
}
#endif
//---------------------------------------------------
char uart_recieve_char(void){
    if((RCSTA&(1<<1))==2){
        RCSTA &= ~(1<<4);
        NOP();
        RCSTA |= (1<<4);
    }
    while(recieve_idle()==0){}
    return RCREG;
}
//-----------------------------------------------------------
void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);  /*This count Provide delay of 1 ms for 8MHz Frequency */
 }