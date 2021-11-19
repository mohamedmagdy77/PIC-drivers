/* 
 * File:   pwm.c
 * Author: futurecomp
 *
 * Created on 23 ?????, 2019, 04:13 ?
 */


#include "PWM.h"
#include <pic18f4550.h>



//-------------------------------------------------------
void pwm_init(unsigned long pwm_freq,unsigned int duty){
    TRISC &= ~(1<<2);       //ccp1 as output
    //frequency of pwm
    PR2 = ((FREQ/(4*pwm_freq*TMR2_PRE))-1);
    //no pre scaler
    T2CON &= ~(1<<1);   
    T2CON &= ~(1<<0);
    //duty cycle
    unsigned int _duty;
    _duty = ((float)duty/1023)*(FREQ/(pwm_freq*TMR2_PRE));
    CCP1CON = (CCP1CON & 0xCF) | ((_duty & 0x03)<<4);
    CCPR1L = (_duty>>2);
}
//---------------------------------------------------------------
void start_pwm(void){
    TMR2 = 0;
    CCP1CON = 0x0C;     //PWM mode: P1A, P1C active-HIGH; P1B, P1D active-HIGH
     //Single output: P1A modulated; P1B, P1C, P1D assigned as port pins
    T2CON |= (1<<2);    //tmr2 on
}
//-----------------------------------------------------------
#if(STOP_PWM_API == TRUE)
void stop_pwm(void){
    CCP1CON &= ~(0x0F);
    T2CON &= ~(1<<2);    //tmr2 off
}
#endif