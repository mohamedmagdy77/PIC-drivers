/* 
 * File:   lcd_45.h
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 03:15 ?
 */

#ifndef LCD_45_H
#define LCD_45_H

#include "sys.h"

#define DATA LATD
#define DIR TRISD
#define EN LD5
#define RS LD4

void send_cmd(unsigned char cmd);
void _init_lcd(void);
void send_chr(unsigned char chr);
void MSdelay(unsigned int val);
void send_string(unsigned char row,unsigned char col,char *string);

#endif