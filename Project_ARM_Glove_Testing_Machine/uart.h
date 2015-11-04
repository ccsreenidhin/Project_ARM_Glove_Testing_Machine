/* 
 * File:   uart.h
 * Author: ccsn
 *
 * Created on December 12, 2015, 10:45 AM
 */

#ifndef UART_H
#define	UART_H

void uartinit(void);
void uarttx(unsigned char *);
char uartrx(void);
void uarttxch(unsigned char);

#endif	/* UART_H */

