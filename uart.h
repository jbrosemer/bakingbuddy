/*
* File: uart.h
* Author: mcshanem & brosemerj 
*
* Created on September 20, 2018, 2:39 PM
*/
#include <inttypes.h>
#ifndef UART_H
#define UART_H

void uart_init();
void uart_write(char x);
char uart_read();
uint8_t uart_write_ready();
uint8_t uart_read_ready();
void uart_write_nb(char x);
char uart_read_nb();
void char_to_string(char *x);

#endif /* UART_H */