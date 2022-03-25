#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF, FSOSCEN = OFF, JTAGEN = OFF
#define _SUPPRESS_PLIB_WARNING 1

#include <xc.h>
#include “tft_master.h”
#include “tft_gfx.h”
#include “uart.h”
#include <stdlib.h>
#include <inttypes.h>
#include <p32xxxx.h>
#include “analog_in.h”
#include “motors.h”
#include “command.h”
#include “scale.h”

void main(){
	uart_init();
	analog_in_init(); //initialize functions
	TRISB = 0;
	command(); //uart module command
}

