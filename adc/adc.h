/* 
 * File:   adc.h
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 01:50 ?
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#ifndef ADC_H
#define ADC_H

#include "sys.h"

void adc_init(void);
int adc_read(int adc);

#endif 
