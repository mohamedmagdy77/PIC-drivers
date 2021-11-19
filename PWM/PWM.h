/* 
 * File:   pwm.h
 * Author: futurecomp
 *
 * Created on 23 ?????, 2019, 04:12 ?
 */

#ifndef PWM_H
#define PWM_H

#include "sys.h"

#define FREQ 8000000
#define TMR2_PRE 1
#define STOP_PWM_API FALSE

void pwm_init(unsigned long pwm_freq,unsigned int duty);
void start_pwm(void);
void stop_pwm(void);

#endif
