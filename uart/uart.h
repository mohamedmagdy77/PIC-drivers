/* 
 * File:   uart.h
 * Author: futurecomp
 *
 * Created on 07 ?????, 2019, 10:56 ?
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#ifndef UART_H
#define UART_H


#include "sys.h"
#include <pic18f4550.h>

#define FREQ 8000000

#define TRUE 1
#define FALSE 0
#define SEND_STR_API TRUE

void uart_init(unsigned int rate);
void uart_send_char(char out);
unsigned char send_idle(void);
void uart_send_string(char *out);
unsigned char recieve_idle(void);
char uart_recieve_char(void);
void MSdelay(unsigned int val);

#endif