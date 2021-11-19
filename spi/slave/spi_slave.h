/* 
 * File:   spi.h
 * Author: futurecomp
 *
 * Created on 21 ?????, 2019, 09:57 ?
 */

#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include "sys.h"

#define IDLE_ACTIVE 0
#define ACTIVE_IDLE 1
#define SAMPLE_MIDDLE 0
#define SAMPLE_END 1
#define POL_HIGH 1
#define POL_LOW 0
#define SLAVE_SS_DISABLED 5
#define SLAVE_SS_ENABLED 4
#define MASTER_TMR 3
#define MASTER_FOSC_64 2
#define MASTER_FOSC_16 1
#define MASTER_FOSC_4 0


void spi_init(char mode,char sample,char select,char pol);
void spi_send(char sending);
char spi_recieve(void);

#endif