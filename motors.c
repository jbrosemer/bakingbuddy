#include <p32xxxx.h>
#include <inttypes.h>
#include “uart.h”
#include <stdio.h>

int i;
int ref3 = 10000;
int fast_wheel = 300000; //fast spinning
int slow_wheel = 400000; //slow spinning
int duration; //how long wheel spins

void pulse(port){ //functionality for pulse width modulation of motors
	if(port == 0x01 || port == 0x04)
		duration = fast_wheel;
	else
		duration = slow_wheel;
	for(i = 0; i<duration; i++){
		if (i>ref3){
			PORTB = port;
		}
		else
			PORTB = 0;
	}
	for(i = 0; i>=0; i–){
		if(ref3<i){
			PORTB = port;
		}
		else
			PORTB = 0;
	}
}
