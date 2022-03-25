/*
 * Author: Maureen Mcshane & Jordyn Brosemer
 * The following program contains functions for the UART initialization and
 * write and read functionality
 * Created on September 20, 2018, 2:39 PM
 */
#include <p32xxxx.h>
#include <inttypes.h>
#include “uart.h”
#include <stdio.h>
uint16_t URXEN = 0x1;
uint16_t UTXEN = 0x1;
uint8_t i;
uint8_t j;
char str[80];
uint8_t buffer[64];
//initialize uart
void uart_init(){
	TRISA = 0xff;
	ANSELA &= ~0x5;
	TRISB = 0x07ff;
	ANSELB = 0x000C;
	U1RXR = 0x0000;
	RPA0R = 0x0001;
	U1BRG = 260;
	U1STA = U1STA | 0x1000;
	U1STA = U1STA | 0x400;
	U1MODE = U1MODE | 0x8000;
}
//blocking write to uart
void uart_write(char x){
	while(U1STA&0x200) { }
	U1TXREG = x;
}
//blocking read from uart
char uart_read(){
	while(!(U1STA&0x1)) { }
	return U1RXREG;
}
//function returns true if it is ready to write
uint8_t uart_write_ready(){
	if(U1STA&0x200)
		return 0;
	else
		return 1;
}
//function returns true if uart is available to read
uint8_t uart_read_ready(){
	if(U1STA&0x1)
		return 1;
	else
		return 0;
}
//function converts an array of char (string) to individual char
void char_to_string(char *x){
	for(j=0;x[j]; j++){
		uart_write(x[j]);
	}
}

void uart_read_string(char *str){
	for(i=0; ; i++){
		str[i] = uart_read();
		uart_write(str[i]);
		if(str[i] == 13){
			break;
		}
	}
	char_to_string(“\n”);
	str[i] = 0;
}
//non-blocking write to uart
void uart_write_nb(char x){
	if(uart_write_ready())
		U1TXREG = x;
}
//non-blocking read from uart
char uart_read_nb(){
	if(uart_read_ready())
		return U1RXREG;
	else
		return 0;
}

